#ifndef EVENTO_CAMBIO_IDIOMA_H
#define EVENTO_CAMBIO_IDIOMA_H

#include "definiciones.h"
#include "../../framework/eventos.h"

namespace App
{

namespace Eventos
{

struct Evento_cambio_idioma:
	public Evento_director_estados_base
{
	virtual int		tipo_evento() const {return cambio_idioma;}
	int			id_idioma;
	Evento_cambio_idioma(int i):id_idioma(i) {}
};
	

} //Fin namespace eventos.
} //Fin namespace app.

#endif
