#ifndef CONTROLADOR_OPCIONES_H
#define CONTROLADOR_OPCIONES_H

#include "controlador_base.h"
#include <vector>
#include <class/compositor_vista.h>
#include <base/localizador_base.h>
#include "../app/definiciones.h"
#include <class/menu_opciones.h>
#include <class/listado_vertical.h>
#include <video/representacion/representacion_agrupada/representacion_agrupada.h>
#include <video/gestores/gestor_texturas.h>
#include "../app/framework_impl/app_config.h"
#include "../app/framework_impl/input.h"

namespace App
{

class Controlador_opciones
	:public Controlador_base
{
	public:

					Controlador_opciones(const DLibV::Fuente_TTF&, Herramientas_proyecto::Localizador_base&, const App_config& c);
	private:

	virtual void 			preloop(DFramework::Input& input, float delta) {}
	virtual void 			postloop(DFramework::Input& input, float delta) {}
	virtual void 			loop(DFramework::Input& input, float delta);
	virtual void 			dibujar(DLibV::Pantalla& pantalla);
	virtual void 			despertar();
	virtual void 			dormir();
	virtual bool			es_posible_abandonar_estado() const {return true;}
	
	void				generar_menu(const App_config&);
	void				generar_representacion_menu();
	void				traducir_interface();

	struct t_listado
	{
		std::string clave, nombre;
	};

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

}
#endif
