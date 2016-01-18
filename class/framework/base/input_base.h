#ifndef PROYECTO_SDL2_BASE_INPUT_H
#define PROYECTO_SDL2_BASE_INPUT_H

#include <map>
#include <vector>
#include <input/controles_sdl/controles_sdl.h>

/*Abstrae los sistemas de input usando la clase Controles_SDL. Cada input del
enum de turno se puede asignar a uno o más valores SDLK_xxx, según lo mismo
pueda hacerse con varias teclas, joystick o no. Esta clase es la propietaria
de la instancia de controles_SDL.

//TODO TODO TODO: Ahora mismo no hay soporte de Joystick ni de ratón!!!.
*/

class Input_base
{
	////////////////////////
	//Definiciones....

	public:

	typedef DLibI::Controles_SDL::Posicion_raton Posicion_raton;
	typedef std::multimap<unsigned int, unsigned int> tipo_mapa;
	typedef std::multimap<unsigned int, unsigned int>::const_iterator tipo_iterador;

	private:

	struct Resultado_lookup
	{
		enum t_mapa {NADA=0, TECLADO=1, RATON=2};
		unsigned int mapa;
		std::vector<unsigned int> val;
		Resultado_lookup(unsigned int tm):mapa(tm) {}
	};

	////////////////////////
	//Propiedades. --

	private:
	DLibI::Controles_SDL controles_sdl;

	protected:
	mutable std::map<unsigned int, Resultado_lookup> lookup;
	tipo_mapa mapa_teclado;
	tipo_mapa mapa_raton;

	void configurar_teclado(int, int);
	void configurar_raton(int, int);

	////////////////////////
	//Métodos

	private:

	Resultado_lookup obtener(unsigned int) const;

	public:

	//Este es el método que tendremos que extender.
	virtual void configurar()=0;

	/* Todas estas vamos a imaginar que son finales, ok?... */

	void turno(); 

	bool es_senal_salida() const;
	bool es_input_down(unsigned int) const;
	bool es_input_up(unsigned int) const;
	bool es_input_pulsado(unsigned int) const;

	bool es_tecla_down(unsigned int i) const {return controles_sdl.es_tecla_down(i);}
	bool es_tecla_up(unsigned int i) const {return controles_sdl.es_tecla_up(i);}	
	bool es_tecla_pulsada(unsigned int i) const {return controles_sdl.es_tecla_pulsada(i);}
	bool hay_eventos_teclado_down() const {return controles_sdl.recibe_eventos_teclado_down();}

	bool es_boton_up(int p_boton) const {return controles_sdl.es_boton_up(p_boton);}
	bool es_boton_down(int p_boton) const {return controles_sdl.es_boton_down(p_boton);}
	bool es_boton_pulsado(int p_boton) const {return controles_sdl.es_boton_pulsado(p_boton);}

//	const DLibI::Controles_SDL::Posicion_raton& acc_posicion_raton() const {return controles_sdl.acc_raton().posicion;}
	Posicion_raton acc_posicion_raton() const {return controles_sdl.obtener_posicion_raton();}

	DLibI::Controles_SDL& acc_controles_sdl() {return controles_sdl;}

	Input_base() {}
};

#endif
