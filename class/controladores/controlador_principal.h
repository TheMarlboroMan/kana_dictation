#ifndef CONTROLADOR_PRINCIPAL
#define CONTROLADOR_PRINCIPAL

#include "controlador_base.h"
#include <vector>
#include <class/compositor_vista.h>
#include "../app/kana.h"
#include "../app/definiciones.h"

class Controlador_principal:public Controlador_base
{
	public:

					Controlador_principal(Director_estados& d, const DLibV::Fuente_TTF&, const DLibV::Fuente_TTF&);
	void				establecer_kanas(const std::vector<App::Kana>& k) {kanas=k;}
	void				generar_cadena_kanas();
	void				establecer_longitud_cadena(size_t l) {longitud_cadena=l;}
	void				establecer_tipo_kana(App::tipos_kana t) {tipo_kana=t;}

	private:

	virtual void 			preloop(Input_base& input, float delta) {}
	virtual void 			postloop(Input_base& input, float delta) {}
	virtual void 			loop(Input_base& input, float delta);
	virtual void 			dibujar(DLibV::Pantalla& pantalla);
	virtual void 			despertar();
	virtual void 			dormir();

	Herramientas_proyecto::Compositor_vista		escena;
	std::vector<App::Kana>				kanas;

	const DLibV::Fuente_TTF& 			ttf_romaji;
	const DLibV::Fuente_TTF& 			ttf_kanas;

	size_t						longitud_cadena;
	bool 						resuelto;
	App::tipos_kana					tipo_kana;

	

};

#endif
