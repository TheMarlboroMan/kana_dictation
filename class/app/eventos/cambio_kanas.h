#ifndef EVENTO_CAMBIO_KANAS_H
#define EVENTO_CAMBIO_KANAS_H

#include "definiciones.h"
#include "../definiciones.h"
#include "../../framework/eventos.h"

namespace App
{

namespace Eventos
{

struct Evento_cambio_kanas:
	public Evento_director_estados_base
{
	virtual int		tipo_evento() const {return cambio_kanas;}
	App::tipos_kana		tipo_kana;
	Evento_cambio_kanas(App::tipos_kana k):tipo_kana(k) {}
};
	

} //Fin namespace eventos.
} //Fin namespace app.

#endif
