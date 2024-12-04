#ifndef PARTIDA_HPP
#define PARTIDA_HPP

#include "Tiempo.hpp"
#include "Bioma.hpp"
#include "Poblacion.hpp"

using namespace std;

struct Partida {
    string nombreJugador;
    Tiempo tiempoInicio;
    Tiempo tiempoTranscurrido;
    string archivoInfo;
    string archivoEventos;
    string archivoConteoEventos;

    Bioma* bioma = nullptr;
    Poblacion* listaPoblaciones = nullptr;
};

Partida* partidaActual = nullptr;

#endif // PARTIDA_HPPs