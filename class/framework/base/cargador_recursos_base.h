#ifndef CARGADOR_RECURSOS_BASE_H
#define CARGADOR_RECURSOS_BASE_H

/*Un cargador de recursos gráficos y de audio. Para cargar los recursos usa
ficheros en disco, localizados en las rutas de turno. Tiene un rollo autoload,
bien para proyectos pequeños, mal para proyectos grandes, puesto que lo que
cargas se queda para siempre cargado.

Estos ficheros tienen una estructura concreta, N valores separados por 
tabuladores.

Aunque se pueden generar texturas a partir de superficies, lo vamos a separar
todo por aquí. Para proyectos más grandes haríamos gestores custom :).

Para graficos (texturas y superficies).

#indice	ruta	transparencia	rtrans	gtrans	btrans
1	data/imagenes/fuente_defecto.png	1	0	0	0

Donde "transparencia" indica si hay transparencia y r, g y btrans indican el 
color de pixel transparente.

Para audio:
#indice	#ruta
1	data/sonidos/defecto.ogg

Al usar este cargador se cargan todos los recursos directamente en memoria. Esto
puede estar bien para aplicaciones pequeñas, pero si hay muchos gráficos mejor
que usemos métodos alternativos para cargarlos y descargarlos según sea 
necesario.

Otra cosa más, si vamos a usarlo no deberíamos almacenar nunca referencias
ni punteros a los recursos, puesto que pueden vaciarse. En su lugar, los 
obtenemos siempre mediante los gestores de turno.
*/

#include <stdexcept>
#include <libDan2.h>
#include <class/lector_txt.h>

extern DLibH::Log_base LOG;

class Cargador_recursos_base
{
	private:

	DLibV::Pantalla * pantalla;

	protected:

	struct Excepcion_carga_recursos
	{
		Excepcion_carga_recursos() {}
	};

	virtual std::vector<std::string> obtener_entradas_audio() const=0;
	virtual std::vector<std::string> obtener_entradas_musica() const=0;
	virtual std::vector<std::string> obtener_entradas_texturas() const=0;
	virtual std::vector<std::string> obtener_entradas_superficies() const=0;
	std::vector<std::string> obtener_entradas_desde_ruta(const std::string& ruta) const;

	private:

	void procesar_entrada_musica(const std::vector<std::string>&);
	void procesar_entrada_audio(const std::vector<std::string>&);
	void procesar_entrada_textura(const std::vector<std::string>&);
	void procesar_entrada_superficie(const std::vector<std::string>&);
	void procesar(const std::vector<std::string>& entradas, void (Cargador_recursos_base::*)(const std::vector<std::string>&));

	public:
	
	Cargador_recursos_base();
	~Cargador_recursos_base();

	void generar_recursos_texturas(DLibV::Pantalla &pantalla);
	void generar_recursos_superficies(DLibV::Pantalla &pantalla);
	void generar_recursos_audio();
	void generar_recursos_musica();
};

#endif
