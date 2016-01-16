#include "bootstrap_aplicacion.h"

#include "../class/controladores/controlador_principal.h"
#include "../class/controladores/controlador_menu.h"
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
	Controlador_principal 		C_P(DI, akashi, kanas);
	Interface_controlador * 	IC=&C_M;

	//TODO: 
	std::vector<Kana> kanas_vocales=lista_kanas.acc_grupo("1 : Vowels"),
		kanas_k=lista_kanas.acc_grupo("2 : K"),
		kanas_s=lista_kanas.acc_grupo("3 : S"),
		kanas_t=lista_kanas.acc_grupo("4 : T"),
		kanas_n=lista_kanas.acc_grupo("5 : N");

	std::vector<Kana> kanas_temporales;
	kanas_temporales.insert(std::end(kanas_temporales), std::begin(kanas_vocales), std::end(kanas_vocales));
	kanas_temporales.insert(std::end(kanas_temporales), std::begin(kanas_k), std::end(kanas_k));
	kanas_temporales.insert(std::end(kanas_temporales), std::begin(kanas_s), std::end(kanas_s));
	kanas_temporales.insert(std::end(kanas_temporales), std::begin(kanas_t), std::end(kanas_t));
	kanas_temporales.insert(std::end(kanas_temporales), std::begin(kanas_n), std::end(kanas_n));

	C_P.establecer_kanas(kanas_temporales);
	C_P.establecer_longitud_cadena(20);

	//Loop principal.
	while(kernel.loop(*IC))
	{
		if(DI.es_cambio_estado())
		{
			switch(DI.acc_estado_actual())
			{
				case Director_estados::t_estados::MENU: break;
				case Director_estados::t_estados::PRINCIPAL: break;
			}

			switch(DI.acc_estado_deseado())
			{
				case Director_estados::t_estados::MENU: 
					IC=&C_M; 
				break;
				case Director_estados::t_estados::PRINCIPAL: 
					IC=&C_P; 
					C_P.generar_cadena_kanas();
				break;
			}

			DI.confirmar_cambio_estado();
		}
	};
}
