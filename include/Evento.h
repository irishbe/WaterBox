#ifndef EVENTO_H
#define EVENTO_H

#include <fstream>
#include "Especie.h"
#include "Tiempo.h"

using namespace std;

void agregarColaEventos(string descripcionEvento);

struct Evento {
    string tipo;
    string descripcion;
    Tiempo tiempoOcurrencia;
    Especie *especieInvolucrada1;
    Especie *especieInvolucrada2;
    string biomaOcurrencia;
};

void crearEvento(string tipo, string bioma, Especie *especie1 = nullptr, Especie *especie2 = nullptr){
    Evento evento;

    evento.tiempoOcurrencia = getTiempoActual();
    evento.biomaOcurrencia = bioma;

    if( tipo == "AGREGAR ESPECIE" ){
        evento.especieInvolucrada1 = especie1;
        evento.descripcion = formatearTiempo(evento.tiempoOcurrencia)
                             + " Agregaste un " + evento.especieInvolucrada1->datosEspecie->nombreComun
                             + " con ID (" + to_string(evento.especieInvolucrada1->id) + ")"
                             + " al bioma " + evento.biomaOcurrencia;
    }
    else if( tipo == "ELIMINAR ESPECIE" ){
        evento.especieInvolucrada1 = especie1;
        evento.descripcion = formatearTiempo(evento.tiempoOcurrencia)
                             + " Eliminaste un " + evento.especieInvolucrada1->datosEspecie->nombreComun
                             + " con ID (" + to_string(evento.especieInvolucrada1->id) + ")"
                             + " del bioma " + evento.biomaOcurrencia;
    }

    // agregarColaEventos(evento)
    agregarColaEventos(evento.descripcion);
}

void agregarColaEventos(string descripcionEvento){
    ofstream archivo("catalogo/ColaEventos.txt", ios::app);

    if( archivo.is_open() ){
        archivo << descripcionEvento << endl;
    }else{
        cout << "No se pudo acceder a la Cola de Eventos.. " << endl;
    }

    archivo.close();
}

#endif // EVENTO_H