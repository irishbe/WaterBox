#ifndef SELECCION_OPCIONES_H
#define SELECCION_OPCIONES_H

#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>

using namespace std;

// Constantes
const char ENTER = 13, ESC = 27, TECLA_ESPECIAL = 224;
const int LEFT = 75, RIGHT = 77, ZERO = '0';
const int COLOR_YELLOW = 14; //color amarillo

// Prototipos de funciones
void gotoxy(int x, int y);
void imprimirDibujoConOpcion(const string& dibujo, const string& opcion, int x, int y, bool seleccionado);
void mostrarOpciones(const vector<string>& opciones, const vector<string>& dibujos, int indiceSeleccionado);
int mostrarMenu(const vector<string>& opciones, const vector<string>& dibujos);



void gotoxy(int x, int y) {
    COORD coord;  
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
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
        gotoxy(x, lineaActual);
        cout << tempDibujo.substr(0, pos); // Imprime la linea del dibujo
        tempDibujo.erase(0, pos + 1); // Elimina la linea impresa
        lineaActual++; // Aumenta la linea actual
    }

    // Imprimir la opcion debajo del dibujo
    gotoxy(x, lineaActual + 1);
    cout << opcion << endl; 

    // Luego restablecer el color
    if (seleccionado) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); 
    }
}

// Funcion que imprime todas las opciones y dibujos
void mostrarOpciones(string titu, const vector<string>& opciones, const vector<string>& dibujos, int indiceSeleccionado) {
    system("cls"); 

    gotoxy(30, 3); cout<<titu<<endl;

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

#endif 
