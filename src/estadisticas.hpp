#ifndef ESTADISTICAS_HPP
#define ESTADISTICAS_HPP

#include "utilidades.hpp"
#include <fstream>

using namespace std;

struct ConteoEvento {
    string tipo;
    int conteo;
};

vector<ConteoEvento> leerEventosGeneral() {
    ifstream archivo("contadorEventosGeneral.txt", ios::in);
    vector<ConteoEvento> eventos;

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo de conteos generales... " << endl;
        return eventos;
    }

    string linea;
    bool dentroDeEventos = false;

    while (getline(archivo, linea)) {
        // Ignorar encabezado y línea separadora
        if (linea.find("CONTEO GENERAL DE LOS EVENTOS") != string::npos) {
            dentroDeEventos = true;
            continue;
        }
        if (linea.find("*******************************************************************************************************") != string::npos) {
            continue;
        }

        if (dentroDeEventos) {
            // Buscar líneas con el formato `TIPO = NUMERO`
            size_t posIgual = linea.find('=');
            if (posIgual != string::npos) {
                // Extraer tipo de evento y conteo
                string tipo = linea.substr(0, posIgual - 1); // Antes del '='
                int conteo = stoi(linea.substr(posIgual + 2)); // Después del '='
                
                // Eliminar espacios alrededor del tipo
                tipo.erase(0, tipo.find_first_not_of(' ')); // Izquierda
                tipo.erase(tipo.find_last_not_of(' ') + 1); // Derecha
                
                eventos.push_back({tipo, conteo});
            }
        }
    }

    archivo.close();
    return eventos;
}

void mostrarEventosGenerales(vector<ConteoEvento>& eventos) {
    int totalEventos = 0;
    for (const auto& evento : eventos) {
        totalEventos += evento.conteo;
    }

    // Si no hay eventos, mostrar mensaje y salir
    if (totalEventos == 0) {
        moverCursor(10, 5);
        cout << "No se registraron eventos de juego." << endl;
        return;
    }

    // Centrar el título y las estadísticas, moviéndolas más a la derecha
    int consolaAncho = 80; // Asumimos un ancho de consola de 80 caracteres
    string titulo = "\tESTADÍSTICAS DE EVENTOS DEL SIMULADOR";
    int espacioTitulo = (consolaAncho - titulo.length()) / 2 + 10; // Desplazamos más a la derecha
    moverCursor(5, 2);
    cout << string(espacioTitulo, ' ') << titulo << endl;

    moverCursor(5, 4);
    // Alineamos mejor los encabezados con mayor espacio para las columnas
    cout << string(espacioTitulo, ' ') << left << setw(30) << "Tipo de Evento" 
         << right << setw(10) << "Conteo"
         << setw(15) << "% del Total"
         << setw(20) << "Gráfico" << endl;

    moverCursor(5, 5);
    // Línea de separación para las cabeceras
    cout << string(espacioTitulo, ' ') << string(75, '-') << endl;

    int fila = 6; // Para posicionar cada evento en una nueva fila
    for (const auto& evento : eventos) {
        double porcentaje = (evento.conteo / static_cast<double>(totalEventos)) * 100;

        // Calcular el tamaño del gráfico de barras
        int barraLength = (evento.conteo * 10) / totalEventos; // Gráfico sobre 10

        moverCursor(5, fila++);
        cout << string(espacioTitulo, ' ') << left << setw(30) << evento.tipo
             << right << setw(10) << evento.conteo
             << setw(15) << fixed << setprecision(2) << porcentaje << "%";

        // Agregar un margen extra de espacio para el gráfico
        cout << setw(10) << " "; // Espacio extra entre porcentaje y gráfico

        // Mostrar gráfico de barras
        cout << "[";
        for (int i = 0; i < barraLength; i++) {
            cout << "*";
        }
        cout << string(10 - barraLength, ' ') << "]" << endl; // Rellenar hasta 10
    }

    moverCursor(5, fila + 2);
    cout << string(espacioTitulo, ' ') << "Total de Eventos Registrados: " << totalEventos << endl;

    // Mostrar eventos con cero conteo
    moverCursor(5, fila + 4);
    cout << string(espacioTitulo, ' ') << "Eventos con cero conteo:" << endl;

    fila += 5;
    for (const auto& evento : eventos) {
        if (evento.conteo == 0) {
            moverCursor(5, fila++);
            cout << string(espacioTitulo, ' ') << "- " << evento.tipo << endl;
        }
    }
}

void imprimirEstadisticas() {
    vector<ConteoEvento> eventos = leerEventosGeneral();

    if (eventos.empty()) {
        cout << "No se encontraron eventos registrados en el archivo." << endl;
    } else {
        mostrarEventosGenerales(eventos);
    }
}

#endif //