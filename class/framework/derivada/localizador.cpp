#include "localizador.h"

Localizador::Localizador(unsigned short int p_idioma)
	:Herramientas_proyecto::Localizador_base(p_idioma), ruta(""),
	c_no_cargado("ERROR 00"), c_no_encontrado("ERROR 01")
{}

Localizador::Localizador(const Herramientas_proyecto::t_cadena& p_ruta, unsigned short int p_idioma)
	:Herramientas_proyecto::Localizador_base(p_idioma), ruta(p_ruta),
	c_no_cargado("ERROR 00"), c_no_encontrado("ERROR 01")
{
	Localizador_base::inicializar();
}

Herramientas_proyecto::t_lista_nombres_archivo Localizador::obtener_lista_archivos()
{
	Herramientas_proyecto::t_lista_nombres_archivo resultado;

	resultado.push_back(ruta);

	return resultado;
}

void Localizador::inicializar(unsigned short int p_idioma)
{		
	Herramientas_proyecto::Localizador_base::cambiar_idioma(p_idioma);
}
