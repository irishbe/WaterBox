#ifndef CRUDDATOS_H
#define CRUDDATOS_H

#include <iostream>
#include "Evento.h"
#include "Especie.h"

using namespace std;

// Función para crear una nueva especie
void crearEspecie(Especie*& especie, const string& nombreComun, const string& biomaNativo, bool esAdmin = false) {
    // Asignar valores a la especie
    especie = new Especie();
    especie->datosEspecie->nombreComun = nombreComun;
    especie->datosEspecie->biomaNativo = biomaNativo;

    // Registrar el evento en la pila y el archivo correspondiente
    registrarEvento("CREAR ESPECIE ADMIN", biomaNativo, especie, esAdmin);
}

// Función para modificar una especie existente
void modificarEspecie(Especie* especie, const string& nuevoNombreComun, const string& nuevoBiomaNativo, bool esAdmin = false) {
    if (especie != nullptr) {
        // Modificar los datos de la especie
        especie->datosEspecie->nombreComun = nuevoNombreComun;
        especie->datosEspecie->biomaNativo = nuevoBiomaNativo;

        // Registrar el evento en la pila y el archivo correspondiente
        registrarEvento("MODIFICAR ESPECIE ADMIN", nuevoBiomaNativo, especie, esAdmin);
    } else {
        cout << "Especie no encontrada." << endl;
    }
}

// Función para eliminar una especie
void eliminarEspecie(Especie*& especie, const string& biomaNativo, bool esAdmin = false) {
    if (especie != nullptr) {
        // Registrar el evento en la pila y el archivo correspondiente antes de eliminar
        registrarEvento("ELIMINAR ESPECIE ADMIN", biomaNativo, especie, esAdmin);

        // Eliminar la especie
        delete especie;
        especie = nullptr;
    } else {
        cout << "Especie no encontrada." << endl;
    }
}

// Función para extraer los datos de una especie
void extraerDatosEspecie(Especie* especie, const string& biomaNativo, bool esAdmin = false) {
    if (especie != nullptr) {
        // Mostrar los datos de la especie
        cout << "Nombre Común: " << especie->datosEspecie->nombreComun << endl;
        cout << "Bioma Nativo: " << especie->datosEspecie->biomaNativo << endl;

        // Registrar el evento en la pila y el archivo correspondiente
        registrarEvento("EXTRAER DATOS ESPECIE ADMIN", biomaNativo, especie, esAdmin);
    } else {
        cout << "Especie no encontrada." << endl;
    }
}

#endif // CRUDDATOS_H
