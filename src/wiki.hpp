#ifndef WIKI_HPP
#define WIKI_HPP

#include "crudDatos.hpp"
#include "Poblacion.hpp"
#include "busquedaBinaria.hpp"

using namespace std;

void wiki_buscar();
void wiki_seleccionarBioma();
void wiki_lista();

// Función para iniciar el menú de la Wiki
void iniciarWiki() {
    int opcion = -1;
    vector<string> dibujos{
        ASCIIBuscarPorNombre(),
        ASCIIBuscarPorBioma(),
        ASCIIBuscarPorFamilia(),
    };

    do{
        opcion = seleccionarConDibujos(dibujos, tituloWikiWater(), "SELECCIONE UNA TIPO DE BUSQUEDA");

        switch (opcion) {
            case 1: // Por nombre
                wiki_buscar();
                break;
            case 2: // Por bioma
                wiki_seleccionarBioma();
                break;
            case 3: // Por listado
                wiki_lista();
                break;
            case -1: // Salir
                cout << "Saliendo... " << endl;
                break;
        }

    } while(opcion != -1);

    getch();
}

void wiki_especies(string nombreEspecie, string tipoEspecie = ""){
    DatosEspecie* datosEspecie = nullptr;

    if( tipoEspecie != "" ){
        datosEspecie = extraerDatosEspecie(tipoEspecie, nombreEspecie);

        if (datosEspecie == nullptr) {
            cout << "\nEspecie no encontrada..." << endl << endl;
            _getch();
            return;
        }

    } else{
        datosEspecie = extraerDatosEspecie("Animal", nombreEspecie);

        if( datosEspecie == nullptr ){
            datosEspecie = extraerDatosEspecie("Vegetal", nombreEspecie);
        }
    }

    if ( datosEspecie == nullptr ) {
        cout << "\nNombre incorrecto" << endl << endl;
        _getch();
        return;
    }

    fondoRGB(2,10,70);

    int y = imprimirTexto(tituloWikiWater(), 0, 3, true) + 7;

    imprimirPoblacion( obtenerSprite(nombreEspecie), "GRANDE", 19, y + 1);

    moverCursor(100, y + 2); cout << datosEspecie->nombreComun << " ("<< datosEspecie->nombreCientifico << ")" << endl;
    moverCursor(100, y + 3); cout << "Familia biológica: " << datosEspecie->familiaBiologica << endl;
    moverCursor(100, y + 4); cout << "Esperanza de vida: " << datosEspecie->esperanzaVida << endl;
    moverCursor(100, y + 5); cout << "Inactividad reproductiva: " << datosEspecie->inactividadReproductiva << endl;
    moverCursor(100, y + 6); cout << "Temperatura: " << datosEspecie->temperaturaMin <<" C° - " << datosEspecie->temperaturaMax <<" C°" << endl;
    moverCursor(100, y + 7); cout << "Salinidad: " << datosEspecie->salinidadMin <<" ups - " << datosEspecie->salinidadMax <<" ups" << endl;
    moverCursor(100, y + 8); cout << "Temperatura: " << datosEspecie->oxigenoMin <<" mg/L - " << datosEspecie->oxigenoMax <<" mg/L" << endl;

    getch();
    fondoRGB(7, 25, 82);
}

// MENÚ BUSCAR ESPECIE
void wiki_buscar(){
    vector<string> nombresEspecies;
    string nombreEspecie;

    nombresEspecies = extraerNombres("Especies");

    nombreEspecie = busquedaBinaria(nombresEspecies);

    if(nombreEspecie == "") return;

    cout << "PRUEBA4";
    wiki_especies(nombreEspecie);
}

void wiki_seleccionarBioma(){
    string bioma, especieSeleccionada;

    vector<string> biomas = extraerNombres("Bioma");
    bioma = seleccionarConFlechas(biomas, tituloWikiWater(), "SELECCIONE UN BIOMA");

    especieSeleccionada = seleccionarConFlechas( extraerNombres("", bioma), tituloWikiWater(), "ESPECIES EN ARRECIFES DE " + bioma);

    wiki_especies(especieSeleccionada);
}

// LISTA DE TODAS LAS ESPECIES
void wiki_lista() {
    cout << "FALTA HACER";
}

#endif