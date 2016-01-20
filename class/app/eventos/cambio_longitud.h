#ifndef EVENTO_CAMBIO_LONGITUD_H
#define EVENTO_CAMBIO_LONGITUD_H

#include "definiciones.h"
#include "../../framework/eventos.h"

namespace App
{

namespace Eventos
{

struct Evento_cambio_longitud:
	public Evento_director_estados_base
{
	virtual int		tipo_evento() const {return cambio_longitud;}
	int			longitud;
	Evento_cambio_longitud(int l):longitud(l) {}
};
	

} //Fin namespace eventos.
} //Fin namespace app.

#endif
