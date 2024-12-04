#include "crudDatos.hpp"
#include "Evento.hpp"
#include "Partida.hpp"

using namespace std;

vector<string> obtenerPoblaciones(){
    vector<string> poblaciones;
    Poblacion* poblacion = partidaActual->listaPoblaciones;
    
    while (poblacion != nullptr) {
        poblaciones.push_back( poblacion->id + " - " + poblacion->nombreEspecie );

        poblacion = poblacion->sgtePoblacion;
    }

    return poblaciones;    
}

Poblacion *seleccionarPoblacion(){
    
    if( partidaActual->listaPoblaciones == nullptr ){
        cout << "No hay poblaciones que seleccionar...";
        getch();
        return nullptr;
    }

    Poblacion *poblacionSeleccionada = partidaActual->listaPoblaciones;
    string opcion;

    opcion = seleccionarConFlechas( obtenerPoblaciones(), tituloPoblacion(), "SELECCIONE UNA POBLACION");

    while( poblacionSeleccionada != nullptr ){
        
        if ( poblacionSeleccionada->id == opcion.substr(0,4) ){ // Comparar el id
            return poblacionSeleccionada;
        }

        poblacionSeleccionada = poblacionSeleccionada->sgtePoblacion;
    }
    
    return nullptr;
}

void generarIDPoblacion() {
    Poblacion* poblacionActual = partidaActual->listaPoblaciones;
    int id = 1;

    // Recorremos la lista de poblaciones para asignar los IDs
    while (poblacionActual != nullptr) {
        poblacionActual->id = "P" + generarIDConFormato(id, 3); // Prefijo 'P' seguido de 3 dígitos
        id++;
        poblacionActual = poblacionActual->sgtePoblacion;
    }
}

void generarIDEspecie(Poblacion* poblacion) {
    Especie* especieActual = poblacion->listaEspecies;
    int id = 1;

    // Recorremos la lista de especies para asignar los IDs
    while (especieActual != nullptr) {
        cout << poblacion->id << endl;
        especieActual->id = "E" + poblacion->id.substr(1,3) + generarIDConFormato(id, 3);
        id++;
        especieActual = especieActual->sgteEspecie;
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

    if ( partidaActual->listaPoblaciones == nullptr ){
        partidaActual->listaPoblaciones = nuevaPoblacion;

    }else{
        Poblacion *aux = partidaActual->listaPoblaciones;

        while( aux->sgtePoblacion != nullptr ){
            aux = aux->sgtePoblacion;
        }

        nuevaPoblacion->antePoblacion = aux;
        aux->sgtePoblacion = nuevaPoblacion;
    }
    
    generarIDPoblacion();
    generarIDEspecie(nuevaPoblacion);
}

void agregarEspecieEnPoblacion(Especie* nuevaEspecie){
    bool existePoblacion = false;
    Poblacion* poblacionActual = partidaActual->listaPoblaciones;
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