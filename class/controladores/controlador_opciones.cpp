#include "controlador_opciones.h"
#include "../app/recursos.h"
#include "../app/localizacion.h"
#include <source/string_utilidades.h>

const std::string Controlador_opciones::k_tam_pantalla="K_TAM_PANTALLA";
const std::string Controlador_opciones::k_tam_pantalla_o1="K_TAM_PANTALLA_VIDEO_01";
const std::string Controlador_opciones::k_tam_pantalla_o2="K_TAM_PANTALLA_VIDEO_02";
const std::string Controlador_opciones::k_tam_pantalla_o3="K_TAM_PANTALLA_VIDEO_03";
const std::string Controlador_opciones::k_tam_pantalla_o4="K_TAM_PANTALLA_VIDEO_04";
const std::string Controlador_opciones::k_tam_pantalla_o5="K_TAM_PANTALLA_VIDEO_05";
const std::string Controlador_opciones::k_tam_pantalla_o6="K_TAM_PANTALLA_VIDEO_06";
const std::string Controlador_opciones::k_idioma="K_IDIOMA";
const std::string Controlador_opciones::k_idioma_o1="K_IDIOMA_01_ES";
const std::string Controlador_opciones::k_idioma_o2="K_IDIOMA_02_EN";

Controlador_opciones::Controlador_opciones(Director_estados &DI, const DLibV::Fuente_TTF& fr, Herramientas_proyecto::Localizador_base& loc)
	:Controlador_base(DI), listado(ANCHO_LISTADO, ALTO_ITEM_LISTADO), rep_listado(true), localizador(loc), ttf_romaji(fr)
{
	//Preparar la escena.
	escena.mapear_fuente("romaji", &ttf_romaji);
	escena.mapear_textura("background", DLibV::Gestor_texturas::obtener(App::Recursos_graficos::RGT_BACKGROUND));
	escena.parsear("data/recursos/layout_opciones.dnot", "layout");

	rep_listado.no_imponer_alpha();
	listado.mut_margen_h(MARGEN_Y);
}

int Controlador_opciones::obtener_dimension_ventana(int i) const
{
	const auto partes=Herramientas_proyecto::explotar(opciones_menu.valor_opcion(k_tam_pantalla), 'x');
	return std::atoi(partes[i].c_str());
}

void Controlador_opciones::traducir_interface()
{
	using namespace App;
	using namespace Herramientas_proyecto;
	using traduccion=Menu_opciones<std::string, std::string>::struct_traduccion;

	std::vector<traduccion> trad={
		{k_tam_pantalla, localizador.obtener(Localizacion::opciones_pantalla)}, 
		{k_tam_pantalla_o1, localizador.obtener(Localizacion::opciones_pantalla_01)},
		{k_tam_pantalla_o2, localizador.obtener(Localizacion::opciones_pantalla_02)},
		{k_tam_pantalla_o3, localizador.obtener(Localizacion::opciones_pantalla_03)},
		{k_tam_pantalla_o4, localizador.obtener(Localizacion::opciones_pantalla_04)},
		{k_tam_pantalla_o5, localizador.obtener(Localizacion::opciones_pantalla_05)},
		{k_tam_pantalla_o6, localizador.obtener(Localizacion::opciones_pantalla_06)},
		{k_idioma, localizador.obtener(Localizacion::opciones_idioma)},
		{k_idioma_o1, localizador.obtener(Localizacion::opciones_idioma_01)},
		{k_idioma_o2, localizador.obtener(Localizacion::opciones_idioma_02)}
	};

	opciones_menu.traducir(trad);
}

void Controlador_opciones::generar_menu(const Configuracion& config)
{
	if(opciones_menu.size()) return;

	opciones_menu.insertar_opcion(k_tam_pantalla, "--");
	opciones_menu.insertar_seleccion_en_opcion(k_tam_pantalla, k_tam_pantalla_o1, "--", "800x500");
	opciones_menu.insertar_seleccion_en_opcion(k_tam_pantalla, k_tam_pantalla_o2, "--", "960x600");
	opciones_menu.insertar_seleccion_en_opcion(k_tam_pantalla, k_tam_pantalla_o3, "--", "1120x700");
	opciones_menu.insertar_seleccion_en_opcion(k_tam_pantalla, k_tam_pantalla_o4, "--", "1280x800");
	opciones_menu.insertar_seleccion_en_opcion(k_tam_pantalla, k_tam_pantalla_o5, "--", "1440x900");
	opciones_menu.insertar_seleccion_en_opcion(k_tam_pantalla, k_tam_pantalla_o6, "--", "1600x1000");

	opciones_menu.insertar_opcion(k_idioma, "--");
	opciones_menu.insertar_seleccion_en_opcion(k_idioma, k_idioma_o1, "--", "0");
	opciones_menu.insertar_seleccion_en_opcion(k_idioma, k_idioma_o2, "--", "1");

	const std::string val_tam_pantalla=std::to_string(config.acc_w_fisica_pantalla())+"x"+std::to_string(config.acc_h_fisica_pantalla());

	opciones_menu.seleccionar_opcion_por_valor(k_tam_pantalla, val_tam_pantalla);
	opciones_menu.seleccionar_opcion_por_valor(k_idioma, std::to_string(config.acc_idioma()));

	traducir_interface();
	generar_representacion_menu();
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

	//TODO: Poner esto mejor... Pero de momento dejarlo como prueba para localizar el bug de fondos negros.
	auto * advertencia=new Representacion_TTF(ttf_romaji, {255, 0, 0, 255}, "CAMBIOS DE RESOLUCION SOLO AL REINICIAR");
	advertencia->establecer_posicion(300, 300);
	rep_listado.insertar_representacion(advertencia);

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

			//TODO: Sólo si lo que ha cambiado es el idioma.

			localizador.cambiar_idioma(std::atoi(opciones_menu.valor_opcion(k_idioma).c_str()));
			traducir_interface();
			generar_representacion_menu();

			//TODO: Actualizar según la clave.
		}
	}
}

void Controlador_opciones::dibujar(DLibV::Pantalla& pantalla)
{
	escena.volcar(pantalla);
	rep_listado.volcar(pantalla);
}
