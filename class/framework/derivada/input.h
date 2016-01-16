#ifndef PROYECTO_SDL2_DERIVADA_INPUT_H
#define PROYECTO_SDL2_DERIVADA_INPUT_H

/*La clase que controla el input. La interfaz pública la sacamos del Input_base
y es esta:

bool es_senal_salida() const;
bool es_input_down(unsigned int) const;
bool es_input_up(unsigned int) const;
bool es_input_pulsado(unsigned int) const;

bool es_tecla_down(unsigned int i) const;
bool es_tecla_up(unsigned int i) const;
bool es_tecla_pulsada(unsigned int i);

bool hay_eventos_teclado_down();
*/

#include "../base/input_base.h"

class Input:public Input_base
{
	/////////////////
	//Definiciones...

	public:

	enum inputs{
I_ESCAPE=0,
I_ESPACIO,
I_ENTER,
I_IZQUIERDA,
I_DERECHA,
I_ARRIBA,
I_ABAJO,
I_CLICK_I,
I_CLICK_D
};

	///////////////////
	// Métodos

	public:

	virtual void configurar();	
	Input():Input_base() {}
};

#endif
