#ifndef LECTOR_KANA_H
#define LECTOR_KANA_H

#include "kana.h"
#include "receptor_kana.h"
#include <class/dnot_parser.h>

/**
El lector de Kana los toma desde un archivo dnot y uno por uno los lee y pasa
a una clase que implemente la interface para recibirlos. Espera que el fichero
a leer tenga una estructura como sigue:

grupos:[
	{
		nombre : "Vowels",
		kanas : [
			{
				silaba:"A",
				hiragana:"あ",
				katakana:"ア"
			},
			{
				silaba:"I",
				hiragana:"い",
				katakana:"イ"
			},
			{
				silaba:"u",
				hiragana:"う",
				katakana:"ウ"
			}
		]
	},
	{
		nombre: "K",
		kanas : [
			{
				silaba:"KA",
				hiragana:"か",
				katakana:"カ"
			}
		]
	}
]

Independientemente de que la sílaba esté o no en mayúsculas va a pasarla a 
uppercase.
*/

namespace App
{

class Lector_kana
{
	public:

	void 		procesar_fichero(const std::string& ruta, Receptor_kana& receptor);

	private:
};

}

#endif
