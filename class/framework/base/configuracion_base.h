#ifndef PROYECTO_SDL2_BASE_CONFIGURACION_H
#define PROYECTO_SDL2_BASE_CONFIGURACION_H

/*
Esta clase lee y escribe en un archivo los datos de configuración de la 
aplicación. Al leer los datos de configuración los almacena entre sus 
propiedades. Podemos (y debemos) extenderla para la configuración de cada
proyecto implementando todos los métodos virtuales puros que tiene.
*/

#include <class/fichero_pares.h>
#include <iostream>

class Configuracion_base_no_fichero_exception
	:public std::runtime_error
{
	public:
	Configuracion_base_no_fichero_exception(const std::string& ruta)
		:std::runtime_error("No se puede localizar el fichero "+ruta)
	{}
};

class Configuracion_base
{
	////////////////////////////////
	// Interface pública.

	public:

	int acc_pantalla_completa() const 	{return std::atoi(pares[obtener_clave_pantalla_completa()].c_str());}
	int acc_modo_hardware() const 		{return std::atoi(pares[obtener_clave_modo_hardware()].c_str());}
	int acc_pantalla_doble_buffer() const 	{return std::atoi(pares[obtener_clave_pantalla_doble_buffer()].c_str());}
	int acc_pantalla_anyformat() const 	{return std::atoi(pares[obtener_clave_pantalla_anyformat()].c_str());}
	int acc_volumen_audio() const		{return std::atoi(pares[obtener_clave_volumen_audio()].c_str());}
	int acc_volumen_musica() const		{return std::atoi(pares[obtener_clave_volumen_musica()].c_str());}
	int acc_audio_ratio() const		{return std::atoi(pares[obtener_clave_audio_ratio()].c_str());}
	int acc_audio_salidas() const		{return std::atoi(pares[obtener_clave_audio_salidas()].c_str());}
	int acc_audio_buffers() const		{return std::atoi(pares[obtener_clave_audio_buffers()].c_str());}
	int acc_audio_canales() const		{return std::atoi(pares[obtener_clave_audio_canales()].c_str());}
	int acc_version_archivo() const		{return std::atoi(pares[obtener_clave_version_archivo()].c_str());}

	void mut_pantalla_completa(int p_valor) 	{pares[obtener_clave_pantalla_completa()]=std::to_string(p_valor);}
	void mut_modo_hardware(int p_valor)		{pares[obtener_clave_modo_hardware()]=std::to_string(p_valor);}
	void mut_pantalla_doble_buffer(int p_valor)	{pares[obtener_clave_pantalla_doble_buffer()]=std::to_string(p_valor);}
	void mut_pantalla_anyformat(int p_valor)	{pares[obtener_clave_pantalla_anyformat()]=std::to_string(p_valor);}
	void mut_volumen_audio(int p_valor)		{pares[obtener_clave_volumen_audio()]=std::to_string(p_valor);}
	void mut_volumen_musica(int p_valor)		{pares[obtener_clave_volumen_musica()]=std::to_string(p_valor);}
	void mut_audio_ratio(int p_valor)		{pares[obtener_clave_audio_ratio()]=std::to_string(p_valor);}
	void mut_audio_salidas(int p_valor)		{pares[obtener_clave_audio_salidas()]=std::to_string(p_valor);}
	void mut_audio_buffers(int p_valor)		{pares[obtener_clave_audio_buffers()]=std::to_string(p_valor);}
	void mut_audio_canales(int p_valor)		{pares[obtener_clave_audio_canales()]=std::to_string(p_valor);}

	void cargar();
	void grabar();

	Configuracion_base(const std::string& ruta, char separador, char comentario);

	protected: 

	//Añade la posibilidad de que clases derivadas guarden sus valores.
	void	configurar(const std::string& clave, const std::string& valor) {pares[clave]=valor;}
	const std::string& valor_configuracion(const std::string& clave) const {return pares[clave];}

	////////////////////////////////////
	// A implementar por clases que la extiendan...

		//Estos simplemente devuelven claves de configuración.
	virtual std::string obtener_clave_version_archivo() const=0;
	virtual std::string obtener_version_archivo() const=0;
	virtual std::string obtener_clave_pantalla_completa() const=0;
	virtual std::string obtener_clave_modo_hardware() const=0;
	virtual std::string obtener_clave_pantalla_doble_buffer() const=0;
	virtual std::string obtener_clave_pantalla_anyformat() const=0;
	virtual std::string obtener_clave_volumen_audio() const=0;
	virtual std::string obtener_clave_volumen_musica() const=0;
	virtual std::string obtener_clave_audio_ratio() const=0;
	virtual std::string obtener_clave_audio_buffers() const=0;
	virtual std::string obtener_clave_audio_salidas() const=0;
	virtual std::string obtener_clave_audio_canales() const=0;

		//Y estos valores de configuración por defecto que se castearán llamando al setter.
	virtual int valor_pantalla_completa_defecto() const=0; //0 -> No / 1 -> Si
	virtual int valor_modo_hardware_defecto() const=0; //0 -> No / 1 -> Si
	virtual int valor_pantalla_doble_buffer_defecto() const=0;	//0 -> No / 1 -> Si
	virtual int valor_pantalla_anyformat_defecto() const=0;	//0 -> No / 1 -> Si
	virtual int valor_volumen_audio_defecto() const=0;	//0-128...
	virtual int valor_volumen_musica_defecto() const=0;	//0-128...
	virtual int valor_audio_ratio_defecto() const=0; //Por ejemplo... 44100.
	virtual int valor_audio_salidas_defecto() const=0; //1 -> mono, 2 -> stereo.
	virtual int valor_audio_buffers_defecto() const=0; //Por ejemplo... 1024;
	virtual int valor_audio_canales_defecto() const=0; //Por ejemplo... 8.

	///////////////////////////////////
	// Propiedades.

	private:

	void 						asignar_valores_por_defecto();

	Herramientas_proyecto::Fichero_pares		pares;
};

#endif
