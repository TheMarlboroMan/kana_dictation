#ifndef FW_CONTROLADOR_INTERFACE_H
#define FW_CONTROLADOR_INTERFACE_H

#include "eventos.h"
#include "estados.h"
#include "input.h"
#include <video/pantalla/pantalla.h>

/**
* Interface para un controlador. Los controladores deben ser registrados en
* el director de estados para que los cambios de estado sean posibles y 
* pueda inyectarse la cola de eventos.
*/

namespace DFramework
{

class Controlador_interface
{
	public:

	Controlador_interface()
		:cola_eventos(nullptr), estados(nullptr), abandonar(false), romper(false) 
	{}

	virtual ~Controlador_interface() 
	{}

	void 				mut_debug(const std::string& c) {debug=c;}
	const std::string& 		acc_debug() const {return debug;}

	bool 				es_abandonar_aplicacion() const {return abandonar;}
	bool 				es_romper_loop() const {return romper;}

	void 				abandonar_aplicacion() {abandonar=true;}
	void 				romper_loop() {romper=true;}

	void				inyectar_cola_eventos(Cola_eventos& c) {cola_eventos=&c;}
	void				inyectar_control_estados(Control_estados& c) {estados=&c;}

	void				encolar_evento(Evento_framework_interface * ev) {cola_eventos->encolar_evento(ev);}

	//TODO: Esto es terrible. 
	void				solicitar_cambio_estado(int v) {estados->validar_y_cambiar_estado(v);}

	virtual void 			preloop(Input& input, float delta)=0;
	virtual void 			loop(Input& input, float delta)=0;
	virtual void 			postloop(Input& input, float delta)=0;
	virtual void 			dibujar(DLibV::Pantalla& pantalla)=0;
	virtual void 			despertar()=0;
	virtual void 			dormir()=0;
	virtual bool			es_posible_abandonar_estado() const=0;

	private:

	Cola_eventos *			cola_eventos;
	Control_estados *		estados;
	std::string 			debug;
	bool 				abandonar,
					romper;
};

}
#endif
