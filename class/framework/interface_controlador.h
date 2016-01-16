#ifndef INTERFACE_CONTROLADOR_H
#define INTERFACE_CONTROLADOR_H

#include "derivada/input.h"
//#include <libDan2.h>
#include "derivada/audio.h"

//#include <string>
//#include <sstream>

class Interface_controlador
{
	private:

	std::string debug;
		
	public:

	Interface_controlador() {}
	virtual ~Interface_controlador() {}

	void mut_debug(const std::string& c) {debug=c;}
	const std::string& acc_debug() const {return debug;}

	virtual void preloop(Input_base& input, float delta)=0;
	virtual void loop(Input_base& input, float delta)=0;
	virtual void postloop(Input_base& input, float delta)=0;
	virtual void dibujar(DLibV::Pantalla& pantalla)=0;
	virtual bool es_abandonar_aplicacion() const=0;
	virtual bool es_romper_loop() const=0;
};


#endif
