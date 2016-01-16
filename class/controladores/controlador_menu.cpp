#include "controlador_menu.h"
#include "../app/recursos.h"

Controlador_menu::Controlador_menu(Director_estados &DI, const DLibV::Fuente_TTF& fr, const Herramientas_proyecto::Localizador_base& loc)
	:Controlador_base(DI), ttf_romaji(fr), seleccion_actual(0)
{
	escena.mapear_fuente("romaji", &ttf_romaji);
	escena.mapear_textura("background", DLibV::Gestor_texturas::obtener(App::Recursos_graficos::RGT_BACKGROUND));
	escena.parsear("data/recursos/layout_menu.dnot", "layout");
	escena.obtener_por_id("seleccion_menu")->establecer_alpha(128);

	//TODO: Constantes o definiciones somewhere...
	static_cast<DLibV::Representacion_TTF *>(escena.obtener_por_id("txt_menu_1"))->asignar(loc.obtener(1));
	static_cast<DLibV::Representacion_TTF *>(escena.obtener_por_id("txt_menu_2"))->asignar(loc.obtener(2));
	static_cast<DLibV::Representacion_TTF *>(escena.obtener_por_id("txt_menu_3"))->asignar(loc.obtener(3));






}

void Controlador_menu::loop(Input_base& input, float delta)
{
	if(input.es_senal_salida() || input.es_input_down(Input::I_ESCAPE))
	{
		abandonar_aplicacion();
	}
	else 
	{
		if(input.es_input_down(Input::I_ESPACIO))
		{
			solicitar_cambio_estado(Director_estados::t_estados::PRINCIPAL);
		}
	}
}

void Controlador_menu::dibujar(DLibV::Pantalla& pantalla)
{
	escena.volcar(pantalla);
}
