// datosEspecies.h
#ifndef DATOS_ESPECIES_H
#define DATOS_ESPECIES_H

#include <string>
using namespace std;

struct Especie {
    string nombreComun;
    string nombreCientifico;
    string familiaBiologica;
    string biomaNativo;
    float esperanzaVida;
    float tasaReproduccion;
    float inactividadReproductiva;
    float salinidadMax;
    float salinidadMin;
    float oxigenoMax;
    float oxigenoMin;
    float tempMax;
    float tempMin;
};

#endif // DATOS_ESPECIES_H
