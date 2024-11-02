#include "utilidades.h"
#include "dibujosASCIII.hpp"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    pantallaCompleta();

    vector<string> opciones = {"POR NOMBRE", "POR BIOMA", "POR LISTADO"};
    vector<string> dibujos = {dibujoArrecife(), dibujoSalinidad(), dibujoLista()};

    fondoRGB(0, 74, 173);

    int seleccion = seleccionarConDibujos(tituloWaterBox(), "SELECCIONE UN TIPO DE BUSQUEDA", opciones, dibujos);

    return 0;
}