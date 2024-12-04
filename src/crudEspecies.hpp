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

void eliminarEspecie() {
    string idEspecie;
    Especie *listaEspecies = nullptr, *especieActual = nullptr, *especieAnterior = nullptr, *especieEncontrada = nullptr;

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
    cout << "\nIngrese el ID de la especie que desea ver sus datos: "; getline(cin, idEspecie);

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
        Poblacion* poblacionActual = partidaActual->listaPoblaciones;

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


    registrarEvento(ELIMINAR_ESPECIE, partidaActual, especieEncontrada);
}

void reproducirEspecies(){
    // Escogiendo a las 2 especies de una misma poblacion
    Poblacion* poblacionSeleccionada = seleccionarPoblacion();
    Especie *especiePadre = nullptr, *especieMadre = nullptr, *especieHija = new Especie();

    if ( poblacionSeleccionada == nullptr ) {
        return;
    }

    especiePadre = seleccionarEspecie(poblacionSeleccionada);

    if( especiePadre == nullptr ){
        return;
    }

    especieMadre = seleccionarEspecie(poblacionSeleccionada);

    if( especieMadre == nullptr ){
        return;
    
    } else if( especieMadre == especiePadre ){
        cout << "La especie padre no puede ser la misma que la madre..." << endl;
        getch();
        return;
    
    } else if( especieMadre->tipoEspecie != especiePadre->tipoEspecie ){
        cout << "No se pueden reproducir especies de diferentes tipos..." << endl;
        getch();
        return;
    }

    // Especificando sus relaciones familiares
    especieHija->padre = especiePadre;
    especieHija->madre = especieMadre;
    especieHija->tipoEspecie = especiePadre->tipoEspecie;
    especieHija->datosEspecie = especiePadre->datosEspecie;

    if ( especiePadre->primerHijo == nullptr ) {
        especiePadre->primerHijo = especieHija;
    
    } else {
        // Navegar hasta el último hijo y añadir el nuevo
        Especie* hijoActual = especiePadre->primerHijo;
        
        while ( hijoActual->sgteHijo ) {
            hijoActual = hijoActual->sgteHijo;
        }

        hijoActual->sgteHijo = especieHija;
    }

    // Agregando la especie al simulador
    agregarEspecieEnPoblacion(especieHija);
    registrarEvento(REPRODUCCION, partidaActual, especiePadre, especieMadre, especieHija);
}

void imprimirArbol(Especie* especie, int nivel = 0) {
    if (!especie) return;

    // Imprimir la especie con indentación adecuada según el nivel
    cout << textoRGB(96,99,18) << "▓▓▓ " << endl;
    for (int i = 0; i < nivel; ++i) cout << textoRGB(96,99,18)  << "▓▓▓";
    cout << textoRGB(96,99,18) << "▓▓▓ " << textoRGB(96,99,18)  << especie->datosEspecie->nombreComun << " " << especie->id;

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

#endif // CRUD_ESPECIES_H