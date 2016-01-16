#include <iostream>
#include "../class/app/kana.cpp"
#include "../class/app/lista_kanas.cpp"

int main(int argc, char ** argv)
{
	using namespace App;

	std::vector<Kana> kanas_vocales={
		Kana("A", "あ", "ア"),
		Kana("I", "い", "イ"),
		Kana("U", "う", "ウ")
	};

	std::vector<Kana> kanas_k={
		Kana("KA", "か",  "カ")
	};

	Lista_kanas LK;

	for(const auto& k: kanas_vocales)
		LK.recibir_kana(k, "1 : Vocales");

	for(const auto& k: kanas_k)
		LK.recibir_kana(k, "2 : K");

	const auto& grupos=LK.obtener_grupos();

	for(const auto& g : grupos)
	{
		std::cout<<"Grupo "<<g<<":"<<std::endl;

		const auto& vector_kanas=LK.acc_grupo(g);
		for(const auto& k : vector_kanas)
		{
			std::cout<<"Kana "<<k.acc_silaba()<<" : Hiragana "<<k.acc_hiragana()<<" Katakana "<<k.acc_katakana()<<std::endl;
		}
	}

	return 0;

}
