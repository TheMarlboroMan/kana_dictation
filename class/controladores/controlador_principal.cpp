#include "controlador_principal.h"
#include <class/generador_numeros.h>
#include "../app/recursos.h"

using namespace App;

Controlador_principal::Controlador_principal(const DLibV::Fuente_TTF& fr, const DLibV::Fuente_TTF& fk, const App::Configuracion_ejercicio& config_ej)
	:configuracion_ejercicio(config_ej), ttf_romaji(fr), ttf_kanas(fk), resuelto(false)

{
	escena.mapear_fuente("kana", &ttf_kanas);
	escena.mapear_fuente("romaji", &ttf_romaji);
	escena.mapear_textura("background", DLibV::Gestor_texturas::obtener(App::Recursos_graficos::RGT_BACKGROUND));
}

void Controlador_principal::generar_cadena_kanas()
{
	if(!kanas.size())
	{
		throw std::runtime_error("No se han seleccionado kanas: imposible generar cadena");
	}

	using namespace Herramientas_proyecto;
	Generador_int gen(0, kanas.size()-1);

	auto tipo_kana=configuracion_ejercicio.acc_tipo_kana();
	size_t i=0;

	while(i < configuracion_ejercicio.acc_longitud())
	{
		int pos=gen();
		str_kana+=tipo_kana==App::tipos_kana::hiragana ? kanas[pos].acc_hiragana() : kanas[pos].acc_katakana();
		str_romaji+=kanas[pos].acc_silaba()+"-";
		++i;
	}

	str_romaji.pop_back();
}

void Controlador_principal::reiniciar_visibilidad_cadenas()
{
	using namespace DLibV;

	Representacion_TTF * rep_ttf_romaji=static_cast<DLibV::Representacion_TTF *>(escena.obtener_por_id("txt_romaji"));
	Representacion_TTF * rep_ttf_kana=static_cast<DLibV::Representacion_TTF *>(escena.obtener_por_id("txt_kana"));

	rep_ttf_romaji->asignar(str_romaji);
	rep_ttf_kana->asignar(str_kana);

	switch(configuracion_ejercicio.acc_direccion_traduccion())
	{
		case App::direcciones_traduccion::romaji_kana:
			rep_ttf_romaji->hacer_visible();
		break;
		case App::direcciones_traduccion::kana_romaji:
			rep_ttf_kana->hacer_visible();
		break;
	}

	//Aún no podemos centrarlos porque no sabemos cuanto miden (sólo se "materializan" al dibujar)...
}

void Controlador_principal::loop(DFramework::Input& input, float delta)
{
	if(input.es_senal_salida())
	{
		abandonar_aplicacion();
	}
	else
	{
		if(input.es_input_down(Input::I_ESCAPE))
		{
			solicitar_cambio_estado(t_estados::MENU);
		}
		else if(input.es_input_down(Input::I_ACEPTAR))
		{
			std::string id_txt;
			switch(configuracion_ejercicio.acc_direccion_traduccion())
			{
				case App::direcciones_traduccion::romaji_kana: id_txt="txt_kana"; break;
				case App::direcciones_traduccion::kana_romaji: id_txt="txt_romaji"; break;
			}

			if(!resuelto)
			{
				resuelto=true;
				escena.obtener_por_id(id_txt)->hacer_visible();
			}
			else
			{
				escena.obtener_por_id(id_txt)->hacer_invisible();
				generar_cadena_kanas();
				reiniciar_visibilidad_cadenas();
			}
		}
	}
}

void Controlador_principal::dibujar(DLibV::Pantalla& pantalla)
{
	auto centrar=[](DLibV::Representacion * rep)
	{
		int w=rep->acc_posicion().w;
		int x=(800 - w) / 2;
		rep->establecer_posicion(x, 0, 0, 0, DLibV::Representacion::FRECT_X);

	};

	centrar(escena.obtener_por_id("txt_romaji"));
	centrar(escena.obtener_por_id("txt_kana"));

	escena.volcar(pantalla);
}

void Controlador_principal::despertar()
{
	str_kana="";
	str_romaji="";
	escena.parsear("data/recursos/layout_principal.dnot", "layout");
	generar_cadena_kanas();
	reiniciar_visibilidad_cadenas();
}

void Controlador_principal::dormir()
{
	escena.vaciar_vista();
}
