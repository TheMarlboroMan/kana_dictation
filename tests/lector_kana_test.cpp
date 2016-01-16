#include <iostream>
#include "../class/app/kana.cpp"
#include "../class/app/lector_kana.cpp"

class Interprete:
	public App::Receptor_kana
{
	public:

	virtual void		recibir_kana(const Kana& kana, const std::string& grupo)
	{
		std::cout<<"Recibido el kana "<<kana.acc_silaba()<<" del grupo "<<grupo<<" : Hiragana: "<<kana.acc_hiragana()<<" Katakana: "<<kana.acc_katakana()<<std::endl;
	}
};

int main(int argc, char ** argv)
{
	using namespace App;

	Interprete I;

	try
	{
		Lector_kana LK;
		LK.procesar_fichero("kanas.dnot", I);
	}
	catch(std::exception& e)
	{
		std::cout<<"Ha ocurrido un error: "<<e.what()<<std::endl;
	}

	return 0;

}
