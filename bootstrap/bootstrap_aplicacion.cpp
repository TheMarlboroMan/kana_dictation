#include "bootstrap_aplicacion.h"

#include "../class/controladores/controlador_principal.h"
#include "../class/controladores/controlador_menu.h"
#include "../class/controladores/controlador_grupos.h"
#include "../class/controladores/controlador_opciones.h"
#include "../class/app/lector_kana.h"
#include "../class/app/lista_kanas.h"
#include "../class/app/eventos/interprete_eventos.h"

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
	pantalla.establecer_posicion(0, 0);

	//Establecer el fondo según valores de configuración.
	SDL_Surface * superficie=DLibV::Utilidades_graficas_SDL::cargar_imagen(config.acc_fondo().c_str(), pantalla.acc_ventana());
	DLibV::Gestor_texturas::obtener(App::Recursos_graficos::RGT_BACKGROUND)->reemplazar(superficie);
	
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
	Controlador_menu 		C_M(akashi, localizador, config.acc_longitud(), App::string_to_tipo_kana(config.acc_silabario()));
	Controlador_opciones 		C_O(akashi, localizador, pantalla);
	Controlador_grupos 		C_G(akashi, localizador, lista_kanas.obtener_grupos(), config.acc_kanas_activos());
	Controlador_principal 		C_P(akashi, kanas);

	//Registrar los controladores con el director de estados.
	Director_estados 		DI;
	DI.registrar_controlador(t_estados::MENU, C_M);
	DI.registrar_controlador(t_estados::PRINCIPAL, C_P);
	DI.registrar_controlador(t_estados::OPCIONES, C_O);
	DI.registrar_controlador(t_estados::GRUPOS, C_G);

	//TODO: Quizás para despertar al primer controlador podamos tener un método "DI->despertar()";
	//Despertar el primer controlador.

	Interface_controlador * 	IC=&C_M;
	App::Eventos::Interprete_eventos IE(pantalla, config);
	IC->despertar();

	//Preparar controladores...
	C_O.generar_menu(config);	//TODO: Quizás mejor lo podamos poner en el constructor.

	//TODO: En todos los "despertar" y "dormir" vamos a poner ahora también el montaje y desmontaje de la 
	//escena. Probablemente tengamos que tocar la escena en si.

	//Loop principal.
	while(kernel.loop(*IC))
	{
		if(DI.es_cambio_estado())
		{
			bool confirmar=true;
			switch(DI.acc_estado_actual())
			{
				case t_estados::GRUPOS: 
					//Comprobar que hay algún grupo seleccionado.
					confirmar=C_G.cantidad_seleccionados();
				break;
			}

			switch(DI.acc_estado_deseado())
			{	
				case t_estados::PRINCIPAL: 
					confirmar=preparar_kanas_principal(C_P, C_G, lista_kanas, config.acc_longitud(), App::string_to_tipo_kana(config.acc_silabario()));
				break;
			}

			if(confirmar) DI.confirmar_cambio_estado(IC);
			else DI.cancelar_cambio_estado();
		}
		
		DI.procesar_cola_eventos(IE);
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
