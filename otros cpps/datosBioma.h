// estructura los datos del Bioma
#ifndef DATOS_BIOMA_H
#define DATOS_BIOMA_H

#include <string>
#include "datosEspecies.h"
using namespace std;

struct Bioma{
	string nombre;
	int diasPasados;
	float nivelSalinidad;
	float nivelOxigeno;
	float nivelTemperatura;
	float nivelContaminacion;
	//Especie* listaEspecies;
};


#endif //datosBioma.h

