#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>

using namespace std;

// Constantes
const char ENTER = 13, ESC = 27, TECLA_ESPECIAL = 224;
const int LEFT = 75, RIGHT = 77, UP = 72, DOWN = 80, ZERO = '0';
const int COLOR_YELLOW = 14;

void pantallaCompleta() {
    HWND consoleWindow = GetConsoleWindow();
    ShowWindow(consoleWindow, SW_MAXIMIZE);
}

void moverCursor(int x, int y) {
    COORD coord; 
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
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

    moverCursor(0,0);
}

string textoRGB(int r, int g, int b) {
    return "\033[38;2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m";
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

// Función para imprimir el título línea por línea moviendo el cursor
int imprimirTitulo(string titulo, int x, int y) {
    string linea;

    if ( x < 0 || y < 0 ) {
        cout << titulo << endl;
        return y;
    }

    // Comprobar si el título comienza con un salto de línea
    if ( !titulo.empty() && titulo[0] == '\n' ) {
        moverCursor(x, y);
        cout << endl;
        y++;
    }

    for (char c : titulo) {
        if (c == '\n') {
            moverCursor(x, y);
            cout << linea << endl;
            linea.clear();
            y++;
        } else {
            linea += c;
        }
    }

    if ( !linea.empty() ) {
        moverCursor(x, y);
        cout << linea << endl;
    }

    return y + 2;
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

// Funcion que imprime un dibujo y su opcion
void imprimirDibujoConOpcion(const string& dibujo, const string& opcion, int x, int y, bool seleccionado) {
    size_t pos = 0;
    string tempDibujo = dibujo;
    int lineaActual = y;

    // Cambiar el color si es la opcion actual
    if (seleccionado) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_YELLOW); 
    }

    while ((pos = tempDibujo.find('\n')) != string::npos) {
        moverCursor(x, lineaActual);
        cout << tempDibujo.substr(0, pos); // Imprime la linea del dibujo
        tempDibujo.erase(0, pos + 1); // Elimina la linea impresa
        lineaActual++; // Aumenta la linea actual
    }

    // Imprimir la opcion debajo del dibujo
    moverCursor(x, lineaActual + 1);
    cout << opcion << endl; 

    // Luego restablecer el color
    if (seleccionado) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); 
    }
}

// Funcion que imprime todas las opciones y dibujos
void mostrarOpciones(string titu, const vector<string>& opciones, const vector<string>& dibujos, int indiceSeleccionado) {
    system("cls"); 

    moverCursor(30, 3); cout<<titu<<endl;

    int y = 6; // Linea inicial 
    int numeroOpciones = opciones.size();

    // Imprimir dibujos y opciones
    for (int i = 0; i < numeroOpciones; ++i) {
        imprimirDibujoConOpcion(dibujos[i], opciones[i], 5 + i * 35, y, i == indiceSeleccionado);
        y = 6; 
    }
}

// Funcion principal
int mostrarMenu(string titulo, const vector<string>& opciones, const vector<string>& dibujos) {
    char tecla;
    int index = 0; 
    int numeroOpciones = opciones.size();

    mostrarOpciones(titulo, opciones, dibujos, index); 

    while (true) {
        tecla = _getch(); 

        if (tecla == ESC || tecla == ZERO) {
            return -1; // Regresar 
        } else if (tecla == TECLA_ESPECIAL) {
            tecla = _getch(); 

            switch (tecla) {
                case LEFT: 
                    index = (index - 1 + numeroOpciones) % numeroOpciones;
                    mostrarOpciones(titulo, opciones, dibujos, index);
                    break;
                case RIGHT: 
                    index = (index + 1) % numeroOpciones;
                    mostrarOpciones(titulo, opciones, dibujos, index);
                    break;
            }
        } else if (tecla == ENTER) {
            return index; // Devuelve la op seleccionada
        }
    }
}

#endif // UTILIDADES_H