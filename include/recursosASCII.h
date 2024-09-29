#ifndef RECURSOSASCII_H
#define RECURSOSASCII_H

#include <iostream>
#include "utilidades.h"

using namespace std;

string tituloWaterBox() {
    return R"( __   __  ___       __  ___________  _______   _______   _______     ______  ___  ___  
|"  |/  \|  "|     /""\("     _   ")/"     "| /"      \ |   _  "\   /    " \|"  \/"  | 
|'  /    \:  |    /    \)__/  \\__/(: ______)|:        |(. |_)  :) // ____  \\   \  /  
|: /'        |   /' /\  \  \\_ /    \/    |  |_____/   )|:     \/ /  /    ) :)\\  \/   
 \//  /\'    |  //  __'  \ |.  |    // ___)_  //      / (|  _  \\(: (____/ // /\.  \   
 /   /  \\   | /   /  \\  \\:  |   (:      "||:  __   \ |: |_)  :)\        / /  \   \  
|___/    \___|(___/    \___)\__|    \_______)|__|  \___)(_______/  \"_____/ |___/\___|"

                    Navega, sumérgete y explora sin límites)";
}

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

void imprimirCuadro(string nombre, int alto, int ancho) {
    if (nombre.length() > ancho - 2) {
        nombre = nombre.substr(0, ancho - 5) + "...";
    }

    cout << "┌" << string(ancho - 2, '-') << "┐" << endl;

    cout << "│" << nombre << string(ancho - nombre.length() - 2, ' ') << "│" << endl;

    for (int i = 0; i < alto - 2; i++) {
        cout << "│" << string(ancho - 2, ' ') << "│" << endl;

    }

    cout << "└" << string(ancho - 2, '-') << "┘" << endl;
}

// Función para imprimir el cuadro en una posición dada
void imprimirCuadro2(string nombre, int alto, int ancho, int posX, int posY) {
    // Ajustar el nombre si es más largo que el ancho disponible
    if (nombre.length() > ancho - 2) {
        nombre = nombre.substr(0, ancho - 5) + "...";
    }

    // Imprimir la línea superior
    moverCursor(posX, posY);
    cout << "┌" << string(ancho - 2, '-') << "┐";

    // Imprimir la línea del nombre
    moverCursor(posX, posY + 1);
    cout << "│" << nombre << string(ancho - nombre.length() - 2, ' ') << "│";

    // Imprimir las líneas intermedias
    for (int i = 2; i < alto; i++) {
        moverCursor(posX, posY + i);
        cout << "│" << string(ancho - 2, ' ') << "│";
    }

    // Imprimir la línea inferior
    moverCursor(posX, posY + alto);
    cout << "└" << string(ancho - 2, '-') << "┘";
}

#endif // RECURSOSASCII_H