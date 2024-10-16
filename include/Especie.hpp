#ifndef ESPECIE_H
#define ESPECIE_H

#include "DatosEspecie.h"

using namespace std;

struct Especie {
    int id;
    string tipoEspecie;
    DatosEspecie* datosEspecie;
    int vida = 100;
    //time_t tiempoVida;
    char genero;
    string color;
    string estadoSalud = "sano";
    //Generacion* generacion;
    Especie* sgteEspecie;
};

#endif // ESPECIE_H
