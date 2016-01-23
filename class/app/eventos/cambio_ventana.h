#ifndef EVENTO_CAMBIO_VENTANA_H
#define EVENTO_CAMBIO_VENTANA_H

#include "definiciones.h"
#include "../../framework/eventos.h"

namespace App
{

namespace Eventos
{

struct Evento_cambio_ventana:
	public DFramework::Evento_framework_interface
{
	virtual int		tipo_evento() const {return cambio_ventana;}
	int			w, h;
	Evento_cambio_ventana(int w, int h):w(w), h(h) {}
};
	

} //Fin namespace eventos.
} //Fin namespace app.

#endif
