#ifndef EVENTO_CAMBIO_DIRECCION_H
#define EVENTO_CAMBIO_DIRECCION_H

#include "definiciones.h"
#include "../definiciones.h"
#include "../../framework/eventos.h"

namespace App
{

namespace Eventos
{

struct Evento_cambio_direccion:
	public DFramework::Evento_framework_interface
{
	virtual int		tipo_evento() const {return cambio_direccion;}
	App::direcciones_traduccion	direccion;
	Evento_cambio_direccion(App::direcciones_traduccion d):direccion(d) {}
};
	

} //Fin namespace eventos.
} //Fin namespace app.

#endif
