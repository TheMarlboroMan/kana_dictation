#include "controlador_opciones.h"
#include "../app/recursos.h"
#include "../app/localizacion.h"

Controlador_opciones::Controlador_opciones(Director_estados &DI, const DLibV::Fuente_TTF& fr, const Herramientas_proyecto::Localizador_base& loc)
	:Controlador_base(DI), localizador(loc), ttf_romaji(fr)
{
	//Preparar la escena.
	escena.mapear_fuente("romaji", &ttf_romaji);
	escena.mapear_textura("background", DLibV::Gestor_texturas::obtener(App::Recursos_graficos::RGT_BACKGROUND));
	escena.parsear("data/recursos/layout_opciones.dnot", "layout");
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
	}
}

void Controlador_opciones::dibujar(DLibV::Pantalla& pantalla)
{
	escena.volcar(pantalla);
}
