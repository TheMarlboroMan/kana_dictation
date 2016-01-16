#ifndef CONTROLADOR_MENU
#define CONTROLADOR_MENU

#include "controlador_base.h"
#include <vector>
#include <class/compositor_vista.h>
#include <base/localizador_base.h>

class Controlador_menu:public Controlador_base
{
	public:

					Controlador_menu(Director_estados& d, const DLibV::Fuente_TTF&, const Herramientas_proyecto::Localizador_base&);

	private:

	virtual void 			preloop(Input_base& input, float delta) {}
	virtual void 			postloop(Input_base& input, float delta) {}
	virtual void 			loop(Input_base& input, float delta);
	virtual void 			dibujar(DLibV::Pantalla& pantalla);

	Herramientas_proyecto::Compositor_vista		escena;

	const DLibV::Fuente_TTF& 			ttf_romaji;
	int						seleccion_actual;

	static const int				ENTRADAS_MENU=4;

};

#endif
