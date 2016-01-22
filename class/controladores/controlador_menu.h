#ifndef CONTROLADOR_MENU
#define CONTROLADOR_MENU

#include "controlador_base.h"
#include <vector>
#include <class/compositor_vista.h>
#include <base/localizador_base.h>
#include "../app/configuracion_ejercicio.h"

class Controlador_menu:public Controlador_base
{
	public:

					Controlador_menu(const DLibV::Fuente_TTF&, const Herramientas_proyecto::Localizador_base&, const App::Configuracion_ejercicio&);

	void				traducir_interface();

	private:

	virtual void 			preloop(Input_base& input, float delta) {}
	virtual void 			postloop(Input_base& input, float delta);
	virtual void 			loop(Input_base& input, float delta);
	virtual void 			dibujar(DLibV::Pantalla& pantalla);
	virtual void 			despertar();
	virtual void 			dormir();
	virtual bool			es_posible_abandonar_estado() const {return true;}

	void				cambiar_seleccion_actual(int);
	void				cambiar_tipo_kana();
	void				cambiar_longitud_actual(int);
	void				cambiar_direccion_traduccion();
	void				actualizar_menu();

	Herramientas_proyecto::Compositor_vista		escena;

	const Herramientas_proyecto::Localizador_base&	localizador;
	const App::Configuracion_ejercicio&		configuracion_ejercicio;
	const DLibV::Fuente_TTF& 			ttf_romaji;

	int						seleccion_actual;
	bool						refrescar;

	static const int				ENTRADAS_MENU=6;
	static const int				SALTO_MENU=60;

	enum menu {
		iniciar=0,
		longitud=1,
		cambiar_tipo=2,
		cambiar_direccion=3,
		seleccion_grupo=4,
		opciones=5
	};
};

#endif
