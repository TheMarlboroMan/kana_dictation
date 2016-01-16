#ifndef RECEPTOR_KANA_H
#define RECEPTOR_KANA_H

namespace App
{

class Kana;

class Receptor_kana
{
	public:

	virtual void		recibir_kana(const Kana&, const std::string& grupo)=0;
};

}

#endif
