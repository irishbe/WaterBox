#ifndef TIME_H
#define TIME_H

#include <ctime>

using namespace std;

struct Tiempo {
    int hora;
    int minutos;
    int segundos;
    int dia;
    int mes;
    int anio;
};

Tiempo getTiempoActual() {
    time_t ahora = time(0);
    tm *ltm = localtime(&ahora);

    Time tiempoActual;
    tiempoActual.hora = ltm->tm_hour;
    tiempoActual.minutos = ltm->tm_min;
    tiempoActual.segundos = ltm->tm_sec;
    tiempoActual.dia = ltm->tm_mday;
    tiempoActual.mes = 1 + ltm->tm_mon;         // Los meses van de 0 a 11, así que se suma 1
    tiempoActual.anio = 1900 + ltm->tm_year;    // El año es contado desde 1900

    return tiempoActual;
}

// Función para formatear el tiempo [YYYY-MM-DD HH:MM:SS]

string formatearTiempo(Tiempo tiempo) {
    // Construir la cadena en el formato solicitado
    string resultado = "[" 
                       + to_string(tiempo.anio) + "-"
                       + (tiempo.mes < 10 ? "0" : "") + to_string(tiempo.mes) + "-"
                       + (tiempo.dia < 10 ? "0" : "") + to_string(tiempo.dia) + " "
                       + (tiempo.hora < 10 ? "0" : "") + to_string(tiempo.hora) + ":"
                       + (tiempo.minutos < 10 ? "0" : "") + to_string(tiempo.minutos) + ":"
                       + (tiempo.segundos < 10 ? "0" : "") + to_string(tiempo.segundos)
                       + "]";
    return resultado;
}

#endif // TIME_H
