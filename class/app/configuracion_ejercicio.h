#ifndef CONFIGURACION_EJERCICIO_H
#define CONFIGURACION_EJERCICIO_H

#include "definiciones.h"

namespace App
{

struct Configuracion_ejercicio
{
	public:

	static const size_t	LONGITUD_MAX=20;

	Configuracion_ejercicio(size_t l, tipos_kana k, direcciones_traduccion d)
		:longitud(l), tipo_kana(k), direccion_traduccion(d)
	{}

	size_t			acc_longitud() const {return longitud;}
	tipos_kana		acc_tipo_kana() const {return tipo_kana;}
	direcciones_traduccion	acc_direccion_traduccion() const {return direccion_traduccion;}

	void			mut_longitud(size_t v) 
	{
		longitud=v;
		if(longitud > LONGITUD_MAX) longitud=LONGITUD_MAX;
		else if(longitud < 1) longitud=1;
	}
	void			mut_tipo_kana(tipos_kana v) {tipo_kana=v;}
	void			mut_direccion_traduccion(direcciones_traduccion v) {direccion_traduccion=v;}

	private:

	size_t			longitud;
	tipos_kana 		tipo_kana;
	direcciones_traduccion	direccion_traduccion;

};

}

#endif
