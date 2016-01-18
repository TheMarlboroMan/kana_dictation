#ifndef LOCALIZACION_H
#define LOCALIZACION_H

namespace App
{

class Localizacion
{
	public:

	enum cadenas{
		iniciar=1,
		longitud=2,
		silabario=3,
		hiragana=4,
		katakana=5,
		escoger_sets=6,
		configuracion=7,
		opciones_pantalla=8,
		opciones_pantalla_01=9,
		opciones_pantalla_02=10,
		opciones_idioma=11,
		opciones_idioma_01=12,
		opciones_idioma_02=13
	};

	private:

	Localizacion();
};

}

#endif
