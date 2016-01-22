#include "bootstrap_aplicacion.h"

#include "../class/controladores/controlador_principal.h"
#include "../class/controladores/controlador_menu.h"
#include "../class/controladores/controlador_grupos.h"
#include "../class/controladores/controlador_opciones.h"
#include "../class/app/lector_kana.h"
#include "../class/app/lista_kanas.h"
#include "../class/app/eventos/interprete_eventos.h"
#include "../class/app/configuracion_ejercicio.h"

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

	//Creación del objeto de datos de ejercicio.
	App::Configuracion_ejercicio	configuracion_ejercicio(config.acc_longitud(), App::string_to_tipo_kana(config.acc_silabario()), App::string_to_direccion_traduccion(config.acc_direccion()));

	//Control de eventos.
	App::Eventos::Interprete_eventos IE(pantalla, config, configuracion_ejercicio);

	//Establecer el fondo según valores de configuración.
	//TODO: Disparar un evento, mejor.
	DLibV::Imagen img(config.acc_fondo().c_str(), pantalla.acc_ventana());
	DLibV::Gestor_texturas::obtener(App::Recursos_graficos::RGT_BACKGROUND)->reemplazar(img);

	//Controladores e interfaces.
	Controlador_menu 		C_M(akashi, localizador, configuracion_ejercicio);
	Controlador_opciones 		C_O(akashi, localizador, pantalla, config);
	Controlador_grupos 		C_G(akashi, localizador, lista_kanas.obtener_grupos(), config.acc_kanas_activos());
	Controlador_principal 		C_P(akashi, kanas, configuracion_ejercicio);

	//Registrar componentes...
		//TODO: Crearlo con referencias a config y lista kanas.
		//TODO: Actualizar makefile!!!.
		//Trastear el método de cambio de estado para que cargue la info.
		//TODO: WARNING... El director de estados NO SABE el tipo del controlador que tiene!!!. Aunque los
		//tenga registrados no podría llamar a los métodos de turno sin un static cast. Todo
		//lo que el director sabe es que son Interface_controlador...

	Director_estados 		DE();
	kernel.establecer_director_estados(DE);
	kernel.establecer_interprete_eventos(IE);
	kernel.registrar_controlador(t_estados::MENU, C_M);
	kernel.registrar_controlador(t_estados::PRINCIPAL, C_P);
	kernel.registrar_controlador(t_estados::OPCIONES, C_O);
	kernel.registrar_controlador(t_estados::GRUPOS, C_G);
	kernel.preparar_loop();

	//TODO... Ahora que tenemos al "director de estados" dentro del kernel
	//podemos infiltrarlo con un método virtual "on_state_change" y hacer
	//este tipo de operaciones. Tendríamos que registrar la lista de kanas
	//y la configuración con el director, pero ya tendríamos menos mierda
	//en el bootstrap.

	preparar_kanas_principal(C_P, C_G, lista_kanas, config.acc_longitud(), App::string_to_tipo_kana(config.acc_silabario()), App::string_to_direccion_traduccion(config.acc_direccion()));

	//Loop principal.
	while(kernel.loop());
}

void App::preparar_kanas_principal(Controlador_principal& C_P, const Controlador_grupos& C_G, const Lista_kanas& lista_kanas, int longitud, App::tipos_kana t, App::direcciones_traduccion dir)
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
		throw std::runtime_error("No hay kanas seleccionados: imposible preparar");
	}

	C_P.establecer_kanas(kanas_temporales);
	C_P.generar_cadena_kanas();
}
