// datosEspecies.h
#ifndef DATOS_ESPECIE_H
#define DATOS_ESPECIE_H

using namespace std;

struct DatosEspecie {
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

#endif // DATOS_ESPECIE_H
