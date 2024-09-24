#include <iostream>
#include <vector>
#include "datosEspecie.h"
#include "Especie.h"
#include "crudDatosEspecies.h"
using namespace std;

void ocultarCursor() {
    cout << "\033[?25l";  // Ocultar el cursor
}

// Secuencia de escape ANSI para mostrar el cursor
void mostrarCursor() {
    cout << "\033[?25h";  // Mostrar el cursor
}

string seleccionarNombre(){
    const char ENTER = 13, ESC = 27, TECLAESPECIAL = 224;
    const int UP = 72, DOWN = 80;
    
    char tecla;
    vector<string> nombreEspecies = {"Gato", "Perro", "Elefante"};
    int index = 0, cantidadEspecies = nombreEspecies.size();
    
    ocultarCursor(); 

    do{
        system("cls");
        cout<<"Selecione alguna de las especies"<<endl;

         for (int i = 0; i < cantidadEspecies; i++) {
            if (i == index) {
                cout << "> " << nombreEspecies[i] << endl;
            } else {
                cout << "  " << nombreEspecies[i] << endl;
            }
        }

        tecla = _getch();

        if( tecla == TECLAESPECIAL ){
            tecla = _getch();  // Capturar el código de la tecla de flecha

            switch(tecla){
                case UP: index = ( index - 1 + cantidadEspecies ) % cantidadEspecies; break;
                case DOWN: index = ( index + 1 ) % cantidadEspecies; break;
            }
        }

        if (tecla == ENTER) {
            mostrarCursor(); 
            return nombreEspecies[index];
        }

    }while( tecla != ESC && tecla != '0');

    mostrarCursor(); 
    return "";
}

int main(){
    Especie *nuevaEspecie = new Especie();
    int tipoEspecie;
    string nombre;

    cout<<"Tipo de especie"<<endl;
    cout<<"1. Animal"<<endl;
    cout<<"2. Vegetal"<<endl;
    cout<<"Escoja ---> "; cin>>tipoEspecie;

    nombre = seleccionarNombre();
    
    if(nombre != ""){
       nuevaEspecie->datosEspecie = extraerDatosEspecie(tipoEspecie, nombre);
    }

    return 0;
}