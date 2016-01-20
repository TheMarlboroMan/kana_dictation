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

	/**** TODO TODO TODO */
	/**** TODO TODO TODO */
	/**** TODO TODO TODO */

	struct Evento_uno:
		public Evento_director_estados_base
	{
		virtual int tipo_evento() const {return 1;}
		std::string val;
		Evento_uno(const std::string& v) {val=v;}
	};

	struct Evento_dos:
		public Evento_director_estados_base
	{
		virtual int tipo_evento() const {return 2;}
		int val_a, val_b;
		Evento_dos(int a, int b) {val_a=a; val_b=b;}
	};

	class Interprete_eventos:
		public Interface_interprete_eventos
	{
		public:
		virtual void interpretar_evento(const Evento_director_estados_base& ev)
		{
			switch(ev.tipo_evento())
			{
				case 1: interpretar_uno(static_cast<const Evento_uno&>(ev)); break;
				case 2: interpretar_dos(static_cast<const Evento_dos&>(ev)); break;
			}
		}

		private:

		void interpretar_uno(const Evento_uno& ev)
		{
			std::cout<<"LEYENDO EL EVENTO UNO "<<ev.val<<std::endl;
		}

		void interpretar_dos(const Evento_dos& ev)
		{
			std::cout<<"LEYENDO EL EVENTO DOS "<<ev.val_a<<" "<<ev.val_b<<std::endl;
		}
	}I_E;

	/**** TODO TODO TODO */
	/**** TODO TODO TODO */
	/**** TODO TODO TODO */

	Director_estados 		DI;
	Controlador_menu 		C_M(DI, akashi, localizador);
	Controlador_opciones 		C_O(DI, akashi, localizador, pantalla);
	C_O.generar_menu(config);
	Controlador_grupos 		C_G(DI, akashi, localizador, lista_kanas.obtener_grupos(), config.acc_kanas_activos());
	Controlador_principal 		C_P(DI, akashi, kanas);
	Interface_controlador * 	IC=&C_M;

	//Loop principal.
	while(kernel.loop(*IC))
	{
		if(DI.es_cambio_estado())
		{
			bool confirmar=true;

			switch(DI.acc_estado_actual())
			{
				case Director_estados::t_estados::MENU: 
					DI.encolar_evento(new Evento_uno("HOLA"));
					DI.encolar_evento(new Evento_dos(1, 2));
				break;
				case Director_estados::t_estados::PRINCIPAL: 
					DI.encolar_evento(new Evento_dos(3, 4));
				break;
				case Director_estados::t_estados::OPCIONES: 
					DI.encolar_evento(new Evento_uno("ADIOS"));

					//TODO: Esto ya no sería necesario aquí y podría ir en el intérprete de eventos.
					config.mut_idioma(C_O.obtener_idioma());
					config.mut_w_fisica_pantalla(C_O.obtener_w_ventana());
					config.mut_h_fisica_pantalla(C_O.obtener_h_ventana());
					config.mut_fondo(C_O.obtener_fondo());
					config.grabar();
					C_M.traducir_interface();
				break;
				case Director_estados::t_estados::GRUPOS: 
					//Comprobar que hay algún grupo seleccionado.
					if(!C_G.cantidad_seleccionados()) 
					{
						confirmar=false;
					}
					else 
					{
						config.mut_kanas_activos(C_G.producir_cadena_kanas_activos());
						config.grabar();
					}
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
		
		DI.procesar_cola_eventos(I_E);
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
