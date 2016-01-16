#include "kernel.h"

Kernel_app::Kernel_app(Herramientas_proyecto::Controlador_argumentos& CARG)
try
:Kernel_base(CARG) 
{

}
catch(Configuracion_base_no_fichero_exception& e)
{
	std::string error="Imposible inicializar configuracion : ";
	error+=e.what();
	throw Kernel_exception(error);
}
