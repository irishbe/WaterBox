#include "simulador.hpp"
#include "wiki.hpp"
#include "utilidades.hpp"

using namespace std;

void ingresarCodigos();

int main() {
    SetConsoleOutputCP(CP_UTF8);
    pantallaCompleta();

    fondoRGB(7, 25, 82);
    
    int opcion = -1;

    string advertencia = textoRGB(242, 47, 6) + "EJECUTAR COMO ADMINISTRADOR PARA VISUALIZAR LOS COLORES DE FONDO Y LOS TITULOS ASCII\n" + textoRGB(255, 255, 255)+"\n\n"; 
    
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
    int x = 10, y = 3;
    string codigo;
    
    y += imprimirTexto( tituloCodigos(), x, y, true);

    fflush(stdin);
    moverCursor(x, y + 3); cout << "INGRESE UN CODIGO DE 5 CARACTERES...";
    moverCursor(x, y + 4); getline(cin, codigo);

    if( codigo == "ADMIN" ){
        moverCursor(x, y + 8); cout << "CODIGO ACEPTADO! ";
        getch();
        
        iniciarCrudJson();

    }else{
        moverCursor(x, y + 8); cout << "ERROR... ";
        getch();
    }

}