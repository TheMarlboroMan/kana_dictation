#ifndef CONTROLADOR_PRINCIPAL
#define CONTROLADOR_PRINCIPAL

#include "controlador_base.h"
#include <vector>
#include <class/compositor_vista.h>
#include "../app/kana.h"
#include "../app/configuracion_ejercicio.h"

class Controlador_principal:public Controlador_base
{
	public:

					Controlador_principal(const DLibV::Fuente_TTF&, const DLibV::Fuente_TTF&, const App::Configuracion_ejercicio&);
	void				establecer_kanas(const std::vector<App::Kana>& k) {kanas=k;}
	void				generar_cadena_kanas();

	private:

	virtual void 			preloop(Input_base& input, float delta) {}
	virtual void 			postloop(Input_base& input, float delta) {}
	virtual void 			loop(Input_base& input, float delta);
	virtual void 			dibujar(DLibV::Pantalla& pantalla);
	virtual void 			despertar();
	virtual void 			dormir();
	virtual bool			es_posible_abandonar_estado() const {return true;}

	void				reiniciar_visibilidad_cadenas();

	Herramientas_proyecto::Compositor_vista		escena;
	std::vector<App::Kana>				kanas;
	std::string					str_kana,
							str_romaji;

	const App::Configuracion_ejercicio&		configuracion_ejercicio;
	const DLibV::Fuente_TTF& 			ttf_romaji;
	const DLibV::Fuente_TTF& 			ttf_kanas;

	bool 						resuelto;
};

#endif
