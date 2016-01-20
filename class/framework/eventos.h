#ifndef FRAMEWORK_EVENTOS_H
#define FRAMEWORK_EVENTOS_H

/**
* Un sistema de mensajería (no necesariamente eventos, pero es un buen nombre)
* para que los diferentes controladores puedan comunicarse con una central,
* que sería el bootstrap de la aplicación.
* De momento no hay nada pensado para que diferentes controladores se 
* comuniquen entre si fuera del código que ya tenemos en el bootstrap. Siempre
* sería posible añadir una cola de mensajes que pueda consumirse entre los
* propios controladores. 
*/

//F-f-f-f-forward :D!.
class Interface_interprete_eventos;

/**
* Base para un evento. Un evento es una estructura que tendrá sus propios 
* valores indicando lo que sea que haya ocurrido.
*/

struct Evento_director_estados_base
{
	//Aún no lo tengo claro.
	//void disparar_evento(Interface_interprete_eventos&)=0;
};


/**
* Esto es la clase base para un interprete de eventos. La idea es que el 
* intérprete sea completamente opcional para la aplicación y que tenga estado.
* Por ejemplo, podría tener una referencia a la configuración para poder
* actualizar los valores de configuración en respuesta a eventos que vayan
* llegando.
*/

class Interface_interprete_eventos
{
	public:

	//TODO: ¿Esto qué hace?.
	//Clase base para un intérprete propio.
};

#endif
