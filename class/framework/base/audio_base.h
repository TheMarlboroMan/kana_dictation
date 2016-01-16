#ifndef PROYECTO_SDL2_BASE_CONTROLADOR_AUDIO_H
#define PROYECTO_SDL2_BASE_CONTROLADOR_AUDIO_H

/*Clase proxy con el controlador de audio. Añadimos alguna utilidad para el 
tema de pausar y despausar sonidos.*/

#include <libDan2.h>

struct Excepcion_audio
{
	std::string mensaje;

	Excepcion_audio(std::string p_m)
		:mensaje(p_m) {}

	Excepcion_audio(const Excepcion_audio& e)
		:mensaje(e.mensaje) {}

	Excepcion_audio& operator=(const Excepcion_audio& e)
	{
		mensaje=e.mensaje;
		return *this;
	}
};

class Audio_base
{
	private:

	Audio_base();

	static DLibA::Controlador_audio_SDL * controlador_audio;
	static DLibA::Cola_sonido cola_sonido;
	static std::vector<unsigned int> canales_detenidos;

	public:

	static void pausar();
	static void pausar_canales_activos();

	static void despausar();
	static void despausar_excepto_activos();
	static void despausar_canales_activos();

	static void debug_estado_canales() {if(controlador_audio) controlador_audio->debug_estado_canales();}
	static void insertar_sonido(DLibA::Estructura_sonido es) {cola_sonido.insertar(es);}
	static void reproducir_musica(DLibA::Musica * m) {controlador_audio->reproducir_musica(*m);}
	static void procesar_cola_sonido() {cola_sonido.procesar_cola();}
	static DLibA::Canal_audio obtener_canal_libre();
	static bool inicializar_entorno_audio(int pratio, int psalidas, int pbuffers, int pcanales);
	static void establecer_volumen(int v) {if(controlador_audio) controlador_audio->establecer_volumen(v);}
	static void establecer_volumen_musica(int v) {if(controlador_audio) controlador_audio->establecer_volumen_musica(v);}
	static int acc_volumen_general_sonido()
	{
		if(controlador_audio) return controlador_audio->acc_volumen_general_sonido();
		else return -1;
	}
};

#endif
