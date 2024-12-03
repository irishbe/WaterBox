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

    if (nodo->palabra.find(prefijo) == 0) {
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
        moverCursor(x,y+1); cout << "Prefijo actual: \"" << prefijo << "\"";

        tecla = getch();

        if (tecla == BACKSPACE && !prefijo.empty()) {
            prefijo.pop_back();

        } else if (isalpha(tecla)) {
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

    }while(tecla != ESC && tecla != ENTER);
}

int main() {
    Nodo* raiz = nullptr;

    // Insertando palabras en el árbol
    raiz = insertar(raiz, "dasa");
    raiz = insertar(raiz, "carro");
    raiz = insertar(raiz, "wama");
    raiz = insertar(raiz, "camino");
    raiz = insertar(raiz, "camion");
    raiz = insertar(raiz, "fancion");
    raiz = insertar(raiz, "ambiar");
    raiz = insertar(raiz, "ratones");
    raiz = insertar(raiz, "rezar");
    raiz = insertar(raiz, "rentar");
    raiz = insertar(raiz, "cachorro");
    raiz = insertar(raiz, "cielo");
    raiz = insertar(raiz, "carrera");
    raiz = insertar(raiz, "animal");
    raiz = insertar(raiz, "perro");
    raiz = insertar(raiz, "gato");
    raiz = insertar(raiz, "caballo");
    raiz = insertar(raiz, "pelota");
    raiz = insertar(raiz, "luna");
    raiz = insertar(raiz, "estrella");
    raiz = insertar(raiz, "noche");
    raiz = insertar(raiz, "sol");
    raiz = insertar(raiz, "mango");
    raiz = insertar(raiz, "manzana");

    string opcion;
    vector<string> resultados;

    do{

        desplegarBuscador(raiz, resultados);
        opcion = seleccionarConFlechas(resultados, "SELECCIONE UNA RESPUESTA");

        system("cls");

    }while(opcion != "");

    return 0;
}
