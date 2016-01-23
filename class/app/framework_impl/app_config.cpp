#include "app_config.h"

using namespace App;

const std::string App_config::CLAVE_IDIOMA="idioma";
const std::string App_config::CLAVE_W_FISICA_PANTALLA="w_fisica_ventana";
const std::string App_config::CLAVE_H_FISICA_PANTALLA="h_fisica_ventana";
const std::string App_config::CLAVE_W_LOGICA_PANTALLA="w_logica_ventana";
const std::string App_config::CLAVE_H_LOGICA_PANTALLA="h_logica_ventana";
const std::string App_config::CLAVE_KANAS_ACTIVOS="kanas_activos";
const std::string App_config::CLAVE_FONDO="fondo";
const std::string App_config::CLAVE_LONGITUD="longitud";
const std::string App_config::CLAVE_SILABARIO="silabario";
const std::string App_config::CLAVE_DIRECCION="direccion";

const std::string App_config::ID_IDIOMA="0";
const std::string App_config::W_FISICA_PANTALLA="800";
const std::string App_config::H_FISICA_PANTALLA="600";
const std::string App_config::W_LOGICA_PANTALLA="800";
const std::string App_config::H_LOGICA_PANTALLA="600";
const std::string App_config::KANAS_ACTIVOS="*";
const std::string App_config::FONDO="data/graficos/background_01.jpg";
const std::string App_config::LONGITUD="5";
const std::string App_config::SILABARIO="hiragana";
const std::string App_config::DIRECCION="a_kana";

App_config::App_config(): Configuracion_base(obtener_ruta_archivo(), obtener_separador_archivo(), obtener_comentario_archivo())
{
	configurar(CLAVE_IDIOMA, ID_IDIOMA);
	configurar(CLAVE_W_FISICA_PANTALLA, W_FISICA_PANTALLA);
	configurar(CLAVE_H_FISICA_PANTALLA, H_FISICA_PANTALLA);
	configurar(CLAVE_W_LOGICA_PANTALLA, W_LOGICA_PANTALLA);
	configurar(CLAVE_H_LOGICA_PANTALLA, H_LOGICA_PANTALLA);
	configurar(CLAVE_KANAS_ACTIVOS, KANAS_ACTIVOS);
	configurar(CLAVE_FONDO, FONDO);
	configurar(CLAVE_LONGITUD, LONGITUD);
	configurar(CLAVE_SILABARIO, SILABARIO);
	configurar(CLAVE_DIRECCION, DIRECCION);
}
