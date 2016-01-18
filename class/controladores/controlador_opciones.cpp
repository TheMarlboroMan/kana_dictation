#include "controlador_opciones.h"
#include "../app/recursos.h"
#include "../app/localizacion.h"

Controlador_opciones::Controlador_opciones(Director_estados &DI, const DLibV::Fuente_TTF& fr, const Herramientas_proyecto::Localizador_base& loc)
	:Controlador_base(DI), listado(ANCHO_LISTADO, ALTO_ITEM_LISTADO), rep_listado(true), localizador(loc), ttf_romaji(fr)
{
	//Preparar la escena.
	escena.mapear_fuente("romaji", &ttf_romaji);
	escena.mapear_textura("background", DLibV::Gestor_texturas::obtener(App::Recursos_graficos::RGT_BACKGROUND));
	escena.parsear("data/recursos/layout_opciones.dnot", "layout");

	rep_listado.no_imponer_alpha();
	listado.mut_margen_h(MARGEN_Y);

	generar_menu();
	generar_representacion_menu();
}

void Controlador_opciones::generar_menu()
{
	using namespace Herramientas_proyecto;
	using traduccion=Menu_opciones<std::string, std::string>::struct_traduccion;

	const std::string k_tam_pantalla="K_TAM_PANTALLA",
		k_tam_pantalla_o1="K_TAM_PANTALLA_VIDEO_01",
		k_tam_pantalla_o2="K_TAM_PANTALLA_VIDEO_02",
		k_idioma="K_IDIOMA",
		k_idioma_o1="K_IDIOMA_01_ES",
		k_idioma_o2="K_IDIOMA_02_EN";

	opciones_menu.insertar_opcion(k_tam_pantalla, "--");
	opciones_menu.insertar_seleccion_en_opcion(k_tam_pantalla, k_tam_pantalla_o1, "--", "800x500");
	opciones_menu.insertar_seleccion_en_opcion(k_tam_pantalla, k_tam_pantalla_o2, "--", "1600x1000");

	opciones_menu.insertar_opcion(k_idioma, "--");
	opciones_menu.insertar_seleccion_en_opcion(k_idioma, k_idioma_o1, "--", "0");
	opciones_menu.insertar_seleccion_en_opcion(k_idioma, k_idioma_o2, "--", "1");

	using namespace App;

	std::vector<traduccion> trad={
		{k_tam_pantalla, localizador.obtener(Localizacion::opciones_pantalla)}, 
		{k_tam_pantalla_o1, localizador.obtener(Localizacion::opciones_pantalla_01)},
		{k_tam_pantalla_o2, localizador.obtener(Localizacion::opciones_pantalla_02)},
		{k_idioma, localizador.obtener(Localizacion::opciones_idioma)},
		{k_idioma_o1, localizador.obtener(Localizacion::opciones_idioma_01)},
		{k_idioma_o2, localizador.obtener(Localizacion::opciones_idioma_02)}
	};

	opciones_menu.traducir(trad);
}

void Controlador_opciones::generar_representacion_menu()
{
	listado.clear();
	const auto& v=opciones_menu.obtener_claves();
	for(const auto& c : v) listado.insertar({c, opciones_menu.nombre_opcion(c)+" : "+opciones_menu.nombre_seleccion(c)});

	rep_listado.vaciar_grupo();
	const auto pagina=listado.obtener_pagina();
	using namespace DLibV;
		
	for(const auto& itemp : pagina)
	{
		auto * txt=new Representacion_TTF(ttf_romaji, {255, 255, 255, 255}, itemp.item.nombre);
		txt->establecer_posicion(X_LISTADO, itemp.y+Y_LISTADO);
		rep_listado.insertar_representacion(txt);
	}

	const int y=Y_LISTADO+(listado.linea_actual().y)-2;
	auto * caja=new Representacion_primitiva_caja({0, y, ANCHO_LISTADO, ALTO_ITEM_LISTADO}, 255, 255, 255);
	caja->establecer_alpha(128);

	rep_listado.insertar_representacion(caja);
}

void Controlador_opciones::loop(Input_base& input, float delta)
{
	if(input.es_senal_salida())
	{
		abandonar_aplicacion();
	}
	else 
	{
		if(input.es_input_down(Input::I_ESCAPE))
		{
			solicitar_cambio_estado(Director_estados::t_estados::MENU);
		}
		else if(input.es_input_down(Input::I_ARRIBA) || input.es_input_down(Input::I_ABAJO))
		{
			listado.cambiar_item(input.es_input_down(Input::I_ARRIBA) ? -1 : 1);
			generar_representacion_menu();
		}
		else if(input.es_input_down(Input::I_IZQUIERDA) || input.es_input_down(Input::I_DERECHA) || input.es_input_down(Input::I_ACEPTAR))
		{
			size_t indice=listado.acc_indice_actual();
			const auto clave=listado[indice].clave;
			opciones_menu.rotar_opcion(clave, input.es_input_down(Input::I_IZQUIERDA) ? -1 : 1);
			generar_representacion_menu();

			//TODO: Actualizar según la clave.

			//TODO: Escribir en configuración.
		}
	}
}

void Controlador_opciones::dibujar(DLibV::Pantalla& pantalla)
{
	escena.volcar(pantalla);
	rep_listado.volcar(pantalla);
}
