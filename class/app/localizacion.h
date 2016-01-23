#ifndef LOCALIZADOR_APP_H
#define LOCALIZADOR_APP_H

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
		reinicio_ventana=8,
		direccion_romaji_kana=40,
		direccion_kana_romaji=41
	};

	private:

	Localizacion();
};

}

#endif
