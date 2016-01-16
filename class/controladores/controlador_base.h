#ifndef CONTROLADOR_BASE
#define CONTROLADOR_BASE

#include "../framework/interface_controlador.h"
#include "director_estados.h"

class Controlador_base:public Interface_controlador
{
	private:

	Director_estados& DI;

	bool abandonar;
	bool romper;

	public:

	void solicitar_cambio_estado(Director_estados::t_estados v) {DI.solicitar_cambio_estado(v);}

	bool es_abandonar_aplicacion() const {return abandonar;}
	bool es_romper_loop() const {return romper;}

	void abandonar_aplicacion() {abandonar=true;}
	void romper_loop() {romper=true;}

	Controlador_base(Director_estados &d): DI(d), abandonar(false), romper(false)
	{}
};

#endif
