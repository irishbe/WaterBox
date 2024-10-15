// estructura los datos del Bioma
#ifndef BIOMA_H
#define BIOMA_H

#include <string>
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


#endif //Bioma.h
