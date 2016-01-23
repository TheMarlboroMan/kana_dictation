#ifndef BASE_DIRECTOR_ESTADOS_H
#define BASE_DIRECTOR_ESTADOS_H

#include <stdexcept>
#include <memory>
#include <vector>
#include <functional>
#include <map>
#include "eventos.h"
#include "estados.h"
#include "controlador_interface.h"
#include "kernel.h"

/**
* Interface para el director de estados que es, en pocas palabras, la aplicación
* en si. Todos los recursos ajenos al Kernel deberían ser propiedad de un 
* director de estados, que los gestiona y los pasa a sus controladores.
*/

namespace DFramework
{

class Director_estados_interface
{
	public:

						Director_estados_interface(int e, std::function<bool(int)> f);

	virtual					~Director_estados_interface() 
	{}

	//Este método se ejecutará justo antes de confirmar un cambio de estado. Se 
	//puede usar para intercambiar información entre controladores justo antes
	//de despertar a uno nuevo. Se ejecuta antes de poner a dormir el estado
	//original y despertar el nuevo.

	virtual void				preparar_cambio_estado(int deseado, int actual)=0;
	void					iniciar(DFramework::Kernel& kernel);
	void					registrar_controlador(int indice, Controlador_interface& controlador);
	void					registrar_interprete_eventos(Interprete_eventos_interface& i) {IE=&i;}

	protected:
	
	std::map<int, Controlador_interface *>	controladores;
	Control_estados				estados;
	Cola_eventos				cola_eventos;

	private:

	bool					loop(DFramework::Kernel&);
	Controlador_interface *			IC;
	Interprete_eventos_interface *		IE;

};


}
#endif
