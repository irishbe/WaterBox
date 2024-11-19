#include "simulador.hpp"
#include "wiki.hpp"

using namespace std;

void ingresarCodigos();

int main() {
    SetConsoleOutputCP(CP_UTF8);
    pantallaCompleta();

    fondoRGB(7, 25, 82);
    
    int opcion = -1;
    string advertencia = "EJECUTAR COMO ADMINISTRADOR EN CASO SE DEFORMEN LOS TEXTOS ASCII\n"; 
    vector<string> dibujos = {
        ASCIISimulador(),
        ASCIIWikiWater(),
        ASCIICodigos()
    };
    
    advertencia.append( tituloWaterBox() );

    do{
        opcion = seleccionarConDibujos(dibujos, advertencia);

        switch(opcion){
            case 1: iniciarSimulador(); break;
            case 2: iniciarWiki(); break;
            case 3: ingresarCodigos(); break;
            case -1: break;
        }

        system("cls");

    }while( opcion != -1);

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