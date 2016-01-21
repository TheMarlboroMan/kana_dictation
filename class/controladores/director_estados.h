#ifndef DIRECTOR_ESTADOS
#define DIRECTOR_ESTADOS

#include "../framework/base_director_estados.h"
#include "estados_controladores.h"

class Director_estados:
	public Base_director_estados
{
	public:

	Director_estados()
		:Base_director_estados(t_estados::MENU, std::function<bool(int)>([](int v){return v >= MENU && v < MAX_ESTADOS;}))
	{}
};

#endif
