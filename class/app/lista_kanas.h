#ifndef LISTA_KANAS_H
#define LISTA_KANAS_H

#include <map>
#include <vector>
#include <string>

#include "receptor_kana.h"
#include "kana.h"

/*
El receptor de kanas contiene un mapa que mapea el nombre del grupo a un vector
de kanas. Implementa la interface que permite conectarlo al lector de Kanas
para cargarlo desde un archivo.

En el mapa los grupos estarán ordenados alfabéticamente según su nombre.
*/

namespace App
{

class Lista_kanas:
	public Receptor_kana
{
	public:

	//Obtiene un vector de kanas para el grupo especificado. Fallará si el grupo no existe.
	const std::vector<Kana>&			acc_grupo(const std::string& grupo) const {return kanas.at(grupo);}

	//Obtiene un vector con el nombre de todos los grupos.
	std::vector<std::string>			obtener_grupos() const;

	////////////
	// Implementación de Receptor_kana

	public:

	virtual void					recibir_kana(const Kana&, const std::string& grupo);

	private:

	std::map<std::string, std::vector<Kana>>	kanas;
};

}

#endif
