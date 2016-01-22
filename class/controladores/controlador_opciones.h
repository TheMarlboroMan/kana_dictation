#ifndef CONTROLADOR_OPCIONES_H
#define CONTROLADOR_OPCIONES_H

#include "controlador_base.h"
#include <vector>
#include <class/compositor_vista.h>
#include <base/localizador_base.h>
#include "../app/definiciones.h"
#include <class/menu_opciones.h>
#include <class/listado_vertical.h>
#include "../framework/derivada/configuracion.h"

class Controlador_opciones:public Controlador_base
{
	public:

					Controlador_opciones(const DLibV::Fuente_TTF&, Herramientas_proyecto::Localizador_base&, DLibV::Pantalla&, const Configuracion& c);
	private:

	virtual void 			preloop(Input_base& input, float delta) {}
	virtual void 			postloop(Input_base& input, float delta) {}
	virtual void 			loop(Input_base& input, float delta);
	virtual void 			dibujar(DLibV::Pantalla& pantalla);
	virtual void 			despertar();
	virtual void 			dormir();
	virtual bool			es_posible_abandonar_estado() const {return true;}
	
	void				generar_menu(const Configuracion&);
	void				generar_representacion_menu();
	void				traducir_interface();

	struct t_listado
	{
		std::string clave, nombre;
	};

	DLibV::Pantalla&				pantalla;
	Herramientas_proyecto::Localizador_base&	localizador;	//No es constante, desde aquí puede cambiar.
	const DLibV::Fuente_TTF& 			ttf_romaji;

	DLibV::Representacion_agrupada		 	rep_listado;
	Herramientas_proyecto::Compositor_vista		escena;
	Herramientas_proyecto::Menu_opciones<std::string, std::string>	opciones_menu;
	Herramientas_proyecto::Listado_vertical<t_listado>	listado;
	std::map<std::string, int>			mapa_traducciones;	//Mapa de traducción del menú: la clave X se corresponderá con el indice Y del localizador.


	//TODO: Repetidos con respecto a otros... Mejor llevarlos a otro sitio...
	static const int 				X_LISTADO=16,
							Y_LISTADO=32,
//							X_SELECCION=270,
							ALTO_ITEM_LISTADO=20,
							//TODO: Ojo, este no se repite!!!.
							ANCHO_LISTADO=400,
							MARGEN_Y=16;

	static const std::string 			k_tam_pantalla,
							k_idioma,
							k_fondo;
};

#endif
