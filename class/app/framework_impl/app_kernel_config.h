#ifndef APP_KERNEL_CONFIG_H
#define APP_KERNEL_CONFIG_H

#include "input.h"
#include "../../framework/kernel_driver_interface.h"
#include <input/controles_sdl/controles_sdl.h>

namespace App
{

class App_kernel_config
	:public DFramework::Kernel_driver_interface
{
	public:

	virtual std::vector<std::string> 	obtener_entradas_audio() const;
	virtual std::vector<std::string> 	obtener_entradas_musica() const;
	virtual std::vector<std::string> 	obtener_entradas_texturas() const;
	virtual std::vector<std::string> 	obtener_entradas_superficies() const;

	//Información para ventana.
	virtual DFramework::Info_ventana	obtener_info_ventana() const;

	//Información del input.
	virtual std::vector<DFramework::Par_input> 	obtener_pares_input() const;
};

}

#endif
