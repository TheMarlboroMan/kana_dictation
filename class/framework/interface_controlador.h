#ifndef INTERFACE_CONTROLADOR_H
#define INTERFACE_CONTROLADOR_H

//TODO: Estos dos de la derivada estan mal colocados. Aquí no se usan pero
//se requiren en el kernel_base, que tampoco debería conocer NADA de la derivada.
//Arreglar.

#include "derivada/input.h"
#include "derivada/audio.h"
#include "eventos.h"
#include "estados.h"

class Interface_controlador
{
	public:

	Interface_controlador()
		:cola_eventos(nullptr), estados(nullptr), abandonar(false), romper(false) 
	{}

	virtual ~Interface_controlador() 
	{}

	void 				mut_debug(const std::string& c) {debug=c;}
	const std::string& 		acc_debug() const {return debug;}

	bool 				es_abandonar_aplicacion() const {return abandonar;}
	bool 				es_romper_loop() const {return romper;}

	void 				abandonar_aplicacion() {abandonar=true;}
	void 				romper_loop() {romper=true;}

	void				inyectar_cola_eventos(Cola_eventos& c) {cola_eventos=&c;}
	void				inyectar_control_estados(Control_estados& c) {estados=&c;}

	void				encolar_evento(Evento_director_estados_base * ev) {cola_eventos->encolar_evento(ev);}
	void				solicitar_cambio_estado(int v) {estados->validar_y_cambiar_estado(v);}

	virtual void 			preloop(Input_base& input, float delta)=0;
	virtual void 			loop(Input_base& input, float delta)=0;
	virtual void 			postloop(Input_base& input, float delta)=0;
	virtual void 			dibujar(DLibV::Pantalla& pantalla)=0;
	virtual void 			despertar()=0;
	virtual void 			dormir()=0;

	private:

	Cola_eventos *			cola_eventos;
	Control_estados *		estados;
	std::string 			debug;
	bool 				abandonar,
					romper;
};


#endif
