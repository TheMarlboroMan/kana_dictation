#ifndef DEFINICIONES_H
#define DEFINICIONES_H

#include <string>

namespace App
{

enum class tipos_kana {hiragana, katakana};
enum class direcciones_traduccion {kana_romaji, romaji_kana};

tipos_kana string_to_tipo_kana(const std::string& str);
std::string tipo_kana_to_string(tipos_kana t);

direcciones_traduccion string_to_direccion_traduccion(const std::string& str);
std::string direccion_traduccion_to_string(direcciones_traduccion t);

}

#endif
