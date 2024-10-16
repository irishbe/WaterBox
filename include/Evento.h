#ifndef EVENTO_H
#define EVENTO_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Especie.h"
#include "Tiempo.h"

using namespace std;

// Definición de la estructura del Nodo para la pila
struct Nodo {
    string descripcion;
    Nodo* siguiente;
};

// Punteros para la pila de eventos del usuario y del administrador
Nodo* pilaEventosUsuario = nullptr;
Nodo* pilaEventosAdmin = nullptr;

// Función para obtener el formato de tiempo actual
string obtenerTiempoActual() {
    return formatearTiempo(getTiempoActual()); // Función de "Tiempo.h" para formatear el tiempo
}

// Función para agregar un evento a la pila
void agregarPila(Nodo*& pila, const string& descripcion) {
    Nodo* nuevo_nodo = new Nodo();
    nuevo_nodo->descripcion = descripcion;
    nuevo_nodo->siguiente = pila;
    pila = nuevo_nodo;
}

// Función para registrar un evento en la pila y en el archivo correspondiente
void registrarEvento(const string& tipo, const string& bioma, Especie* especie1 = nullptr, bool esAdmin = false) {
    string descripcion = obtenerTiempoActual();

    // Generación de la descripción del evento según el tipo
    if (tipo == "AGREGAR ESPECIE") {
        descripcion += " Agregaste una especie " + (especie1 ? (especie1->datosEspecie->nombreComun) : "") +
                       " con ID (" + to_string(especie1->id) + ") al bioma " + bioma;
    } else if (tipo == "ELIMINAR ESPECIE") {
        descripcion += " Eliminaste un " + (especie1 ? (especie1->datosEspecie->nombreComun) : "") +
                       " con ID (" + to_string(especie1->id) + ") del bioma " + bioma;
    } else if (tipo == "MOSTRAR DATOS ESPECIE") {
        descripcion += " Se han mostrado los datos de la especie " + (especie1 ? (especie1->datosEspecie->nombreComun) : "") +
                       " con ID (" + to_string(especie1->id) + ")";
    } else if (tipo == "CREAR ESPECIE ADMIN") {
        descripcion += " Creaste una nueva especie " + (especie1 ? (especie1->datosEspecie->nombreComun) : "");
    } else if (tipo == "MODIFICAR ESPECIE ADMIN") {
        descripcion += " Modificaste la especie " + (especie1 ? (especie1->datosEspecie->nombreComun) : "");
    } else if (tipo == "ELIMINAR ESPECIE ADMIN") {
        descripcion += " Eliminaste la especie " + (especie1 ? (especie1->datosEspecie->nombreComun) : "");
    } else if (tipo == "EXTRAER DATOS ESPECIE ADMIN") {
        descripcion += " Extrajiste los datos de la especie " + (especie1 ? (especie1->datosEspecie->nombreComun) : "");
    }

    // Agregar el evento a la pila correspondiente
    if (esAdmin) {
        agregarPila(pilaEventosAdmin, descripcion);
        actualizarArchivoEventos("ColaEventosAdmin.txt", pilaEventosAdmin);
    } else {
        agregarPila(pilaEventosUsuario, descripcion);
        actualizarArchivoEventos("ColaEventos.txt", pilaEventosUsuario);
    }
}

// Función para actualizar el archivo de eventos, guardando todos los eventos en orden inverso
void actualizarArchivoEventos(const string& nombreArchivo, Nodo* pila) {
    ofstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        vector<string> eventos; // Usamos un vector para almacenar los eventos temporalmente

        // Recorremos la pila y almacenamos las descripciones en el vector
        Nodo* aux = pila;
        while (aux != nullptr) {
            eventos.push_back(aux->descripcion);
            aux = aux->siguiente;
        }

        // Escribimos los eventos en el archivo en orden inverso
        for (auto it = eventos.rbegin(); it != eventos.rend(); ++it) {
            archivo << *it << endl;
        }

        archivo.close();
    } else {
        cout << "No se pudo acceder al archivo " << nombreArchivo << endl;
    }
}

// Función para mostrar todos los eventos en la consola
void mostrarEventos(Nodo* pila) {
    vector<string> eventos; // Usamos un vector para almacenar los eventos temporalmente

    // Recorremos la pila y almacenamos las descripciones en el vector
    Nodo* aux = pila;
    while (aux != nullptr) {
        eventos.push_back(aux->descripcion);
        aux = aux->siguiente;
    }

    // Mostramos los eventos en la consola en orden inverso
    cout << "Historial de eventos:" << endl;
    for (auto it = eventos.rbegin(); it != eventos.rend(); ++it) {
        cout << *it << endl;
    }
}

#endif // EVENTO_H
