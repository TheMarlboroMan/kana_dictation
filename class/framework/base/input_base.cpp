#include "input_base.h"

void Input_base::turno()
{
	controles_sdl.recoger();
}

/*Input_base::tipo_par Input_base::obtener(unsigned int i) const
{
	tipo_par resultado=mapa.equal_range(i);
	return resultado;
}*/

Input_base::Resultado_lookup Input_base::obtener(unsigned int i) const
{
	//TODO: Esto puede dar problemas en el futuro si queremos usar el mismo
	//input para dos cosas distintas.

	//Vamos a cachear cada input en el dispositivo que le pertenece... Lookup es clave => tipo_input
	auto it=lookup.find(i);

	if(it!=lookup.end())
	{
		return it->second;
	}
	else
	{
		Resultado_lookup resultado(Resultado_lookup::NADA, 0);	

		auto it=mapa_teclado.find(i);
		if(it!=mapa_teclado.end())
		{
			resultado.mapa=Resultado_lookup::TECLADO;
			resultado.val=it->second;
		}
		else
		{
			it=mapa_raton.find(i);
			if(it!=mapa_raton.end()) 
			{
				resultado.mapa=Resultado_lookup::RATON;	
				resultado.val=it->second;
			}					
		}
	
		lookup.insert(std::make_pair(i,resultado));
		return resultado;
	}
}

bool Input_base::es_senal_salida() const
{
	return controles_sdl.es_senal_salida();
}

bool Input_base::es_input_down(unsigned int i) const
{
	Resultado_lookup rl=obtener(i);
	switch(rl.mapa)
	{
		case Resultado_lookup::TECLADO:
			if(controles_sdl.es_tecla_down(rl.val)) return true;
		break;
		case Resultado_lookup::RATON:
			if(controles_sdl.es_boton_down(rl.val)) return true;
		break;
		default: break;
	}

	return false;
}

bool Input_base::es_input_up(unsigned int i) const
{
	Resultado_lookup rl=obtener(i);
	switch(rl.mapa)
	{
		case Resultado_lookup::TECLADO:
			if(controles_sdl.es_tecla_up(rl.val)) return true;
		break;
		case Resultado_lookup::RATON:
			if(controles_sdl.es_boton_up(rl.val)) return true;
		break;
		default: break;
	}

	return false;
}

bool Input_base::es_input_pulsado(unsigned int i) const
{
	Resultado_lookup rl=obtener(i);
	switch(rl.mapa)
	{
		case Resultado_lookup::TECLADO:
			if(controles_sdl.es_tecla_pulsada(rl.val)) return true;
		break;
		case Resultado_lookup::RATON:
			if(controles_sdl.es_boton_pulsado(rl.val)) return true;
		break;
		default: break;
	}

	return false;
}
