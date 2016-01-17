#include "bootstrap_aplicacion.h"

#include "../class/controladores/controlador_principal.h"
#include "../class/controladores/controlador_menu.h"
#include "../class/controladores/controlador_grupos.h"
#include "../class/controladores/controlador_opciones.h"
#include "../class/app/lector_kana.h"
#include "../class/app/lista_kanas.h"

using namespace App;

void App::loop_aplicacion(Kernel_app& kernel)
{
	//Preparar pantalla...
	auto& pantalla=kernel.acc_pantalla();
	auto& config=kernel.acc_configuracion();

	int wf=config.acc_w_fisica_pantalla(), 
		hf=config.acc_h_fisica_pantalla(),
		wl=config.acc_w_logica_pantalla(),
		hl=config.acc_h_logica_pantalla();

	pantalla.inicializar(wf, hf);
	pantalla.establecer_medidas_logicas(wl, hl);
	pantalla.establecer_modo_ventana(config.acc_modo_pantalla());
	
	//Ojo con retirar esto porque si no cargamos recursos va a estallar :D.
	kernel.mut_mostrar_fps(false);

	//Cargar fuentes.
	//TODO: Crear un gestor de fuentes que podamos usar para no tener que pasarlas por ahí.
	DLibV::Fuente_TTF akashi("data/fuentes/Akashi.ttf", 20);
	DLibV::Fuente_TTF kanas("data/fuentes/Kanas.ttf", 32);

	//Cargar Kanas...
	Lista_kanas lista_kanas;
	Lector_kana lector_kanas;
	lector_kanas.procesar_fichero("data/recursos/kanas.dnot", lista_kanas);

	//Cargar cadenas...
	Localizador localizador=Localizador("data/localizacion/strings");
	localizador.inicializar(config.acc_idioma());

	//Controladores e interfaces.
	Director_estados 		DI;
	Controlador_menu 		C_M(DI, akashi, localizador);
	Controlador_opciones 		C_O(DI, akashi, localizador);
	Controlador_grupos 		C_G(DI, akashi, localizador, lista_kanas.obtener_grupos());
	Controlador_principal 		C_P(DI, akashi, kanas);
	Interface_controlador * 	IC=&C_M;

	//TODO: Asignar al controlador de grupos los grupos que están marcados según la configuración.

	//Loop principal.
	while(kernel.loop(*IC))
	{
		if(DI.es_cambio_estado())
		{
			bool confirmar=true;

			switch(DI.acc_estado_actual())
			{
				case Director_estados::t_estados::MENU: break;
				case Director_estados::t_estados::PRINCIPAL: break;
				case Director_estados::t_estados::OPCIONES: break;
				case Director_estados::t_estados::GRUPOS: 
					//Comprobar que hay algún grupo seleccionado.
					if(!C_G.cantidad_seleccionados()) confirmar=false;
					//TODO: Guardar preferencias de grupos seleccionados en la configuración.
				break;
			}

			switch(DI.acc_estado_deseado())
			{	
				case Director_estados::t_estados::MENU: 
					IC=&C_M; 
				break;
				case Director_estados::t_estados::GRUPOS: 
					IC=&C_G; 
				break;
				case Director_estados::t_estados::OPCIONES: 
					IC=&C_O; 
				break;
				case Director_estados::t_estados::PRINCIPAL: 
					confirmar=preparar_kanas_principal(C_P, C_G, lista_kanas, C_M.acc_longitud_cadena(), C_M.acc_tipo_kana());
					if(confirmar) IC=&C_P;
				break;
			}

			if(confirmar) DI.confirmar_cambio_estado();
			else DI.cancelar_cambio_estado();
		}
	};
}

bool App::preparar_kanas_principal(Controlador_principal& C_P, const Controlador_grupos& C_G, const Lista_kanas& lista_kanas, int longitud, App::tipos_kana t)
{
	std::vector<Kana> kanas_temporales;
	const auto grupos=C_G.obtener_grupos_seleccionados();
		
	for(const auto& nombre : grupos)
	{
		const auto& v=lista_kanas.acc_grupo(nombre);
		kanas_temporales.insert(std::end(kanas_temporales), std::begin(v), std::end(v));
	}

	//TODO: Comprobar esto trasteando con el fichero de config.

	if(!kanas_temporales.size())
	{
		return false;
	}

	C_P.establecer_kanas(kanas_temporales);
	C_P.establecer_longitud_cadena(longitud);
	C_P.establecer_tipo_kana(t);
	C_P.generar_cadena_kanas();

	return true;
}
