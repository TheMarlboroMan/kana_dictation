#include "controlador_grupos.h"
#include "../app/recursos.h"
#include "../app/localizacion.h"
#include <algorithm>

Controlador_grupos::Controlador_grupos(Director_estados &DI, const DLibV::Fuente_TTF& fr, const Herramientas_proyecto::Localizador_base& loc, const std::vector<std::string>& gr)
	:Controlador_base(DI), rep_listado(true), listado(ANCHO_LISTADO, ALTO_ITEM_LISTADO), localizador(loc), ttf_romaji(fr)
{
	//Preparar la escena.
	escena.mapear_fuente("romaji", &ttf_romaji);
	escena.mapear_textura("background", DLibV::Gestor_texturas::obtener(App::Recursos_graficos::RGT_BACKGROUND));
	escena.parsear("data/recursos/layout_grupos.dnot", "layout");

	auto v=gr;
	//TODO: Este sort es una mieeeeerda.
	std::sort(std::begin(v), std::end(v));
	for(const auto& n : v) grupos.push_back({n, true});

	listado.mut_margen_h(MARGEN_Y);
	rep_listado.no_imponer_alpha();

	componer_vista_listado();
}

void Controlador_grupos::componer_vista_listado()
{
	listado.clear();
	for(const auto& i : grupos) listado.insertar(i);

	rep_listado.vaciar_grupo();

	const auto pagina=listado.obtener_pagina();
	using namespace DLibV;
		
	for(const auto& itemp : pagina)
	{
		auto * txt=new Representacion_TTF(ttf_romaji, {255, 255, 255, 255}, itemp.item.nombre);
		txt->establecer_posicion(X_LISTADO, itemp.y+Y_LISTADO);

		auto * sel=itemp.item.seleccionado ? 
			new Representacion_TTF(ttf_romaji, {0, 255, 0, 255}, "+"):
			new Representacion_TTF(ttf_romaji, {255, 0, 0, 255}, "-");

		sel->establecer_posicion(X_SELECCION, itemp.y+Y_LISTADO);

		rep_listado.insertar_representacion(txt);
		rep_listado.insertar_representacion(sel);	
	}

	const int y=Y_LISTADO+(listado.linea_actual().y)-2;
	auto * caja=new Representacion_primitiva_caja({0, y, ANCHO_LISTADO, ALTO_ITEM_LISTADO}, 255, 255, 255);
	caja->establecer_alpha(128);

	rep_listado.insertar_representacion(caja);
}

void Controlador_grupos::loop(Input_base& input, float delta)
{	if(input.es_senal_salida())
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
			componer_vista_listado();
		}
		else if(input.es_input_down(Input::I_IZQUIERDA) || input.es_input_down(Input::I_DERECHA) || input.es_input_down(Input::I_ACEPTAR))
		{
			size_t indice=listado.acc_indice_actual();
			grupos[indice].seleccionado=!grupos[indice].seleccionado;
			componer_vista_listado();
		}
	}
}

void Controlador_grupos::dibujar(DLibV::Pantalla& pantalla)
{
	escena.volcar(pantalla);
	rep_listado.volcar(pantalla);
}

std::vector<std::string> Controlador_grupos::obtener_grupos_seleccionados() const
{
	std::vector<std::string> res;
	for(const auto &g : grupos)
		if(g.seleccionado) res.push_back(g.nombre);
	return res;
}

size_t Controlador_grupos::cantidad_seleccionados() const
{
	size_t res=0;
	for(const auto &g : grupos)
		if(g.seleccionado) ++res;
	return res;
}
