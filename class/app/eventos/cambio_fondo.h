#ifndef EVENTO_CAMBIO_FONDO_H
#define EVENTO_CAMBIO_FONDO_H

#include <string>
#include "definiciones.h"
#include "../../framework/eventos.h"

namespace App
{

namespace Eventos
{

struct Evento_cambio_fondo:
	public Evento_director_estados_base
{
	virtual int		tipo_evento() const {return cambio_fondo;}

	std::string		ruta_fondo;

	Evento_cambio_fondo(const std::string& r): ruta_fondo(r) {}
};
	

} //Fin namespace eventos.
} //Fin namespace app.

#endif
