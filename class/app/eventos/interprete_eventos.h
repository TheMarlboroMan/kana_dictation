#ifndef INTERPRETE_EVENTOS_H
#define INTERPRETE_EVENTOS_H

#include "definiciones.h"
#include "../../framework/eventos.h"
#include "../../framework/derivada/configuracion.h"
#include <video/pantalla/pantalla.h>

#include "cambio_fondo.h"
#include "cambio_idioma.h"
#include "cambio_kanas.h"
#include "cambio_ventana.h"
#include "cambio_longitud.h"
#include "cambio_grupos.h"

namespace App
{
namespace Eventos
{

class Interprete_eventos:
	public Interface_interprete_eventos
{
	public:

	Interprete_eventos(DLibV::Pantalla& pantalla, Configuracion& config);
	virtual void		interpretar_evento(const Evento_director_estados_base&);

	private:

	DLibV::Pantalla&	pantalla;
	Configuracion&		config;

	void			interpretar_evento(const Evento_cambio_fondo&);
	void			interpretar_evento(const Evento_cambio_idioma&);
	void			interpretar_evento(const Evento_cambio_kanas&);
	void			interpretar_evento(const Evento_cambio_longitud&);
	void			interpretar_evento(const Evento_cambio_ventana&);
	void			interpretar_evento(const Evento_cambio_grupos&);
};


}//Fin namespace eventos.
}//Fin namespace app

#endif
