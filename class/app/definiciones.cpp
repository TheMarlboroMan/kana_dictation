#include "definiciones.h"

using namespace App;

tipos_kana App::string_to_tipo_kana(const std::string& str)
{
	if(str=="hiragana") return tipos_kana::hiragana;
	else if(str=="katakana") return tipos_kana::katakana;
	return tipos_kana::hiragana;
}

std::string App::tipo_kana_to_string(tipos_kana t)
{
	switch(t)
	{
		case tipos_kana::hiragana: return "hiragana"; break;
		case tipos_kana::katakana: return "katakana"; break;
		default: return "hiragana"; break;
	}
}


direcciones_traduccion App::string_to_direccion_traduccion(const std::string& str)
{
	if(str=="a_kana") return direcciones_traduccion::romaji_kana;
	else if(str=="a_romaji") return direcciones_traduccion::kana_romaji;
	return direcciones_traduccion::romaji_kana;
}

std::string App::direccion_traduccion_to_string(direcciones_traduccion t)
{
	switch(t)
	{
		case direcciones_traduccion::romaji_kana: return "a_kana"; break;
		case direcciones_traduccion::kana_romaji: return "a_romaji"; break;
		default: return "a_kana"; break;
	}
}
