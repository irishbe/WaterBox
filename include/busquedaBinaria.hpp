#ifndef BUSQUEDA_BINARIA_HPP
#define BUSQUEDA_BINARIA_HPP

#include "utilidades.hpp"

// Estructura ABB
struct Nodo {
    string palabra;
    Nodo* izquierdo = nullptr;
    Nodo* derecho = nullptr;
};

// Función recursiva para insertar palabras en el árbol
Nodo* insertar(Nodo* nodo, string palabra) {
    if (nodo == nullptr) {
        nodo = new Nodo();
        nodo->palabra = palabra;
        
        return nodo;
    }

    // Insertamos de forma lexicográfica
    if (palabra < nodo->palabra) {
        nodo->izquierdo = insertar(nodo->izquierdo, palabra);
    } else {
        nodo->derecho = insertar(nodo->derecho, palabra);
    }

    return nodo;
}

// Función recursiva para buscar las palabras con el prefijo dado
void buscarPorPrefijo(Nodo* nodo, string prefijo, vector<string>& resultados) {
    if (nodo == nullptr) {
        return;
    }

    string palabraMin = toLowerStr(nodo->palabra);
    string prefijoMin = toLowerStr(prefijo);

    if (palabraMin.find(prefijoMin) == 0) {
        resultados.push_back(nodo->palabra);
    }

    buscarPorPrefijo(nodo->izquierdo, prefijo, resultados);
    buscarPorPrefijo(nodo->derecho, prefijo, resultados);
}

// Función que maneja la búsqueda de palabras por prefijo
void desplegarBuscador(Nodo *raiz, vector<string> &resultados) {
    string prefijo;
    char tecla;

    do{
        int x = 10, y = 3;
        
        y += imprimirTexto( tituloEspecie(), x, y, true) + 2;
        y += imprimirTexto("INGRESE EL NOMBRE DE ALGUNA ESPECIE: ", x, y, true, true) + 2;
            
        moverCursor(x,y); cout << "(ESC para salir) (ENTER para escoger)";
        moverCursor(x,y+1); cout << "Prefijo actual: " << prefijo;

        tecla = getch();

        if( tecla == ESC ){
            break;

        }else if ( tecla == BACKSPACE && !prefijo.empty() ) {
            prefijo.pop_back();

        } else if( tecla == SPACEBAR ) {
            prefijo += " ";

        } else if ( isalpha(tecla) ) {
            prefijo += tecla;
        }

        resultados.clear();
        buscarPorPrefijo(raiz, prefijo, resultados);

        system("cls");

        if (prefijo.empty() || resultados.empty()) {
            moverCursor(x,y+3); cout << "No se encontraron coincidencias.";
        
        } else {
            moverCursor(x,y+3);cout << "Sugerencias: ";

            for (int i=0; i < resultados.size(); i++) {
                moverCursor(x,y+4+i); cout << "  " << resultados[i];
            }
        }

    }while(tecla != ENTER);
}

string busquedaBinaria(vector<string> opciones){
    Nodo* raiz = nullptr;

    string opcion = "";
    vector<string> resultados;

    for(int i=0; i < opciones.size(); i++){
        raiz = insertar(raiz, opciones[i]);
    }

    do{

        desplegarBuscador(raiz, resultados);

        if( !resultados.empty() ){
            opcion = seleccionarConFlechas(resultados, "SELECCIONE UNA RESPUESTA");
        }

        system("cls");

    }while(opcion != "");

    return opcion;
}

#endif // BUSQUEDA_BINARIA.HPP