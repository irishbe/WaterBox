#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include "Poblacion.hpp"

using namespace std;

// Nodo para el arbol (no es binario)  
struct NodoArbol {
    Especie* especie; 
    vector<NodoArbol*> hijos;

    NodoArbol(Especie* especie) : especie(especie) {}
};

// Nodo para la lista enlazada
struct NodoLista {
    NodoArbol* raiz; // Raiz del arbol
    NodoLista* siguiente;

    NodoLista(NodoArbol* raiz) : raiz(raiz), siguiente(NULL) {}
};

// Cola simple implementada con lista enlazada
struct NodoCola {
    NodoArbol* nodo;
    NodoCola* siguiente;
    NodoCola(NodoArbol* nodo) : nodo(nodo), siguiente(NULL) {}
};

struct Cola {
    NodoCola* frente;
    NodoCola* final;

    Cola() : frente(NULL), final(NULL) {}

    bool estaVacia() {
        return frente == NULL;
    }

    void encolar(NodoArbol* nodo) {
        NodoCola* nuevoNodo = new NodoCola(nodo);
        if (estaVacia()) {
            frente = final = nuevoNodo;
        } else {
            final->siguiente = nuevoNodo;
            final = nuevoNodo;
        }
    }

    NodoArbol* desencolar() {
        if (estaVacia()) {
            return NULL;
        }
        NodoArbol* nodo = frente->nodo;
        NodoCola* temp = frente;
        frente = frente->siguiente;
        delete temp;
        return nodo;
    }
};

// Conjunto sin duplicados implementado con lista enlazada
struct NodoConjunto {
    string nombre;
    NodoConjunto* siguiente;
    NodoConjunto(const string& nombre) : nombre(nombre), siguiente(NULL) {}
};

struct Conjunto {
    NodoConjunto* cabeza;

    Conjunto() : cabeza(NULL) {}

    bool contiene(const string& nombre) {
        NodoConjunto* actual = cabeza;
        while (actual) {
            if (actual->nombre == nombre) {
                return true;
            }
            actual = actual->siguiente;
        }
        return false;
    }

    void agregar(const string& nombre) {
        if (!contiene(nombre)) {
            NodoConjunto* nuevoNodo = new NodoConjunto(nombre);
            nuevoNodo->siguiente = cabeza;
            cabeza = nuevoNodo;
        }
    }
};

// Generador de ID unico secuencial
int generadorID = 1;  // Variable estatica para generar IDs secuenciales

string generarID() {
    stringstream ss;
    ss << setw(3) << setfill('0') << generadorID++;  // Formato de 3 digitos, con ceros a la izquierda
    return ss.str();
}

void imprimirArbol(NodoArbol* raiz, int nivel, Conjunto& visitados) {
    if (!raiz) return;

    // Verificar si este nodo ya fue visitado
    if (visitados.contiene(raiz->especie->id)) {
        return; // Si ya fue visitado, no lo imprimimos
    }

    // Marcar este nodo como visitado
    visitados.agregar(raiz->especie->id);

    // Imprimir el nodo con la indentacion correspondiente
    for (int i = 0; i < nivel; ++i) {
        cout << "  ";
    }
    cout << "- " << raiz->especie->id << endl;

    // Recorrer a los hijos
    for (auto hijo : raiz->hijos) {
        imprimirArbol(hijo, nivel + 1, visitados);
    }
}

void imprimirArbolDesdeRaiz(NodoArbol* raiz) {
    Conjunto visitados;
    imprimirArbol(raiz, 0, visitados);
}

void imprimirListaEspecies(Poblacion* poblacion) {
    if (!poblacion || !poblacion->listaEspecies) {
        cout << "No hay especies en esta poblacion." << endl;
        return;
    }

    Especie* especieActual = poblacion->listaEspecies;
    while (especieActual) {
        cout << "Especie ID: " << especieActual->id << endl;
        especieActual = especieActual->sgteEspecie;
    }
}

Poblacion* buscarPoblacion(Poblacion* listaPoblaciones, const string& idPoblacion) {
    Poblacion* actual = listaPoblaciones;
    while (actual) {
        if (actual->id == idPoblacion) {
            return actual;
        }
        actual = actual->sgtePoblacion;
    }
    return NULL; // Poblacion no encontrada
}

void eventoReproduccion(Poblacion* listaPoblaciones) {
    if (!listaPoblaciones) {
        cout << "Error: La lista de poblaciones esta vacia." << endl;
        return;
    }

    // Mostrar las poblaciones disponibles
    cout << endl <<"Poblaciones disponibles:" << endl;
    Poblacion* actual = listaPoblaciones;
    while (actual) {
        cout << "ID Poblacion: " << actual->id << endl;
        actual = actual->sgtePoblacion;
    }

    // Seleccion de poblacion
    string idPoblacionSeleccionada;
    cout << "Seleccione una poblacion por ID: ";
    cin >> idPoblacionSeleccionada;

    Poblacion* poblacionSeleccionada = buscarPoblacion(listaPoblaciones, idPoblacionSeleccionada);
    if (!poblacionSeleccionada) {
        cout << "Error: Poblacion no encontrada." << endl;
        return;
    }

    // Mostrar las especies de la poblacion seleccionada
    cout << "Especies disponibles en la poblacion " << idPoblacionSeleccionada << ":" << endl;
    imprimirListaEspecies(poblacionSeleccionada);

    // Seleccion de dos especies
    string idEspecie1, idEspecie2;
    cout << "Seleccione el ID de la primera especie: ";
    cin >> idEspecie1;
    cout << "Seleccione el ID de la segunda especie: ";
    cin >> idEspecie2;

    // Buscar las especies seleccionadas
    Especie* especie1 = NULL;
    Especie* especie2 = NULL;
    Especie* especieActual = poblacionSeleccionada->listaEspecies;
    while (especieActual) {
        if (especieActual->id == idEspecie1) {
            especie1 = especieActual;
        }
        if (especieActual->id == idEspecie2) {
            especie2 = especieActual;
        }
        especieActual = especieActual->sgteEspecie;
    }

    if (!especie1 || !especie2) {
        cout << "Error: No se encontraron una o ambas especies seleccionadas." << endl;
        return;
    }

    // Crear el hijo de las especies seleccionadas
    Especie* hijo = new Especie();
    hijo->id = generarID();  // Asignamos un ID unico secuencial
    hijo->tipoEspecie = especie1->tipoEspecie;  // Asumimos que la especie del hijo es la misma
    hijo->datosEspecie = new DatosEspecie();
    hijo->datosEspecie->nombreComun = "Hijo de " + especie1->datosEspecie->nombreComun + " y " + especie2->datosEspecie->nombreComun;
    
    // Agregar el hijo a la lista de especies (por simplicidad agregamos al final de la lista de especies de la poblacion)
    hijo->sgteEspecie = poblacionSeleccionada->listaEspecies;
    poblacionSeleccionada->listaEspecies = hijo;

    cout << "Hijo creado con ID: " << hijo->id << endl;
}

void mostrarMenu(Poblacion* listaPoblaciones) {
    int opcion;
    do {
        cout << "\n--- Menu ---\n";
        cout << "1) Reproducir especies\n";
        cout << "2) Mostrar arbol de especies de una poblacion\n";
        cout << "3) Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                eventoReproduccion(listaPoblaciones);  // Llamamos a la funcion para la reproduccion de especies
                break;
            case 2:
                {
                    // Solicitar ID de poblacion
                    string idPoblacion;
                    cout << "Ingrese el ID de la poblacion: ";
                    cin >> idPoblacion;

                    Poblacion* poblacionSeleccionada = buscarPoblacion(listaPoblaciones, idPoblacion);
                    if (poblacionSeleccionada) {
                        cout << "Arbol de especies de la poblacion " << idPoblacion << ":\n";
                        
                        // Ahora construimos el �rbol para la poblaci�n
                        NodoArbol* raiz = NULL;
                        Especie* especieActual = poblacionSeleccionada->listaEspecies;
                        
                        // Creamos el �rbol de especies con las especies de la poblaci�n
                        while (especieActual) {
                            NodoArbol* nuevoNodo = new NodoArbol(especieActual);
                            if (raiz == NULL) {
                                raiz = nuevoNodo;
                            } else {
                                // Enlazar los nodos (esto depende de c�mo quieras construir el �rbol)
                                raiz->hijos.push_back(nuevoNodo);
                            }
                            especieActual = especieActual->sgteEspecie;
                        }

                        // Mostrar �rbol completo
                        imprimirArbolDesdeRaiz(raiz);
                    } else {
                        cout << "Poblacion no encontrada." << endl;
                    }
                }
                break;
            case 3:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion no valida, intente nuevamente." << endl;
                break;
        }
    } while (opcion != 3);
}

int main() {
    // Crear datos para las especies
    DatosEspecie* datos1 = new DatosEspecie{"Especie A", "Nombre cientifico A"};
    DatosEspecie* datos2 = new DatosEspecie{"Especie B", "Nombre cientifico B"};
    DatosEspecie* datos3 = new DatosEspecie{"Especie C", "Nombre cientifico C"};

    // Crear las especies
    Especie* especie1 = new Especie{"E1", 'M', "sano", 100, datos1, NULL};
    Especie* especie2 = new Especie{"E2", 'F', "sano", 100, datos2, NULL};
    Especie* especie3 = new Especie{"E3", 'F', "sano", 100, datos3, NULL};

    // Crear una poblaci�n y enlazar las especies
    Poblacion* poblacion1 = new Poblacion();
    
    poblacion1->id= "ID1";
    poblacion1->nombreEspecie="ESPECIESSS 1";
    poblacion1->listaEspecies= especie1;
    
    especie1->sgteEspecie = especie2;
    especie2->sgteEspecie = especie3;

    // Crear una segunda poblaci�n con una especie
    DatosEspecie* datos4 = new DatosEspecie{"Especie D", "Nombre cientifico D"};
    Especie* especie4 = new Especie{"E4", 'M', "sano", 100, datos4, NULL};
    
    
    Poblacion* poblacion2 = new Poblacion();
    
    poblacion2->id= "ID2";
    poblacion2->nombreEspecie= "ESPECIESSS 2";
    poblacion2->listaEspecies= especie4;

    // Enlazar las poblaciones
    poblacion1->sgtePoblacion = poblacion2;

    // Ejecutar menu
    mostrarMenu(poblacion1);

    return 0;
}
