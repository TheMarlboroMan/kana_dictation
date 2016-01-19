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

					Controlador_opciones(Director_estados& d, const DLibV::Fuente_TTF&, Herramientas_proyecto::Localizador_base&, DLibV::Pantalla&);
	int				obtener_idioma() const {return std::atoi(opciones_menu.valor_opcion(k_idioma).c_str());}
	int				obtener_w_ventana() const {return obtener_dimension_ventana(0);}
	int				obtener_h_ventana() const {return obtener_dimension_ventana(1);}
	void				generar_menu(const Configuracion&);

	private:

	virtual void 			preloop(Input_base& input, float delta) {}
	virtual void 			postloop(Input_base& input, float delta) {}
	virtual void 			loop(Input_base& input, float delta);
	virtual void 			dibujar(DLibV::Pantalla& pantalla);
	
	int				obtener_dimension_ventana(int) const;

	void				generar_representacion_menu();
	void				traducir_interface();

	struct t_listado
	{
		std::string clave, nombre;
	};

	DLibV::Pantalla&				pantalla;
	Herramientas_proyecto::Compositor_vista		escena;
	Herramientas_proyecto::Menu_opciones<std::string, std::string>	opciones_menu;
	Herramientas_proyecto::Listado_vertical<t_listado>	listado;
	DLibV::Representacion_agrupada		 	rep_listado;


	Herramientas_proyecto::Localizador_base&	localizador;	//No es constante, desde aquí puede cambiar.
	const DLibV::Fuente_TTF& 			ttf_romaji;

	//TODO: Repetidos con respecto a otros... Mejor llevarlos a otro sitio...
	static const int 				X_LISTADO=16,
							Y_LISTADO=32,
//							X_SELECCION=270,
							ALTO_ITEM_LISTADO=20,
							ANCHO_LISTADO=300,
							MARGEN_Y=16;

	static const std::string 			k_tam_pantalla,
							k_tam_pantalla_o1,
							k_tam_pantalla_o2,
							k_tam_pantalla_o3,
							k_tam_pantalla_o4,
							k_tam_pantalla_o5,
							k_tam_pantalla_o6,
							k_idioma,
							k_idioma_o1,
							k_idioma_o2,
							k_fondo;
};

#endif
