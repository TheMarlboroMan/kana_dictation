#ifndef PROYECTO_SDL2_DERIVADA_LOCALIZADOR_H
#define PROYECTO_SDL2_DERIVADA_LOCALIZADOR_H

/*Clase de localización de idiomas... Es muy sencillo de usar, básicamente
lo instanciamos de este modo:

Localizador loc=Localizador("ruta/a/archivos");
loc.inicializar(0); //Donde 0 es el identificador de idioma.

Los archivos, por convención, se llaman nombre_archivo.#id_idioma.dat, y son
archivos de texto plano en los que se abren y cierran tags de texto con la 
siguiente estructura.

<#clave_numerica#$>Texto<#>

Por ejemplo.

<1$>Texto uno<#>
<2$>Texto dos<#>
<100$>Texto cien<#>

Para obtener un texto es tan fácil como loc.obtener(#id_texto#), que devuelve
un std::string con el texto de turno. Si no se encuentra el texto devolverá
la cadena definida como c_no_encontrado. Si no se ha cargado el localizador
devolverá la cadena definida como c_no_cargado.
*/

#include <base/localizador_base.h>

namespace App
{

class Localizador
	:public Herramientas_proyecto::Localizador_base
{
	private:
	Herramientas_proyecto::t_cadena ruta;
	Herramientas_proyecto::t_cadena c_no_cargado;
	Herramientas_proyecto::t_cadena c_no_encontrado;

	protected:
	Herramientas_proyecto::t_lista_nombres_archivo obtener_lista_archivos();
	Herramientas_proyecto::t_cadena const& cadena_no_cargado() const {return c_no_cargado;}
	Herramientas_proyecto::t_cadena const& cadena_no_encontrado() const {return c_no_encontrado;}

	public:

	void inicializar(unsigned short int p_idioma);

	Localizador(unsigned short int p_idioma=0);
	Localizador(const Herramientas_proyecto::t_cadena& p_ruta, unsigned short int p_idioma=0);
};
}
#endif
