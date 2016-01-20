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
