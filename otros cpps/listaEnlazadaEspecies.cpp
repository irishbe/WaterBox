#include <iostream>
#include "utilidades.h"
#include "Especie.h"
#include "crudDatos.h"

using namespace std;
Especie *listaEspecies = nullptr;

void generarIDs();
void agregarEspecie();
void enlistarEspecies();
void mostrarEspecie();
void eliminarEspecie();

int main() {
    char opc;

    do{
        cout << "----------- MENU DE OPCIONES -----------" << endl << endl;
        cout << "1. Agregar Especie" << endl;
        cout << "2. Enlistar Especies" << endl;
        cout << "3. Mostrar Especie" << endl;
        cout << "4. Eliminar Especie " << endl;
        cout << "0. SALIR" << endl;

        cout << "\nOpcion ---> "; cin >> opc; 
        system("cls");

        switch(opc){
            case '1': agregarEspecie(); break;
            case '2': enlistarEspecies(); _getch(); break;
            case '3': mostrarEspecie(); break;
            case '4': eliminarEspecie(); break;
            case '0': cout << "\nSaliendo..." << endl; _getch(); break;
            default : cout << "\nOpcion invalida..." << endl; _getch(); break; 
        }

        system("cls");

    }while(opc != '0');

    return 0;
}

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
    string tipoEspecie;
    vector<string> tiposEspecies = {"Animal", "Vegetal"};

    tipoEspecie = seleccionConFlechas("Tipo de especie", tiposEspecies, "horizontal");
    if( tipoEspecie == "" ) return;

    // Escogiendo el nombre de la especie a agregar
    string nombre;
    vector<string> nombresEspecies = extraerNombresEspecies(tipoEspecie);
    if( nombresEspecies.empty() ){
        cout << "\nNo se encontraron especies en \"" << tipoEspecie << "\"..." << endl << endl;
        _getch();
        return;   
    }

    nombre = seleccionConFlechas("Seleccione el nombre de la especie", nombresEspecies, "vertical");
    if( nombre == "" ) return;

    // Asignacion de datos a la especie
    DatosEspecie *datos = extraerDatosEspecie(tipoEspecie, nombre);
    if ( datos == nullptr ) {
        cout << "\nEspecie \"" << nombre << "\" no fue encontrada en \"" << tipoEspecie << "\"... " << endl << endl;
        _getch();
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
    cout << "\nEspecie \"" << nuevaEspecie->datosEspecie->nombreComun << "\" con ID (" << nuevaEspecie->id << ") fue agregada con exito! " << endl << endl;
    
    _getch();
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
        _getch();
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
    cout << "Rango temperatura: [" << especieEncontrada->tempMax << ", " << especieEncontrada->tempMin << "]" << endl << endl;

    _getch();
}

void eliminarEspecie(){
    enlistarEspecies();

    if( listaEspecies == nullptr ){
        _getch();
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
        
        delete aux->datosEspecie;
        delete aux;

        cout << "\nEspecie con ID (" << idBuscado << ") eliminada con exito!" << endl;
        
        // Reajustar los IDs después de la eliminación
        generarIDs();
    }

    _getch();
}