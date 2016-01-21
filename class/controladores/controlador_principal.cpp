#include "controlador_principal.h"
#include <class/generador_numeros.h>
#include "../app/recursos.h"

Controlador_principal::Controlador_principal(const DLibV::Fuente_TTF& fr, const DLibV::Fuente_TTF& fk)
	:ttf_romaji(fr), ttf_kanas(fk), longitud_cadena(6), resuelto(false), tipo_kana(App::tipos_kana::hiragana)
{
	escena.mapear_fuente("kana", &ttf_kanas);
	escena.mapear_fuente("romaji", &ttf_romaji);
	escena.mapear_textura("background", DLibV::Gestor_texturas::obtener(App::Recursos_graficos::RGT_BACKGROUND));
	escena.parsear("data/recursos/layout_principal.dnot", "layout");
}

void Controlador_principal::generar_cadena_kanas()
{
	if(!kanas.size())
	{
		throw std::runtime_error("No kanas selected, unable to generate string");
	}

	using namespace Herramientas_proyecto;
	Generador_int gen(0, kanas.size()-1);

	std::string str_kana, str_romaji;
	size_t i=0;
	while(i < longitud_cadena)
	{
		int pos=gen();
		str_kana+=tipo_kana==App::tipos_kana::hiragana ? kanas[pos].acc_hiragana() : kanas[pos].acc_katakana();
		str_romaji+=kanas[pos].acc_silaba()+"-";
		++i;
	}

	str_romaji.pop_back();

	using namespace DLibV;

	Representacion_TTF * rep_ttf_romaji=static_cast<DLibV::Representacion_TTF *>(escena.obtener_por_id("txt_romaji"));
	Representacion_TTF * rep_ttf_kana=static_cast<DLibV::Representacion_TTF *>(escena.obtener_por_id("txt_kana"));

	rep_ttf_romaji->asignar(str_romaji);
	rep_ttf_kana->asignar(str_kana);
	rep_ttf_kana->hacer_invisible();

	//Aún no podemos centrarlos porque no sabemos cuanto miden (sólo se "materializan" al dibujar)...

	resuelto=false;
}

void Controlador_principal::loop(Input_base& input, float delta)
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
			if(!resuelto)
			{
				resuelto=true;
				escena.obtener_por_id("txt_kana")->hacer_visible();
			}
			else
			{
				generar_cadena_kanas();
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

}

void Controlador_principal::dormir()
{

}
