#ifndef CONTROLADOR_BASE
#define CONTROLADOR_BASE

#include "../framework/controlador_interface.h"
#include "estados_controladores.h"

namespace App
{

/**
* Base para los controladores de la aplicación. Contendría cosas que pensemos
* que deben ser comunes.
*/

class Controlador_base
	:public DFramework::Controlador_interface
{
	public:

	Controlador_base()
	{}
};

}
#endif
