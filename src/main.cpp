#include <iostream>
#include "simulador.hpp"
#include "wiki.hpp"

using namespace std;

void ingresarCodigos();

int main() {
    SetConsoleOutputCP(CP_UTF8);
    pantallaCompleta();

    string opcionMenu, advertencia = "EJECUTAR COMO ADMINISTRADOR EN CASO SE DEFORMEN LOS TEXTOS ASCII\n"; 
    vector<string> opcionesMenu = {"INICIAR", "WIKIWATER", "CODIGOS", "SALIR"};
    
    advertencia.append( tituloWaterBox() );

    do{
        opcionMenu = seleccionConFlechas( advertencia, opcionesMenu, "vertical", true, 30, 5);

        system("cls");

        if( opcionMenu == "INICIAR" ){
            iniciarSimulador();
        }
        else if( opcionMenu == "WIKIWATER" ){
            iniciarWiki();
        }
        else if( opcionMenu == "CODIGOS"){
            ingresarCodigos();
        }
        else if( opcionMenu == "SALIR" || opcionMenu == ""){
            cout<<"\nSaliendo...";
            getch();
        }
        else{
            cout << "Opcion invalida" << endl;
            getch();
        }

        system("cls");

    }while( opcionMenu != "SALIR" && opcionMenu != "");

    return 0;
}

void ingresarCodigos(){
    string codigo;
    
    cout << "INGRESE UN CODIGO DE 5 CARACTERES..." << endl;
    getline(cin, codigo);

    if( codigo == "ADMIN" ){
        cout << "\n\nCODIGO ACEPTADO!" << endl << endl;
        getch();
        iniciarCrudJson();

    }else{
        cout << "\n\nERROR..." << endl << endl;
        getch();
    }
}