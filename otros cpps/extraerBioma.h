// para extraer la info del Bioma
#ifndef EXTRAER_BIOMA_H
#define EXTRAER_BIOMA_H

#include <string>
#include "datosBioma.h"
#include "json.hpp"
using namespace std;
using json = nlohmann::json;


void agregarBioma(){
	
	string nombre;
	int diasPasados;
	float nivelSal, nivelOxi, nivelTemp, nivelCont;
	// Especie* listaEspecies
	
	fflush(stdin);
	cout<<"Nombre-->";
	getline(cin, nombre);
	
	fflush(stdin);
	cout<<"Dias pasados-->";
	cin>>diasPasados;
	
	fflush(stdin);
	cout<<"Nivel Salinidad-->";
	cin>>nivelSal;
	
	fflush(stdin);
	cout<<"Nivel Oxigeno-->";
	cin>>nivelOxi;
	
	fflush(stdin);
	cout<<"Nivel Temperatura-->";
	cin>>nivelTemp;
	
	fflush(stdin);
	cout<<"Nivel Contaminacion-->";
	cin>>nivelCont;
	
	json bio={
		{"nombre", nombre},
        {"diasPasados", diasPasados},
        {"nivelSalinidad", nivelSal},
        {"nivelOxigeno", nivelOxi},
        {"nivelTemperatura", nivelTemp},
        {"nivelContaminacion", nivelCont}
	};
	
	
	json biomass;	
	ifstream archivo("bioma.json");
	
    if (archivo) {
        archivo>>biomass;
        archivo.close();
    } else {
        biomass = json::array();
    }
    
    biomass.push_back(bio);
	
	ofstream salida("bioma.json");
    salida<<biomass.dump(4)<<endl;
    salida.close();
}



Bioma extraerBioma(string nombreBuscado){
	
	json biomas;     			//variable para sacar info total del json
	Bioma biomaEncontrado;		//para la info del biomita
	
	ifstream archivo("bioma.json");
    if (archivo){
        archivo>>biomas;	//extraer
        archivo.close();
    } 
	else{
        biomas = json::array();	
    }
	
	//****************************************************************************
	for (const auto& bioma : biomas) {
        if (bioma["nombre"] == nombreBuscado) {
            // Asignamos los datos a la estructura
            biomaEncontrado.nombre = bioma["nombre"];
            biomaEncontrado.diasPasados = bioma["diasPasados"];
            biomaEncontrado.nivelSalinidad = bioma["nivelSalinidad"];
            biomaEncontrado.nivelOxigeno = bioma["nivelOxigeno"];
            biomaEncontrado.nivelTemperatura = bioma["nivelTemperatura"];
            biomaEncontrado.nivelContaminacion = bioma["nivelContaminacion"];
            //biomaEncontrado.listaEspecies = bioma["listaEspecies"];

            // Mostramos los datos
            cout << endl;
            cout << "****DATOS DEL BIOMA****:\n";
            cout << "Nombre: "<< biomaEncontrado.nombre <<endl;
            cout << "Dias Pasados: "<< biomaEncontrado.diasPasados <<endl;
            cout << "Nivel Salinidad: "<< biomaEncontrado.nivelSalinidad <<endl;
            cout << "Nivel Oxigeno: "<< biomaEncontrado.nivelOxigeno <<endl;
            cout << "Nivel Temperatura: "<< biomaEncontrado.nivelTemperatura <<endl;
            cout << "Nivel Contaminacion: "<< biomaEncontrado.nivelContaminacion <<endl;
            cout << "ListaEspecies: listo"; 

            return biomaEncontrado; // Retornamos el bioma con los datos
        }
    }

    cout << "Bioma no encontrado.\n";
    return Bioma(); //Damos una estruct vacia si no se encuentra
}

#endif
