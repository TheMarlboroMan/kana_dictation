#include "lista_kanas.h"

using namespace App;

void Lista_kanas::recibir_kana(const Kana& kana, const std::string& grupo)
{
	if(!kanas.count(grupo))
	{
		kanas[grupo]=std::vector<Kana>();
	}

	kanas[grupo].push_back(kana);
}

std::vector<std::string> Lista_kanas::obtener_grupos() const
{
	std::vector<std::string> res;

	for(const auto& grupo : kanas)
	{
		res.push_back(grupo.first);
	}

	return res;
}
