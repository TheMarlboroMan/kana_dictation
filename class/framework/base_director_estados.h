#ifndef BASE_DIRECTOR_ESTADOS_H
#define BASE_DIRECTOR_ESTADOS_H

#include <stdexcept>
#include <memory>
#include <vector>
#include "../framework/eventos.h"


class Base_director_estados
{

	public:

	Base_director_estados(int e)
		:actual(e), deseado(e)
	{}

	~Base_director_estados() {}

	bool es_cambio_estado() const {return actual!=deseado;}

	void procesar_cola_eventos(Interface_interprete_eventos& i)
	{
		//TODO: Estamos implementando el visitor pattern aquí... 
		//No lo quiero para nada. Hay que mantener mucho en
		//varios ficheros y prefiero tener que tocar sólo los
		//ficheros del intérprete y eventos.
		for(auto& ev : eventos)
		{
			ev.recibir_interprete(i);
			//TODO...
		}
	}

	void solicitar_cambio_estado(int v) 
	{
		if(!validar_cambio_estado(v)) throw std::runtime_error("Director_estados recibe estado erróneo");
		deseado=v;
	}

	void confirmar_cambio_estado() {actual=deseado;}
	void cancelar_cambio_estado() {deseado=actual;}

	void encolar_evento(Evento_director_estados_base * ev) 
	{
		cola_eventos.push_back(std::unique_ptr<Evento_director_estados_base>(ev));
	}

	int acc_estado_deseado() {return deseado;}
	int acc_estado_actual() {return actual;}

	virtual bool validar_cambio_estado(int)=0;

	private:
	
	std::vector<std::unique_ptr<Evento_director_estados_base>>		cola_eventos;
	int actual, deseado;

};

#endif
