#include "controlador_menu.h"
#include "../app/recursos.h"
#include "../app/localizacion.h"
#include "../app/eventos/cambio_longitud.h"
#include "../app/eventos/cambio_kanas.h"
#include "../app/eventos/cambio_direccion.h"

Controlador_menu::Controlador_menu(const DLibV::Fuente_TTF& fr, const Herramientas_proyecto::Localizador_base& loc, int longitud, App::tipos_kana tipo_kana, App::direcciones_traduccion dir)
	:localizador(loc), ttf_romaji(fr), seleccion_actual(0), 
	longitud_actual(longitud), tipo_kana(tipo_kana), direccion_traduccion(dir)
{
	//Preparar la escena.
	escena.mapear_fuente("romaji", &ttf_romaji);
	escena.mapear_textura("background", DLibV::Gestor_texturas::obtener(App::Recursos_graficos::RGT_BACKGROUND));
	
	if(longitud_actual < 1 || longitud_actual > LONGITUD_MAX) longitud_actual=5;
}

void Controlador_menu::traducir_interface()
{
	using namespace App;

	int indice_silabario=tipo_kana==App::tipos_kana::hiragana ? Localizacion::cadenas::hiragana : Localizacion::cadenas::katakana;
	int indice_direccion=direccion_traduccion==App::direcciones_traduccion::romaji_kana ? Localizacion::cadenas::direccion_romaji_kana : Localizacion::cadenas::direccion_kana_romaji;

	std::string str_silabario=localizador.obtener(Localizacion::cadenas::silabario)+localizador.obtener(indice_silabario);
	std::string str_longitud=localizador.obtener(Localizacion::cadenas::longitud)+std::to_string(longitud_actual);
	std::string str_direccion=localizador.obtener(indice_direccion);

	//TODO: Quizás la posibilidad de traducir una escena podamos hacerla directamente en la clase escena
	//usando unidades de traducción.

	static_cast<DLibV::Representacion_TTF *>(escena.obtener_por_id("txt_menu_1"))->asignar(localizador.obtener(Localizacion::cadenas::iniciar));
	static_cast<DLibV::Representacion_TTF *>(escena.obtener_por_id("txt_menu_2"))->asignar(str_longitud);
	static_cast<DLibV::Representacion_TTF *>(escena.obtener_por_id("txt_menu_3"))->asignar(str_silabario);
	static_cast<DLibV::Representacion_TTF *>(escena.obtener_por_id("txt_menu_4"))->asignar(str_direccion);
	static_cast<DLibV::Representacion_TTF *>(escena.obtener_por_id("txt_menu_5"))->asignar(localizador.obtener(Localizacion::cadenas::escoger_sets));
	static_cast<DLibV::Representacion_TTF *>(escena.obtener_por_id("txt_menu_6"))->asignar(localizador.obtener(Localizacion::cadenas::configuracion));
}

void Controlador_menu::loop(Input_base& input, float delta)
{
	if(input.es_senal_salida() || input.es_input_down(Input::I_ESCAPE))
	{
		abandonar_aplicacion();
	}
	else 
	{
		if(input.es_input_down(Input::I_ARRIBA) || input.es_input_down(Input::I_ABAJO))
		{
			cambiar_seleccion_actual(input.es_input_down(Input::I_ARRIBA) ? -1 : 1);
		}
		else if(input.es_input_down(Input::I_IZQUIERDA) || input.es_input_down(Input::I_DERECHA))
		{
			switch(seleccion_actual)
			{
				case longitud: cambiar_longitud_actual(input.es_input_down(Input::I_IZQUIERDA) ? -1 : 1); break;
				case cambiar_tipo: cambiar_tipo_kana(); break;
			}
		}
		else if(input.es_input_down(Input::I_ACEPTAR))
		{
			switch(seleccion_actual)
			{
				case iniciar: 		solicitar_cambio_estado(t_estados::PRINCIPAL); break;
				case seleccion_grupo: 	solicitar_cambio_estado(t_estados::GRUPOS); break;
				case cambiar_tipo: 	cambiar_tipo_kana(); break;
				case cambiar_direccion: cambiar_direccion_traduccion(); break;
				case opciones: 		solicitar_cambio_estado(t_estados::OPCIONES); break;
			}
		}
	}
}

void Controlador_menu::cambiar_seleccion_actual(int dir)
{
	if(dir < 0 && seleccion_actual > 0) --seleccion_actual;
	else if(dir > 0 && seleccion_actual < ENTRADAS_MENU) ++seleccion_actual;

	int y=escena.obtener_por_id("menu_1")->acc_posicion().y;

	//TODO: Poder definir constantes en las escenas y poderlas usar aquí.
	//TODO: Usar constantes también dentro de la definición de la escena con operaciones matemáticas simples.
	escena.obtener_por_id("seleccion_menu")->establecer_posicion(0, y + (seleccion_actual * SALTO_MENU), 0 , 0, DLibV::Representacion::FRECT_Y);
}

void Controlador_menu::cambiar_longitud_actual(int dir)
{
	int temp=longitud_actual+dir;
	if(temp > 0  && temp <= LONGITUD_MAX) 
	{
		using namespace App;
		longitud_actual=temp;
		std::string str_longitud=localizador.obtener(Localizacion::cadenas::longitud)+std::to_string(longitud_actual);
		static_cast<DLibV::Representacion_TTF *>(escena.obtener_por_id("txt_menu_2"))->asignar(str_longitud);

		encolar_evento(new App::Eventos::Evento_cambio_longitud(longitud_actual));
	}
}

void Controlador_menu::cambiar_tipo_kana()
{
	using namespace App;
	int tipo_str=0;

	if(tipo_kana==tipos_kana::hiragana) 
	{
		tipo_kana=tipos_kana::katakana;
		tipo_str=Localizacion::katakana;
	}
	else 
	{
		tipo_kana=tipos_kana::hiragana;
		tipo_str=Localizacion::hiragana;
	}

	std::string str_silabario=localizador.obtener(Localizacion::cadenas::silabario)+localizador.obtener(tipo_str);
	static_cast<DLibV::Representacion_TTF *>(escena.obtener_por_id("txt_menu_3"))->asignar(str_silabario);
	encolar_evento(new App::Eventos::Evento_cambio_kanas(tipo_kana));
}

void Controlador_menu::cambiar_direccion_traduccion()
{
	using namespace App;
	int tipo_str=0;

	if(direccion_traduccion==direcciones_traduccion::kana_romaji) 
	{
		direccion_traduccion=direcciones_traduccion::romaji_kana;
		tipo_str=Localizacion::direccion_romaji_kana;
	}
	else 
	{
		direccion_traduccion=direcciones_traduccion::kana_romaji;
		tipo_str=Localizacion::direccion_kana_romaji;
	}

	std::string str=localizador.obtener(tipo_str);
	static_cast<DLibV::Representacion_TTF *>(escena.obtener_por_id("txt_menu_4"))->asignar(str);
	encolar_evento(new App::Eventos::Evento_cambio_direccion(direccion_traduccion));
}

void Controlador_menu::dibujar(DLibV::Pantalla& pantalla)
{
	escena.volcar(pantalla);
}

void Controlador_menu::despertar()
{
	escena.parsear("data/recursos/layout_menu.dnot", "layout");
	escena.obtener_por_id("seleccion_menu")->establecer_alpha(128);
	traducir_interface();
}

void Controlador_menu::dormir()
{
	escena.vaciar_vista();
}
