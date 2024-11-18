#ifndef UTILIDADES_HPP
#define UTILIDADES_HPP

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>

#include <ArteASCII/asciiEspecies.hpp>
#include <ArteASCII/asciiMenu.hpp>
#include <ArteASCII/asciiTitulos.hpp>

using namespace std;

// Constantes
const char ENTER = 13, ESC = 27, TECLA_ESPECIAL = 224;
const int LEFT = 75, RIGHT = 77, UP = 72, DOWN = 80, ZERO = '0';

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

void pantallaCompleta() {
    HWND consoleWindow = GetConsoleWindow();
    ShowWindow(consoleWindow, SW_MAXIMIZE);
}

void habilitarASCII() {
    // Obtener el manejador de la consola
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // Habilitar el procesamiento de secuencias ANSI
    DWORD modoConsola;
    GetConsoleMode(hConsole, &modoConsola);
    modoConsola |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hConsole, modoConsola);
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

void fondoRGB(int r, int g, int b) {
    // Obtener el tamaño de la consola
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int consoleWidth = obtenerAnchoConsola();
    int consoleHeight = 20;

    // Cambiar el color de fondo con ANSI y llenar cada línea con espacios
    cout << "\033[48;2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m";
    
    for (int i = 0; i < consoleHeight; ++i) {
        cout << string(consoleWidth, ' ');
    }

    // Mover el cursor a la posición inicial
    moverCursor(0, 0);
    system("cls");
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

// ------------------------------------------ SELECCIONAR CON DIBUJOS ------------------------------------------

// Funcion que imprime un dibujo y su opcion
void imprimirOpcionDibujo(string dibujo, int x, int &y, bool seleccionado) {
    size_t pos = 0;
    string tempDibujo = dibujo;
    int lineaActual = y;

    // Cambiar el color si es la opción seleccionada
    if (seleccionado) {
        cout << textoRGB(255,255,0);
    }

    // Imprimir el dibujo línea por línea
    while ((pos = tempDibujo.find('\n')) != string::npos) {
        moverCursor(x, lineaActual);
        cout << tempDibujo.substr(0, pos); // Imprime la línea del dibujo
        tempDibujo.erase(0, pos + 1); // Elimina la línea impresa
        lineaActual++; // Aumenta la línea actual
    }

    // Imprimir cualquier contenido restante (última línea sin '\n')
    if (!tempDibujo.empty()) {
        moverCursor(x, lineaActual);
        cout << tempDibujo;
        lineaActual++;
    }

    // Restablecer el color
    if (seleccionado) {
        cout << textoRGB(255,255,255);
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

void imprimirOpcionesDibujos(string titulo, string subtitulo, vector<string> dibujos, bool centrar, int indiceSeleccionado) {
    system("cls"); 

    int y = 3, x = 0;
    
    if ( subtitulo != "" ){
        y += imprimirTexto(titulo, x, y, centrar) + 3;
        y += imprimirTexto(subtitulo, x, y, centrar, true) + 3;
    }else{
        y += imprimirTexto(titulo, x, y, centrar) + 5;
    }

    int numeroOpciones = dibujos.size();

    int margenIzquierda = 10;
    int espacioDisponible = obtenerAnchoConsola() - margenIzquierda;
    int espacioEntreDibujos = espacioDisponible / numeroOpciones;

    int espacioRestante = espacioDisponible - (espacioEntreDibujos * numeroOpciones);
    int xOffset = margenIzquierda;

    for (int i = 0; i < numeroOpciones; ++i) {
        x = xOffset + i * espacioEntreDibujos;
        imprimirOpcionDibujo(dibujos[i], x, y, i == indiceSeleccionado);
    }

    moverCursor(margenIzquierda, y + 13);
    cout << "Presione ESC o 0 para cancelar" << endl;
}

// Función principal mejorada
int seleccionarConDibujos(vector<string> dibujos, string titulo, string subtitulo = "", bool centrar = true) {
    char tecla;
    int opcionSeleccionada = 0;
    int numeroOpciones = dibujos.size();

    cout << textoRGB(255,255,255);
    ocultarCursor();

    while (true) {
        // Mostrar las opciones inicialmente
        imprimirOpcionesDibujos(titulo, subtitulo, dibujos, centrar, opcionSeleccionada);

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
        } 

        // Manejo de la tecla Enter
        if (tecla == ENTER) {
            mostrarCursor();
            return opcionSeleccionada + 1;  // Devuelve la opción seleccionada
        }
    }
}

// --------------------------------------------------- SELECCIONAR CON FLECHAS -------------------------------------

// Funcion que imprime un dibujo y su opcion
void imprimirOpcionFlecha(string opcion, int x, int y, bool seleccionado) {// Cambiar el color si es la opción seleccionada
    moverCursor(x, y);
    
    if (seleccionado) {
        cout << textoRGB(255,255,0) << opcion << textoRGB(255,255,255);
    }else{
        cout << opcion;
    }

}

void imprimirOpcionesFlechas(string titulo, string subtitulo, vector<string> opciones, bool centrar, int indiceSeleccionado) {
    system("cls"); 

    int y = 3, x = 0;
    
    if ( subtitulo != "" ){
        y += imprimirTexto(titulo, x, y, centrar) + 3;
        y += imprimirTexto(subtitulo, x, y, centrar, true) + 3;
    }else{
        y += imprimirTexto(titulo, x, y, centrar) + 5;
    }

    int numeroOpciones = opciones.size();

    int margenIzquierda = 10;
    int espacioDisponible = obtenerAnchoConsola() - margenIzquierda;
    int espacioEntreDibujos = espacioDisponible / numeroOpciones;

    int espacioRestante = espacioDisponible - (espacioEntreDibujos * numeroOpciones);
    x = margenIzquierda;

    for (int i = 0; i < numeroOpciones; ++i) {
        imprimirOpcionFlecha(opciones[i], x, y + i, i == indiceSeleccionado);
    }

    moverCursor(x, y + numeroOpciones + 5);
    cout << "Presione ESC o 0 para cancelar" << endl;
}

// Función para la selección con flechas
string seleccionConFlechas(vector<string> opciones, string titulo, string subtitulo = "", bool centrar = true) {
    char tecla;
    int index = 0;
    int numeroOpciones = opciones.size(); // Obtiene el tamaño del vector

    cout << textoRGB(255,255,255);
    ocultarCursor();

    while (true) {

        // Mostrar las opciones inicialmente
        imprimirOpcionesFlechas(titulo, subtitulo, opciones, centrar, index);

        tecla = _getch(); 

        // Manejo de la tecla especial (ESC o '0' para regresar)
        if (tecla == ESC || tecla == ZERO) {
            mostrarCursor();
            return "";  // Regresar si se presiona ESC o '0'
        }

        // Manejo de las teclas de flecha
        if (tecla == TECLA_ESPECIAL) {
            tecla = _getch(); 

            switch (tecla) {
                case UP: 
                    index = (index - 1 + numeroOpciones) % numeroOpciones;
                    break;
                case DOWN: 
                    index = (index + 1) % numeroOpciones;
                    break;
            }
        }
        
        // Manejo de la tecla Enter
        if (tecla == ENTER) {
            mostrarCursor();
            return opciones[index];  // Devuelve la opción seleccionada
        }
    }
}

#endif // UTILIDADES.HPP