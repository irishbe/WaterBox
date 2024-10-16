#include <iostream>
#include <string>
#include <sstream>   // Para istringstream
#include <windows.h> // Para usar la API de Windows
#include "utilidades.h"
#include "Especie.h"
#include "crudDatosEspecies.h"
using namespace std;

// Función que retorna un sprite ASCII como string
string obtenerSprite() {
    return 
    "\n  |   |__"
    "\n>((((:<__"
    "\n  |   |  ";
}

string obtenerSprite2(){
    return
    "\n  m  m  "
    "\n><(((('>";
}

string obtenerSprite3(){
    return
    "\n \\_____)\\_____      "
    "\n  /--_____||__`_>    "
    "\n          )/         "
    "\n          '          "; 
}

// Función para imprimir el cuadro según el tamaño
void imprimirCuadro(int alto, int ancho, int posX, int posY) {
    // Imprimir la línea superior
    moverCursor(posX, posY);
    cout << "+";
    for (int i = 0; i < ancho - 2; i++) cout << "-";
    cout << "+";

    // Imprimir las líneas laterales
    for (int y = 1; y < alto - 1; y++) {
        moverCursor(posX, posY + y);
        cout << "|";
        for (int i = 0; i < ancho - 2; i++) cout << " ";
        cout << "|";
    }

    // Imprimir la línea inferior
    moverCursor(posX, posY + alto - 1);
    cout << "+";
    for (int i = 0; i < ancho - 2; i++) cout << "-";
    cout << "+";
}

// Función para insertar el sprite centrado en el recuadro
void insertarSprite(string sprite, int posX, int posY, int anchoCuadro, int altoCuadro) {
    // Dividir el sprite en líneas
    istringstream spriteStream(sprite);
    string linea;
    int lineCount = 0;

    // Contar cuántas líneas tiene el sprite para centrar en Y
    int spriteHeight = 0;
    while (getline(spriteStream, linea)) {
        spriteHeight++;
    }

    // Calcular la posición inicial en Y para centrar el sprite verticalmente
    int startY = posY + (altoCuadro - spriteHeight) / 2;

    // Volver al inicio del stream
    spriteStream.clear();
    spriteStream.seekg(0, ios::beg);

    // Imprimir cada línea del sprite centrada horizontal y verticalmente
    while (getline(spriteStream, linea)) {
        // Calcular el offset para centrar la línea del sprite en X
        int offsetX = (anchoCuadro - 2 - linea.size()) / 2;
        moverCursor(posX + 1 + offsetX, startY + lineCount);
        cout << linea;
        lineCount++;
    }
}

// Función para imprimir la población dentro del cuadro
void imprimirPoblacion(Especie *especie, string sprite, string tamanio, int posX, int posY) {
    int alto = 0;
    int ancho = 0;

    // Determinar el tamaño del cuadro según el argumento
    if (tamanio == "PEQUEÑO") {
        alto = 7;   // Altura para cuadro pequeño
        ancho = 20; // Ancho para cuadro pequeño
    } else if (tamanio == "MEDIANO") {
        alto = 8;   // Altura para cuadro mediano
        ancho = 28; // Ancho para cuadro mediano
    } else if (tamanio == "GRANDE") {
        alto = 9;  // Altura para cuadro grande
        ancho = 40; // Ancho para cuadro grande
    } else {
        cout << "\nTamanio no reconocido, se usará tamanio mediano por defecto." << endl;
        alto = 8;   
        ancho = 28; 
    }

    // Imprimir el cuadro
    imprimirCuadro(alto, ancho, posX, posY);

    // Imprimir nombre especie
    moverCursor(posX + 1, posY + 1);
    cout << especie->datosEspecie->nombreComun;

    // Imprimir contador especies
    moverCursor(posX + ancho - 2, posY + 1);
    cout << especie->id;

    // Insertar el sprite centrado en el cuadro
    insertarSprite(sprite, posX, posY, ancho, alto);

    // Mover el cursor debajo del cuadro
    moverCursor(posX, posY + alto + 1);
}

int main() {
    pantallaCompleta();

    Especie *especie1 = new Especie();
    especie1->datosEspecie = extraerDatosEspecie("Animal", "Camaron Limpiador");

    Especie *especie2 = new Especie();
    especie2->datosEspecie = extraerDatosEspecie("Animal", "Pez payaso");

    Especie *especie3 = new Especie();
    especie3->datosEspecie = extraerDatosEspecie("Animal", "Tiburon de arrecife");

    imprimirPoblacion(especie1, obtenerSprite(), "MEDIANO", 3, 0); // Cambia el tamaño y la posición según necesites
    imprimirPoblacion(especie2, obtenerSprite2(), "PEQUEÑO", 3, 10);
    imprimirPoblacion(especie3, obtenerSprite3(), "GRANDE", 5, 20);

    //moverCursor(70, 40);
    getch();
    return 0;
}
#include <iostream>
#include <string>
#include <sstream>   // Para istringstream
#include <windows.h> // Para usar la API de Windows
#include "utilidades.h"
#include "Especie.h"
#include "crudDatosEspecies.h"
using namespace std;

// Función que retorna un sprite ASCII como string
string obtenerSprite() {
    return 
    "\n  |   |__"
    "\n>((((:<__"
    "\n  |   |  ";
}

string obtenerSprite2(){
    return
    "\n  m  m  "
    "\n><(((('>";
}

string obtenerSprite3(){
    return
    "\n \\_____)\\_____      "
    "\n  /--_____||__`_>    "
    "\n          )/         "
    "\n          '          "; 
}

// Función para imprimir el cuadro según el tamaño
void imprimirCuadro(int alto, int ancho, int posX, int posY) {
    // Imprimir la línea superior
    moverCursor(posX, posY);
    cout << "+";
    for (int i = 0; i < ancho - 2; i++) cout << "-";
    cout << "+";

    // Imprimir las líneas laterales
    for (int y = 1; y < alto - 1; y++) {
        moverCursor(posX, posY + y);
        cout << "|";
        for (int i = 0; i < ancho - 2; i++) cout << " ";
        cout << "|";
    }

    // Imprimir la línea inferior
    moverCursor(posX, posY + alto - 1);
    cout << "+";
    for (int i = 0; i < ancho - 2; i++) cout << "-";
    cout << "+";
}

// Función para insertar el sprite centrado en el recuadro
void insertarSprite(string sprite, int posX, int posY, int anchoCuadro, int altoCuadro) {
    // Dividir el sprite en líneas
    istringstream spriteStream(sprite);
    string linea;
    int lineCount = 0;

    // Contar cuántas líneas tiene el sprite para centrar en Y
    int spriteHeight = 0;
    while (getline(spriteStream, linea)) {
        spriteHeight++;
    }

    // Calcular la posición inicial en Y para centrar el sprite verticalmente
    int startY = posY + (altoCuadro - spriteHeight) / 2;

    // Volver al inicio del stream
    spriteStream.clear();
    spriteStream.seekg(0, ios::beg);

    // Imprimir cada línea del sprite centrada horizontal y verticalmente
    while (getline(spriteStream, linea)) {
        // Calcular el offset para centrar la línea del sprite en X
        int offsetX = (anchoCuadro - 2 - linea.size()) / 2;
        moverCursor(posX + 1 + offsetX, startY + lineCount);
        cout << linea;
        lineCount++;
    }
}

// Función para imprimir la población dentro del cuadro
void imprimirPoblacion(Especie *especie, string sprite, string tamanio, int posX, int posY) {
    int alto = 0;
    int ancho = 0;

    // Determinar el tamaño del cuadro según el argumento
    if (tamanio == "PEQUEÑO") {
        alto = 7;   // Altura para cuadro pequeño
        ancho = 20; // Ancho para cuadro pequeño
    } else if (tamanio == "MEDIANO") {
        alto = 8;   // Altura para cuadro mediano
        ancho = 28; // Ancho para cuadro mediano
    } else if (tamanio == "GRANDE") {
        alto = 9;  // Altura para cuadro grande
        ancho = 40; // Ancho para cuadro grande
    } else {
        cout << "\nTamanio no reconocido, se usará tamanio mediano por defecto." << endl;
        alto = 8;   
        ancho = 28; 
    }

    // Imprimir el cuadro
    imprimirCuadro(alto, ancho, posX, posY);

    // Imprimir nombre especie
    moverCursor(posX + 1, posY + 1);
    cout << especie->datosEspecie->nombreComun;

    // Imprimir contador especies
    moverCursor(posX + ancho - 2, posY + 1);
    cout << especie->id;

    // Insertar el sprite centrado en el cuadro
    insertarSprite(sprite, posX, posY, ancho, alto);

    // Mover el cursor debajo del cuadro
    moverCursor(posX, posY + alto + 1);
}

int main() {
    pantallaCompleta();

    Especie *especie1 = new Especie();
    especie1->datosEspecie = extraerDatosEspecie("Animal", "Camaron Limpiador");

    Especie *especie2 = new Especie();
    especie2->datosEspecie = extraerDatosEspecie("Animal", "Pez payaso");

    Especie *especie3 = new Especie();
    especie3->datosEspecie = extraerDatosEspecie("Animal", "Tiburon de arrecife");

    imprimirPoblacion(especie1, obtenerSprite(), "MEDIANO", 3, 0); // Cambia el tamaño y la posición según necesites
    imprimirPoblacion(especie2, obtenerSprite2(), "PEQUEÑO", 3, 10);
    imprimirPoblacion(especie3, obtenerSprite3(), "GRANDE", 5, 20);

    //moverCursor(70, 40);
    getch();
    return 0;
}