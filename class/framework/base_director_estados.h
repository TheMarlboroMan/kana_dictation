#ifndef BASE_DIRECTOR_ESTADOS_H
#define BASE_DIRECTOR_ESTADOS_H

#include <stdexcept>
#include <memory>
#include <vector>
#include <functional>
#include <map>
#include "../framework/eventos.h"
#include "estados.h"
#include "interface_controlador.h"


class Base_director_estados
{
	public:

						Base_director_estados(int e, std::function<bool(int)> f)
		:estados(e, f)
	{}

						~Base_director_estados() 
	{}

	bool					es_cambio_estado() const {return estados.es_cambio_estado();}

	void					confirmar_cambio_estado(Interface_controlador *& IC) 
	{
		int estado_original=estados.acc_estado_actual();
		int estado_deseado=estados.acc_estado_deseado();

		controladores[estado_original]->dormir();
		controladores[estado_deseado]->despertar();

		IC=controladores[estado_deseado];

		estados.confirmar_cambio_estado();
	}

	void					cancelar_cambio_estado() {estados.cancelar_cambio_estado();}

	int					acc_estado_deseado() const {return estados.acc_estado_deseado();}
	int					acc_estado_actual() const {return estados.acc_estado_actual();}

	void					procesar_cola_eventos(Interface_interprete_eventos& i) {cola_eventos.procesar_cola_completa(i);}
	void					encolar_evento(Evento_director_estados_base * ev) {cola_eventos.encolar_evento(ev);}

	void					registrar_controlador(int indice, Interface_controlador& controlador)
	{
		if(controladores.count(indice))
		{
			throw std::runtime_error("Se intenta registrar el controlador con indice duplicado");
		}
		
		controladores[indice]=&controlador;
		controlador.inyectar_cola_eventos(cola_eventos);
		controlador.inyectar_control_estados(estados);
	}

	private:
	
	std::map<int, Interface_controlador *>	controladores;
	Control_estados				estados;
	Cola_eventos				cola_eventos;

};

#endif
