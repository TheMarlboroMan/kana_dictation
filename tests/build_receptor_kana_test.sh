#!/bin/bash

if [ -z "$DIR_HERRAMIENTAS_PROYECTO" ]; then
    echo "Es necesario setear DIR_HERRAMIENTAS_PROYECTO a la raiz de las herramientas del proyecto con export DIR_HERRAMIENTAS_PROYECTO=valor"
    exit 1
fi

g++ receptor_kana_test.cpp -o receptor_kana_test.out $DIR_HERRAMIENTAS_PROYECTO/objects/dnot_token.o $DIR_HERRAMIENTAS_PROYECTO/objects/dnot_parser.o   -I $DIR_HERRAMIENTAS_PROYECTO -Wall -pedantic -std=c++11
