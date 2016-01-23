#include "director_estados.h"
#include <herramientas/log_base/log_base.h>
#include "../app/recursos.h"

using namespace App;

extern DLibH::Log_base LOG;

Director_estados::Director_estados(DFramework::Kernel& kernel, App::App_config& config)
	:Director_estados_interface(t_estados::MENU, std::function<bool(int)>([](int v){return v >= MENU && v < MAX_ESTADOS;})),
	configuracion_ejercicio(config.acc_longitud(), App::string_to_tipo_kana(config.acc_silabario()), App::string_to_direccion_traduccion(config.acc_direccion())),
	IE(kernel.acc_pantalla(), config, configuracion_ejercicio),
	akashi("data/fuentes/Akashi.ttf", 20),
	kanas("data/fuentes/Kanas.ttf", 32),
	localizador("data/localizacion/strings")
{
	//Preparar pantalla...
	auto& pantalla=kernel.acc_pantalla();

	int wf=config.acc_w_fisica_pantalla(), 
		hf=config.acc_h_fisica_pantalla(),
		wl=config.acc_w_logica_pantalla(),
		hl=config.acc_h_logica_pantalla();

	pantalla.inicializar(wf, hf);
	pantalla.establecer_medidas_logicas(wl, hl);
	pantalla.establecer_modo_ventana(config.acc_modo_pantalla());

	//Cargar Kanas...
	lector_kanas.procesar_fichero("data/recursos/kanas.dnot", lista_kanas);

	//Cargar cadenas...
	localizador.inicializar(config.acc_idioma());

	//Establecer el fondo según valores de configuración.
	//TODO: Disparar un evento, mejor.
	DLibV::Imagen img(config.acc_fondo().c_str(), pantalla.acc_ventana());
	DLibV::Gestor_texturas::obtener(App::Recursos_graficos::RGT_BACKGROUND)->reemplazar(img);

	registrar_controladores(config);
}

void Director_estados::registrar_controladores(const App::App_config& config)
{
	registrar_interprete_eventos(IE);

	CM.reset(new Controlador_menu(akashi, localizador, configuracion_ejercicio));
	CO.reset(new Controlador_opciones(akashi, localizador, config));
	CG.reset(new Controlador_grupos(akashi, localizador, lista_kanas.obtener_grupos(), config.acc_kanas_activos()));
	CP.reset(new Controlador_principal(akashi, kanas, configuracion_ejercicio));

	registrar_controlador(t_estados::MENU, *CM.get());
	registrar_controlador(t_estados::OPCIONES, *CO.get());
	registrar_controlador(t_estados::GRUPOS, *CG.get());
	registrar_controlador(t_estados::PRINCIPAL, *CP.get());


}

void Director_estados::preparar_cambio_estado(int deseado, int actual)
{

}
