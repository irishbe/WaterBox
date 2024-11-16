#ifndef EVENTO_H
#define EVENTO_H

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

// Guardar eventos en el archivo especificado
void registrarEventosEnArchivo(Evento* eventos, string nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo" << endl;
        return;
    }
    Evento* temp = eventos;
    while (temp) {
        archivo << "Tipo de Evento: " << temp->tipo << endl;
        archivo << "Descripción: " << temp->descripcion << endl;
        archivo << "Bioma de Ocurrencia: " << temp->biomaOcurrencia->nombre << endl;
        if (temp->especie1) archivo << "Especie 1: " << temp->especie1->datosEspecie->nombreComun << endl;
        if (temp->especie2) archivo << "Especie 2: " << temp->especie2->datosEspecie->nombreComun << endl;
        archivo << "-----------------------" << endl;
        temp = temp->sgteEvento;
    }
    archivo.close();
}

// Crear y escribir en "descripcionEventos.txt"
void guardarDescripcionEventos(const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo" << endl;
        return;
    }

    // Escribir eventos de la cola
    archivo << "Eventos en la Cola:" << endl;
    Evento* temp = colaEventos;
    while (temp) {
        archivo << "Tipo de Evento: " << temp->tipo << endl;
        archivo << "Descripción: " << temp->descripcion << endl;
        archivo << "Bioma de Ocurrencia: " << temp->biomaOcurrencia->nombre << endl;
        if (temp->especie1) archivo << "Especie 1: " << temp->especie1->datosEspecie->nombreComun << endl;
        if (temp->especie2) archivo << "Especie 2: " << temp->especie2->datosEspecie->nombreComun << endl;
        archivo << "-----------------------" << endl;
        temp = temp->sgteEvento;
    }

    // Escribir eventos de la pila
    archivo << "\nEventos en la Pila:" << endl;
    temp = pilaEventos;
    while (temp) {
        archivo << "Tipo de Evento: " << temp->tipo << endl;
        archivo << "Descripción: " << temp->descripcion << endl;
        archivo << "Bioma de Ocurrencia: " << temp->biomaOcurrencia->nombre << endl;
        if (temp->especie1) archivo << "Especie 1: " << temp->especie1->datosEspecie->nombreComun << endl;
        if (temp->especie2) archivo << "Especie 2: " << temp->especie2->datosEspecie->nombreComun << endl;
        archivo << "-----------------------" << endl;
        temp = temp->sgteEvento;
    }
    archivo.close();
}

// Crear y escribir en "conteoTiposEventos.txt"
void guardarConteoTiposEventos(const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo" << endl;
        return;
    }

    int conteoEventos[13] = {0}; // Array para contar cada tipo de evento
    Evento* temp = pilaEventos;

    // Contar eventos en la pila
    while (temp) {
        conteoEventos[temp->tipo]++;
        temp = temp->sgteEvento;
    }

    // Contar eventos en la cola
    temp = colaEventos;
    while (temp) {
        conteoEventos[temp->tipo]++;
        temp = temp->sgteEvento;
    }

    // Guardar el conteo en el archivo
    archivo << "Conteo de Tipos de Eventos:" << endl;
    for (int i = 0; i < 13; ++i) {
        archivo << "Tipo de Evento " << i << ": " << conteoEventos[i] << endl;
    }
    archivo.close();
}

// Función para mostrar los eventos registrados en pantalla
void mostrarEventos() {
    cout << "\nHistorial de eventos :" << endl << endl;

    vector<string> descripcionEventos;
    Evento* aux = pilaEventos;

    while (aux != nullptr) {
        descripcionEventos.push_back(aux->descripcion);
        aux = aux->sgteEvento;
    }

    aux = colaEventos;
    
    while (aux != nullptr) {
        descripcionEventos.push_back(aux->descripcion);
        aux = aux->sgteEvento;
    }

    ordenarEventosPorTiempo(descripcionEventos);

    // Mostramos los eventos en el orden adecuado
    for (auto it = descripcionEventos.rbegin(); it != descripcionEventos.rend(); ++it) {
        cout << *it << endl;
    }
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
        
    }else{
        enqueue(colaEventos, nuevoEvento);
    }

    registrarEventosEnArchivo(colaEventos, "ColaEventos.txt");
    mostrarEventos();
}

#endif // EVENTO_H
