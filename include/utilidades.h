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

    if (!linea.empty()) {
        moverCursor(x, y);
        cout << linea << endl;
    }

    return y;
}

// Función para imprimir las opciones
void imprimirOpciones(vector<string>& opciones, string sentido, int x, int y, int index) {
    for (int i = 0; i < opciones.size(); i++) {
        
        if(x >= 0 && y >= 0 ){

            if (sentido == "vertical") {
                moverCursor(x, y + (i + 1) );
            } else{
                moverCursor(x + (i * 15), y);
            }

        }else{

            if (sentido == "vertical") {
                cout << endl;
            }else{
                cout << "   ";
            }

        }

        if (i == index) {
            cout << "> " << opciones[i];
        } else {
            cout << "  " << opciones[i];
        }
    }
}

void imprimirCancelar(){
    cout << "\n\nPresione ESC o 0 para cancelar la seleccion." << endl;
}

// Función para la selección con flechas
string seleccionConFlechas(string titulo, vector<string> opciones, string sentido, int posX = -1, int posY = -1) {
    const char ENTER = 13, ESC = 27, TECLAESPECIAL = 224;
    const int UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77;

    char tecla;
    int index = 0, tituloY; // Inicializa el índice en 0
    int numeroOpciones = opciones.size(); // Obtiene el tamaño del vector

    if( sentido != "vertical" && sentido != "horizontal" ) return "";

    ocultarCursor();

    do {
        system("cls");
        tituloY = imprimirTitulo(titulo, posX, posY); // Actualizar posY según la altura del título

        // Imprime las opciones en la posición Y que sigue al título
        imprimirOpciones(opciones, sentido, posX, tituloY + 2, index); // Dejar espacio para el título

        imprimirCancelar();

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
            }else{
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