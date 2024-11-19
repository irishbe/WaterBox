#include "Poblacion.hpp"
#include "crudDatos.hpp"
#include "Evento.hpp"

using namespace std;

void insertarEspecie(Especie* nuevaEspecie);
Poblacion* extraerPoblacion(string id);

void crearPoblacion(Especie* nuevaEspecie);
void mostrarPoblaciones();
void mostrarEspeciesDePoblacion(string id);

Poblacion* listaPoblaciones = nullptr;


void generarIDPoblacion() {
    Poblacion* poblacionActual = listaPoblaciones;
    int id = 0;

    // Recorremos la lista de poblaciones para asignar los IDs
    while ( poblacionActual != nullptr ){
        poblacionActual->id = id;
        id++;
        poblacionActual = poblacionActual->sgtePoblacion;
    }
}

void generarIDEspecie(Poblacion* poblacion) {
    Especie* especieActual = poblacion->listaEspecies;
    int id = 0;

    // Recorremos la lista de poblaciones para asignar los IDs
    while ( especieActual != nullptr ){
        especieActual->id = id;
        id++;
        especieActual = especieActual->sgteEspecie;
    }
}

void insertarEspecie(Especie* nuevaEspecie){
    bool existePoblacion = false;
    Poblacion* poblacionActual = listaPoblaciones;
    Poblacion* poblacionEncontrada = nullptr;

    // RECORRE PARA BUSCAR SI EXISTE UNA POBLACION PARA ESA ESPECIE
    while( poblacionActual != nullptr && !existePoblacion ){
        
        if( poblacionActual->nombreEspecie == nuevaEspecie->datosEspecie->nombreComun ){
            poblacionEncontrada = poblacionActual;
            existePoblacion = true;
        }

        poblacionActual = poblacionActual->sgtePoblacion;
    }

    if( existePoblacion ){
        Especie* especieActual = poblacionEncontrada->listaEspecies;

        while ( especieActual->sgteEspecie != nullptr ) {
            especieActual = especieActual->sgteEspecie;
        }

        especieActual->sgteEspecie = nuevaEspecie;

        poblacionEncontrada->contadorEspecies++;
        generarIDEspecie(poblacionEncontrada);

    } else{
        crearPoblacion(nuevaEspecie);
    }
}

void crearPoblacion(Especie* nuevaEspecie){
    Poblacion* nuevaPoblacion = new Poblacion();

    nuevaPoblacion->antePoblacion = nullptr;
    nuevaPoblacion->sgtePoblacion = nullptr;

    nuevaPoblacion->listaEspecies = nuevaEspecie;
    nuevaPoblacion->tipoEspecie = nuevaEspecie->tipoEspecie;
    nuevaPoblacion->nombreEspecie = nuevaEspecie->datosEspecie->nombreComun;
    nuevaPoblacion->contadorEspecies = 1;

    generarIDEspecie(nuevaPoblacion);

    if ( listaPoblaciones == nullptr ){
        listaPoblaciones = nuevaPoblacion;

    }else{
        Poblacion *aux = listaPoblaciones;

        while( aux->sgtePoblacion != nullptr ){
            aux = aux->sgtePoblacion;
        }

        nuevaPoblacion->antePoblacion = aux;
        aux->sgtePoblacion = nuevaPoblacion;
    }

    generarIDPoblacion();
}

void mostrarPoblaciones() {
    Poblacion* poblacionActual = listaPoblaciones;

    if ( listaPoblaciones == nullptr ) {
        cout << "No hay poblaciones registradas." << endl << endl;
        return;
    }

    cout << "----------- LISTA DE POBLACIONES -----------" << endl << endl;
    
    while ( poblacionActual != nullptr ) {
        cout << poblacionActual->id << ". Poblacion de (" << poblacionActual->tipoEspecie << " - " << poblacionActual->nombreEspecie << ")" << endl;
        poblacionActual = poblacionActual->sgtePoblacion;
    }
}

void buscarPoblacion() {
    string id;
    cout << "Ingrese el ID de la población a buscar: "; getline(cin, id);

    Poblacion* poblacionBuscada = listaPoblaciones;

    // RECORRE PARA BUSCAR LA POBLACION SEGUN EL ID
    while ( poblacionBuscada != nullptr ) {

        if ( poblacionBuscada->id == id) {
            cout << "POBLACION ENCONTRADA! " << endl;

            cout << "ID: " << poblacionBuscada->id << endl;
            cout << "Tipo de sus especies: " << poblacionBuscada->tipoEspecie << endl;
            cout << "Nombre de sus especies: " << poblacionBuscada->nombreEspecie << endl;
            cout << "Cantidad de especies presentes: " << poblacionBuscada->contadorEspecies << endl;

            return;
        }

        poblacionBuscada = poblacionBuscada->sgtePoblacion;
    }

    cout << "Población con ID " << id << " no encontrada." << endl;
}

Poblacion* extraerPoblacion(string id){
    Poblacion* poblacionBuscada = listaPoblaciones;

    // RECORRE PARA BUSCAR LA POBLACION SEGUN EL ID
    while ( poblacionBuscada != nullptr ) {

        if ( poblacionBuscada->id == id) {
            return poblacionBuscada;
        }

        poblacionBuscada = poblacionBuscada->sgtePoblacion;
    }

    cout << "Población con ID " << id << " no encontrada." << endl;
    return poblacionBuscada;
}