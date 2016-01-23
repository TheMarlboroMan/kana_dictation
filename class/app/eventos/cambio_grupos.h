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
	public DFramework::Evento_framework_interface
{
	virtual int		tipo_evento() const {return cambio_grupos;}

	std::string		grupos;

	Evento_cambio_grupos(const std::string& r): grupos(r) {}
};
	

} //Fin namespace eventos.
} //Fin namespace app.

#endif
