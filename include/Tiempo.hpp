#ifndef TIME_HPP
#define TIME_HPP

#include <ctime>
#include <string>
#include <vector>

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

    Tiempo tiempoActual;
    tiempoActual.hora = ltm->tm_hour;
    tiempoActual.minutos = ltm->tm_min;
    tiempoActual.segundos = ltm->tm_sec;
    tiempoActual.dia = ltm->tm_mday;
    tiempoActual.mes = 1 + ltm->tm_mon;
    tiempoActual.anio = 1900 + ltm->tm_year;

    return tiempoActual;
}

string formatearTiempo(Tiempo tiempo) {
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

string formatearFecha(Tiempo tiempo) {
    string resultado = to_string(tiempo.anio) + "-"
                       + (tiempo.mes < 10 ? "0" : "") + to_string(tiempo.mes) + "-"
                       + (tiempo.dia < 10 ? "0" : "") + to_string(tiempo.dia);
    return resultado;
}

string formatearHora(Tiempo tiempo) {
    string resultado = (tiempo.hora < 10 ? "0" : "") + to_string(tiempo.hora) + ":"
                       + (tiempo.minutos < 10 ? "0" : "") + to_string(tiempo.minutos) + ":"
                       + (tiempo.segundos < 10 ? "0" : "") + to_string(tiempo.segundos);
    return resultado;
}

// Función para comparar fechas en formato "[YYYY-MM-DD HH:MM:SS]"
bool compararFecha(string descripcion1, string descripcion2) {
    return descripcion1.substr(0, 20) < descripcion2.substr(0, 20);
}

#endif // TIME_HPP