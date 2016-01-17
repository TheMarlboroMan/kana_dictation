#ifndef CONTROLADOR_OPCIONES_H
#define CONTROLADOR_OPCIONES_H

#include "controlador_base.h"
#include <vector>
#include <class/compositor_vista.h>
#include <base/localizador_base.h>
#include "../app/definiciones.h"

class Controlador_opciones:public Controlador_base
{
	public:

					Controlador_opciones(Director_estados& d, const DLibV::Fuente_TTF&, const Herramientas_proyecto::Localizador_base&);

	private:

	virtual void 			preloop(Input_base& input, float delta) {}
	virtual void 			postloop(Input_base& input, float delta) {}
	virtual void 			loop(Input_base& input, float delta);
	virtual void 			dibujar(DLibV::Pantalla& pantalla);

	Herramientas_proyecto::Compositor_vista		escena;
	const Herramientas_proyecto::Localizador_base&	localizador;
	const DLibV::Fuente_TTF& 			ttf_romaji;
};

#endif
