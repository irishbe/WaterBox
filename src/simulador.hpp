#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "crudEspecies.hpp"
#include "utilidades.hpp"
#include "Evento.hpp"

using namespace std;

// Declaración de variables globales
const float oxigenoMin = 0, oxigenoMax = 14;
const float salinidadMin = 0, salinidadMax = 330;
const float temperaturaMin = 0, temperaturaMax = 40;
const float contaminacionMin = 0, contaminacionMax = 100;

// Declaraciones de funciones
void mostrarTodosCuadros(float oxigeno, float salinidad, float temperatura, float contaminacion);
void modificarFactor(float &oxigeno, float &salinidad, float &temperatura, float &contaminacion);
void imprimirPoblaciones();
int mostrarMenuFactores();

// Función para iniciar el simulador
void iniciarSimulador() {
    bool desplegarCuadros = true;
    int opcion = -1;
    
    vector<string> dibujos = {
        ASCIIAgregarEspecie(),
        ASCIIEnlistarEspecies(),
        ASCIIModificarFactores(),
        ASCIIEliminarEspecie()
    };

    // Valores iniciales de los factores
    float oxigeno = 7.0, salinidad = 165.0, temperatura = 20.0, contaminacion = 50.0;

    do {

        if (desplegarCuadros){
            mostrarTodosCuadros(oxigeno, salinidad, temperatura, contaminacion);
            mostrarEventos(pilaEventos, "Pila de eventos");
            getch();
        }

        opcion = seleccionarConDibujos( dibujos, tituloWaterBox(), "SELECCIONE UNA OPCION");

        switch (opcion){
            case 1: agregarEspecie(); desplegarCuadros = true; break;
            case 2: enlistarEspecies(); desplegarCuadros = false; getch(); break;
            case 3: buscarEspecie(); desplegarCuadros = false; break;
            case 4: modificarFactor(oxigeno, salinidad, temperatura, contaminacion); desplegarCuadros = true; break;
            case 5: eliminarEspecie(); desplegarCuadros = true; break;
            case -1: break;
            default: cout << "Opción inválida..." << endl; desplegarCuadros = false; getch(); break;
        }

        system("cls");

    } while (opcion != -1);
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

    imprimirPoblaciones();
}

void imprimirPoblaciones() {
    Poblacion* poblacionActual = listaPoblaciones;

    // Variables locales para las posiciones
    int posXLocal = 15;
    int posYLocal = 5;

    while (poblacionActual != nullptr) {
        // Imprimir la población actual en la posición actual
        // ERROR imprimirPoblacion(poblacionActual, obtenerSprite(poblacionActual->nombreEspecie), "MEDIANO", posXLocal, posYLocal);

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

void modificarFactor(float &oxigeno, float &salinidad, float &temperatura, float &contaminacion) {
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
                cin >> oxigeno;
                if (oxigeno < oxigenoMin || oxigeno > oxigenoMax) {
                    cout << "Valor fuera de rango. Debe estar entre " << oxigenoMin << " y " << oxigenoMax << " mg/L." << endl;
                    getch();
                }
                break;
            case 2: // Salinidad
                cout << "Ingrese el nivel de salinidad (Mín. 0 / Máx. 330 ups): ";
                cin >> salinidad;
                if (salinidad < salinidadMin || salinidad > salinidadMax) {
                    cout << "Valor fuera de rango. Debe estar entre " << salinidadMin << " y " << salinidadMax << " ups." << endl;
                    getch();
                }
                break;
            case 3: // Temperatura
                cout << "Ingrese la temperatura (Mín. 0 / Máx. 40 °C): ";
                cin >> temperatura;
                if (temperatura < temperaturaMin || temperatura > temperaturaMax) {
                    cout << "Valor fuera de rango. Debe estar entre " << temperaturaMin << " y " << temperaturaMax << " °C." << endl;
                    getch();
                }
                break;
            case 4: // Contaminación
                cout << "Ingrese el nivel de contaminación (Mín. 0 / Máx. 100 %): ";
                cin >> contaminacion;
                if (contaminacion < contaminacionMin || contaminacion > contaminacionMax) {
                    cout << "Valor fuera de rango. Debe estar entre " << contaminacionMin << " y " << contaminacionMax << " %." << endl;
                    getch();
                }
                break;
            case -1: break;
            default:
                cout << "Opción inválida..." << endl;
                getch();
                break;
        }

        system("cls");
        mostrarTodosCuadros(oxigeno, salinidad, temperatura, contaminacion);
        mostrarEventos(pilaEventos, "Pila de eventos");

        system("cls");

    } while (opcion != -1);
}

#endif // SIMULADOR_H