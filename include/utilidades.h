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

string seleccionConFlechas(string titulo, vector<string> opciones, string sentido, int posX = NULL, int posY = NULL) {
    const char ENTER = 13, ESC = 27, TECLAESPECIAL = 224;
    const int UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77;

    char tecla;
    int index = 0; // Inicializa el índice en 0
    int numeroOpciones = opciones.size(); // Obtiene el tamaño del vector

    ocultarCursor();

    do{
        system("cls");
        cout << titulo << endl << endl;

        // Muestra las opciones en vertical u horizontal
        for (int i = 0; i < numeroOpciones; i++) {
            // Calcular la posición para cada opción
            int currentX = posX;
            int currentY = posY;

            if (sentido == "vertical") {
                currentY += i; // Incrementar la posición Y para cada opción
            } else if (sentido == "horizontal") {
                currentX += i; // Incrementar la posición X para cada opción
            } else {
                cout << "Sentido no válido." << endl;
                mostrarCursor();
                return "";
            }

            // Mover el cursor a la posición actual antes de imprimir
            if(posX != NULL && posY != NULL){
                moverCursor(currentX, currentY);
            }
            
            // Imprimir la opción con un marcador si es la seleccionada
            if (i == index) {
                cout << "> " << opciones[i] << endl;
            } else {
                cout << "  " << opciones[i] << endl;
            }
        }

        cout << "\nPresione ESC o 0 para cancelar la seleccion." << endl;

        tecla = _getch();

        if (tecla == TECLAESPECIAL) {
            tecla = _getch(); // Capturar el código de la tecla de flecha

            // Mover el índice según el sentido y la tecla presionada
            if (sentido == "vertical") {
                switch (tecla) {
                    case UP: 
                        index = (index - 1 + numeroOpciones) % numeroOpciones; break;
                    case DOWN: 
                        index = (index + 1) % numeroOpciones; break;
                }
            } else if (sentido == "horizontal") {
                switch (tecla) {
                    case LEFT: 
                        index = (index - 1 + numeroOpciones) % numeroOpciones; break;
                    case RIGHT: 
                        index = (index + 1) % numeroOpciones; break;
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