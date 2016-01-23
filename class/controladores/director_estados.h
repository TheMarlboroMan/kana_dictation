#ifndef DIRECTOR_ESTADOS
#define DIRECTOR_ESTADOS

#include <memory>
#include "../framework/director_estados_interface.h"
#include "estados_controladores.h"
#include "controlador_grupos.h"
#include "controlador_menu.h"
#include "controlador_opciones.h"
#include "controlador_principal.h"
#include "../app/lector_kana.h"
#include "../app/lista_kanas.h"
#include "../app/configuracion_ejercicio.h"
#include "../app/localizador.h"
#include "../app/eventos/interprete_eventos.h"

/*
* El director de estados es la aplicación: los recursos externos al Kernel
* y los métodos propios que no son de los controladores.
*/

namespace App
{

class Director_estados:
	public DFramework::Director_estados_interface
{
	public:

							Director_estados(DFramework::Kernel& kernel, App::App_config& config);

	virtual void					preparar_cambio_estado(int deseado, int actual);

	private:

	void						registrar_controladores(const App::App_config& config);

	App::Configuracion_ejercicio			configuracion_ejercicio;
	App::Eventos::Interprete_eventos 		IE;

	//TODO: Crear un gestor de fuentes que podamos usar para no tener que pasarlas por ahí.
	DLibV::Fuente_TTF 				akashi;
	DLibV::Fuente_TTF 				kanas;
	Lista_kanas 					lista_kanas;
	Lector_kana 					lector_kanas;
	Localizador 					localizador;

	std::unique_ptr<Controlador_grupos>		CG;
	std::unique_ptr<Controlador_menu>		CM;
	std::unique_ptr<Controlador_opciones>		CO;
	std::unique_ptr<Controlador_principal>		CP;
};

}
#endif
