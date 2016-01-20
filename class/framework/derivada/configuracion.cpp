#include "configuracion.h"

const std::string Configuracion::CLAVE_IDIOMA="idioma";
const std::string Configuracion::CLAVE_W_FISICA_PANTALLA="w_fisica_ventana";
const std::string Configuracion::CLAVE_H_FISICA_PANTALLA="h_fisica_ventana";
const std::string Configuracion::CLAVE_W_LOGICA_PANTALLA="w_logica_ventana";
const std::string Configuracion::CLAVE_H_LOGICA_PANTALLA="h_logica_ventana";
const std::string Configuracion::CLAVE_KANAS_ACTIVOS="kanas_activos";
const std::string Configuracion::CLAVE_FONDO="fondo";
const std::string Configuracion::CLAVE_LONGITUD="longitud";
const std::string Configuracion::CLAVE_SILABARIO="silabario";

const std::string Configuracion::ID_IDIOMA="0";
const std::string Configuracion::W_FISICA_PANTALLA="800";
const std::string Configuracion::H_FISICA_PANTALLA="600";
const std::string Configuracion::W_LOGICA_PANTALLA="800";
const std::string Configuracion::H_LOGICA_PANTALLA="600";
const std::string Configuracion::KANAS_ACTIVOS="*";
const std::string Configuracion::FONDO="data/graficos/background_01.jpg";
const std::string Configuracion::LONGITUD="5";
const std::string Configuracion::SILABARIO="hiragana";

Configuracion::Configuracion(): Configuracion_base(obtener_ruta_archivo(), obtener_separador_archivo(), obtener_comentario_archivo())
{
	configurar(CLAVE_IDIOMA, ID_IDIOMA);
	configurar(CLAVE_W_FISICA_PANTALLA, W_FISICA_PANTALLA);
	configurar(CLAVE_H_FISICA_PANTALLA, H_FISICA_PANTALLA);
	configurar(CLAVE_W_LOGICA_PANTALLA, W_LOGICA_PANTALLA);
	configurar(CLAVE_H_LOGICA_PANTALLA, H_LOGICA_PANTALLA);
	configurar(CLAVE_KANAS_ACTIVOS, KANAS_ACTIVOS);
	configurar(CLAVE_FONDO, FONDO);
}
