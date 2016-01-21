#ifndef CONTROLADOR_BASE
#define CONTROLADOR_BASE

#include "../framework/interface_controlador.h"
#include "estados_controladores.h"

/**
* Base para los controladores de la aplicación. Contendría cosas que pensemos
* que deben ser comunes.
*/

class Controlador_base
	:public Interface_controlador
{
	public:

	Controlador_base()
	{}


};

#endif
