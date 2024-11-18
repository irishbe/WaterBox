#ifndef SIMULADOR_HPP
#define SIMULADOR_HPP

#include "crudEspecies.hpp"
#include "utilidades.hpp"
#include "Evento.hpp"

using namespace std;

const float oxigenoMin = 0, oxigenoMax = 14;
const float salinidadMin = 0, salinidadMax = 330;
const float temperaturaMin = 0, temperaturaMax = 40;
const float contaminacionMin = 0, contaminacionMax = 100;

// Declaraciones de funciones
void mostrarTodosCuadros();
void modificarFactor();
void imprimirPoblaciones();
int mostrarMenuFactores();

// Función para iniciar el simulador
void iniciarSimulador() {
    // Seleccion del bioma
    int opcion = -1;

    if( biomaSimulador == nullptr ){
        vector<string> dibujos = {
            ASCIIBiomaArrecifeCoral(),
            ASCIIBiomaOceanoProfundo()
        };
        
        opcion = seleccionarConDibujos(dibujos, tituloBiomas(), "SELECCIONE UN BIOMA");

        system("cls");

        switch(opcion){
            case 1: biomaSimulador = extraerBioma("Arrecifes de Coral"); break;
            case 2: biomaSimulador = extraerBioma("Oceano Profundo"); break;
            case -1: break;
        }
    }

    bool desplegarCuadros = true;
    opcion = -1;

    vector<string> dibujos = {
        ASCIIAgregarEspecie(),
        ASCIIEnlistarEspecies(),
        ASCIIModificarFactores(),
        ASCIIEliminarEspecie()
    };

    do {

        system("cls");

        if (desplegarCuadros){
            mostrarTodosCuadros();
            mostrarEventos();
            getch();
        }

        opcion = seleccionarConDibujos( dibujos, tituloWaterBox(), "SELECCIONE UNA OPCION");

        system("cls");

        switch (opcion){
            case 1: agregarEspecie(); desplegarCuadros = true; break;
            case 2: enlistarEspecies(); desplegarCuadros = false; getch(); break;
            case 3: modificarFactor(); desplegarCuadros = true; break;
            case 4: eliminarEspecie(); desplegarCuadros = true; break;
            case -1: break;
        }

        system("cls");

    } while (opcion != -1);
}

void mostrarTodosCuadros() {
    cout << "Bioma: " << biomaSimulador->nombre << endl << endl;

    // Cálculo de los porcentajes según los valores ingresados
    int porcentajeOxigeno = (biomaSimulador->nivelOxigeno - oxigenoMin) * 100 / (oxigenoMax - oxigenoMin);
    int porcentajeSalinidad = (biomaSimulador->nivelSalinidad - salinidadMin) * 100 / (salinidadMax - salinidadMin);
    int porcentajeTemperatura = (biomaSimulador->nivelTemperatura - temperaturaMin) * 100 / (temperaturaMax - temperaturaMin);
    int porcentajeContaminacion = (biomaSimulador->nivelTemperatura - contaminacionMin) * 100 / (contaminacionMax - contaminacionMin);

    // Mostrar barras de progreso
    imprimirBarra("Oxígeno", porcentajeOxigeno); cout << "\t";
    imprimirBarra("Salinidad", porcentajeSalinidad); cout << "\t";
    imprimirBarra("Temperatura", porcentajeTemperatura); cout << "\t";
    imprimirBarra("Contaminación", porcentajeContaminacion); cout << endl;

    imprimirPoblaciones();
}

void imprimirPoblaciones() {
    Poblacion* poblacionActual = listaPoblaciones;
    // Variables locales para las posiciones
    int posXLocal = 15;
    int posYLocal = 5;

    while (poblacionActual != nullptr) {
        // Imprimir la población actual en la posición actual
        imprimirPoblacion(poblacionActual, obtenerSprite(poblacionActual->nombreEspecie), "MEDIANO", posXLocal, posYLocal);

        // Actualizar las posiciones
        if (posXLocal + 23 <= 130) {
            posXLocal += 23;
        } else {
            posXLocal = 15;
            posYLocal += 8;
        }

        // Avanzar a la siguiente población
        poblacionActual = poblacionActual->sgtePoblacion;
    }
}

void modificarFactor() {
    int opcion = -1;
    vector<string> dibujos = {
        ASCIIOxigeno(),
        ASCIISalinidad(),
        ASCIITemperatura(),
        ASCIIContaminacion()
    };
    
    do {
        opcion = seleccionarConDibujos(dibujos, tituloWikiWater(), "SELECCIONE EL FACTOR A MODIFICAR");
        system("cls");

        switch (opcion) {
            case 1: // Oxígeno
                cout << "Ingrese el nivel de oxígeno (Mín. 0 / Máx. 14 mg/L): ";
                cin >> biomaSimulador->nivelOxigeno;
                if (biomaSimulador->nivelOxigeno < oxigenoMin || biomaSimulador->nivelOxigeno > oxigenoMax) {
                    cout << "Valor fuera de rango. Debe estar entre " << oxigenoMin << " y " << oxigenoMax << " mg/L." << endl;
                    getch();
                }
                break;
            case 2: // Salinidad
                cout << "Ingrese el nivel de salinidad (Mín. 0 / Máx. 330 ups): ";
                cin >> biomaSimulador->nivelSalinidad;
                if (biomaSimulador->nivelSalinidad < salinidadMin || biomaSimulador->nivelSalinidad > salinidadMax) {
                    cout << "Valor fuera de rango. Debe estar entre " << salinidadMin << " y " << salinidadMax << " ups." << endl;
                    getch();
                }
                break;
            case 3: // Temperatura
                cout << "Ingrese la temperatura (Mín. 0 / Máx. 40 °C): ";
                cin >> biomaSimulador->nivelTemperatura;
                if (biomaSimulador->nivelTemperatura < temperaturaMin || biomaSimulador->nivelTemperatura > temperaturaMax) {
                    cout << "Valor fuera de rango. Debe estar entre " << temperaturaMin << " y " << temperaturaMax << " °C." << endl;
                    getch();
                }
                break;
            case 4: // Contaminación
                cout << "Ingrese el nivel de contaminación (Mín. 0 / Máx. 100 %): ";
                cin >> biomaSimulador->nivelContaminacion;
                if (biomaSimulador->nivelContaminacion < contaminacionMin || biomaSimulador->nivelContaminacion > contaminacionMax) {
                    cout << "Valor fuera de rango. Debe estar entre " << contaminacionMin << " y " << contaminacionMax << " %." << endl;
                    getch();
                }
                break;
            case -1: break;
        }

        system("cls");

    } while (opcion != -1);
}

#endif // SIMULADOR_H