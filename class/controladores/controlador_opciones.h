#ifndef CONTROLADOR_OPCIONES_H
#define CONTROLADOR_OPCIONES_H

#include "controlador_base.h"
#include <vector>
#include <class/compositor_vista.h>
#include <base/localizador_base.h>
#include "../app/definiciones.h"
#include <class/menu_opciones.h>
#include <class/listado_vertical.h>

class Controlador_opciones:public Controlador_base
{
	public:

					Controlador_opciones(Director_estados& d, const DLibV::Fuente_TTF&, const Herramientas_proyecto::Localizador_base&);

	private:

	virtual void 			preloop(Input_base& input, float delta) {}
	virtual void 			postloop(Input_base& input, float delta) {}
	virtual void 			loop(Input_base& input, float delta);
	virtual void 			dibujar(DLibV::Pantalla& pantalla);

	void				generar_menu();
	void				generar_representacion_menu();

	struct t_listado
	{
		std::string clave, nombre;
	};

	Herramientas_proyecto::Compositor_vista		escena;
	Herramientas_proyecto::Menu_opciones<std::string, std::string>	opciones_menu;
	Herramientas_proyecto::Listado_vertical<t_listado>	listado;
	DLibV::Representacion_agrupada		 	rep_listado;


	const Herramientas_proyecto::Localizador_base&	localizador;
	const DLibV::Fuente_TTF& 			ttf_romaji;

	//TODO: Repetidos con respecto a otros... Mejor llevarlos a otro sitio...
	static const int 				X_LISTADO=16,
							Y_LISTADO=32,
//							X_SELECCION=270,
							ALTO_ITEM_LISTADO=20,
							ANCHO_LISTADO=300,
							MARGEN_Y=16;
};

#endif
