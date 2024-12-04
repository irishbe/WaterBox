#ifndef CRUD_ESPECIES_HPP
#define CRUD_ESPECIES_HPP

#include "crudPoblaciones.hpp"
#include "Evento.hpp"
#include <cmath>

using namespace std;

vector<string> obtenerEspecies(Poblacion *poblacion){
    vector<string> especies;
    Especie* especie = poblacion->listaEspecies;

    while ( especie != nullptr ) {
        especies.push_back( especie->id + " - " + especie->datosEspecie->nombreComun + " - " + to_string(especie->vida) + " HP");

        especie = especie->sgteEspecie;
    }

    return especies; 
}

Especie* seleccionarEspecie(Poblacion *poblacionSelecionada){
    if( poblacionSelecionada->listaEspecies == nullptr ){
        cout << "No hay especies que seleccionar...";
        getch();
        return nullptr;
    }

    Especie* especieSeleccionada = poblacionSelecionada->listaEspecies;
    string opcion;

    opcion = seleccionarConFlechas( obtenerEspecies(poblacionSelecionada), tituloEspecie(), "SELECCIONE UNA ESPECIE");

    while( especieSeleccionada != nullptr ){
        
        if ( especieSeleccionada->id == opcion.substr(0,7) ){ // Comparar el id
            return especieSeleccionada;
        }

        especieSeleccionada = especieSeleccionada->sgteEspecie;
    }
    
    return nullptr;
}

void verificarRangoFactores(Especie* &especie, Bioma* bioma) {
    int vidaInicial = especie->vida;

    // Verificar rango oxígeno
    if (!(especie->datosEspecie->oxigenoMin <= bioma->nivelOxigeno && 
          especie->datosEspecie->oxigenoMax >= bioma->nivelOxigeno)) {
        
        especie->vida -= 10;
    }

    // Verificar rango temperatura
    if (!(especie->datosEspecie->temperaturaMin <= bioma->nivelTemperatura && 
          especie->datosEspecie->temperaturaMax >= bioma->nivelTemperatura)) {
        
        especie->vida -= 10;
    }

    // Verificar rango salinidad
    if (!(especie->datosEspecie->salinidadMin <= bioma->nivelSalinidad && 
          especie->datosEspecie->salinidadMax >= bioma->nivelSalinidad)) {
        
        especie->vida -= 10;
    }

    // Verificar el % de contaminacion
    especie->vida -= floor(bioma->nivelContaminacion / 10) * 10;

    if( vidaInicial != especie->vida ){
        registrarEvento(ENFERMEDAD, partidaActual, especie);
    }
}

void agregarEspecie(){
    string tipoEspecie, nombreEspecie;
    Especie *nuevaEspecie = new Especie();

    // SELECCIONAR EL TIPO DE ESPECIE A AGREGAR
    tipoEspecie = seleccionarConFlechas(tiposEspecies, tituloAgregarEspecie(), "SELECCIONE UN TIPO DE ESPECIE");
    
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
    nombreEspecie = seleccionarConFlechas(nombresEspecies, tituloAgregarEspecie(), "SELECCIONE EL NOMBRE DE LA ESPECIE PARA AGREGAR");
    
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

    agregarEspecieEnPoblacion(nuevaEspecie);
    registrarEvento(AGREGAR_ESPECIE, partidaActual, nuevaEspecie);

    verificarRangoFactores(nuevaEspecie, partidaActual->bioma);
}

void enlistarEspecies(){
    Poblacion* poblacionSeleccionada = seleccionarPoblacion();

    if ( poblacionSeleccionada == nullptr ) {
        return;
    }

    vector<string> especies = obtenerEspecies( poblacionSeleccionada );

    cout << "Lista de " << poblacionSeleccionada->nombreEspecie << " en la Poblacion con ID " << poblacionSeleccionada->id << endl << endl;
    
    for(int i=0; i < especies.size() ; i++){
       cout << "\t" << especies[i] << endl;
    }
    
}

void procesoEliminarEspecie(Poblacion* poblacion, Especie* especieSeleccionada) {
    if (poblacion == nullptr || especieSeleccionada == nullptr) {
        // No se imprimen mensajes, solo se retorna
        return;
    }

    // Referencias para la lista de especies
    Especie* especieActual = poblacion->listaEspecies;
    Especie* especieAnterior = nullptr;

    // Buscar y eliminar la especie seleccionada
    while (especieActual != nullptr) {
        if (especieActual == especieSeleccionada) {
            if (especieAnterior == nullptr) {
                // Eliminar la cabeza de la lista
                poblacion->listaEspecies = especieActual->sgteEspecie;
            } else {
                // Ajustar los punteros para eliminar la especie
                especieAnterior->sgteEspecie = especieActual->sgteEspecie;
            }

            // Liberar memoria de la especie y sus datos
            if (especieActual->datosEspecie) {
                delete especieActual->datosEspecie;
            }
            delete especieActual;

            // Registrar el evento de eliminación (sin imprimir)
            registrarEvento(ELIMINAR_ESPECIE, partidaActual, especieSeleccionada);
            return;
        }

        especieAnterior = especieActual;
        especieActual = especieActual->sgteEspecie;
    }
}

void eliminarEspecie() {
    // Seleccionar la población de la que se eliminará una especie
    Poblacion* poblacionSeleccionada = seleccionarPoblacion();
    if (poblacionSeleccionada == nullptr) {
        return;
    }

    // Seleccionar la especie a eliminar
    Especie* especieSeleccionada = seleccionarEspecie(poblacionSeleccionada);
    if (especieSeleccionada == nullptr) {
        return;
    }

    // Llamar a la función de proceso para eliminar la especie seleccionada
    procesoEliminarEspecie(poblacionSeleccionada, especieSeleccionada);
}

void procesoReproduccion(Especie* especiePadre, Especie* especieMadre, Poblacion* poblacionSeleccionada) {
    if (!especiePadre || !especieMadre || !poblacionSeleccionada) {
        cout << "Datos incompletos para realizar la reproducción." << endl;
        return;
    }

    // Crear la nueva especie hija
    Especie* especieHija = new Especie();
    especieHija->padre = especiePadre;
    especieHija->madre = especieMadre;
    especieHija->tipoEspecie = especiePadre->tipoEspecie; // Asumimos que son del mismo tipo
    especieHija->datosEspecie = new DatosEspecie(*especiePadre->datosEspecie); // Copiar características

    // Añadir la hija a la lista de hijos del padre
    if (!especiePadre->primerHijo) {
        especiePadre->primerHijo = especieHija;
    } else {
        Especie* hijoActual = especiePadre->primerHijo;
        while (hijoActual->sgteHijo) {
            hijoActual = hijoActual->sgteHijo;
        }
        hijoActual->sgteHijo = especieHija;
    }

    // Añadir la nueva especie hija a la población
    agregarEspecieEnPoblacion(especieHija);

    // Registrar el evento
    registrarEvento(REPRODUCCION, partidaActual, especiePadre, especieMadre, especieHija);

    cout << "Reproducción exitosa. La nueva especie ha sido creada." << endl;
}

void reproducirEspecies() {
    // Escogiendo la población
    Poblacion* poblacionSeleccionada = seleccionarPoblacion();
    if (!poblacionSeleccionada) {
        cout << "No se seleccionó ninguna población." << endl;
        return;
    }

    // Escogiendo las especies padre y madre
    Especie* especiePadre = seleccionarEspecie(poblacionSeleccionada);
    if (!especiePadre) {
        cout << "No se seleccionó ninguna especie padre." << endl;
        return;
    }

    Especie* especieMadre = seleccionarEspecie(poblacionSeleccionada);
    if (!especieMadre) {
        cout << "No se seleccionó ninguna especie madre." << endl;
        return;
    }

    // Validaciones
    if (especiePadre == especieMadre) {
        cout << "La especie padre no puede ser la misma que la madre." << endl;
        getch();
        return;
    }

    if (especiePadre->tipoEspecie != especieMadre->tipoEspecie) {
        cout << "No se pueden reproducir especies de diferentes tipos." << endl;
        getch();
        return;
    }

    // Realizar la reproducción
    procesoReproduccion(especiePadre, especieMadre, poblacionSeleccionada);
}

void imprimirArbol(Especie* especie, int nivel = 0) {
    if (!especie) return;

    // Imprimir la especie con indentación adecuada según el nivel
    cout << textoRGB(96, 235, 101) << "▓▓▓ " << endl;
    for (int i = 0; i < nivel; ++i) cout << textoRGB(96, 235, 101)  << "▓▓▓";
    cout << textoRGB(96, 235, 101) << "▓▓▓ " << textoRGB(255,255,255)  << especie->datosEspecie->nombreComun << " " << especie->id;

    // Mostrar los padres si existen
    if (especie->padre || especie->madre) {
        cout << " (";
        if (especie->padre) {
            cout << "Padre: " << especie->padre->id;
        }
        if (especie->padre && especie->madre) {
            cout << ", ";
        }
        if (especie->madre) {
            cout << "Madre: " << especie->madre->id;
        }
        cout << ")";
    }

    cout << endl;

    // Mostrar los hijos con indentación aumentada
    Especie* hijo = especie->primerHijo;
    while (hijo) {
        imprimirArbol(hijo, nivel + 1);
        hijo = hijo->sgteHijo;
    }
}

void imprimirArbolDePoblacion() {
    Poblacion* poblacionSeleccionada = seleccionarPoblacion();

    if (poblacionSeleccionada == nullptr) {
        return;
    }

    cout << "Árbol generacional de la Población de " << poblacionSeleccionada->tipoEspecie << " con ID "<< poblacionSeleccionada->id << endl << endl;

    // Recorrer y mostrar solo las especies raíz (sin padre)
    Especie* listaEspecies = poblacionSeleccionada->listaEspecies;
    while (listaEspecies) {

        if (listaEspecies->padre == nullptr) {
            imprimirArbol(listaEspecies, 0);
        }

        listaEspecies = listaEspecies->sgteEspecie;
    }

    getch();
}

void evaluarCambioFactores(){
    Poblacion* pActual = partidaActual->listaPoblaciones;

    while( pActual != nullptr ){
        Especie* eActual = pActual->listaEspecies;

        while( eActual != nullptr ){
            verificarRangoFactores(eActual, partidaActual->bioma);
            eActual = eActual->sgteEspecie;
        }

        pActual = pActual->sgtePoblacion;
    }
}

#endif // CRUD_ESPECIES_H