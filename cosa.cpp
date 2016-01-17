#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

int main(int argc, char ** argv)
{
	SDL_InitSubSystem(SDL_INIT_VIDEO);
	TTF_Init();

	const int w=1024 / 2, h=600 / 2;

	std::string str="CADENA LARGA";

	SDL_Window * ventana=SDL_CreateWindow("", 
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		w, h, 0); 

	SDL_Renderer * renderer=SDL_CreateRenderer(ventana, -1, 0);
	SDL_RenderSetLogicalSize(renderer, w / 2, h / 2);

	SDL_RenderSetClipRect(renderer, NULL);
	SDL_SetRenderDrawColor(renderer, 128, 128, 128, 128);
	SDL_RenderClear(renderer);

	TTF_Font * fuente=TTF_OpenFont("data/fuentes/Akashi.ttf", 32);

	if(fuente==nullptr) std::cout<<"NO FUENTE"<<std::endl;

	SDL_Surface * s=TTF_RenderUTF8_Blended(fuente, str.c_str(), {0, 0, 0, 255});

	if(!s) std::cout<<"NO SURF"<<std::endl;

	SDL_Texture * tex = SDL_CreateTextureFromSurface(renderer, s);

	if(!tex) std::cout<<"NO TEX"<<std::endl;

	SDL_Rect caja{10, 10, 0, 0};

	TTF_SizeUTF8(fuente, str.c_str(), &caja.w, &caja.h);

	SDL_Rect caja2{0, 0, caja.w, caja.h};

	SDL_RenderCopy(renderer, tex, &caja2, &caja) >= 0;	
	SDL_RenderPresent(renderer);
	SDL_Delay(2000);

	//SDL_SetWindowFullscreen(ventana, 0);
	//SDL_SetWindowFullscreen(ventana, SDL_WINDOW_FULLSCREEN_DESKTOP);

//	SDL_SetWindowFullscreen(ventana, SDL_WINDOW_FULLSCREEN);
//	SDL_RenderCopy(renderer, tex, NULL, &caja) >= 0;	
//	SDL_RenderPresent(renderer);
//	SDL_Delay(2000);

	return 1;
}
