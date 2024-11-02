#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>
#include <algorithm>  // Para std::count

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

// Función para calcular el número de líneas en un dibujo
int contarLineas(string dibujo) {
    return count(dibujo.begin(), dibujo.end(), '\n') + 1;
}

void imprimirDibujoConOpcion(string& dibujo, const string& opcion, int x, int y, int alturaMax, bool seleccionado) {
    size_t pos = 0;
    string tempDibujo = dibujo;
    int lineaActual = y;

    // Cambiar el color si es la opción actual
    if (seleccionado) {
        cout << textoRGB(255,255,0);
    }

    // Dividir el dibujo en líneas y imprimirlas
    while ((pos = tempDibujo.find('\n')) != string::npos) {
        moverCursor(x, lineaActual); // Mover el cursor a la posición x
        cout << tempDibujo.substr(0, pos); // Imprimir la línea
        tempDibujo.erase(0, pos + 1);
        lineaActual++;
    }
    moverCursor(x, lineaActual); // Mover el cursor a la siguiente línea
    cout << tempDibujo; // Imprimir la última línea del dibujo

    // Imprimir la opción en la misma posición x que el dibujo
    moverCursor(x, lineaActual + 1); // Mover el cursor a la posición especificada
    cout << opcion;

    // Restablecer el color si es la opción seleccionada
    if (seleccionado) {
        cout << resetearColor();
    }
}

// Función para mostrar todas las opciones y dibujos de forma uniforme
void mostrarOpciones(string titulo, string subtitulo, vector<string> opciones, vector<string> dibujos, int indiceSeleccionado) {
    system("cls");

    int anchoConsola = obtenerAnchoConsola();
    int y = 3; // Línea inicial para el título
    int tituloY = imprimirTitulo(titulo, anchoConsola / 2 - titulo.size() / 2, y); // Centramos el título en la consola
    
    
    moverCursor(anchoConsola/2 - 42/2, tituloY + 1); cout << "------------------------------------------";
    moverCursor(anchoConsola/2 - subtitulo.size()/2, tituloY + 2); cout << subtitulo;
    moverCursor(anchoConsola/2 - 42/2, tituloY + 3); cout << "------------------------------------------";

    y = tituloY + 7; // Dejar espacio entre el título y las opciones

    // Calcular la altura máxima de los dibujos
    int alturaMax = 0;
    for (const auto& dibujo : dibujos) {
        alturaMax = max(alturaMax, contarLineas(dibujo));
    }

    // Imprimir dibujos y opciones distribuidos uniformemente
    int numeroOpciones = opciones.size();
    int espacioEntreDibujos = (anchoConsola - numeroOpciones * 30) / (numeroOpciones + 1);
    int x = 5 + espacioEntreDibujos;

    for (int i = 0; i < numeroOpciones; ++i) {
        // Llamar a la función para imprimir cada dibujo y opción
        imprimirDibujoConOpcion(dibujos[i], opciones[i], x, y, alturaMax, i == indiceSeleccionado);
        x += 30 + espacioEntreDibujos; // Avanzar según el ancho del dibujo más el espacio
    }

    imprimirCancelar(anchoConsola / 2 - 42 / 2, y + alturaMax + 4);
}

// Función de seleccion
int seleccionarConDibujos(string titulo, string subtitulo, vector<string> opciones, vector<string> dibujos) {
    char tecla;
    int index = 0; 
    int numeroOpciones = opciones.size();

    // Verificar que el número de opciones coincide con el número de dibujos
    if (numeroOpciones != dibujos.size()) {
        cerr << "Error: El número de opciones no coincide con el número de dibujos." << endl;
        return 0; // Retorna 0 si hay un error de coincidencia
    }

    ocultarCursor();

    do {

        mostrarOpciones(titulo, subtitulo, opciones, dibujos, index); 
        
        tecla = _getch(); 

        if (tecla == TECLA_ESPECIAL) {
            tecla = _getch(); 

            if(tecla == LEFT){
                index = (index - 1 + numeroOpciones) % numeroOpciones;
            } else if(tecla == RIGHT){
                index = (index + 1) % numeroOpciones;
            }

        } else if (tecla == ENTER) {
            mostrarCursor();
            return index + 1; // Devuelve la opción seleccionada (1 a n)
        }

    } while(tecla != ESC && tecla != ZERO);

    mostrarCursor();
    return 0; // Retorna 0 si se cancela la selección
}

#endif // UTILIDADES_H