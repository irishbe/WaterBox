#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "utilidades.hpp" // Incluir el header con la función moverCursor

using namespace std;

struct Evento {
    string tipo; // Nombre del evento
    int conteo;  // Conteo del evento
};

void mostrarEventosJuego(vector<Evento>& eventos) {
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
            moverCursor(7, fila++);
            cout << string(espacioTitulo, ' ') << "- " << evento.tipo << endl;
        }
    }
}

int main() {
    ifstream archivo("contadorEventos.txt");
    if (!archivo.is_open()) {
        moverCursor(10, 5);
        cout << "No hay eventos registrados." << endl;
        return 0;
    }

    vector<Evento> eventos;
    string linea;

    // Leer el archivo y extraer solo los eventos de juego
    while (getline(archivo, linea)) {
        size_t pos = linea.find("Tipo de Evento");
        if (pos != string::npos) {
            string tipo = linea.substr(pos + 15, linea.find('=') - pos - 15);
            tipo.erase(0, tipo.find_first_not_of(' '));  // Limpiar espacios
            tipo.erase(tipo.find_last_not_of(' ') + 1);
            
            int conteo = stoi(linea.substr(linea.find('=') + 2));
            // Mostrar solo los eventos de juego
            if (tipo != "CREAR_ESPECIE_ADMIN" && tipo != "ELIMINAR_ESPECIE_ADMIN" && 
                tipo != "EDITAR_ESPECIE_ADMIN" && tipo != "CREAR_BIOMA_ADMIN" &&
                tipo != "ELIMINAR_BIOMA_ADMIN" && tipo != "EDITAR_BIOMA_ADMIN") {
                eventos.push_back({tipo, conteo});
            }
        }
    }

    archivo.close();

    mostrarEventosJuego(eventos); // Llamar a la función que muestra los eventos de juego

    return 0;
}
