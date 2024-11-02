#ifndef POBLACION_H
#define POBLACION_H

#include "Especie.hpp"
using namespace std;

struct Poblacion {
    int id;
    string tipoEspecie;
    string nombreEspecie;
    int anchoCuadro;
    int altoCuadro;
    int contadorEspecies;

    Especie* listaEspecies;
    Poblacion* antePoblacion;
    Poblacion* sgtePoblacion;
};

#endif // ESPECIE_H


