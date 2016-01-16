#ifndef KERNEL_MOTOR_SDL2_H
#define KERNEL_MOTOR_SDL2_H

#include <string>
#include "configuracion_base.h"
#include "input_base.h"
#include "audio_base.h"
#include "cargador_recursos_base.h"
#include "../interface_controlador.h"
#include <class/controlador_argumentos.h>

class Kernel_exception
	:public std::runtime_error
{
	public:
	Kernel_exception(const std::string& m):std::runtime_error(m) {}
};


class Kernel_base
{
	///////////////////
	// Propiedades

	private:

	bool mostrar_fps;
	float paso_delta;

	Herramientas_proyecto::Controlador_argumentos& controlador_argumentos;
	DLibH::Controlador_fps_SDL controlador_fps;
	DLibV::Pantalla pantalla;

	///////////////////////////
	// Internos...

	private:

	void inicializar_entorno_grafico(DLibV::Pantalla& pantalla, unsigned int w, unsigned int h);
	void configurar_entorno_grafico(DLibV::Pantalla& pantalla, unsigned int w, unsigned int h);
	void inicializar_entorno_audio();
	void configurar_entorno_audio();

	/////////////////////
	// Interfaz pública

	public:

	Kernel_base(Herramientas_proyecto::Controlador_argumentos&);
	~Kernel_base();

	virtual void inicializar();
	bool loop(Interface_controlador& CI);
	void ciclar_modo_pantalla();

	DLibV::Pantalla& acc_pantalla() {return pantalla;}
	Herramientas_proyecto::Controlador_argumentos& acc_controlador_argumentos() {return controlador_argumentos;}

	bool es_mostrar_fps() const {return mostrar_fps;}
	float acc_paso_delta() const {return paso_delta;}

	void mut_mostrar_fps(bool v) {mostrar_fps=v;}
	void mut_paso_delta(float v) {paso_delta=v;}

//	virtual void ejecutar()=0;	//Sera el loop principal de la aplicación. Debe llamar al "loop" propio del kernel base.
	virtual void paso()=0;	//Antes siquiera de recoger el input...
	virtual void preloop()=0;	//Tras recoger input, antes de preloop de controlador.
	virtual void postloop()=0;		//Tras loop, antes de post loop de controlador.
	virtual std::string acc_titulo_inicial() const=0;
	virtual bool acc_mostrar_cursor_inicial() const=0;
	virtual int acc_w_pantalla_inicial() const=0;
	virtual int acc_h_pantalla_inicial() const=0;
	virtual Input_base& acc_input()=0;
	virtual Configuracion_base& acc_configuracion()=0;
	virtual Cargador_recursos_base& acc_cargador_recursos()=0;
	virtual unsigned int acc_recurso_fps() const=0;
};

#endif
