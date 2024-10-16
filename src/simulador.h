#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "crudEspecies.h"
#include "recursosASCII.h"

using namespace std;

float oxigenoMin = 0, oxigenoMax = 14;
float salinidadMin = 0, salinidadMax = 330;
float temperaturaMin = 0, temperaturaMax = 40;
float contaminacionMin = 0, contaminacionMax = 100;

void mostrarTodosCuadros(float oxigeno, float salinidad, float temperatura, float contaminacion);
void mostrarConsolaEventos();
void modificarFactor(float &oxigeno, float &salinidad, float &temperatura, float &contaminacion);

void iniciarSimulador() {
    string opcion, titulo = "MENU DE OPCIONES\n";
    vector<string> opciones = {"Agregar especie", "Enlistar especies", "Mostrar datos especie", "Eliminar especie", "Modificar factores", "CANCELAR", "SALIR"};
    bool desplegarCuadros = true;
    
    // Valores iniciales de los factores
    float oxigeno = 7.0, salinidad = 165.0, temperatura = 20.0, contaminacion = 50.0;

    do {
        if( desplegarCuadros ){
            mostrarTodosCuadros(oxigeno, salinidad, temperatura, contaminacion);
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
        else if (opcion == "Modificar factores") {
            modificarFactor(oxigeno, salinidad, temperatura, contaminacion);
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

void mostrarTodosCuadros(float oxigeno, float salinidad, float temperatura, float contaminacion) {
    cout << endl << endl;

    // Cálculo de los porcentajes según los valores ingresados
    int porcentajeOxigeno = (oxigeno - oxigenoMin) * 100 / (oxigenoMax - oxigenoMin);
    int porcentajeSalinidad = (salinidad - salinidadMin) * 100 / (salinidadMax - salinidadMin);
    int porcentajeTemperatura = (temperatura - temperaturaMin) * 100 / (temperaturaMax - temperaturaMin);
    int porcentajeContaminacion = (contaminacion - contaminacionMin) * 100 / (contaminacionMax - contaminacionMin);

    // Mostrar barras de progreso
    imprimirBarra("Oxígeno", porcentajeOxigeno); cout << "\t";
    imprimirBarra("Salinidad", porcentajeSalinidad); cout << "\t";
    imprimirBarra("Temperatura", porcentajeTemperatura); cout << "\t";
    imprimirBarra("Contaminación", porcentajeContaminacion); cout << endl;

    // Mostrar cuadros con datos de ejemplo
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

void modificarFactor(float &oxigeno, float &salinidad, float &temperatura, float &contaminacion) {
    string opcion, titulo = "MENU DE OPCIONES\n";
    vector<string> opciones = {"Oxígeno", "Salinidad", "Temperatura", "Contaminación", "CANCELAR", "SALIR"};

    do {
        opcion = seleccionConFlechas(titulo, opciones, "horizontal");

        system("cls");

        if (opcion == "Oxígeno (Mín. 0 / Máx. 14)") {
            cout << "Ingrese el nivel de oxígeno (mg/L): ";
            cin >> oxigeno;
            if (oxigeno < oxigenoMin || oxigeno > oxigenoMax) {
                cout << "Valor fuera de rango. Debe estar entre " << oxigenoMin << " y " << oxigenoMax << " mg/L." << endl;
                getch();
            }
        }
        else if (opcion == "Salinidad (Mín. 0 / Máx. 330)") {
            cout << "Ingrese el nivel de salinidad (ups): ";
            cin >> salinidad;
            if (salinidad < salinidadMin || salinidad > salinidadMax) {
                cout << "Valor fuera de rango. Debe estar entre " << salinidadMin << " y " << salinidadMax << " ups." << endl;
                getch();
            }
        }
        else if (opcion == "Temperatura (Mín. 0 / Máx. 40)") {
            cout << "Ingrese la temperatura (°C): ";
            cin >> temperatura;
            if (temperatura < temperaturaMin || temperatura > temperaturaMax) {
                cout << "Valor fuera de rango. Debe estar entre " << temperaturaMin << " y " << temperaturaMax << " °C." << endl;
                getch();
            }
        }
        else if (opcion == "Contaminación (Mín. 0 / Máx. 100)") {
            cout << "Ingrese el nivel de contaminación (%): ";
            cin >> contaminacion;
            if (contaminacion < contaminacionMin || contaminacion > contaminacionMax) {
                cout << "Valor fuera de rango. Debe estar entre " << contaminacionMin << " y " << contaminacionMax << " %." << endl;
                getch();
            }
        }
        else if (opcion == "CANCELAR") {
            continue;
        }
        else if (opcion == "SALIR" || opcion == "") {
            break;
        }
        else {
            cout << "Opción inválida..." << endl;
            getch();
        }

        mostrarTodosCuadros(oxigeno, salinidad, temperatura, contaminacion);
        mostrarConsolaEventos();
        getch();

        system("cls");

    } while (opcion != "SALIR" && opcion != "");
}

#endif // SIMULADOR_H