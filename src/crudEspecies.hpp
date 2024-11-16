#ifndef CRUD_ESPECIES_HPP
#define CRUD_ESPECIES_HPP

#include <iostream>
#include "crudPoblaciones.hpp"
#include "Evento.hpp"

using namespace std;

void generarIDs();
void agregarEspecie();
void enlistarEspecies();
void buscarEspecie();
void eliminarEspecie();

Especie* extraerListaEspecies();


void agregarEspecie(){
    string tipoEspecie, nombreEspecie;
    Especie *nuevaEspecie = new Especie();

    // SELECCIONAR EL TIPO DE ESPECIE A AGREGAR
    tipoEspecie = seleccionConFlechas("Tipo de especie\n", tiposEspecies, "horizontal");
    
    if( tipoEspecie.empty() ){
        return;
    }

    // BUSCANDO LOS NOMBRES DE LAS ESPECIES EN LOS JSON
    vector<string> nombresEspecies = extraerNombres(tipoEspecie);

    if( nombresEspecies.empty() ){
        cout << "\nNo se encontraron especies en \"" << tipoEspecie << "\"..." << endl << endl;
        return;
    }

    // SELECCIONAR EL NOMBRE DE LA ESPECIE A AGREGAR
    nombreEspecie = seleccionConFlechas("Seleccione el nombre de la especie", nombresEspecies, "vertical");
    
    if( nombreEspecie.empty() ){
        return;
    }

    // ASIGNACION DE DATOS A LA ESPECIE
    DatosEspecie *datos = extraerDatosEspecie(tipoEspecie, nombreEspecie);

    if ( datos == nullptr ) {
        cout << "\nEspecie \"" << nombreEspecie << "\" no fue encontrada en \"" << tipoEspecie << "\"... " << endl << endl;
        return;
    }


    // DATOS VALIDADOS
    nuevaEspecie->tipoEspecie = tipoEspecie;
    nuevaEspecie->datosEspecie = datos;
    nuevaEspecie->sgteEspecie = nullptr;

    /*
        Solucion temporal
    */
    Bioma *bioma = new Bioma();
    bioma->nombre = "Bioma temporal";

    insertarEspecie(nuevaEspecie);
    registrarEvento(AGREGAR_ESPECIE, bioma, nuevaEspecie);
}

void enlistarEspecies(){
    Especie *listaEspecies = extraerListaEspecies(), *especieActual = nullptr;

    if ( listaEspecies == nullptr ){
        cout << "\nNo hay especies en la lista..." << endl << endl;
        return;
    }

    especieActual = listaEspecies;

    // IMPRESION DE LAS ESPECIES DISPONIBLES EN LA POBLACION
    system("cls");
    cout << "----------- LISTA DE ESPECIES DE LA POBLACION  -----------" << endl << endl;

    while ( especieActual != nullptr ) {
        cout << especieActual->id << ". " << especieActual->datosEspecie->nombreComun << endl;
        especieActual = especieActual->sgteEspecie;
    }

    cout << endl;
}

void buscarEspecie() {
    int idEspecie;
    Especie *listaEspecies = extraerListaEspecies(), *especieActual = nullptr, *especieEncontrada = nullptr;

    if ( listaEspecies == nullptr ){
        cout << "\nNo hay especies en la lista..." << endl << endl;
        return;
    }

    especieActual = listaEspecies;

    // IMPRESION DE LAS ESPECIES DISPONIBLES EN LA POBLACION
    system("cls");
    cout << "----------- LISTA DE ESPECIES DE LA POBLACION  -----------" << endl << endl;

    while ( especieActual != nullptr ) {
        cout << especieActual->id << ". " << especieActual->datosEspecie->nombreComun << endl;
        especieActual = especieActual->sgteEspecie;
    }

    cout << endl;
    

    // BUSCANDO LA ESPECIE EN LA LISTA DE ESPECIES DE LA POBLACION
    cout << "\nIngrese el ID de la especie que desea ver sus datos: "; cin >> idEspecie;

    especieActual = listaEspecies;

    while (especieActual != nullptr) {
        if (especieActual->id == idEspecie) {
            especieEncontrada = especieActual;  // Encontrar la especie
            break;
        }
        especieActual = especieActual->sgteEspecie;
    }

    if (especieEncontrada == nullptr) {
        cout << "\nEspecie con ID (" << idEspecie << ") no encontrada..." << endl;
        return;
    }

    cout << "\n\n----------- DATOS DE LA ESPECIE -----------" << endl << endl;
    cout << "Nombre comun: " << especieEncontrada->datosEspecie->nombreComun << endl;
    cout << "Nombre cientifico: " << especieEncontrada->datosEspecie->nombreCientifico << endl;
    cout << "Familia biologica: " << especieEncontrada->datosEspecie->familiaBiologica << endl;
    cout << "Bioma nativo: " << especieEncontrada->datosEspecie->biomaNativo << endl;
    cout << "Esperanza de vida: " << especieEncontrada->datosEspecie->esperanzaVida << endl;
    cout << "Tasa de reproduccion: " << especieEncontrada->datosEspecie->tasaReproduccion << endl;
    cout << "Inactividad reproductiva: " << especieEncontrada->datosEspecie->inactividadReproductiva << endl;
    cout << "Rango salinidad: [" << especieEncontrada->datosEspecie->salinidadMax << ", " << especieEncontrada->datosEspecie->salinidadMin << "]" << endl;
    cout << "Rango oxigeno: [" << especieEncontrada->datosEspecie->oxigenoMax << ", " << especieEncontrada->datosEspecie->oxigenoMin << "]" << endl;
    cout << "Rango temperatura: [" << especieEncontrada->datosEspecie->temperaturaMax << ", " << especieEncontrada->datosEspecie->temperaturaMin << "]" << endl << endl;
}

void eliminarEspecie() {
    int idEspecie;
    Especie *listaEspecies = extraerListaEspecies(), *especieActual = nullptr, *especieAnterior = nullptr, *especieEncontrada = nullptr;

    if ( listaEspecies == nullptr ){
        cout << "\nNo hay especies en la lista..." << endl << endl;
        return;
    }

    especieActual = listaEspecies;

    // IMPRESION DE LAS ESPECIES DISPONIBLES EN LA POBLACION
    system("cls");
    cout << "----------- LISTA DE ESPECIES DE LA POBLACION  -----------" << endl << endl;

    while ( especieActual != nullptr ) {
        cout << especieActual->id << ". " << especieActual->datosEspecie->nombreComun << endl;
        especieActual = especieActual->sgteEspecie;
    }

    cout << endl;
    

    // BUSCANDO LA ESPECIE EN LA LISTA DE ESPECIES DE LA POBLACION
    cout << "\nIngrese el ID de la especie que desea ver sus datos: "; cin >> idEspecie;

    especieActual = listaEspecies;

    while ( especieActual != nullptr ) {

        if (especieActual->id == idEspecie) {
            especieEncontrada = especieActual;  // Encontrar la especie
            break;
        }

        especieAnterior = especieActual;
        especieActual = especieActual->sgteEspecie;
    }

    if ( especieEncontrada == nullptr ) {
        cout << "\nEspecie con ID (" << idEspecie << ") no encontrada..." << endl;
        return;
    }

    // VERIFICA SI SE BORRA LA CABEZA
    if ( especieAnterior == nullptr ) {
        listaEspecies = especieActual->sgteEspecie;

    } else{
        especieAnterior->sgteEspecie = especieActual->sgteEspecie;
        
        delete especieActual->datosEspecie;
        delete especieActual;

        // ELIMINAR POBLACION SI NO HAY ESPECIES
        Poblacion* poblacionActual = listaPoblaciones;

        while (poblacionActual != nullptr) {
            if (poblacionActual->listaEspecies == nullptr) {

                // ELIMINAR POBLACION VACIA
                if (poblacionActual->antePoblacion != nullptr) {
                    poblacionActual->antePoblacion->sgtePoblacion = poblacionActual->sgtePoblacion;
                }

                if (poblacionActual->sgtePoblacion != nullptr) {
                    poblacionActual->sgtePoblacion->antePoblacion = poblacionActual->antePoblacion;
                }

                delete poblacionActual;
                break;
            }
            poblacionActual = poblacionActual->sgtePoblacion;
        }
    }


    registrarEvento(ELIMINAR_ESPECIE, nullptr, especieEncontrada);
}

Especie* extraerListaEspecies(){
    int idPoblacion;
    Poblacion* poblacionSeleccionada;
    Especie* especieActual = nullptr;

    mostrarPoblaciones();

    if( listaPoblaciones == nullptr ){
        return nullptr;
    }
    
    cout << "\nIngrese el ID de la población que desea ver sus especies: "; cin >> idPoblacion;

    // IMPRIMIENDO LA LISTA DE ESPECIES DE LA POBLACION
    poblacionSeleccionada = extraerPoblacion(idPoblacion);

    if( poblacionSeleccionada == nullptr ){
        cout << "No hay especies que enlistar..." <<endl << endl;
        return nullptr;
    }

    return poblacionSeleccionada->listaEspecies;
}

#endif // CRUD_ESPECIES_H