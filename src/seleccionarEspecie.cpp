#include <iostream>
#include "utilidades.h"
#include "Especie.h"
#include "crudDatosEspecies.h"

using namespace std;
Especie *listaEspecies = nullptr;

string seleccionarNombre() {
    const char ENTER = 13, ESC = 27, TECLAESPECIAL = 224;
    const int UP = 72, DOWN = 80;
    
    char tecla;
    vector<string> nombreEspecies = {"Gato", "Perro", "Elefante"};
    int index = 0, cantidadEspecies = nombreEspecies.size();
    
    ocultarCursor(); 

    do {
        system("cls");
        cout << "Seleccione alguna de las especies" << endl;

        for (int i = 0; i < cantidadEspecies; i++) {
            if (i == index) {
                cout << "> " << nombreEspecies[i] << endl;
            } else {
                cout << "  " << nombreEspecies[i] << endl;
            }
        }

        tecla = _getch();

        if (tecla == TECLAESPECIAL) {
            tecla = _getch();  // Capturar el código de la tecla de flecha

            switch (tecla) {
                case UP: index = (index - 1 + cantidadEspecies) % cantidadEspecies; break;
                case DOWN: index = (index + 1) % cantidadEspecies; break;
            }
        }

        if (tecla == ENTER) {
            mostrarCursor(); 
            return nombreEspecies[index];
        }

    } while (tecla != ESC && tecla != '0');

    mostrarCursor(); 
    return "";
}
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
            case '2': enlistarEspecies(); break;
            default: cout << "\nOpcion invalida! " << endl; break; 
        }

        _getch();
        system("cls");

    }while(opc != '0');
    
    return 0;
}

void agregarEspecie(){
    Especie *nuevaEspecie = new Especie();
    short tipoEspecie;
    string nombre;

    cout << "Tipo de especie" << endl;
    cout << "1. Animal" << endl;
    cout << "2. Vegetal" << endl;
    cout << "Escoja ---> "; cin >> tipoEspecie;

    nombre = seleccionarNombre();
    
    if (nombre != "") {
       nuevaEspecie->datosEspecie = extraerDatosEspecie(tipoEspecie, nombre);
       nuevaEspecie->sgteEspecie = nullptr;
    }else{
        delete nuevaEspecie;
        return;
    }

    if( listaEspecies == nullptr ){
        listaEspecies = nuevaEspecie;
        listaEspecies->id = 0;
    }else{
        Especie *aux = listaEspecies;
        short cantidadEspecies = 1;

        while( aux->sgteEspecie != nullptr ){
            aux = aux->sgteEspecie;
            cantidadEspecies++;
        }

        nuevaEspecie->id = cantidadEspecies;
        aux->sgteEspecie = nuevaEspecie;
    }

    cout << "\nEspecie \""<< nuevaEspecie->datosEspecie->nombreComun << "\" con ID (" << nuevaEspecie->id << ") fue agregada con exito! " << endl;
}

void enlistarEspecies(){
    Especie *aux = listaEspecies;
    
    if( listaEspecies == nullptr ){
        cout << "No hay especies que enlistar..." <<endl;
    }else{
        cout << "----------- LISTA DE ESPECIES -----------" << endl << endl;

        while( aux != nullptr ){
            cout << aux->id << ". " << aux->datosEspecie->nombreComun << endl;
            aux = aux->sgteEspecie;
        }
    }
}
/* Mostramos los datos
            cout << "\nDATOS DE LA ESPECIE:\n";
            cout << "Nombre comun: " << especieEncontrada->nombreComun << endl;
            cout << "Nombre cientifico: " << especieEncontrada->nombreCientifico << endl;
            cout << "Familia biologica: " << especieEncontrada->familiaBiologica << endl;
            cout << "Bioma nativo: " << especieEncontrada->biomaNativo << endl;
            cout << "Esperanza de vida: " << especieEncontrada->esperanzaVida << endl;
            cout << "Tasa de reproduccion: " << especieEncontrada->tasaReproduccion << endl;
            cout << "Inactividad reproductiva: " << especieEncontrada->inactividadReproductiva << endl;
            cout << "Rango salinidad: [" << especieEncontrada->salinidadMax << ", " << especieEncontrada->salinidadMin << "]" << endl;
            cout << "Rango oxigeno: [" << especieEncontrada->oxigenoMax << ", " << especieEncontrada->oxigenoMin << "]" << endl;
            cout << "Rango temperatura: [" << especieEncontrada->tempMax << ", " << especieEncontrada->tempMin << "]" << endl;
*/