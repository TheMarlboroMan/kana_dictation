#ifndef DIRECTOR_ESTADOS
#define DIRECTOR_ESTADOS

#include "../framework/base_director_estados.h"

class Director_estados:
	public Base_director_estados
{
	public:
	enum t_estados {MENU, PRINCIPAL, GRUPOS, OPCIONES};

	public:

	Director_estados()
		:Base_director_estados(t_estados::MENU)
	{}

	virtual bool validar_cambio_estado(int e)
	{
		return e >= MENU && e <= OPCIONES;
	}
};

#endif
