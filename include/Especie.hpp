#ifndef ESPECIE_H
#define ESPECIE_H

#include "DatosEspecie.hpp"

using namespace std;

struct Especie {
    string id;
    string tipoEspecie;
    DatosEspecie* datosEspecie;
    int vida = 100;
    //time_t tiempoVida;
    char genero;
    string color;
    string estadoSalud = "sano";

    Especie* sgteEspecie = nullptr;
    Especie* primerHijo = nullptr;
    Especie* sgteHijo = nullptr;
    Especie* padre = nullptr;
    Especie* madre = nullptr;
};

#endif // ESPECIE_H
