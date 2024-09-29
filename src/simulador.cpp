#include <iostream>
#include <windows.h>
#include "recursosASCII.h"

using namespace std;

int main() {
    pantallaCompleta();
    SetConsoleOutputCP(CP_UTF8);

    imprimirBarra("Oxígeno", 30); cout << "\t";
    imprimirBarra("Salinidad", 30); cout << "\t";
    imprimirBarra("Temperatura", 70); cout << "\t";
    imprimirBarra("Contaminación", 30);

    imprimirCuadro2("Animaaal", 5, 21, 15, 5);
    imprimirCuadro2("Animaaal", 5, 21, 38, 5);
    imprimirCuadro2("Animaaal", 5, 21, 61, 5);
    imprimirCuadro2("Animaaal", 5, 21, 84, 5);
    imprimirCuadro2("Animaaal", 5, 21, 107, 5);
    imprimirCuadro2("Animaaal", 5, 21, 130, 5);
    imprimirCuadro2("Animaaal", 5, 21, 153, 5);

    /*cout << endl;
    imprimirCuadro("NOMBREEEEEEEEEEEEEEEEEEEEEEEEEE", 5, 21);
    cout << " ";
    imprimirCuadro("NOMBREEEEEEEEEEEEEEEEEEEEEEEEEE", 5, 21);
    cout << " ";
    imprimirCuadro("NOMBREEEEEEEEEEEEEEEEEEEEEEEEEE", 5, 21);
    cout << " ";
    imprimirCuadro("NOMBREEEEEEEEEEEEEEEEEEEEEEEEEE", 5, 21);
    cout << " ";
    imprimirCuadro("NOMBREEEEEEEEEEEEEEEEEEEEEEEEEE", 5, 21);
    
    cout << endl;
    imprimirCuadro("NOMBRE", 7, 21);
    cout << " ";
    imprimirCuadro("NOMBRE", 7, 21);
    cout << " ";
    imprimirCuadro("NOMBRE", 7, 21);
    cout << " ";
    imprimirCuadro("NOMBRE", 7, 21);
    cout << " ";
    imprimirCuadro("NOMBRE", 7, 21);
    cout << " ";
    imprimirCuadro("NOMBRE", 7, 21);
    
    cout << endl;
    imprimirCuadro("NOMBRE", 9, 33);
    cout << " ";
    imprimirCuadro("NOMBRE", 9, 33);
    cout << " ";
    imprimirCuadro("NOMBRE", 9, 33);
    cout << " ";
    imprimirCuadro("NOMBRE", 9, 33);*/


    return 0;
}