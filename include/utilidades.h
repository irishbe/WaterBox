#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>

using namespace std;

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
    const char ENTER = 13, ESC = 27, TECLAESPECIAL = 224;
    const int UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77;

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

        if (tecla == TECLAESPECIAL) {
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

    } while (tecla != ESC && tecla != '0');

    mostrarCursor();
    return "";
}

#endif // UTILIDADES_H