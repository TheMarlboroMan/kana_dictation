#include "interprete_eventos.h"
#include "../recursos.h"
#include "../definiciones.h"
#include <video/superficie/imagen.h>
#include <herramientas/log_base/log_base.h>
#include <video/utilidades_graficas_sdl/utilidades_graficas_sdl.h>
#include <video/gestores/gestor_texturas.h>


extern DLibH::Log_base LOG;

using namespace App::Eventos;

Interprete_eventos::Interprete_eventos(DLibV::Pantalla& pantalla, App::App_config& config, App::Configuracion_ejercicio& config_ej):
	pantalla(pantalla), config(config), config_ejercicio(config_ej)
{

}

void Interprete_eventos::interpretar_evento(const DFramework::Evento_framework_interface& ev)
{
	switch(ev.tipo_evento())
	{
		case cambio_fondo: 	interpretar_evento(static_cast<const Evento_cambio_fondo&>(ev)); break;
		case cambio_idioma:	interpretar_evento(static_cast<const Evento_cambio_idioma&>(ev)); break;
		case cambio_ventana:	interpretar_evento(static_cast<const Evento_cambio_ventana&>(ev)); break;
		case cambio_kanas:	interpretar_evento(static_cast<const Evento_cambio_kanas&>(ev)); break;
		case cambio_longitud:	interpretar_evento(static_cast<const Evento_cambio_longitud&>(ev)); break;
		case cambio_grupos:	interpretar_evento(static_cast<const Evento_cambio_grupos&>(ev)); break;
		case cambio_direccion:	interpretar_evento(static_cast<const Evento_cambio_direccion&>(ev)); break;
		default:
			LOG<<"Un evento del tipo "<<ev.tipo_evento()<<" no ha sido interpretado"<<std::endl;
		break;
	}
}

void Interprete_eventos::interpretar_evento(const Evento_cambio_fondo& ev)
{
	LOG<<"Recibido evento de cambio de fondo "<<ev.ruta_fondo<<std::endl;
	config.mut_fondo(ev.ruta_fondo);

	DLibV::Imagen img(ev.ruta_fondo.c_str(), pantalla.acc_ventana());
	DLibV::Gestor_texturas::obtener(App::Recursos_graficos::RGT_BACKGROUND)->reemplazar(img);

	config.grabar();
}

void Interprete_eventos::interpretar_evento(const Evento_cambio_idioma& ev)
{
	LOG<<"Recibido evento de cambio de idioma "<<ev.id_idioma<<std::endl;
	config.mut_idioma(ev.id_idioma);
	config.grabar();
}

void Interprete_eventos::interpretar_evento(const Evento_cambio_ventana& ev)
{
	LOG<<"Recibido evento de cambio de ventana "<<ev.w<<" x "<<ev.h<<std::endl;
	config.mut_w_fisica_pantalla(ev.w);
	config.mut_h_fisica_pantalla(ev.h);
	config.grabar();
}

void Interprete_eventos::interpretar_evento(const Evento_cambio_kanas& ev)
{
	LOG<<"Recibido evento de cambio de kanas"<<std::endl;
	config_ejercicio.mut_tipo_kana(ev.tipo_kana);
	config.mut_silabario(App::tipo_kana_to_string(ev.tipo_kana));
	config.grabar();
}

void Interprete_eventos::interpretar_evento(const Evento_cambio_longitud& ev)
{
	LOG<<"Recibido evento de cambio de longitud "<<ev.longitud<<std::endl;
	config_ejercicio.mut_longitud(ev.longitud);
	config.mut_longitud(ev.longitud);
	config.grabar();
}

void Interprete_eventos::interpretar_evento(const Evento_cambio_grupos& ev)
{
	LOG<<"Recibido evento de cambio de grupos "<<ev.grupos<<std::endl;
	config.mut_kanas_activos(ev.grupos);
	config.grabar();
}

void Interprete_eventos::interpretar_evento(const Evento_cambio_direccion& ev)
{
	LOG<<"Recibido evento de cambio de direccion"<<std::endl;
	config_ejercicio.mut_direccion_traduccion(ev.direccion);
	config.mut_direccion(App::direccion_traduccion_to_string(ev.direccion));
	config.grabar();
}
