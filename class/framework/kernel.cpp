#include "kernel.h"
#include <cstdlib>

using namespace DFramework;

Kernel::Kernel(Herramientas_proyecto::Controlador_argumentos& carg, Kernel_driver_interface& kdi, Configuracion_base& config)
	:paso_delta(0.01), controlador_argumentos(carg), 
	controlador_fps(), pantalla()
{
	inicializar(kdi, config);
}

void Kernel::inicializar(const Kernel_driver_interface& kdi, const Configuracion_base& config)
{
	inicializar_entorno_grafico(kdi.obtener_info_ventana());
	inicializar_entorno_audio(config);

	//Inicializar recursos.
	Cargador_recursos cargador_recursos;
	cargador_recursos.generar_recursos_texturas(kdi.obtener_entradas_texturas(), pantalla);
	cargador_recursos.generar_recursos_superficies(kdi.obtener_entradas_superficies(), pantalla);
	cargador_recursos.generar_recursos_audio(kdi.obtener_entradas_audio());
	cargador_recursos.generar_recursos_musica(kdi.obtener_entradas_musica());
	
	//Inicializar controles.
	input.configurar(kdi.obtener_pares_input()); 

	//Inicialización controlador tiempo.
	controlador_fps.inicializar();
}

void Kernel::inicializar_entorno_grafico(const Info_ventana& iv)
{
	pantalla.inicializar(iv.w_fisica, iv.h_fisica);
	pantalla.establecer_medidas_logicas(iv.w_logica, iv.h_logica);
	pantalla.establecer_modo_ventana(DLibV::Pantalla::M_VENTANA);
	pantalla.establecer_titulo(iv.nombre.c_str());
	DLibV::Utilidades_graficas_SDL::mostrar_ocultar_cursor(iv.mostrar_cursor);
}

void Kernel::ciclar_modo_pantalla()
{
	unsigned int modo=pantalla.acc_modo_ventana();
	++modo;

	if(modo == DLibV::Pantalla::M_MAX_MODO)
	{
		modo=DLibV::Pantalla::M_VENTANA;
	}

	pantalla.establecer_modo_ventana(modo);
}


void Kernel::inicializar_entorno_audio(const Configuracion_base& config)
{
	Audio::inicializar_entorno_audio(
		config.acc_audio_ratio(), 
		config.acc_audio_salidas(),
		config.acc_audio_buffers(),
		config.acc_audio_canales());

	Audio::establecer_volumen(config.acc_volumen_audio());
	Audio::establecer_volumen_musica(config.acc_volumen_musica());
}
