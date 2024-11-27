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

// Desformatear un string "[YYYY-MM-DD HH:MM:SS]" a un objeto Tiempo
Tiempo desformatearTiempo(string formato) {
    Tiempo tiempo;
    char separador; // Para capturar los caracteres como '-' y ':'

    stringstream ss(formato);
    ss.ignore(1); // Ignorar el primer '['
    ss >> tiempo.anio >> separador >> tiempo.mes >> separador >> tiempo.dia;
    ss >> tiempo.hora >> separador >> tiempo.minutos >> separador >> tiempo.segundos;

    return tiempo;
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

Tiempo calcularTiempoTranscurrido(Tiempo inicio) {
    Tiempo actual = getTiempoActual();
    tm tmInicio = {0}, tmActual = {0};

    // Convertir `Tiempo` a `tm` para facilitar cálculos
    tmInicio.tm_year = inicio.anio - 1900;
    tmInicio.tm_mon = inicio.mes - 1;
    tmInicio.tm_mday = inicio.dia;
    tmInicio.tm_hour = inicio.hora;
    tmInicio.tm_min = inicio.minutos;
    tmInicio.tm_sec = inicio.segundos;

    tmActual.tm_year = actual.anio - 1900;
    tmActual.tm_mon = actual.mes - 1;
    tmActual.tm_mday = actual.dia;
    tmActual.tm_hour = actual.hora;
    tmActual.tm_min = actual.minutos;
    tmActual.tm_sec = actual.segundos;

    // Convertir `tm` a `time_t` para calcular la diferencia en segundos
    time_t tInicio = mktime(&tmInicio);
    time_t tActual = mktime(&tmActual);

    int segundosTranscurridos = static_cast<int>(difftime(tActual, tInicio));

    // Convertir segundos a `Tiempo` (hh:mm:ss + días)
    Tiempo tiempoTranscurrido;
    tiempoTranscurrido.anio = 0; // No se calculan años
    tiempoTranscurrido.mes = 0;  // No se calculan meses
    tiempoTranscurrido.dia = segundosTranscurridos / (24 * 3600);
    tiempoTranscurrido.hora = (segundosTranscurridos % (24 * 3600)) / 3600;
    tiempoTranscurrido.minutos = (segundosTranscurridos % 3600) / 60;
    tiempoTranscurrido.segundos = segundosTranscurridos % 60;

    return tiempoTranscurrido;
}

#endif // TIME_HPP