#ifndef RECURSOSASCII_H
#define RECURSOSASCII_H

#include <iostream>
#include <sstream>
#include "utilidades.h"

using namespace std;

string tituloWaterBox() {
    return 
    "\n __   __  ___       __  ___________  _______   _______   _______     ______  ___  ___"
    "\n|\"  |/  \\|  \"|     /\"\"\\(\"     _   \")/\"     \"| /\"      \\ |   _  \"\\   /    \" \\|\"  \\/\"  |"
    "\n|\'  /    \\:  |    /    \\\\)_/  \\\\\\\\/(: ______)|:        |(. |_)  :) // __   \\\\\\   \\\\  /  "
    "\n|: /\'        |   /' /\\  \\  \\\\_ /    \\/    |  |_____/   )|:     \\/ /  /    ) :)\\\\  \\/   "
    "\n \\//  /\\\'    |  //  __'  \\ |.  |    // ___)_  //      / (|  _  \\\\(: (____/ // /\\.  \\   "
    "\n /   /  \\\\   | /   /  \\\\  \\\\:  |   (:      \"||:  __   \\ |: |_)  :)\\        / /  \\   \\  "
    "\n|___/    \\___|(___/    \\___)\\__|    \\_______)|__|  \\___)(_______/  \\\"_____/ |___/\\___|";
}

string rgb(int r, int g, int b) {
    return "\033[38;2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m";
}

string obtenerSprite(string nombreEspecie) {
    
    if (nombreEspecie == "Pez payaso") {
        return  rgb(255,127,0) + " m  m\n" +
                rgb(255,127,0) + "><" + 
                rgb(255,255,255) + "(" + 
                rgb(255,127,0) + "(" +
                rgb(255,255,255) + "(" +
                rgb(255,127,0) + "(" +
                rgb(255,255,255) + "'>";

    } else if( nombreEspecie == "Tiburon de arrecife" ){
        return  "\\_____)\\_____\n"
                "/--_____||__`_>\n"
                "        )/     \n"
                "        '        ";

    } else if( nombreEspecie == "Langosta comun" ){
        return  "       __  \n"
                "v  |  |    \n"
                "<((((())---\n"
                "v  |  |__    ";

    } else if( nombreEspecie == "Pez mariposa" ){
        return  " _____  \n"
                "(| | |) \n"
                "(____o_>\n"
                "     v    ";

    } else if( nombreEspecie == "Camaron Limpiador" ){
        return  " |    |__\n"
                ">((((:<__\n"
                " |    |  ";

    } else if( nombreEspecie == "Algas coralinas" ){
        return  " vv vv vv   \n"
                "< <<  >>  >>\n"
                "  vv vv  vv  ";
    
    } else if( nombreEspecie == "Pez Linterna" ){
        return  "     ___o\n"
                " ___|__  \n"
                "(    o | \n"
                "(_<___(  \n"
                "    v      ";
    
    } else if( nombreEspecie == "Pez Vibora" ){
        return  "       /      \n"
                "       /      \n"
                "><((((((((((')\n"
                "        w       ";
    
    } else if( nombreEspecie == "Medusa Peine" ){
        return  " __________  \n"
                "( ---|--|- ) \n"
                " (  --|--|  )\n"
                "(__________)   ";
    } else{
        return "???";
    }
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
    int startY = posY + (altoCuadro - spriteHeight) / 2;

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
        ancho = 28; // Ancho para cuadro mediano
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

    // Imprimir nombre especie
    moverCursor(posX + 1, posY + 1);
    cout << poblacion->nombreEspecie;

    // Imprimir contador especies
    moverCursor(posX + ancho - 2, posY + 1);
    cout << poblacion->contadorEspecies;

    // Insertar el sprite centrado en el cuadro
    insertarSprite(sprite, posX, posY, ancho, alto);

    // Mover el cursor debajo del cuadro
    moverCursor(posX, posY + alto + 1);
}

#endif // RECURSOSASCII_H