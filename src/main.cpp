#include <iostream>
#include <windows.h>
#include "recursosASCII.h"

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);

    cout << obtenerArteASCII();
    //vector<string> opcionesMenu = {"INICIAR", "WIKIWATER", "CODIGOS", "SALIR"};
    
    string opcion = seleccionConFlechas( tituloWaterBox(), opcionesMenu, "vertical", 10, 5);

    return 0;
}