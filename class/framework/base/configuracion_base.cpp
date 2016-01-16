#include "configuracion_base.h"
#include <map>
#include <source/string_utilidades.h>

/*
Al crear el objeto aún no podemos cargar la información de los valores por
defecto (métodos virtuales) así que no podremos intentar acceder a ningún
valor hasta haber cargado la configuración.
*/

Configuracion_base::Configuracion_base(const std::string& ruta, char separador, char comentario)
try
	:pares(ruta, separador, comentario)
{

}
catch(Herramientas_proyecto::Fichero_pares_exception& e)
{
	throw Configuracion_base_no_fichero_exception(ruta);
}

void Configuracion_base::asignar_valores_por_defecto()
{
	mut_pantalla_completa(valor_pantalla_completa_defecto());
	mut_modo_hardware(valor_modo_hardware_defecto());
	mut_pantalla_doble_buffer(valor_pantalla_doble_buffer_defecto());
	mut_pantalla_anyformat(valor_pantalla_anyformat_defecto());
	mut_volumen_audio(valor_volumen_audio_defecto());
	mut_volumen_musica(valor_volumen_musica_defecto());
	mut_audio_ratio(valor_audio_ratio_defecto());
	mut_audio_salidas(valor_audio_salidas_defecto());
	mut_audio_buffers(valor_audio_buffers_defecto());
	mut_audio_canales(valor_audio_canales_defecto());
}

/*
Se asignan los valores por defecto, luego se cargan los valores de disco y se
guardan de nuevo para guardar aquellos que podían faltar en el disco.
*/

void Configuracion_base::cargar()
{
	asignar_valores_por_defecto();

	//Al cargar los pares se pierde la información inicial al 
	//sobreescribirse el objeto. Tendríamos que "sincronizarlos".

	auto copia_pares=pares;
	pares.cargar();
	pares.sincronizar(copia_pares);
	pares.guardar();
}

void Configuracion_base::grabar()
{
	pares.guardar();
}
