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

					Controlador_principal(const DLibV::Fuente_TTF&, const DLibV::Fuente_TTF&);
	void				establecer_kanas(const std::vector<App::Kana>& k) {kanas=k;}
	void				generar_cadena_kanas(size_t);
	void				establecer_tipo_kana(App::tipos_kana t) {tipo_kana=t;}
	void				establecer_direccion(App::direcciones_traduccion d) {direccion=d;}

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

	bool 						resuelto;

	//TODO: Realmente no me gusta... son copias!.

	App::tipos_kana					tipo_kana;
	App::direcciones_traduccion			direccion;
	size_t						copia_longitud;

	

};

#endif
