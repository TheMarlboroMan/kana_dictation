#ifndef EVENTO_CAMBIO_GRUPOS_H
#define EVENTO_CAMBIO_GRUPOS_H

#include <string>
#include "definiciones.h"
#include "../../framework/eventos.h"

namespace App
{

namespace Eventos
{

struct Evento_cambio_grupos:
	public Evento_director_estados_base
{
	virtual int		tipo_evento() const {return cambio_grupos;}

	std::string		grupos;

	Evento_cambio_grupos(const std::string& r): grupos(r) {}
};
	

} //Fin namespace eventos.
} //Fin namespace app.

#endif
