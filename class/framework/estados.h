#ifndef CONTROL_ESTADOS_FRAMEWORK_K
#define CONTROL_ESTADOS_FRAMEWORK_K

#include <exception>
#include <iostream>
#include <functional>

/*
* Pequeña clase de control de estados: básicamente controla con un entero el
* estado actual y el estado al que se desea cambiar. Su única finalidad es
* eliminar dependencias cíclicas: tanto el director como los controladores
* dependen de esta clase.
*/

namespace DFramework
{

class Control_estados
{
	public:

	Control_estados(int e, std::function<bool(int)> f)
		:validar_estado(f), actual(e), deseado(e)
	{}


	void				validar_y_cambiar_estado(int v)
	{
		if(!validar_estado(v)) throw std::runtime_error("Control_estados recibe estado erróneo");
		deseado=v;
	}
	
	bool					es_cambio_estado() const {return actual!=deseado;}
	void					confirmar_cambio_estado() {actual=deseado;}
	void					cancelar_cambio_estado() {deseado=actual;}
	int					acc_estado_deseado() const {return deseado;}
	int					acc_estado_actual() const {return actual;}

	private:

	std::function<bool(int)>		validar_estado;
	int 					actual, 
						deseado;
};

}
#endif
