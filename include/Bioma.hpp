// estructura los datos del Bioma
#ifndef BIOMA_HPP
#define BIOMA_HPP

#include <string>
using namespace std;

struct Bioma{
	string nombre;
	//int diasPasados;
	float nivelSalinidad;
	float nivelOxigeno;
	float nivelTemperatura;
	float nivelContaminacion;
	//Especie* listaEspecies;
};

// Declaración de variables globales
Bioma* biomaSimulador = nullptr;

#endif //Bioma.hpp
