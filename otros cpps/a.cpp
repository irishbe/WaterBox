#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

// Estructura de Especie con soporte para múltiples hijos y padres
struct Especie {
    string id;
    string tipoEspecie;
    int vida = 100;
    char genero;
    string color;
    string estadoSalud = "sano";
    
    Especie* sgteEspecie = nullptr;   // Siguiente especie en la lista de la población
    Especie* primerHijo = nullptr;    // Primer hijo
    Especie* sgteHijo = nullptr;      // Siguiente hijo en la lista de hermanos
    Especie* padre = nullptr;         // Referencia al padre de la especie
    Especie* madre = nullptr;         // Referencia a la madre de la especie
};

// Estructura de Población
struct Poblacion {
    string id;
    string tipoEspecie;
    string nombreEspecie;
    int contadorEspecies = 0;
    Especie* listaEspecies = nullptr; // Lista enlazada de especies
    Poblacion* antePoblacion = nullptr;
    Poblacion* sgtePoblacion = nullptr;
};

// Generadores de ID único
int generadorIDPoblacion = 1;
int generadorIDEspecie = 1;

string generarIDPoblacion() {
    stringstream ss;
    ss << setw(3) << setfill('0') << generadorIDPoblacion++;
    return ss.str();
}

string generarIDEspecie(const string& idPoblacion) {
    stringstream ss;
    ss << idPoblacion << setw(3) << setfill('0') << generadorIDEspecie++;
    return ss.str();
}

// Crear una nueva especie
Especie* crearEspecie(const string& tipoEspecie, const string& idPoblacion, char genero, const string& color) {
    Especie* nueva = new Especie();
    nueva->id = generarIDEspecie(idPoblacion);
    nueva->tipoEspecie = tipoEspecie;
    nueva->genero = genero;
    nueva->color = color;
    return nueva;
}

// Añadir una especie a la población
void anadirEspecieAPoblacion(Poblacion* poblacion, Especie* especie) {
    especie->sgteEspecie = poblacion->listaEspecies;
    poblacion->listaEspecies = especie;
    poblacion->contadorEspecies++;
}

// Añadir un hijo a una especie
void anadirHijo(Especie* padre, Especie* madre, Especie* hijo) {
    hijo->padre = padre; // Asignar el padre al hijo
    hijo->madre = madre; // Asignar la madre al hijo
    if (!padre->primerHijo) {
        padre->primerHijo = hijo; // Si no tiene hijos, este será el primero
    } else {
        // Navegar hasta el último hijo y añadir el nuevo
        Especie* actual = padre->primerHijo;
        while (actual->sgteHijo) {
            actual = actual->sgteHijo;
        }
        actual->sgteHijo = hijo;
    }
}

int main() {
    // Crear una población
    Poblacion* poblacion = new Poblacion();
    poblacion->id = generarIDPoblacion();
    poblacion->tipoEspecie = "Pez Payaso";
    poblacion->nombreEspecie = "Clownfish";

    // Crear especies (padres)
    Especie* pez1 = crearEspecie("Pez Payaso", poblacion->id, 'M', "Naranja");
    Especie* pez2 = crearEspecie("Pez Payaso", poblacion->id, 'F', "Naranja");

    // Añadir especies a la población
    anadirEspecieAPoblacion(poblacion, pez1);
    anadirEspecieAPoblacion(poblacion, pez2);

    // Crear hijos
    Especie* hijo1 = crearEspecie("Pez Payaso", poblacion->id, 'M', "Naranja");
    Especie* hijo2 = crearEspecie("Pez Payaso", poblacion->id, 'F', "Naranja");
    Especie* hijo3 = crearEspecie("Pez Payaso", poblacion->id, 'M', "Amarillo");
    Especie* hijo4 = crearEspecie("Pez Payaso", poblacion->id, 'F', "Amarillo");
    Especie* hijo5 = crearEspecie("Pez Payaso", poblacion->id, 'M', "Rojo");
    Especie* hijo6 = crearEspecie("Pez Payaso", poblacion->id, 'F', "Rojo");
    Especie* hijo7 = crearEspecie("Pez Payaso", poblacion->id, 'M', "Azul");
    Especie* hijo8 = crearEspecie("Pez Payaso", poblacion->id, 'F', "Azul");

    // Crear más hijos (generaciones adicionales)
    Especie* hijo9 = crearEspecie("Pez Payaso", poblacion->id, 'M', "Verde");
    Especie* hijo10 = crearEspecie("Pez Payaso", poblacion->id, 'F', "Verde");
    Especie* hijo11 = crearEspecie("Pez Payaso", poblacion->id, 'M', "Morado");

    // Añadir hijos a los padres
    anadirHijo(pez1, pez2, hijo1);
    anadirHijo(pez1, pez2, hijo2);
    anadirHijo(pez1, pez2, hijo3);
    anadirHijo(pez1, pez2, hijo4);
    anadirHijo(pez1, pez2, hijo5);
    anadirHijo(pez1, pez2, hijo6);
    anadirHijo(pez1, pez2, hijo7);
    anadirHijo(pez1, pez2, hijo8);

    // Añadir más generaciones
    anadirHijo(hijo1, pez2, hijo9);
    anadirHijo(hijo2, pez2, hijo10);
    anadirHijo(hijo3, pez2, hijo11);

    // Crear más hijos para las generaciones anteriores
    Especie* hijo12 = crearEspecie("Pez Payaso", poblacion->id, 'M', "Gris");
    Especie* hijo13 = crearEspecie("Pez Payaso", poblacion->id, 'F', "Gris");

    // Añadir más generaciones de hijos
    anadirHijo(hijo9, pez2, hijo12);
    anadirHijo(hijo10, pez2, hijo13);

    // Mostrar población
    mostrarPoblacion(poblacion);

    return 0;
}
