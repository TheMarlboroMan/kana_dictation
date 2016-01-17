#ifndef CONTROLADOR_GRUPOS
#define CONTROLADOR_GRUPOS

#include "controlador_base.h"
#include <vector>
#include <string>
#include <class/compositor_vista.h>
#include <base/localizador_base.h>
#include <class/listado_vertical.h>

/**
El controlador para seleccionar los grupos de kanas activos. Guardará un vector
con el nombre de los grupos y si está o no seleccionado. A partir de los nombres
de los grupos seleccionados se podrá sacar el conjunto de los kanas deseados.
*/

class Controlador_grupos:public Controlador_base
{
	public:

					Controlador_grupos(Director_estados& d, const DLibV::Fuente_TTF&, const Herramientas_proyecto::Localizador_base&, const std::vector<std::string>& grupos);
	std::vector<std::string>	obtener_grupos_seleccionados() const;
	size_t				cantidad_seleccionados() const;

		
	private:

	struct grupo
	{
		std::string 		nombre;
		bool 			seleccionado;
		bool			operator<(const grupo& o) {return nombre < o.nombre;}
	};

	virtual void 			preloop(Input_base& input, float delta) {}
	virtual void 			postloop(Input_base& input, float delta) {}
	virtual void 			loop(Input_base& input, float delta);
	virtual void 			dibujar(DLibV::Pantalla& pantalla);

	void				componer_vista_listado();

	Herramientas_proyecto::Compositor_vista		escena;
	DLibV::Representacion_agrupada		 	rep_listado;
	std::vector<grupo>				grupos;
	Herramientas_proyecto::Listado_vertical<grupo>	listado;

	const Herramientas_proyecto::Localizador_base&	localizador;
	const DLibV::Fuente_TTF& 			ttf_romaji;

	static const int 				X_LISTADO=16,
							Y_LISTADO=32,
							X_SELECCION=270,
							ALTO_ITEM_LISTADO=20,
							ANCHO_LISTADO=300,
							MARGEN_Y=16;
};

#endif
