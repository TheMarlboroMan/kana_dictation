#ifndef KERNEL_APP_SDL2
#define KERNEL_APP_SDL2

#include "../base/kernel_base.h"

#include "../derivada/cargador_recursos.h"
#include "../derivada/configuracion.h"
#include "../derivada/input.h"
#include "../derivada/localizador.h"

#include "../../app/recursos.h"

class Kernel_app:public Kernel_base
{
	private:

	//Debemos declarar estas cosas, que hacen falta.

	Input input;
	Configuracion configuracion;
	Cargador_recursos cargador_recursos;

	public:

	Kernel_app(Herramientas_proyecto::Controlador_argumentos& CARG);

	virtual void inicializar() {Kernel_base::inicializar();}	//Si es necesario podemos personalizar varios aspectos aquí. Esto se llamará una única vez, en el main.
	virtual void paso() {}		//Se llamará una vez por cada consumo de delta en el loop del kernel base.
	virtual void preloop() {}	//Se llamará antes del consumo de delta en el loop del kernel base.
	virtual void postloop() {}	//Idem, pero despúes.
	virtual std::string acc_titulo_inicial() const {return std::string("KANA DICTATION");}
	virtual bool acc_mostrar_cursor_inicial() const {return true;}
	virtual int acc_w_pantalla_inicial() const {return 800;}
	virtual int acc_h_pantalla_inicial() const {return 600;}
	virtual Input_base& acc_input() {return input;}
	virtual Configuracion& acc_configuracion() {return configuracion;}
	virtual Cargador_recursos_base& acc_cargador_recursos() {return cargador_recursos;}
	virtual unsigned int acc_recurso_fps() const {return 0;}
};

#endif
