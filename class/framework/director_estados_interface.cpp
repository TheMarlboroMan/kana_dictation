#include "director_estados_interface.h"

using namespace DFramework;

Director_estados_interface::Director_estados_interface(int e, std::function<bool(int)> f)
	:estados(e, f), IC(nullptr), IE(nullptr)
{

}

void Director_estados_interface::iniciar(DFramework::Kernel& kernel)
{
	IC=controladores[estados.acc_estado_actual()];
	IC->despertar();
	while(loop(kernel));
}

void Director_estados_interface::registrar_controlador(int indice, Controlador_interface& controlador)
{
	if(controladores.count(indice))
	{
		//TODO: Otro tipo de excepción??
		throw std::runtime_error("Se intenta registrar el controlador con indice duplicado");
	}
	
	controladores[indice]=&controlador;
	controlador.inyectar_cola_eventos(cola_eventos);
	controlador.inyectar_control_estados(estados);
}

bool Director_estados_interface::loop(DFramework::Kernel& kernel)
{
	//Aquí se mide el tiempo desde el último paso por este loop...
	kernel.iniciar_paso_loop();
	float paso_delta=kernel.acc_paso_delta();

	auto& input=kernel.acc_input();

	IC->preloop(input, paso_delta);

	//Aquí se consume el tiempo desde el último paso en bloques de "paso_delta".
	while(kernel.consumir_loop(paso_delta))
	{
		input.turno();

		IC->loop(input, paso_delta);

		kernel.procesar_cola_sonido();

		if(IC->es_romper_loop()) 
		{
			break;
		}

		if(estados.es_cambio_estado()) 
		{
			if(!IC->es_posible_abandonar_estado())
			{
				estados.cancelar_cambio_estado();
			}
			else
			{
				preparar_cambio_estado(estados.acc_estado_deseado(), estados.acc_estado_actual());
				if(IE!=nullptr && cola_eventos.size()) cola_eventos.procesar_cola_completa(*IE);
				break;
			}
		}
	
		if(IE!=nullptr && cola_eventos.size()) cola_eventos.procesar_cola_completa(*IE);
	}

	if(estados.es_cambio_estado())
	{
		//Confirmación del cambio de estados.
		int estado_original=estados.acc_estado_actual();
		int estado_deseado=estados.acc_estado_deseado();

		controladores[estado_original]->dormir();
		controladores[estado_deseado]->despertar();

		IC=controladores[estado_deseado];

		estados.confirmar_cambio_estado();
	}
	else
	{
		IC->postloop(input, paso_delta);

		kernel.turno_fps();

		auto& pantalla=kernel.acc_pantalla();

		IC->dibujar(pantalla);

/*
		std::string fps="FPS:"+std::to_string(controlador_fps.acc_frames_contados())+"\n"+IC->acc_debug();
		DLibV::Representacion_texto_auto txt(DLibV::Gestor_superficies::obtener(acc_recurso_fps()), fps);
		txt.hacer_estatica();
		txt.establecer_posicion(pantalla.acc_w()-128, 6);
		txt.volcar(pantalla);
*/
		pantalla.actualizar();
	}

	return !IC->es_abandonar_aplicacion();
}
