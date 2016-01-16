#ifndef KANA_H
#define KANA_H

#include <string>

/*
El Kana no tiene conciencia del grupo al que pertenece, contiene tan sólo
la sílaba en Romaji y dos cadenas para hiragana y katakana.
*/

namespace App
{

class Kana
{
	public:

	Kana(const std::string&, const std::string&, const std::string&);
	
	const std::string	acc_silaba() const {return silaba;}
	const std::string	acc_hiragana() const {return hiragana;}
	const std::string	acc_katakana() const {return katakana;}

	private:

	std::string		silaba;
	std::string		hiragana;
	std::string		katakana;
};

}

#endif
