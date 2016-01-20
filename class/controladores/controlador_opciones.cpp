#include "controlador_opciones.h"
#include "../app/recursos.h"
#include "../app/localizacion.h"
#include <source/string_utilidades.h>
#include <class/dnot_parser.h>
#include "../app/eventos/cambio_fondo.h"
#include "../app/eventos/cambio_idioma.h"
#include "../app/eventos/cambio_ventana.h"

const std::string Controlador_opciones::k_tam_pantalla="01_K_TAM_VENTANA";
const std::string Controlador_opciones::k_idioma="02_K_IDIOMA";
const std::string Controlador_opciones::k_fondo="03_K_FONDO";

Controlador_opciones::Controlador_opciones(Director_estados &DI, const DLibV::Fuente_TTF& fr, Herramientas_proyecto::Localizador_base& loc, DLibV::Pantalla& p)
	:Controlador_base(DI), pantalla(p), localizador(loc), ttf_romaji(fr), rep_listado(true), listado(ANCHO_LISTADO, ALTO_ITEM_LISTADO)
{
	//Preparar la escena.
	escena.mapear_fuente("romaji", &ttf_romaji);
	escena.mapear_textura("background", DLibV::Gestor_texturas::obtener(App::Recursos_graficos::RGT_BACKGROUND));
	escena.parsear("data/recursos/layout_opciones.dnot", "layout");

	rep_listado.no_imponer_alpha();
	listado.mut_margen_h(MARGEN_Y);
}

void Controlador_opciones::traducir_interface()
{
	using namespace App;
	using namespace Herramientas_proyecto;
	using traduccion=Menu_opciones<std::string, std::string>::struct_traduccion;

	std::vector<traduccion> trad={};
	for(const auto& par : mapa_traducciones)
		trad.push_back({par.first, localizador.obtener(par.second)});

	opciones_menu.traducir(trad);
}

void Controlador_opciones::generar_menu(const Configuracion& config)
{
	if(opciones_menu.size()) return;

	//Leer del fichero y rellenar tanto el menú como el mapa de traducción.
	using namespace Herramientas_proyecto;
	const auto parser=parsear_dnot("data/recursos/menu.dnot");
	const auto opciones=parser["menu"].acc_lista();

	for(const auto& opcion : opciones)
	{
		const std::string k_opcion=opcion["clave"];
		mapa_traducciones[k_opcion]=opcion["trans"];
		opciones_menu.insertar_opcion(k_opcion, "--");

		const auto& selecciones=opcion["opciones"].acc_lista();
		for(const auto& seleccion : selecciones)
		{
			const std::string k_seleccion=seleccion["clave"];
			mapa_traducciones[k_seleccion]=seleccion["trans"];
			opciones_menu.insertar_seleccion_en_opcion(k_opcion, k_seleccion, "--", seleccion["valor"]);
		}
	}

	//TODO: Eliminar esta dependencia: mejor pasar los valores en el constructor.

	//Escoger las opciones adecuadas según la configuración del usuario.
	const std::string val_tam_pantalla=std::to_string(config.acc_w_fisica_pantalla())+"x"+std::to_string(config.acc_h_fisica_pantalla());
	opciones_menu.seleccionar_opcion_por_valor(k_tam_pantalla, val_tam_pantalla);
	opciones_menu.seleccionar_opcion_por_valor(k_idioma, std::to_string(config.acc_idioma()));
	opciones_menu.seleccionar_opcion_por_valor(k_fondo, config.acc_fondo());

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

			if(clave==k_idioma)
			{
				int id_idioma=std::atoi(opciones_menu.valor_opcion(k_idioma).c_str());
				localizador.cambiar_idioma(id_idioma);
				traducir_interface();
				encolar_evento(new App::Eventos::Evento_cambio_idioma(id_idioma));
			}
			else if(clave==k_fondo)
			{
				const std::string fondo=opciones_menu.valor_opcion(k_fondo);
				encolar_evento(new App::Eventos::Evento_cambio_fondo(fondo));
			}
			else if(clave==k_tam_pantalla)
			{
				const auto partes=Herramientas_proyecto::explotar(opciones_menu.valor_opcion(k_tam_pantalla), 'x');
				int w=std::atoi(partes[0].c_str());
				int h=std::atoi(partes[1].c_str());
				encolar_evento(new App::Eventos::Evento_cambio_ventana(w, h));
			}

			generar_representacion_menu();
		}
	}
}

void Controlador_opciones::dibujar(DLibV::Pantalla& pantalla)
{
	escena.volcar(pantalla);
	rep_listado.volcar(pantalla);
}
