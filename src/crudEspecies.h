#ifndef CRUD_ESPECIES_H
#define CRUD_ESPECIES_H

#include <iostream>
#include "crudDatos.h"
#include "Especie.h"
//#include "Evento.hpp"

using namespace std;

Especie *listaEspecies = nullptr;

void generarIDs();
void agregarEspecie();
void enlistarEspecies();
void mostrarEspecie();
void eliminarEspecie();

void generarIDs(){
    Especie *especieActual = listaEspecies;
    short id = 0;

    // Recorremos la lista para asignar los IDs
    while( especieActual != nullptr ){
        especieActual->id = id;
        id++;
        especieActual = especieActual->sgteEspecie;
    }
}

void agregarEspecie() {
    // Escogiendo el archivo de extraccion (animales.json o vegetales.json)
    string tipoEspecie, evento;

    tipoEspecie = seleccionConFlechas("Tipo de especie\n", tiposEspecies, "horizontal");
    if( tipoEspecie == "" ) return;

    // Escogiendo el nombre de la especie a agregar
    string nombre;
    vector<string> nombresEspecies = extraerNombres(tipoEspecie);
    if( nombresEspecies.empty() ){
        cout << "\nNo se encontraron especies en \"" << tipoEspecie << "\"..." << endl << endl;
        return;   
    }

    nombre = seleccionConFlechas("Seleccione el nombre de la especie", nombresEspecies, "vertical");
    if( nombre == "" ) return;

    // Asignacion de datos a la especie
    DatosEspecie *datos = extraerDatosEspecie(tipoEspecie, nombre);
    if ( datos == nullptr ) {
        cout << "\nEspecie \"" << nombre << "\" no fue encontrada en \"" << tipoEspecie << "\"... " << endl << endl;
        return;
    }

    Especie *nuevaEspecie = new Especie();
    nuevaEspecie->datosEspecie = datos;
    nuevaEspecie->sgteEspecie = nullptr;

    // Inserta en la lista
    if ( listaEspecies == nullptr ) {
        listaEspecies = nuevaEspecie;
    } else {
        Especie *aux = listaEspecies;

        // Recorremos hasta el final de la lista
        while ( aux->sgteEspecie != nullptr ) {
            aux = aux->sgteEspecie;
        }

        aux->sgteEspecie = nuevaEspecie;
    }

    generarIDs();

    //crearEvento("AGREGAR ESPECIE", "Arrecifes de coral", nuevaEspecie);
}

void enlistarEspecies(){    
    if( listaEspecies == nullptr ){
        cout << "No hay especies que enlistar..." <<endl << endl;
        return;
    }

    Especie *aux = listaEspecies;
    cout << "----------- LISTA DE ESPECIES -----------" << endl << endl;

    while ( aux != nullptr ) {
        cout << aux->id << ". " << aux->datosEspecie->nombreComun << endl;
        aux = aux->sgteEspecie;
    }
    cout << endl;
}

void mostrarEspecie(){
    enlistarEspecies();

    if( listaEspecies == nullptr ){
        return; 
    }

    Especie *aux = listaEspecies;
    short idBuscado;

    cout << "ID de la especie a mostrar mas informacion ---> "; cin>> idBuscado;

    while( aux != nullptr && aux->id != idBuscado){
        aux = aux->sgteEspecie;
    }

    if ( aux == nullptr ) {
        cout << "\nEspecie con ID (" << idBuscado << ") no encontrada..." << endl;
        return;
    }
    
    DatosEspecie *especieEncontrada = aux->datosEspecie;

    cout << "\n\n----------- DATOS DE LA ESPECIE -----------" << endl << endl;
    cout << "Nombre comun: " << especieEncontrada->nombreComun << endl;
    cout << "Nombre cientifico: " << especieEncontrada->nombreCientifico << endl;
    cout << "Familia biologica: " << especieEncontrada->familiaBiologica << endl;
    cout << "Bioma nativo: " << especieEncontrada->biomaNativo << endl;
    cout << "Esperanza de vida: " << especieEncontrada->esperanzaVida << endl;
    cout << "Tasa de reproduccion: " << especieEncontrada->tasaReproduccion << endl;
    cout << "Inactividad reproductiva: " << especieEncontrada->inactividadReproductiva << endl;
    cout << "Rango salinidad: [" << especieEncontrada->salinidadMax << ", " << especieEncontrada->salinidadMin << "]" << endl;
    cout << "Rango oxigeno: [" << especieEncontrada->oxigenoMax << ", " << especieEncontrada->oxigenoMin << "]" << endl;
    cout << "Rango temperatura: [" << especieEncontrada->temperaturaMax << ", " << especieEncontrada->temperaturaMin << "]" << endl << endl;
}

void eliminarEspecie(){
    enlistarEspecies();

    if( listaEspecies == nullptr ){
        return; 
    }

    Especie *aux = listaEspecies, *anterior = nullptr;
    short idBuscado;

    cout << "ID de la especie a eliminar ---> "; cin >> idBuscado;

    while( aux != nullptr && aux->id != idBuscado){
        anterior = aux;
        aux = aux->sgteEspecie;
    }

    if ( aux == nullptr ) {
        cout << "\nEspecie con ID (" << idBuscado << ") no encontrada..." << endl;
    }else{

        if( anterior == nullptr ){
            listaEspecies = aux->sgteEspecie;
        }else{
            anterior->sgteEspecie = aux->sgteEspecie;
        }
        
        //crearEvento("ELIMINAR ESPECIE", "Arrecifes de coral", aux);
        
        delete aux->datosEspecie;
        delete aux;

        
        // Reajustar los IDs después de la eliminación
        generarIDs();
    }
}

#endif // CRUD_ESPECIES_H