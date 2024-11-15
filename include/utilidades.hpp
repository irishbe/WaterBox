#ifndef UTILIDADES_HPP
#define UTILIDADES_HPP

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>

#include <ArteASCII/asciiMenu.hpp>
#include <ArteASCII/asciiTitulos.hpp>

using namespace std;

// Constantes
const char ENTER = 13, ESC = 27, TECLA_ESPECIAL = 224;
const int LEFT = 75, RIGHT = 77, UP = 72, DOWN = 80, ZERO = '0';

void pantallaCompleta() {
    HWND consoleWindow = GetConsoleWindow();
    ShowWindow(consoleWindow, SW_MAXIMIZE);
}

int obtenerAnchoConsola() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1; // Ancho de la ventana actual
}

void moverCursor(int x, int y) {
    COORD coord; 
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

string textoRGB(int r, int g, int b) {
    return "\033[38;2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m";
}

string resetearColor(){
    return "\033[38;2;" + to_string(255) + ";" + to_string(255) + ";" + to_string(255) + "m";
}

void fondoRGB(int r, int g, int b) {
    // Obtener el tamaño de la consola
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int consoleWidth = csbi.dwSize.X;
    int consoleHeight = csbi.dwSize.Y;

    // Cambiar el color de fondo con ANSI y llenar cada línea con espacios
    cout << "\033[48;2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m";
    
    for (int i = 0; i < consoleHeight; ++i) {
        cout << string(consoleWidth, ' ');
    }

    // Mover el cursor a la posición inicial
    moverCursor(0, 0);
}

void ocultarCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;  // Ocultar el cursor
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void mostrarCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = TRUE;  // Mostrar el cursor
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}


//------------------------------------------- SELECCIONAR CON FLECHAS ----------------------------------



// Función para imprimir el título línea por línea moviendo el cursor
int imprimirTitulo(const string& titulo, int x = -1, int y = -1) {
    vector<string> lineas;
    size_t pos = 0;
    size_t siguientePos;

    // Dividir el título en líneas
    while ((siguientePos = titulo.find('\n', pos)) != string::npos) {
        lineas.push_back(titulo.substr(pos, siguientePos - pos));
        pos = siguientePos + 1;
    }
    lineas.push_back(titulo.substr(pos)); // Agregar la última línea

    // Obtener el ancho de la consola
    int anchoConsola = obtenerAnchoConsola();

    // Si no se proporcionan coordenadas
    if (x < 0 && y < 0) {
        y = 0; // Usar la primera línea si no se proporciona y
    }

    // Imprimir cada línea centrada
    for (const string& linea : lineas) {
        string lineaRecortada = linea;
        lineaRecortada.erase(0, lineaRecortada.find_first_not_of(' ')); // Eliminar espacios al inicio
        lineaRecortada.erase(lineaRecortada.find_last_not_of(' ') + 1); // Eliminar espacios al final

        if (lineaRecortada.empty()) {
            moverCursor(x >= 0 ? x : 0, y);
            cout << endl; // Simplemente imprime una línea vacía
            y++;
            continue;
        }

        int longitudLinea = lineaRecortada.length();
        int espacioIzquierdo = (anchoConsola - longitudLinea) / 2;

        // Asegurarse de que no imprima espacio negativo
        if (espacioIzquierdo < 0) espacioIzquierdo = 0;

        moverCursor(x >= 0 ? x : espacioIzquierdo, y); // Usar el x calculado o el proporcionado
        cout << lineaRecortada << endl;
        y++; // Incrementar y para la siguiente línea
    }

    return y; // Retornar la nueva posición y
}

// Función para imprimir las opciones
int imprimirOpciones(vector<string> opciones, string sentido, bool centrado, int x, int y, int index) {
    
    if ( sentido == "horizontal" ){
        cout << "\n";
    }

    for (int i = 0; i < opciones.size(); i++) {
        
        // Mover el cursor según el sentido
        if (sentido == "vertical") {
            
            if( x >= 0 && y >= 0 ){
                moverCursor(x, y + (i + 1));
            }else{
                cout << endl;
            }

            if (centrado) {
                cout << "\t\t\t";
            }

        } else if( sentido == "horizontal" ){  // Horizontal

            if( x >= 0 && y >= 0 ){
                moverCursor(x + (i * 15), y);
            }else{
                cout << "   ";
            }
            
            if (centrado) {
                cout << "\t\t\t";
            }
        }

        // Imprimir la opción
        if (i == index) {
            cout << "> " << opciones[i];
        } else {
            cout << "  " << opciones[i];
        }
    }

    return y + opciones.size() + 3;
}

void imprimirCancelar(int x, int y){
    if( x >= 0 && y >= 0 ){
        moverCursor(x,y);
        cout << "Presione ESC o 0 para cancelar la seleccion." << endl;
    }else{
        cout << "\n\nPresione ESC o 0 para cancelar la seleccion." << endl;
    }
}

// Función para la selección con flechas
string seleccionConFlechas(string titulo, vector<string> opciones, string sentido, bool centrado = false, int posX = -1, int posY = -1) {
    char tecla;
    int index = 0, tituloY, opcionesY; // Inicializa el índice en 0
    int numeroOpciones = opciones.size(); // Obtiene el tamaño del vector

    if( sentido != "vertical" && sentido != "horizontal" ) return "";

    ocultarCursor();

    do {
        system("cls");
        tituloY = imprimirTitulo(titulo, posX, posY); // Actualizar posY según la altura del título

        // Imprime las opciones en la posición Y que sigue al título
        opcionesY = imprimirOpciones(opciones, sentido, centrado, posX, tituloY, index); // Dejar espacio para el título

        imprimirCancelar(posX, opcionesY);

        tecla = _getch();

        if (tecla == TECLA_ESPECIAL) {
            tecla = _getch(); // Capturar el código de la tecla de flecha


            if (sentido == "vertical") {

                switch (tecla) {
                    case UP:
                        index = (index - 1 + numeroOpciones) % numeroOpciones; // Mover hacia arriba en vertical
                        break;
                    case DOWN:
                        index = (index + 1) % numeroOpciones; // Mover hacia abajo en vertical
                        break;
                }

            }else if(sentido == "horizontal"){

                switch (tecla) {
                    case LEFT:
                        index = (index - 1 + numeroOpciones) % numeroOpciones; // Mover hacia la izquierda en horizontal
                        break;
                    case RIGHT:
                        index = (index + 1) % numeroOpciones; // Mover hacia la derecha en horizontal
                        break;
                }

            }
        }

        if (tecla == ENTER) {
            mostrarCursor();
            return opciones[index];
        }

    } while (tecla != ESC && tecla != ZERO);

    mostrarCursor();
    return "";
}


// ------------------------------------------ SELECCIONAR CON DIBUJOS ------------------------------------------

// Funcion que imprime un dibujo y su opcion
void imprimirDibujo(string dibujo, int x, int y, bool seleccionado) {
    size_t pos = 0;
    string tempDibujo = dibujo;
    int lineaActual = y;

    // Cambiar el color si es la opción seleccionada
    if (seleccionado) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    }

    // Imprimir el dibujo línea por línea
    while ((pos = tempDibujo.find('\n')) != string::npos) {
        moverCursor(x, lineaActual);
        cout << tempDibujo.substr(0, pos); // Imprime la línea del dibujo
        tempDibujo.erase(0, pos + 1); // Elimina la línea impresa
        lineaActual++; // Aumenta la línea actual
    }

    // Restablecer el color
    if (seleccionado) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
}

int imprimirTexto(string texto, int x, int y, bool centrar, bool isSubtitulo = false) {
    int lineaActual = y;
    int altura = 0;
    size_t inicio = 0, pos = 0;
    bool ultimaLineaVacia = false;

    if (isSubtitulo && !texto.empty()) {
        int anchoTexto = texto.length() + 4;
        string borde = string(anchoTexto, '-');
        int xCentered = (obtenerAnchoConsola() - anchoTexto) / 2;

        moverCursor(xCentered, lineaActual);
        cout << borde;
        lineaActual++;
        altura++;

        moverCursor(xCentered, lineaActual);
        cout << "  " << texto << "  ";
        lineaActual++;
        altura++;

        moverCursor(xCentered, lineaActual);
        cout << borde;
        lineaActual++;
        altura++;
    } else {
        // Procesar el texto línea por línea, considerando los saltos de línea '\n'
        while ((pos = texto.find('\n', inicio)) != string::npos) {
            string linea = texto.substr(inicio, pos - inicio);

            if (centrar) {
                int xCentered = (obtenerAnchoConsola() - linea.length()) / 2;
                moverCursor(xCentered, lineaActual);
            } else {
                moverCursor(x, lineaActual);
            }

            cout << linea;
            lineaActual++;
            altura++;
            inicio = pos + 1;

            // Verificar si la última línea era vacía
            if (inicio == texto.length()) {
                ultimaLineaVacia = true;
            }
        }

        // Imprimir la última línea si queda texto sin un salto de línea final
        if (inicio < texto.length() || ultimaLineaVacia) {
            string ultimaLinea = texto.substr(inicio);
            if (centrar) {
                int xCentered = (obtenerAnchoConsola() - ultimaLinea.length()) / 2;
                moverCursor(xCentered, lineaActual);
            } else {
                moverCursor(x, lineaActual);
            }

            cout << ultimaLinea;
            lineaActual++;
            altura++;
        }
    }

    return altura;
}

void mostrarOpciones(string titulo, string subtitulo, vector<string> dibujos, bool centrar, int indiceSeleccionado) {
    system("cls"); 

    int y = 3;
    
    if ( subtitulo != "" ){
        y += imprimirTexto(titulo, 0, y, centrar) + 3;
        y += imprimirTexto(subtitulo, 0, y, centrar, true) + 3;
    }else{
        y += imprimirTexto(titulo, 0, y, centrar) + 4;
    }

    int numeroOpciones = dibujos.size();

    int margenIzquierda = 10;
    int espacioDisponible = obtenerAnchoConsola() - margenIzquierda;
    int espacioEntreDibujos = espacioDisponible / numeroOpciones;

    int espacioRestante = espacioDisponible - (espacioEntreDibujos * numeroOpciones);
    int xOffset = margenIzquierda;

    for (int i = 0; i < numeroOpciones; ++i) {
        int xPos = xOffset + i * espacioEntreDibujos;
        imprimirDibujo(dibujos[i], xPos, y, i == indiceSeleccionado);
    }
}

// Función principal mejorada
int seleccionarConDibujos(const vector<string>& dibujos, const string& titulo, const string& subtitulo = "", bool centrar = true) {
    ocultarCursor();
    
    char tecla;
    int opcionSeleccionada = 0;
    int numeroOpciones = dibujos.size();

    // Mostrar las opciones inicialmente
    mostrarOpciones(titulo, subtitulo, dibujos, centrar, opcionSeleccionada);

    while (true) {
        tecla = _getch(); 

        // Manejo de la tecla especial (ESC o '0' para regresar)
        if (tecla == ESC || tecla == ZERO) {
            mostrarCursor();
            return -1;  // Regresar si se presiona ESC o '0'
        }

        // Manejo de las teclas de flecha
        if (tecla == TECLA_ESPECIAL) {
            tecla = _getch(); 

            switch (tecla) {
                case LEFT: 
                    opcionSeleccionada = (opcionSeleccionada - 1 + numeroOpciones) % numeroOpciones;
                    break;
                case RIGHT: 
                    opcionSeleccionada = (opcionSeleccionada + 1) % numeroOpciones;
                    break;
            }

            // Actualizar la visualización después del cambio de opción
            mostrarOpciones(titulo, subtitulo, dibujos, centrar, opcionSeleccionada);
        } 

        // Manejo de la tecla Enter
        if (tecla == ENTER) {
            mostrarCursor();
            return opcionSeleccionada;  // Devuelve la opción seleccionada
        }
    }
}

#endif // UTILIDADES.HPP