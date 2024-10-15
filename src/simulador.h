#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "crudEspecies.h"
#include "recursosASCII.h"

using namespace std;

void mostrarTodosCuadros();
void mostrarConsolaEventos();

void iniciarSimulador() {
    string opcion, titulo = "MENU DE OPCIONES\n";
    vector<string> opciones = {"Agregar especie", "Enlistar especies", "Mostrar datos especie", "Eliminar especie", "CANCELAR", "SALIR"};
    bool desplegarCuadros = true;

    do {
        if( desplegarCuadros ){
            mostrarTodosCuadros();
            mostrarConsolaEventos();
            getch();
        }

        opcion = seleccionConFlechas(titulo, opciones, "horizontal");

        system("cls");

        if (opcion == "Agregar especie") {
            agregarEspecie();
            desplegarCuadros = true;
        }
        else if (opcion == "Enlistar especies") {
            enlistarEspecies();
            desplegarCuadros = false;
            getch();
        } 
        else if (opcion == "Mostrar datos especie") {
            mostrarEspecie();
            desplegarCuadros = false;
            getch();
        } 
        else if (opcion == "Eliminar especie") {
            eliminarEspecie();
            desplegarCuadros = true;
        }
        else if( opcion == "CANCELAR" ){
            desplegarCuadros = true;
            continue;
        }
        else if ( opcion == "SALIR" || opcion == "" ) {
            
        } 
        else {
            cout << "Opcion invalida..." << endl;
            desplegarCuadros = false;
            getch();          
        }

        system("cls");

    } while ( opcion != "SALIR" && opcion != "" );

}

void mostrarTodosCuadros(){
    cout << endl << endl;
    
    imprimirBarra("Oxígeno", 30); cout << "\t";
    imprimirBarra("Salinidad", 30); cout << "\t";
    imprimirBarra("Temperatura", 70); cout << "\t";
    imprimirBarra("Contaminación", 30); cout << endl;

    imprimirCuadro2("Animaaal", 5, 21, 15, 5);
    imprimirCuadro2("Animaaal", 5, 21, 38, 5);
    imprimirCuadro2("Animaaal", 5, 21, 61, 5);
    imprimirCuadro2("Animaaal", 5, 21, 84, 5);
    imprimirCuadro2("Animaaal", 5, 21, 107, 5);
    imprimirCuadro2("Animaaal", 5, 21, 130, 5);

    imprimirCuadro2("Animaaal", 7, 21, 15, 11);
    imprimirCuadro2("Animaaal", 7, 21, 38, 11);
    imprimirCuadro2("Animaaal", 7, 21, 61, 11);
    imprimirCuadro2("Animaaal", 7, 21, 84, 11);
    imprimirCuadro2("Animaaal", 7, 21, 107, 11);
    imprimirCuadro2("Animaaal", 7, 21, 130, 11);

    imprimirCuadro2("Animaaal", 9, 33, 15, 19);
    imprimirCuadro2("Animaaal", 9, 33, 49, 19);
    imprimirCuadro2("Animaaal", 9, 33, 84, 19);
    imprimirCuadro2("Animaaal", 9, 33, 118, 19);
}

void mostrarConsolaEventos() {
    string linea;
    ifstream archivo("catalogo/ColaEventos.txt");

    if ( !archivo.is_open() ) {
        cout << "\n\nNo se pudo abrir el archivo... " << endl << endl;
        return;
    }

    cout << "\n\nConsola de Eventos" << endl << endl;

    // Lee el archivo línea por línea
    while (getline(archivo, linea)) {
        cout << linea << endl;
    }

    archivo.close();
}

#endif // SIMULADOR_H