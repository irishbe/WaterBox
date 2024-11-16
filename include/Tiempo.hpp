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

bool compararFecha(string evento1, string evento2) {
    return evento1.substr(0, 20) > evento2.substr(0, 20);
}

void ordenarEventosPorTiempo(vector<string>& descripcionEventos) {
    int n = descripcionEventos.size();
    
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (!compararFecha(descripcionEventos[j], descripcionEventos[j + 1])) {
                string temp = descripcionEventos[j];
                descripcionEventos[j] = descripcionEventos[j + 1];
                descripcionEventos[j + 1] = temp;
            }
        }
    }
}

#endif // TIME_HPP