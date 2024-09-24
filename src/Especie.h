#ifndef ESPECIE_H
#define ESPECIE_H

#include "DatosEspecie.h"

using namespace std;

struct Especie {
    int id;
    DatosEspecie* datosEspecie;
    int vida;
    //time_t tiempoVida;
    char genero;
    string color;
    string estadoSalud;
    //Generacion* generacion;
    Especie* sgteEspecie;
};

#endif // ESPECIE_H
