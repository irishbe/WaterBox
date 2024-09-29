#ifndef EVENTO_H
#define EVENTO_H

#include "Especie.h"
#include "Tiempo.h"

using namespace std;

struct Evento {
    string tipo;
    string descripcion;
    Tiempo tiempoOcurrencia;
    Especie especieInvolucrada1;
    Especie especieInvolucrada2;
    string biomaOcurrencia;
};

string crearEvento(string tipo, Especie especie1, Especie especie2, string bioma){
    Evento evento;

    if( tipo == "ESPECIE AGREGADA" ){
        evento.tiempoOcurrencia = getTiempoActual();
        evento.especieInvolucrada1 = especie1;
        evento.biomaOcurrencia = bioma;
        evento.descripcion = formatearTiempo(evento.tiempoOcurrencia)
                             + " Agregaste un " + evento.especieInvolucrada1 
                             + " al bioma " + evento.bioma;
    }

    // agregarColaEventos(evento)
    return evento.descripcion;
}

#endif // EVENTO_H
