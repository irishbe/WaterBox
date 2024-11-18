#ifndef EVENTO_HPP
#define EVENTO_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Especie.hpp"
#include "Tiempo.hpp"
#include "Bioma.hpp"

using namespace std;

// Enum para los tipos de eventos
enum TipoEvento {
    AGREGAR_ESPECIE,
    ELIMINAR_ESPECIE,
    MODIFICAR_FACTORES,
    REPRODUCCION,
    DEPREDACION,
    CAZA,
    ENFERMEDAD,
    CREAR_ESPECIE_ADMIN,
    ELIMINAR_ESPECIE_ADMIN,
    EDITAR_ESPECIE_ADMIN,
    CREAR_BIOMA_ADMIN,
    ELIMINAR_BIOMA_ADMIN,
    EDITAR_BIOMA_ADMIN
};

// Almacena el conteo de tipos de eventos
int conteoTiposEvento[13] = {0};

// Estructura del evento
struct Evento {
    TipoEvento tipo;
    string descripcion;
    Tiempo tiempo;
    Bioma* biomaOcurrencia;
    Especie* especie1;
    Especie* especie2;
    Evento* sgteEvento;
};

// Listas globales para la pila y las colas
Evento* pilaEventos = nullptr;
Evento* colaEventos = nullptr;

// Archivo de eventos .txt
const string ARCHIVO_EVENTOS_HOY = "eventos[" + formatearFecha( getTiempoActual() ) + "].txt";
const string ARCHIVO_CONTEO_EVENTOS = "contadorEventos.txt";

// Función para agregar evento a la pila
void push(Evento*& pilaEventos, Evento* nuevoEvento) {
    nuevoEvento->sgteEvento = pilaEventos;
    pilaEventos = nuevoEvento;
}

// Función para remover el último evento de la pila
Evento* pop(Evento*& pilaEventos) {
    if (!pilaEventos) return nullptr;
    Evento* eventoEliminado = pilaEventos;
    pilaEventos = pilaEventos->sgteEvento;
    eventoEliminado->sgteEvento = nullptr;
    return eventoEliminado;
}

// Función para agregar evento al final de la cola
void enqueue(Evento*& colaEventos, Evento* nuevoEvento) {
    if (!colaEventos) {
        colaEventos = nuevoEvento;
    } else {
        Evento* temp = colaEventos;
        while (temp->sgteEvento) {
            temp = temp->sgteEvento;
        }
        temp->sgteEvento = nuevoEvento;
    }
}

// Funcion para ordenar los eventos por fecha
void ordenarEventosPorTiempo(vector<Evento>& eventos) {
    int n = eventos.size();
    
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (!compararFecha(eventos[j].descripcion, eventos[j + 1].descripcion)) {
                Evento temp = eventos[j];
                eventos[j] = eventos[j + 1];
                eventos[j + 1] = temp;
            }
        }
    }
}

// Juntar y extrer todos los eventos de la cola y la pila ordenados por tiempo
vector<Evento> eventosPilaCola(){
    vector<Evento> eventos;

    // Agregar eventos de la pila al vector
    Evento* temp = pilaEventos;

    while (temp != nullptr) {
        eventos.push_back(*temp);
        temp = temp->sgteEvento;
    }

    // Agregar eventos de la cola al vector
    temp = colaEventos;
    
    while (temp != nullptr) {
        eventos.push_back(*temp);
        temp = temp->sgteEvento;
    }

    ordenarEventosPorTiempo(eventos);

    return eventos;
}

// Crear y escribir en "estadisticasSimulador.txt"
void actualizarConteoEventos(Evento *evento) {
    ifstream archivoLectura(ARCHIVO_CONTEO_EVENTOS);

    if (archivoLectura) {
        string linea;
        int index = 0;
        while (getline(archivoLectura, linea) && index < 13) {
            size_t pos = linea.find("=");
            if (pos != string::npos) {
                conteoTiposEvento[index] = stoi(linea.substr(pos + 1));
            }
            index++;
        }
        archivoLectura.close();
    }

    if (evento->tipo >= 0 && evento->tipo < 13) {
        conteoTiposEvento[evento->tipo]++;
    }

    ofstream archivoEscritura(ARCHIVO_CONTEO_EVENTOS);
    if (!archivoEscritura) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    archivoEscritura << "Conteo de Tipos de Eventos:" << endl;
    archivoEscritura << "1. AGREGAR_ESPECIE = " << conteoTiposEvento[AGREGAR_ESPECIE] << endl;
    archivoEscritura << "2. ELIMINAR_ESPECIE = " << conteoTiposEvento[ELIMINAR_ESPECIE] << endl;
    archivoEscritura << "3. MODIFICAR_FACTORES = " << conteoTiposEvento[MODIFICAR_FACTORES] << endl;
    archivoEscritura << "4. REPRODUCCION = " << conteoTiposEvento[REPRODUCCION] << endl;
    archivoEscritura << "5. DEPREDACION = " << conteoTiposEvento[DEPREDACION] << endl;
    archivoEscritura << "6. CAZA = " << conteoTiposEvento[CAZA] << endl;
    archivoEscritura << "7. ENFERMEDAD = " << conteoTiposEvento[ENFERMEDAD] << endl;
    archivoEscritura << "8. CREAR_ESPECIE_ADMIN = " << conteoTiposEvento[CREAR_ESPECIE_ADMIN] << endl;
    archivoEscritura << "9. ELIMINAR_ESPECIE_ADMIN = " << conteoTiposEvento[ELIMINAR_ESPECIE_ADMIN] << endl;
    archivoEscritura << "10. EDITAR_ESPECIE_ADMIN = " << conteoTiposEvento[EDITAR_ESPECIE_ADMIN] << endl;
    archivoEscritura << "11. CREAR_BIOMA_ADMIN = " << conteoTiposEvento[CREAR_BIOMA_ADMIN] << endl;
    archivoEscritura << "12. ELIMINAR_BIOMA_ADMIN = " << conteoTiposEvento[ELIMINAR_BIOMA_ADMIN] << endl;
    archivoEscritura << "13. EDITAR_BIOMA_ADMIN = " << conteoTiposEvento[EDITAR_BIOMA_ADMIN] << endl;

    archivoEscritura.close();
}

// Crear y escribir en "eventos[FECHA].txt"
void guardarEventoArchivo(Evento* nuevoEvento) {
    ofstream archivo(ARCHIVO_EVENTOS_HOY, ios::app);
    if (!archivo) {
        cerr << "Error al abrir el archivo" << endl;
        return;
    }

    archivo << "Tipo de Evento: " << nuevoEvento->tipo << endl;
    archivo << "Descripción: " << nuevoEvento->descripcion << endl;
    archivo << "Bioma de Ocurrencia: " << nuevoEvento->biomaOcurrencia->nombre << endl;
    if (nuevoEvento->especie1) archivo << "Especie 1: " << nuevoEvento->especie1->datosEspecie->nombreComun << endl;
    if (nuevoEvento->especie2) archivo << "Especie 2: " << nuevoEvento->especie2->datosEspecie->nombreComun << endl;
    archivo << "-----------------------" << endl;

    archivo.close();

    actualizarConteoEventos(nuevoEvento);
}

void registrarEvento(TipoEvento tipo, Bioma* bioma = nullptr, Especie* especie1 = nullptr, Especie* especie2 = nullptr) {
    Evento* nuevoEvento = new Evento;
    string descripcion = formatearTiempo( getTiempoActual() );

    // Generar la descripción del evento según el tipo
    switch (tipo) {
        case AGREGAR_ESPECIE:
            descripcion += " Agregaste una especie " + (especie1 ? especie1->datosEspecie->nombreComun : "") +
                           " al bioma " + bioma->nombre;
            break;
        case ELIMINAR_ESPECIE:
            descripcion += " Eliminaste una especie " + (especie1 ? especie1->datosEspecie->nombreComun : "") +
                           " del bioma " + bioma->nombre;
            break;
        case MODIFICAR_FACTORES:
            descripcion += " Modificaste los factores del bioma " + bioma->nombre + " " +
                           "[o:" + to_string(bioma->nivelOxigeno)       + "," +
                           "s:"  + to_string(bioma->nivelSalinidad)     + "," +
                           "t:"  + to_string(bioma->nivelTemperatura)   + "," +
                           "c:"  + to_string(bioma->nivelContaminacion) + "]";
            break;
        case CREAR_ESPECIE_ADMIN:
            descripcion += " Creaste una nueva especie " + (especie1 ? especie1->datosEspecie->nombreComun : "");
            break;
        case EDITAR_ESPECIE_ADMIN:
            descripcion += " Editaste la especie " + (especie1 ? especie1->datosEspecie->nombreComun : "");
            break;
        case ELIMINAR_ESPECIE_ADMIN:
            descripcion += " Eliminaste la especie " + (especie1 ? especie1->datosEspecie->nombreComun : "");
            break;
        case CREAR_BIOMA_ADMIN:
            descripcion += " Creaste un nuevo bioma " + bioma->nombre;
            break;
        case EDITAR_BIOMA_ADMIN:
            descripcion += " Editaste el bioma " + bioma->nombre;
            break;
        case ELIMINAR_BIOMA_ADMIN:
            descripcion += " Eliminaste el bioma " + bioma->nombre;
            break;
        default:
            descripcion += " Evento ??? registrado.";
            break;
    }

    // Configurar el evento
    nuevoEvento->tipo = tipo;
    nuevoEvento->descripcion = descripcion;
    nuevoEvento->biomaOcurrencia = bioma;
    nuevoEvento->especie1 = especie1;
    nuevoEvento->especie2 = especie2;
    nuevoEvento->sgteEvento = nullptr;
    
    if( AGREGAR_ESPECIE || ELIMINAR_ESPECIE || MODIFICAR_FACTORES ){
        push(pilaEventos, nuevoEvento);
    }else{
        enqueue(colaEventos, nuevoEvento);
    }

    guardarEventoArchivo(nuevoEvento);
}

// Función para mostrar los eventos registrados en pantalla
void mostrarEventos() {
    cout << "\nHistorial de eventos :" << endl << endl;

    // Mostramos los eventos en el orden adecuado
    vector<Evento> eventos = eventosPilaCola();
    for(int i=0; i < eventos.size(); i++) {
        cout << eventos[i].descripcion << endl;
    }
}

#endif // EVENTO_HPP