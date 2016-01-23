#include "controlador_menu.h"
#include "../app/recursos.h"
#include "../app/localizacion.h"
#include "../app/eventos/cambio_longitud.h"
#include "../app/eventos/cambio_kanas.h"
#include "../app/eventos/cambio_direccion.h"

using namespace App;

Controlador_menu::Controlador_menu(const DLibV::Fuente_TTF& fr, const Herramientas_proyecto::Localizador_base& loc, const App::Configuracion_ejercicio&	configuracion_ejercicio)
	:localizador(loc), configuracion_ejercicio(configuracion_ejercicio), ttf_romaji(fr), seleccion_actual(0), refrescar(false)
{
	//Preparar la escena.
	escena.mapear_fuente("romaji", &ttf_romaji);
	escena.mapear_textura("background", DLibV::Gestor_texturas::obtener(App::Recursos_graficos::RGT_BACKGROUND));
}

void Controlador_menu::traducir_interface()
{
	using namespace App;

	//TODO: Quizás la posibilidad de traducir una escena podamos hacerla directamente en la clase escena
	//usando unidades de traducción.

	static_cast<DLibV::Representacion_TTF *>(escena.obtener_por_id("txt_menu_1"))->asignar(localizador.obtener(Localizacion::cadenas::iniciar));
	static_cast<DLibV::Representacion_TTF *>(escena.obtener_por_id("txt_menu_5"))->asignar(localizador.obtener(Localizacion::cadenas::escoger_sets));
	static_cast<DLibV::Representacion_TTF *>(escena.obtener_por_id("txt_menu_6"))->asignar(localizador.obtener(Localizacion::cadenas::configuracion));

	actualizar_menu();
}

void Controlador_menu::loop(DFramework::Input& input, float delta)
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
				case cambiar_direccion: cambiar_direccion_traduccion(); break;
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

void Controlador_menu::postloop(DFramework::Input& input, float delta)
{
	if(refrescar)
	{
		actualizar_menu();
		refrescar=false;
	}
}

void Controlador_menu::actualizar_menu()
{
	using namespace App;

	int indice_silabario=configuracion_ejercicio.acc_tipo_kana()==App::tipos_kana::hiragana ? Localizacion::cadenas::hiragana : Localizacion::cadenas::katakana;
	int indice_direccion=configuracion_ejercicio.acc_direccion_traduccion()==App::direcciones_traduccion::romaji_kana ? Localizacion::cadenas::direccion_romaji_kana : Localizacion::cadenas::direccion_kana_romaji;

	std::string str_silabario=localizador.obtener(Localizacion::cadenas::silabario)+localizador.obtener(indice_silabario);
	std::string str_longitud=localizador.obtener(Localizacion::cadenas::longitud)+std::to_string(configuracion_ejercicio.acc_longitud());
	std::string str_direccion=localizador.obtener(indice_direccion);

	static_cast<DLibV::Representacion_TTF *>(escena.obtener_por_id("txt_menu_2"))->asignar(str_longitud);
	static_cast<DLibV::Representacion_TTF *>(escena.obtener_por_id("txt_menu_3"))->asignar(str_silabario);
	static_cast<DLibV::Representacion_TTF *>(escena.obtener_por_id("txt_menu_4"))->asignar(str_direccion);
}

void Controlador_menu::cambiar_seleccion_actual(int dir)
{
	//TODO: Bug, puedes ir más abajo de lo que debes.

	if(dir < 0 && seleccion_actual > 0) --seleccion_actual;
	else if(dir > 0 && seleccion_actual < ENTRADAS_MENU-1) ++seleccion_actual;

	int y=escena.obtener_por_id("menu_1")->acc_posicion().y;

	//TODO: Poder definir constantes en las escenas y poderlas usar aquí.
	//TODO: Usar constantes también dentro de la definición de la escena con operaciones matemáticas simples.
	escena.obtener_por_id("seleccion_menu")->establecer_posicion(0, y + (seleccion_actual * SALTO_MENU), 0 , 0, DLibV::Representacion::FRECT_Y);
}

void Controlador_menu::cambiar_longitud_actual(int dir)
{
	encolar_evento(new App::Eventos::Evento_cambio_longitud(configuracion_ejercicio.acc_longitud()+dir));
	refrescar=true;
}

void Controlador_menu::cambiar_tipo_kana()
{
	using namespace App;
	auto tipo_kana=configuracion_ejercicio.acc_tipo_kana();

	if(tipo_kana==tipos_kana::hiragana) tipo_kana=tipos_kana::katakana;
	else tipo_kana=tipos_kana::hiragana;

	encolar_evento(new App::Eventos::Evento_cambio_kanas(tipo_kana));
	refrescar=true;
}

void Controlador_menu::cambiar_direccion_traduccion()
{
	using namespace App;
	auto direccion_traduccion=configuracion_ejercicio.acc_direccion_traduccion();

	if(direccion_traduccion==direcciones_traduccion::kana_romaji) direccion_traduccion=direcciones_traduccion::romaji_kana;
	else direccion_traduccion=direcciones_traduccion::kana_romaji;

	encolar_evento(new App::Eventos::Evento_cambio_direccion(direccion_traduccion));
	refrescar=true;
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

	int y=escena.obtener_por_id("menu_1")->acc_posicion().y;
	escena.obtener_por_id("seleccion_menu")->establecer_posicion(0, y + (seleccion_actual * SALTO_MENU), 0 , 0, DLibV::Representacion::FRECT_Y);
}

void Controlador_menu::dormir()
{
	escena.vaciar_vista();
}
