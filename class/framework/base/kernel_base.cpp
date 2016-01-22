#include "kernel_base.h"
#include <cstdlib>

Kernel_base::Kernel_base(Herramientas_proyecto::Controlador_argumentos& carg)
	:
	mostrar_fps(true),
	paso_delta(0.01),
	controlador_argumentos(carg),
	controlador_fps(),
	pantalla(), 
	IC(nullptr),
	DE(nullptr),
	IE(nullptr)
{

}

Kernel_base::~Kernel_base()
{

}

void Kernel_base::inicializar()
{
	//Cargar configuración.
	Configuracion_base& configuracion=acc_configuracion();
	configuracion.cargar();

	inicializar_entorno_grafico(pantalla, acc_w_pantalla_inicial(), acc_h_pantalla_inicial());
	inicializar_entorno_audio();

	//Inicializar recursos.
	Cargador_recursos_base& cargador_recursos=acc_cargador_recursos();
	cargador_recursos.generar_recursos_texturas(pantalla);
	cargador_recursos.generar_recursos_superficies(pantalla);
	cargador_recursos.generar_recursos_audio();
	cargador_recursos.generar_recursos_musica();
	
	//Inicializar controles.
	Input_base& i=acc_input();
	i.configurar(); 

	//Inicialización controlador tiempo.
	controlador_fps.inicializar();	
}

void Kernel_base::inicializar_entorno_grafico(DLibV::Pantalla& pantalla, unsigned int w, unsigned int h)
{
	configurar_entorno_grafico(pantalla, w, h);
	pantalla.establecer_titulo(acc_titulo_inicial().c_str());
	DLibV::Utilidades_graficas_SDL::mostrar_ocultar_cursor(acc_mostrar_cursor_inicial());
}

void Kernel_base::configurar_entorno_grafico(DLibV::Pantalla& pantalla, unsigned int w, unsigned int h)
{
	pantalla.inicializar(w, h);
	pantalla.establecer_medidas_logicas(w, h);
	pantalla.establecer_modo_ventana(DLibV::Pantalla::M_VENTANA);
}

void Kernel_base::ciclar_modo_pantalla()
{
	unsigned int modo=pantalla.acc_modo_ventana();
	++modo;

	if(modo == DLibV::Pantalla::M_MAX_MODO)
	{
		modo=DLibV::Pantalla::M_VENTANA;
	}

	pantalla.establecer_modo_ventana(modo);
}


void Kernel_base::inicializar_entorno_audio()
{
	Configuracion_base& configuracion=acc_configuracion();

	Audio::inicializar_entorno_audio(
		configuracion.acc_audio_ratio(), 
		configuracion.acc_audio_salidas(),
		configuracion.acc_audio_buffers(),
		configuracion.acc_audio_canales());

	configurar_entorno_audio();
}

void Kernel_base::configurar_entorno_audio()
{
	Configuracion_base& configuracion=acc_configuracion();

	Audio::establecer_volumen(configuracion.acc_volumen_audio());
	Audio::establecer_volumen_musica(configuracion.acc_volumen_musica());
}

bool Kernel_base::loop()
{
	//Aquí se mide el tiempo desde el último paso por este loop...
	controlador_fps.iniciar_paso_loop();
	Input_base& input=acc_input();

	preloop();
	IC->preloop(input, paso_delta);

	//Aquí se consume el tiempo desde el último paso en bloques de "paso_delta".
	while(controlador_fps.consumir_loop(paso_delta) )
	{
		paso();
		
		input.turno();

		IC->loop(input, paso_delta);

		Audio::procesar_cola_sonido();

		if(IC->es_romper_loop()) 
		{
			break;
		}

		if(DE->es_cambio_estado()) 
		{
			if(!IC->es_posible_abandonar_estado())
			{
				DE->cancelar_cambio_estado();
			}
			else
			{
				DE->preparar_cambio_estado();
				if(IE!=nullptr) DE->procesar_cola_eventos(*IE);
				break;
			}
		}
	
		if(IE!=nullptr) DE->procesar_cola_eventos(*IE);
	}

	if(DE->es_cambio_estado())
	{
		DE->confirmar_cambio_estado(IC);
	}
	else
	{
		postloop();
		IC->postloop(input, paso_delta);

		controlador_fps.turno();

		IC->dibujar(pantalla);

		if(mostrar_fps)
		{
			std::string fps="FPS:"+std::to_string(controlador_fps.acc_frames_contados())+"\n"+IC->acc_debug();
			DLibV::Representacion_texto_auto txt(DLibV::Gestor_superficies::obtener(acc_recurso_fps()), fps);
			txt.hacer_estatica();
			txt.establecer_posicion(pantalla.acc_w()-128, 6);
			txt.volcar(pantalla);
		}	

		pantalla.actualizar();
	}

	return !IC->es_abandonar_aplicacion();
}

void Kernel_base::establecer_director_estados(Base_director_estados& BDE)
{
	if(DE!=nullptr)
	{
		throw Kernel_exception("El director de estados ya ha sido registrado");
	}
	
	DE=&BDE;
}

void Kernel_base::registrar_controlador(int clave, Interface_controlador& I)
{
	if(DE==nullptr)
	{
		throw Kernel_exception("El director de estados no ha sido registrado para registrar controlador");
	}

	DE->registrar_controlador(clave, I);
}

void Kernel_base::preparar_loop()
{
	DE->despertar_controlador_inicial(IC);
}

void Kernel_base::establecer_interprete_eventos(Interface_interprete_eventos& E)
{
	if(IE!=nullptr)
	{
		throw Kernel_exception("El intérprete de eventos ya ha sido registrado");
	}
	
	IE=&E;
}
