#include "app_kernel_config.h"
#include <SDL2/SDL.h>

using namespace App;



std::vector<std::string> App_kernel_config::obtener_entradas_audio() const
{
	return obtener_entradas_desde_ruta(std::string("data/recursos/audio.txt"));
}

std::vector<std::string> App_kernel_config::obtener_entradas_musica() const
{
	return obtener_entradas_desde_ruta(std::string("data/recursos/musica.txt"));
}

std::vector<std::string> App_kernel_config::obtener_entradas_texturas() const
{
	return obtener_entradas_desde_ruta(std::string("data/recursos/texturas.txt"));
}

std::vector<std::string> App_kernel_config::obtener_entradas_superficies() const
{
	return obtener_entradas_desde_ruta(std::string("data/recursos/superficies.txt"));
}

//Información para ventana.
DFramework::Info_ventana App_kernel_config::obtener_info_ventana() const
{
	return DFramework::Info_ventana{800, 600, 800, 600, "KanaFun", true};
}

std::vector<DFramework::Par_input> App_kernel_config::obtener_pares_input() const
{
	using namespace DFramework;
	std::vector<Par_input> res{
		Par_input{Par_input::tipos::teclado, Input::I_ESCAPE, SDL_SCANCODE_ESCAPE},
		Par_input{Par_input::tipos::teclado, Input::I_ACEPTAR, SDL_SCANCODE_SPACE},
		Par_input{Par_input::tipos::teclado, Input::I_ACEPTAR, SDL_SCANCODE_RETURN},
		Par_input{Par_input::tipos::teclado, Input::I_IZQUIERDA, SDL_SCANCODE_LEFT},
		Par_input{Par_input::tipos::teclado, Input::I_DERECHA, SDL_SCANCODE_RIGHT},
		Par_input{Par_input::tipos::teclado, Input::I_ARRIBA, SDL_SCANCODE_UP},
		Par_input{Par_input::tipos::teclado, Input::I_ABAJO, SDL_SCANCODE_DOWN}};

	return res;
}
