#include "controlador_grupos.h"
#include "../app/recursos.h"
#include "../app/localizacion.h"
#include "../app/eventos/cambio_grupos.h"
#include <algorithm>
#include <source/string_utilidades.h>


//Este valor es conocido también por la configuración en su propia definición. Realmente está repetido.
const std::string Controlador_grupos::WILDCARD_TODOS_KANAS="*";

Controlador_grupos::Controlador_grupos(Director_estados &DI, const DLibV::Fuente_TTF& fr, const Herramientas_proyecto::Localizador_base& loc, const std::vector<std::string>& gr, const std::string& kanas_activos)
	:Controlador_base(DI), rep_listado(true), listado(ANCHO_LISTADO, ALTO_ITEM_LISTADO), localizador(loc), ttf_romaji(fr)
{
	//Preparar la escena.
	escena.mapear_fuente("romaji", &ttf_romaji);
	escena.mapear_textura("background", DLibV::Gestor_texturas::obtener(App::Recursos_graficos::RGT_BACKGROUND));
	escena.parsear("data/recursos/layout_grupos.dnot", "layout");

	auto v=gr;
	std::sort(std::begin(v), std::end(v)); //Se ordenan por nombre y se insertan sin seleccionar.
	for(const auto& n : v) grupos.push_back({n, false});

	listado.mut_margen_h(MARGEN_Y);
	rep_listado.no_imponer_alpha();

	establecer_kanas_activos(kanas_activos);
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
			componer_vista_listado();
		}
		else if(input.es_input_down(Input::I_IZQUIERDA) || input.es_input_down(Input::I_DERECHA) || input.es_input_down(Input::I_ACEPTAR))
		{
			size_t indice=listado.acc_indice_actual();
			grupos[indice].seleccionado=!grupos[indice].seleccionado;

			encolar_evento(new App::Eventos::Evento_cambio_grupos(producir_cadena_kanas_activos()));
			componer_vista_listado();
		}
	}
}

void Controlador_grupos::dibujar(DLibV::Pantalla& pantalla)
{
	componer_vista_listado();
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

std::string Controlador_grupos::producir_cadena_kanas_activos() const
{
	size_t total=0;
	std::string res;

	for(const auto &g : grupos)
	{
		if(g.seleccionado) 
		{
			res+=g.nombre+SEPARADOR_KANAS_ACTIVOS;
			++total;
		}
	}

	if(res.size()) res.pop_back();
	return total==grupos.size() ? WILDCARD_TODOS_KANAS : res;
}

void Controlador_grupos::establecer_kanas_activos(const std::string& k)
{
	auto seleccionar_todos=[this]() {for(auto& g : grupos) g.seleccionado=true;};

	if(k==WILDCARD_TODOS_KANAS)
	{
		seleccionar_todos();
	}
	else
	{
		auto v=Herramientas_proyecto::explotar(k, SEPARADOR_KANAS_ACTIVOS);
		int total_activos=0;

		for(const auto& clave : v)
		{
			for(auto& g : grupos) 
			{
				if(g.nombre==clave) 
				{
					g.seleccionado=true;
					++total_activos;
				}
			}
		}

		if(!total_activos) seleccionar_todos();	//Si no hay ninguno activo porque la configuración esté reventada, los seleccionamos todos.
	}

	//TODO: Lanzar evento...

	componer_vista_listado();
}
