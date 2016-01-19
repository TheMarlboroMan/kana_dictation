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
		opciones_pantalla=10,
		opciones_pantalla_01=11,
		opciones_pantalla_02=12,
		opciones_pantalla_03=13,
		opciones_pantalla_04=14,
		opciones_pantalla_05=15,
		opciones_pantalla_06=16,
		opciones_idioma=20,
		opciones_idioma_01=21,
		opciones_idioma_02=22
	};

	private:

	Localizacion();
};

}

#endif
