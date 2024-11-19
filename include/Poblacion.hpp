#ifndef POBLACION_HPP
#define POBLACION_HPP

#include "Especie.hpp"
#include "utilidades.hpp"
using namespace std;

struct Poblacion {
    string id;
    string tipoEspecie;
    string nombreEspecie;
    int anchoCuadro;
    int altoCuadro;
    int contadorEspecies;

    Especie* listaEspecies;
    Poblacion* antePoblacion;
    Poblacion* sgtePoblacion;
};


// Funciones de impresion
void imprimirBarra(string nombre, float porcentaje) {
    const int totalBloques = 10;
    int bloquesLlenos = (porcentaje * totalBloques) / 100;
    int bloquesVacios = totalBloques - bloquesLlenos;

    cout << nombre << " ";

    for (int i = 0; i < totalBloques; i++) {
        if (i < bloquesLlenos) {
            cout << "█";
        } else {
            cout << "▒";
        }
    }

    cout << " " << porcentaje << "%";
}

void imprimirCuadro(int alto, int ancho, int posX, int posY) {
    // Imprimir la lÃ­nea superior
    moverCursor(posX, posY);
    cout << "+";
    for (int i = 0; i < ancho - 2; i++) cout << "-";
    cout << "+";

    // Imprimir las lÃ­neas laterales
    for (int y = 1; y < alto - 1; y++) {
        moverCursor(posX, posY + y);
        cout << "|";
        for (int i = 0; i < ancho - 2; i++) cout << " ";
        cout << "|";
    }

    // Imprimir la lÃ­nea inferior
    moverCursor(posX, posY + alto - 1);
    cout << "+";
    for (int i = 0; i < ancho - 2; i++) cout << "-";
    cout << "+";
}

int contarCaracteresSinANSI(const string& linea) {
    int count = 0;
    bool inEscape = false;
    for (char c : linea) {
        if (c == '\033') {
            inEscape = true;
        } else if (inEscape && c == 'm') {
            inEscape = false;
        } else if (!inEscape) {
            count++;
        }
    }
    return count;
}

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
    int effectiveHeight = altoCuadro - 1;
    int startY = posY + 2 + (effectiveHeight - spriteHeight) / 2;

    // Volver al inicio del stream
    spriteStream.clear();
    spriteStream.seekg(0, ios::beg);

    // Imprimir cada línea del sprite centrada horizontal y verticalmente
    while (getline(spriteStream, linea)) {
        int visibleLength = contarCaracteresSinANSI(linea);
        int offsetX = (anchoCuadro - 2 - visibleLength) / 2;
        moverCursor(posX + 1 + offsetX, startY + lineCount);
        cout << linea;
        lineCount++;
    }
}

void imprimirPoblacion(Poblacion* poblacion, string sprite, string tamanio, int posX, int posY) {
    int alto = 0;
    int ancho = 0;

    // Determinar el tamaÃ±o del cuadro segÃºn el argumento
    if (tamanio == "PEQUENIO") {
        alto = 7;   // Altura para cuadro pequeÃ±o
        ancho = 20; // Ancho para cuadro pequeÃ±o
    } else if (tamanio == "MEDIANO") {
        alto = 8;   // Altura para cuadro mediano
        ancho = 30; // Ancho para cuadro mediano
    } else if (tamanio == "GRANDE") {
        alto = 9;  // Altura para cuadro grande
        ancho = 40; // Ancho para cuadro grande
    } else {
        cout << "\nTamanio no reconocido, se usara el tamanio mediano por defecto." << endl;
        alto = 7;   
        ancho = 28; 
    }

    // Imprimir el cuadro
    imprimirCuadro(alto, ancho, posX, posY);

    // Insertar el sprite centrado en el cuadro
    insertarSprite(sprite, posX, posY, ancho, alto);

    // Imprimir nombre especie
    moverCursor(posX + 1, posY + 1);
    cout << poblacion->nombreEspecie;

    // Imprimir contador especies
    moverCursor(posX + ancho - 2, posY + 1);
    cout << poblacion->contadorEspecies;

    // Mover el cursor debajo del cuadro
    moverCursor(posX, posY + alto + 1);
}

#endif // ESPECIE_H