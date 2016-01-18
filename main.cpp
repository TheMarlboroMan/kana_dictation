#include <libDan2.h>
#include <defDanSDL.h>
#include "class/framework/derivada/kernel.h"
#include "bootstrap/bootstrap_aplicacion.h"
#include <class/menu_opciones.h>

//Declaración del log del motor en espacio global.
DLibH::Log_base LOG;

int main(int argc, char ** argv)
{
	if(DLibH::Herramientas_SDL::iniciar_SDL(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK))
	{
		//Inicializar control de logs.
		LOG.inicializar("data/logs/info.log");
		LOG.activar();

		DLibH::Log_motor::arrancar("data/logs/log_motor.log");

		//Inicializar control de argumentos.
		Herramientas_proyecto::Controlador_argumentos CARG(argc, argv);

		try
		{
			Kernel_app kernel(CARG);
			kernel.inicializar();

			//Función en el espacio de nombres "App", definida en "include_controladores.h"
			using namespace App;
			loop_aplicacion(kernel);
		}
		catch(std::exception &e)
		{
			std::cout<<"Saliendo: se atraṕo una excepción : "<<e.what()<<std::endl;
		}
	}
	
	DLibH::Log_motor::finalizar();
	DLibH::Herramientas_SDL::apagar_SDL();

	return 0;
}
