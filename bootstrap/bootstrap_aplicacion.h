#ifndef BOOTSTRAP_APLICACION
#define BOOTSTRAP_APLICACION

#include "../class/controladores/director_estados.h"
#include "../class/framework/derivada/kernel.h"
#include "../class/app/definiciones.h"

class Controlador_principal;
class Controlador_grupos;

namespace App
{
class Lista_kanas;

bool preparar_kanas_principal(Controlador_principal&, const Controlador_grupos&, const Lista_kanas&, int, App::tipos_kana);
void loop_aplicacion(Kernel_app& kernel);
}

#endif
