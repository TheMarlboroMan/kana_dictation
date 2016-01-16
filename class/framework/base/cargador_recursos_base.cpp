#include "cargador_recursos_base.h"

Cargador_recursos_base::Cargador_recursos_base()
	:pantalla(nullptr)
{

}

Cargador_recursos_base::~Cargador_recursos_base() 
{

}

void Cargador_recursos_base::procesar(const std::vector<std::string>& entradas, void (Cargador_recursos_base::*procesar_valores)(const std::vector<std::string>&))
{
	const char separador='\t';
	for(auto& linea : entradas)
	{
		(this->*procesar_valores)(DLibH::Herramientas::explotar(linea, separador));
	}
}

void Cargador_recursos_base::generar_recursos_texturas(DLibV::Pantalla &p)
{
	DLibV::Gestor_texturas::vaciar();
	pantalla=&p;
	try
	{

		procesar(obtener_entradas_texturas(), &Cargador_recursos_base::procesar_entrada_textura);
	}
	catch(Excepcion_carga_recursos& e)
	{
		LOG<<"ERROR: No se ha cargado el archivo de texturas"<<std::endl;
	}
	pantalla=nullptr;
}

void Cargador_recursos_base::generar_recursos_superficies(DLibV::Pantalla &p)
{
	pantalla=&p;
	DLibV::Gestor_superficies::vaciar();
	try
	{
		procesar(obtener_entradas_superficies(), &Cargador_recursos_base::procesar_entrada_superficie);
	}
	catch(Excepcion_carga_recursos& e)
	{
		LOG<<"ERROR: No se ha cargado el archivo de superficies"<<std::endl;
	}
}

void Cargador_recursos_base::generar_recursos_audio()
{
	//OJO: Vacia sonido y música.
	DLibA::Gestor_recursos_audio::liberar();
	try
	{
		procesar(obtener_entradas_audio(), &Cargador_recursos_base::procesar_entrada_audio);
	}
	catch(Excepcion_carga_recursos& e)
	{
		LOG<<"ERROR: No se ha localizado el archivo de recursos de audio"<<std::endl;
	}
	pantalla=nullptr;
}

void Cargador_recursos_base::generar_recursos_musica()
{
	try
	{
		procesar(obtener_entradas_musica(), &Cargador_recursos_base::procesar_entrada_musica);
	}
	catch(Excepcion_carga_recursos& e)
	{
		LOG<<"ERROR: No se ha localizado el archivo de recursos de música"<<std::endl;
	}
}

void Cargador_recursos_base::procesar_entrada_textura(const std::vector<std::string>& valores)
{
	if(valores.size()!=6) LOG<<"ERROR: No hay 6 parametros para recursos textura, en su lugar "<<valores.size()<<std::endl;
	else 
	{
		unsigned int indice=std::atoi(valores[0].c_str());
		std::string ruta=valores[1];
		unsigned int transparencia=std::atoi(valores[2].c_str());

		SDL_Surface * superficie=DLibV::Utilidades_graficas_SDL::cargar_imagen(ruta.c_str(), pantalla->acc_ventana());

		if(!superficie)
		{
			LOG<<"ERROR: Cargador recursos base no se ha podido cargar superficie para textura en "<<ruta<<std::endl;
		}
		else
		{
			if(transparencia)
			{
				unsigned int r=std::atoi(valores[3].c_str());
				unsigned int g=std::atoi(valores[4].c_str());
				unsigned int b=std::atoi(valores[5].c_str());

				SDL_SetColorKey(superficie, SDL_TRUE, SDL_MapRGB(superficie->format, r, g, b));
			}
			
			DLibV::Textura * t=new DLibV::Textura(pantalla->acc_renderer(), superficie);

			if(DLibV::Gestor_texturas::insertar(indice, t)==-1)
			{
				LOG<<"ERROR: No se ha podido insertar textura "<<indice<<" en "<<ruta<<std::endl;
			}	
		}
	}			
}

void Cargador_recursos_base::procesar_entrada_superficie(const std::vector<std::string>& valores)
{
	if(valores.size()!=6) LOG<<"ERROR: No hay 6 parametros para recursos superficie, en su lugar "<<valores.size()<<std::endl;
	else 
	{
		unsigned int indice=std::atoi(valores[0].c_str());
		std::string ruta=valores[1];
		unsigned int transparencia=std::atoi(valores[2].c_str());

		SDL_Surface * superficie=DLibV::Utilidades_graficas_SDL::cargar_imagen(ruta.c_str(), pantalla->acc_ventana());

		if(!superficie)
		{
			LOG<<"ERROR: Cargador recursos base no se ha podido cargar superficie para textura en "<<ruta<<std::endl;
		}
		else
		{
			if(transparencia)
			{
				unsigned int r=std::atoi(valores[3].c_str());
				unsigned int g=std::atoi(valores[4].c_str());
				unsigned int b=std::atoi(valores[5].c_str());

				SDL_SetColorKey(superficie, SDL_TRUE, SDL_MapRGB(superficie->format, r, g, b));
			}
			

			DLibV::Imagen * t=new DLibV::Imagen(superficie);

			if(DLibV::Gestor_superficies::insertar(indice, t)==-1)
			{
				LOG<<"ERROR: No se ha podido insertar superficie "<<indice<<" en "<<ruta<<std::endl;
			}	
		}
	}			
}


void Cargador_recursos_base::procesar_entrada_audio(const std::vector<std::string>& valores)
{
	if(valores.size()!=2) LOG<<"ERROR: No hay 2 parametros para recursos audio, en su lugar "<<valores.size()<<std::endl;
	else 
	{
		unsigned int indice=std::atoi(valores[0].c_str());
		std::string ruta=valores[1];

		if(DLibA::Gestor_recursos_audio::insertar_sonido(indice, ruta.c_str())==-1)
		{
			LOG<<"ERROR: No se ha podido insertar recurso audio "<<indice<<" en "<<ruta<<std::endl;
		}	
	}			
}

void Cargador_recursos_base::procesar_entrada_musica(const std::vector<std::string>& valores)
{
	if(valores.size()!=2) LOG<<"ERROR: No hay 2 parametros para recursos musica, en su lugar "<<valores.size()<<std::endl;
	else 
	{
		unsigned int indice=std::atoi(valores[0].c_str());
		std::string ruta=valores[1];

		if(DLibA::Gestor_recursos_audio::insertar_musica(indice, ruta.c_str())==-1)
		{
			LOG<<"ERROR: No se ha podido insertar recurso musica "<<indice<<" en "<<ruta<<std::endl;
		}	
	}			
}

std::vector<std::string> Cargador_recursos_base::obtener_entradas_desde_ruta(const std::string& ruta) const
{	
	Herramientas_proyecto::Lector_txt L(ruta, '#');
	std::vector<std::string> resultado;

	if(!L)
	{
		throw Excepcion_carga_recursos();
	}

	while(true)
	{
		std::string linea=L.leer_linea();
		if(!L) break;
		resultado.push_back(linea);
	}

	return resultado;
}
