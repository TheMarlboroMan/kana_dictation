#include "input.h"

using namespace DFramework;

void Input::turno()
{
	controles_sdl.recoger();
}

Input::Resultado_lookup Input::obtener(unsigned int i) const
{
	//TODO: Esto puede dar problemas en el futuro si queremos usar el mismo
	//input para dos cosas distintas.

	//Vamos a cachear cada input en el dispositivo que le pertenece... 

	auto it=lookup.find(i);

	if(it!=lookup.end())
	{
		return it->second;
	}
	else
	{
		Resultado_lookup resultado(Resultado_lookup::NADA);

		auto f=[&resultado, this, i](const tipo_mapa& mapa, unsigned int tipo)
		{
			resultado.mapa=tipo;
			auto it=mapa.equal_range(i);
			for(auto r=it.first; r!=it.second; ++r)
				resultado.val.push_back(r->second);

			lookup.insert(std::make_pair(i,resultado));
		};

		if(mapa_teclado.count(i))
		{
			f(mapa_teclado, Resultado_lookup::TECLADO); 
		}
		else if(mapa_raton.count(i))
		{
			f(mapa_raton, Resultado_lookup::RATON); 
		}

		return resultado;
	}
}

bool Input::es_senal_salida() const
{
	return controles_sdl.es_senal_salida();
}

bool Input::es_input_down(unsigned int i) const
{
	Resultado_lookup rl=obtener(i);
	switch(rl.mapa)
	{
		case Resultado_lookup::TECLADO:
			for(auto val : rl.val) 
				if(controles_sdl.es_tecla_down(val)) return true;
		break;
		case Resultado_lookup::RATON:
			for(auto val : rl.val) 
				if(controles_sdl.es_boton_down(val)) return true;
		break;
		default: break;
	}

	return false;
}

bool Input::es_input_up(unsigned int i) const
{
	Resultado_lookup rl=obtener(i);
	switch(rl.mapa)
	{
		case Resultado_lookup::TECLADO:
			for(auto val : rl.val) 
				if(controles_sdl.es_tecla_up(val)) return true;
		break;
		case Resultado_lookup::RATON:
			for(auto val : rl.val) 
				if(controles_sdl.es_boton_up(val)) return true;
		break;
		default: break;
	}

	return false;
}

bool Input::es_input_pulsado(unsigned int i) const
{
	Resultado_lookup rl=obtener(i);
	switch(rl.mapa)
	{
		case Resultado_lookup::TECLADO:
			for(auto val : rl.val) 
				if(controles_sdl.es_tecla_pulsada(val)) return true;
		break;
		case Resultado_lookup::RATON:
			for(auto val : rl.val)
				if(controles_sdl.es_boton_pulsado(val)) return true;
		break;
		default: break;
	}

	return false;
}

void Input::configurar(const std::vector<Par_input>& v)
{
	for(const auto& i : v)
	{
		switch(i.tipo)
		{
			case Par_input::tipos::teclado:
				mapa_teclado.insert(std::make_pair(i.clave, i.sdl_clave));			
			break;

			case Par_input::tipos::raton:
				mapa_raton.insert(std::make_pair(i.clave, i.sdl_clave));
			break;
		}
	}
}
