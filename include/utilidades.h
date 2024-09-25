#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <windows.h>
#include <conio.h>
#include <vector>

using namespace std;

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

string seleccionConFlechas(string titulo, vector<string> opciones, string sentido) {
    const char ENTER = 13, ESC = 27, TECLAESPECIAL = 224;
    const int UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77;

    char tecla;
    int index = 0; // Inicializa el índice en 0
    int numeroOpciones = opciones.size(); // Obtiene el tamaño del vector

    ocultarCursor();

    do {
        system("cls");
        cout << titulo << endl << endl;

        // Muestra las opciones en vertical u horizontal
        if (sentido == "vertical") {
            for (int i = 0; i < numeroOpciones; i++) {
                if (i == index) {
                    cout << "> " << opciones[i] << endl;
                } else {
                    cout << "  " << opciones[i] << endl;
                }
            }
        } else if (sentido == "horizontal") {
            for (int i = 0; i < numeroOpciones; i++) {
                if (i == index) {
                    cout << "> " << opciones[i] << " ";
                } else {
                    cout << "  " << opciones[i] << " ";
                }
            }
            cout << endl;
        } else {
            cout << "Sentido no válido." << endl;
            mostrarCursor();
            return "";
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