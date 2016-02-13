#include "lector_kana.h"
#include <algorithm>

using namespace App;

void Lector_kana::procesar_fichero(const std::string& ruta, Receptor_kana& receptor)
{
	auto tok=Herramientas_proyecto::parsear_dnot("data/recursos/kanas.dnot");
	const auto grupos=tok["grupos"].acc_lista();

	for(const auto& grupo : grupos)
	{
		const std::string nombre_grupo=grupo["nombre"];

		const auto& vector_kanas=grupo["kanas"].acc_lista();

		for(const auto& estructura : vector_kanas)
		{
			std::string silaba=estructura["silaba"];
			std::transform(silaba.begin(), silaba.end(), silaba.begin(), ::toupper);

			receptor.recibir_kana(Kana(silaba, estructura["hiragana"], estructura["katakana"]), nombre_grupo);
		}
	}
}
