#include <iostream>
#include "utilidades.h"
#include "Especie.h"
#include "crudDatosEspecies.h"

using namespace std;
Especie *listaEspecies = nullptr;

void agregarEspecie();
void enlistarEspecies();
void mostrarEspecie();

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
            default: cout << "\nOpcion invalida! " << endl; break; 
        }

        system("cls");

    }while(opc != '0');
    
    return 0;
}

void agregarEspecie() {
    string nombre, tipoEspecie;
    vector<string> tiposEspecies = {"Animal", "Vegetal"};
    vector<string> nombresEspecies = {"Gato", "Perro", "Elefante"};

    tipoEspecie = seleccionConFlechas("Tipo de especie", tiposEspecies, "horizontal");
    if( tipoEspecie == "" ) return;

    nombre = seleccionConFlechas("Seleccione el nombre de la especie", nombresEspecies, "vertical");
    if( nombre == "" ) return;


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
        listaEspecies->id = 0;
    } else {
        Especie *aux = listaEspecies;
        short cantidadEspecies = 1;

        // Recorremos hasta el final de la lista
        while ( aux->sgteEspecie != nullptr ) {
            aux = aux->sgteEspecie;
            cantidadEspecies++;
        }

        nuevaEspecie->id = cantidadEspecies;
        aux->sgteEspecie = nuevaEspecie;
    }

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