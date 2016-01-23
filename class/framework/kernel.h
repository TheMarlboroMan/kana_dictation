#ifndef KERNEL_MOTOR_SDL2_H
#define KERNEL_MOTOR_SDL2_H

#include <string>
#include "kernel_driver_interface.h"
#include "configuracion_base.h"
#include "input.h"
#include "audio.h"
#include "cargador_recursos.h"
#include <class/controlador_argumentos.h>

/**
* El Kernel es propietario de los recursos y la interface de input. No es
* propietario de la configuración, que puede variar para cada proyecto.
*/

namespace DFramework
{

class Kernel_exception
	:public std::runtime_error
{
	public:
	Kernel_exception(const std::string& m):std::runtime_error(m) {}
};


class Kernel
{
	public:

				Kernel(Herramientas_proyecto::Controlador_argumentos&, Kernel_driver_interface&, Configuracion_base&);
	void 			ciclar_modo_pantalla();
	int			acc_fps() const {return controlador_fps.acc_frames_contados();}

	Input&			acc_input() {return input;}
	DLibV::Pantalla& 	acc_pantalla() {return pantalla;}
	Herramientas_proyecto::Controlador_argumentos& acc_controlador_argumentos() {return controlador_argumentos;}

	float 			acc_paso_delta() const {return paso_delta;}
	void 			mut_paso_delta(float v) {paso_delta=v;}
	void			turno_fps() {controlador_fps.turno();}
	void			iniciar_paso_loop() {controlador_fps.iniciar_paso_loop();}
	bool			consumir_loop(float delta) {return controlador_fps.consumir_loop(delta);}
	void			procesar_cola_sonido() {Audio::procesar_cola_sonido();}


	///////////////////
	// Propiedades

	private:

	float paso_delta;

	Herramientas_proyecto::Controlador_argumentos& 	controlador_argumentos;
	DLibH::Controlador_fps_SDL 			controlador_fps;
	DLibV::Pantalla 				pantalla;
	Input						input;

	///////////////////////////
	// Internos...

	private:

	void 			inicializar(const Kernel_driver_interface&, const Configuracion_base&);
	void 			inicializar_entorno_grafico(const Info_ventana&);
	void 			inicializar_entorno_audio(const Configuracion_base& config);
};

}
#endif
