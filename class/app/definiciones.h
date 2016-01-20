#ifndef DEFINICIONES_H
#define DEFINICIONES_H

#include <string>

namespace App
{

enum class tipos_kana {hiragana, katakana};
tipos_kana string_to_tipo_kana(const std::string& str);
std::string tipo_kana_to_string(tipos_kana t);

}

#endif
