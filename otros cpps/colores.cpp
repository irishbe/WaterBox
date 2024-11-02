#include <iostream>
#include "utilidades.h"

using namespace std;

int main(){
    fondoRGB(82, 137, 152); // Fondo azul verdoso

    // Título
    moverCursor(20, 1);
    cout << textoRGB(33, 94, 232) << "WIKIWATER" << endl;

    // Cuadro de la ballena
    moverCursor(5, 3);
    cout << textoRGB(255, 255, 255) << "+---------------------------+" << endl;
    moverCursor(5, 4);
    cout << "|        Ballena           |" << endl;
    moverCursor(5, 5);
    cout << "|                           |" << endl;
    moverCursor(5, 6);
    cout << "|           \":\"            |" << endl;
    moverCursor(5, 7);
    cout << "|       __     |\"\\/\"|      |" << endl;
    moverCursor(5, 8);
    cout << "|    _/o  \\_  /  \\ /  |    |" << endl;
    moverCursor(5, 9);
    cout << "|   (  (    ) )   / / /    |" << endl;
    moverCursor(5, 10);
    cout << "|   '---'---'    ~~~~~~    |" << endl;
    moverCursor(5, 11);
    cout << "+---------------------------+" << endl;

    // Información de la ballena
    moverCursor(30, 4);
    cout << textoRGB(255, 0, 0) << "Nombre cientifico: Ballentius" << endl;
    moverCursor(30, 5);
    cout << "Habitat: Arrecife de coral" << endl;

    // Datos adicionales
    moverCursor(30, 7);
    cout << textoRGB(255, 215, 0) << "♡ Esperanza de vida: 2000" << endl;
    moverCursor(30, 8);
    cout << "☾ Inactividad Reproductiva: 3m" << endl;
    moverCursor(30, 9);
    cout << "☼ Temperatura: 19°" << endl;
    moverCursor(30, 10);
    cout << "◉ Salinidad: 12" << endl;
    moverCursor(30, 11);
    cout << "◌ Oxigeno: 3" << endl;

    // Resetear colores
    textoRGB(0,0,0);

    return 0;
}