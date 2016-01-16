#include <iostream>
#include "../class/app/kana.cpp"

int main(int argc, char ** argv)
{
	using namespace App;

	Kana a("A", "あ", "ア");
	Kana ka("KA", "か", "カ");
	
	std::cout<<"Kana "<<a.acc_silaba()<<" Hiragana: "<<a.acc_hiragana()<<" Katakana: "<<a.acc_katakana()<<std::endl<<
	"Kana "<<ka.acc_silaba()<<" Hiragana: "<<ka.acc_hiragana()<<" Katakana: "<<ka.acc_katakana()<<std::endl;

	return 0;

}
