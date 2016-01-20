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
		reinicio_ventana=8
	};

	private:

	Localizacion();
};

}

#endif
