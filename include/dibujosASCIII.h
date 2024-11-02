#ifndef DIBUJOSASCII_H
#define DIBUJOSASCII_H

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

string tituloSeleccionarBioma(){
    return
    "\n███████████  █████    ███████    ██████   ██████   █████████    █████████  "
    "\n░███░░░░░███░░███   ███░░░░░███ ░░██████ ██████   ███░░░░░███  ███░░░░░███"
    "\n░███    ░███ ░███  ███     ░░███ ░███░█████░███  ░███    ░███ ░███    ░░░  "
    "\n░██████████  ░███ ░███      ░███ ░███░░███ ░███  ░███████████ ░░█████████  "
    "\n░███░░░░░███ ░███ ░███      ░███ ░███ ░░░  ░███  ░███░░░░░███  ░░░░░░░░███ "
    "\n░███    ░███ ░███ ░░███     ███  ░███      ░███  ░███    ░███  ███    ░███ "
    "\n███████████  █████ ░░░███████░   █████     █████ █████   █████░░█████████  "
    "\n░░░░░░░░░░░  ░░░░░    ░░░░░░░    ░░░░░     ░░░░░ ░░░░░   ░░░░░  ░░░░░░░░░  ";
}


//Dibujos especies
string pezPayaso(){
        return  textoRGB(255,127,0) + " m  m\n" +
                textoRGB(255,127,0) + "><" + 
                textoRGB(255,255,255) + "(" + 
                textoRGB(255,127,0) + "(" +
                textoRGB(255,255,255) + "(" +
                textoRGB(255,127,0) + "(" +
                textoRGB(255,255,255) + "'>";
 }

 string tiburonDeArrecife(){
        return  textoRGB(9,12,187) + "\\_____)\\_____\n" +
                textoRGB(9,12,187) + "/--_____||__`_>\n" + 
                textoRGB(9,12,187) + "        )/     \n" + 
                textoRGB(9,12,187) + "        '        ";
 }

 string langostaComun(){
        return  textoRGB(187,39,9) + "       __  \n" +
                textoRGB(187,39,9) + "v  |  |    \n" + 
                textoRGB(187,39,9) + "<((((())---\n" + 
                textoRGB187,39,9) + "v  |  |__    ";
 }

string pezMariposa(){
        return  textoRGB(255,255,255) + " _____  \n" +
                textoRGB(0,0,0) + "(" + 
                textoRGB(247,223,71) + "| " + 
                textoRGB(0,0,0) + "| " +
                textoRGB(247,223,71) + "|" +
                textoRGB(255,255,255) + ") \n" +
                textoRGB(0,0,0) + "(" +
                textoRGB(247,223,71) + "__" +
                textoRGB(0,0,0) + "__" +
                textoRGB(247,223,71) + "o_" +
                textoRGB(255,255,255) + "> \n" +
                textoRGB(0,0,0) + "     v    ";
 }

string camaronLimpiador(){
        return  textoRGB(255,255,255) + " |    |__\n" +
                textoRGB(247, 13, 74) + ">((((:<__\n" + 
                textoRGB(255,255,255) + " |    |  ";
 }

string algasCoralinas(){
        return  textoRGB(195,50,231) + " vv vv vv   \n" +
                textoRGB(195,50,231) + "< <<  >>  >>\n" + 
                textoRGB(195,50,231) + "  vv vv  vv  ";;
 }

string pezLinterna(){
        return  textoRGB(255,255,255) + "     ___o\n" +
                textoRGB(51,21,32) + " ___" +
                textoRGB(255,255,255) + "|" + 
                textoRGB(51,21,32) + "__  \n" +
                textoRGB(51,21,32) + "(    o | \n" +
                textoRGB(51,21,32) + "(_" +
                textoRGB(255,255,255) + "<" +
                textoRGB(51,21,32) + "___(  \n" +
                textoRGB(255,255,255) + "    v      ";
 }

string pezVibora(){
        return  textoRGB(255,255,255) + "       /      \n" +
                textoRGB(255,255,255) + "       /      \n" +
                textoRGB(65,61,122) + "><" + 
                textoRGB(111,81,117 ) + "((((((((((')\n" +
                textoRGB(65,61,122) + "        w       ";
 }

string medusaPeine(){
        return  textoRGB(32,232,211) + " __________  \n" +
                textoRGB(32,232,211) + "( ---|--|- ) \n" +
                textoRGB(32,232,211) + " (  --|--|  )\n" + 
                textoRGB(32,232,211) + "(__________)   ";
 }

//Dibujos Opciones

string ASCIagregarEspecie(){
        return  textoRGB(255,255,255) + "─────▀▄▀─────▄─────▄\n" +
                textoRGB(255,255,255) + "──▄███████▄──▀██▄██▀\n" +
                textoRGB(255,255,255) + "▄█████▀█████▄──▄█\n" +
                textoRGB(255,255,255) + "███████▀████████▀\n" +
                textoRGB(255,255,255) + "─▄▄▄▄▄▄███████▀  \n";
}

//Funcion doble uso -> ASCI de "Enlistar Especies" (Opcion de simulación) y de "Por Nombre" (Opción de WikiWater)
string ASCIenlistarEspecies_PorNombre(){
        return  textoRGB(255,255,255) + " ><(((('>  ><(((('>  ><(((('>\n" +
                textoRGB(255,255,255) + "     ><(((('>  ><(((('> \n" +
                textoRGB(255,255,255) + " ><(((('>  ><(((('>  ><(((('>\n";
}


string ASCImostrarDatosEspecie(){
        return  textoRGB(255,255,255) + "█████████████████████\n" +
                textoRGB(255,255,255) + "█       DATOS       █\n" +
                textoRGB(255,255,255) + "█   █████████████   █\n" +
                textoRGB(255,255,255) + "█   █           █   █\n" +
                textoRGB(255,255,255) + "█   █  ><((('>  █   █\n" +
                textoRGB(255,255,255) + "█   █████████████   █\n" +
                textoRGB(255,255,255) + "█                   █\n" +
                textoRGB(255,255,255) + "█████████████████████\n";       
}

string ASCImodificarFactores(){
        return  textoRGB(255,255,255) + "─▀▀▌───────▐▀▀\n" +
                textoRGB(255,255,255) + "─▄▀░◌░░░░░░░▀▄\n" +
                textoRGB(255,255,255) + "▐░░◌░▄▀██▄█░░░▌\n" +
                textoRGB(255,255,255) + "▐░░░▀████▀▄░░░▌\n" +
                textoRGB(255,255,255) + "═▀▄▄▄▄▄▄▄▄▄▄▄▀═\n";    
 }

string ASCImodificarFactores(){
        return  textoRGB(255,255,255) + "█▓▒░X░▒▓█   \n";            
}

//Dibujos Modificar Factores

string ASCIoxigeno(){
        return  textoRGB(255,255,255) + "○\n" +
                textoRGB(255,255,255) + "○    ○\n" +
                textoRGB(255,255,255) + "   ○    ○\n" +
                textoRGB(255,255,255) + "○    ○    ○\n" +
                textoRGB(255,255,255) + "   ○    ○\n";    
 }

//Funcion doble uso -> ASCI de "Salinidad" (Opcion de "Modificar Factores") y de "Por Bioma" (Opción de WikiWater)
string ASCIsalinidad_PorBioma(){
        return  textoRGB(255,255,255) + "────▄████▄─────\n" +
                textoRGB(255,255,255) + "─▄██▀─▀▀─▀██▄──\n" +
                textoRGB(255,255,255) + "███───────███─█\n" +
                textoRGB(255,255,255) + "███─█─█───███─▀\n" +
                textoRGB(255,255,255) + "─▀██▄─█─▄██▀──▄\n" +
                textoRGB(255,255,255) + "───▀████▀─────\n";    
}

string ASCItemperatura(){
        return  textoRGB(255,255,255) + " \ | / \n" +
                textoRGB(255,255,255) + "-- ☼ -- \n" +
                textoRGB(255,255,255) + " / | \\n";
}

string ASCIcontaminacion(){
        return  textoRGB(255,255,255) + "▄▀▀▄▀▀▄▀▀▄▀▀▄▀▀▄\n" +
                textoRGB(255,255,255) + "▀▄▄▀▄▄▀▄▄▀▄▄▀▄▄▀\n" +
                textoRGB(255,255,255) + "▄▀▀▄▀▀▄▀▀▄▀▀▄▀▀▄\n" +
                textoRGB(255,255,255) + "▀▄▄▀▄▄▀▄▄▀▄▄▀▄▄▀\n";
}

//Funcion de "Por Listado" (Opción de WikiWater)
string ASCIporListado(){
        return  textoRGB(255,255,255) + "█████████████████████\n" +
                textoRGB(255,255,255) + "█       LISTA       █\n" +
                textoRGB(255,255,255) + "█   █████████████   █\n" +
                textoRGB(255,255,255) + "█   █           █   █\n" +
                textoRGB(255,255,255) + "█   █  ><((('>  █   █\n" +
                textoRGB(255,255,255) + "█   █████████████   █\n" +
                textoRGB(255,255,255) + "█                   █\n" +
                textoRGB(255,255,255) + "█████████████████████\n";       
}

//Dibujo Códigos
string ASCIporListado(){
        return  textoRGB(255,255,255) + "──▄▀▀▀▄───────────────\n" +
                textoRGB(255,255,255) + "──█───█───────────────\n" +
                textoRGB(255,255,255) + "─███████─────────▄▀▀▄─\n" +
                textoRGB(255,255,255) + "░██───██░░█▀█▀▀▀▀█░░█░\n" +
                textoRGB(255,255,255) + "░███▄███░░▀░▀░░░░░▀▀░░ \n";  
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