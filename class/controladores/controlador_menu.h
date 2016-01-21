#ifndef CONTROLADOR_MENU
#define CONTROLADOR_MENU

#include "controlador_base.h"
#include <vector>
#include <class/compositor_vista.h>
#include <base/localizador_base.h>
#include "../app/definiciones.h"

class Controlador_menu:public Controlador_base
{
	public:

					Controlador_menu(const DLibV::Fuente_TTF&, const Herramientas_proyecto::Localizador_base&, int longitud, App::tipos_kana tipo_kana);

	void				traducir_interface();

	private:

	virtual void 			preloop(Input_base& input, float delta) {}
	virtual void 			postloop(Input_base& input, float delta) {}
	virtual void 			loop(Input_base& input, float delta);
	virtual void 			dibujar(DLibV::Pantalla& pantalla);
	virtual void 			despertar();
	virtual void 			dormir();

	void				cambiar_seleccion_actual(int);
	void				cambiar_tipo_kana();
	void				cambiar_longitud_actual(int);

	Herramientas_proyecto::Compositor_vista		escena;
	const Herramientas_proyecto::Localizador_base&	localizador;

	const DLibV::Fuente_TTF& 			ttf_romaji;
	int						seleccion_actual;
	int						longitud_actual;
	App::tipos_kana					tipo_kana;

	static const int				ENTRADAS_MENU=4;
	static const int				LONGITUD_MAX=20;
	static const int				SALTO_MENU=60;

	enum menu {
		iniciar=0,
		longitud=1,
		cambiar_tipo=2,
		seleccion_grupo=3,
		opciones=4
	};
};

#endif
