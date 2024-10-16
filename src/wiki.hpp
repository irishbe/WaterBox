#ifndef WIKI_H
#define WIKI_H

#include <iostream>
#include "utilidades.h"
#include "crudDatos.hpp"

using namespace std;

//FUNCION GOTOXY
void gotoxy(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void wiki_buscar();
void wiki_seleccionarBioma();
void wiki_lista();
void wiki_especies(string nombreEspecie);

//ARRECIFES_DE_CORAL
void tiburon_arrecife();
void pez_payaso();
void langosta_comun();
void pez_mariposa();
void camaron_limpiador();
void algas_coralinas();
//OCEANO_PROFUNDO
void pez_linterna();
void pez_vibora();
void medusa_peine();

void iniciarWiki(){
    string opcion;
    vector<string> opciones = {"Por nombre", "Por bioma", "Por listado", "SALIR"};

    do{
        opcion = seleccionConFlechas("Seleccione un tipo de busqueda", opciones, "vertical");

        system("cls");

        if( opcion == "Por nombre" ){
            wiki_buscar();

        }else if( opcion == "Por bioma" ){
            wiki_seleccionarBioma();
            
        }else if( opcion == "Por listado" ){
            wiki_lista();

        }else if( opcion == "SALIR" || opcion == ""){
            cout << "Saliendo... " << endl;

        }else{
            cout << "Opcion invalida... " << endl;
        }

        getch();

    }while( opcion != "SALIR" && opcion != "" );
}

//TITULO WIKIWATER
void titulo_wikiwater(){
    gotoxy(23,2);                                                                    
    cout<<",--.   ,--.,--.,--. ,--.,--.,--.   ,--.  ,---. ,--------.,------.,------."<<endl;
    gotoxy(23,3);
    cout<<"|  |   |  ||  ||  .'   /|  ||  |   |  | /  O  \\'--.  .--'|  .---'|  .--. '"<<endl; 
    gotoxy(23,4);   
    cout<<"|  |.'.|  ||  ||  .   ' |  ||  |.'.|  ||  .-.  |  |  |   |  --, |  '--'.'"<<endl; 
    gotoxy(23,5);   
    cout<<"|   ,'.   ||  ||  |\\   \\|  ||   ,'.   ||  | |  |  |  |   |  ---.|  |\\  \\"<<endl;  
    gotoxy(23,6);   
    cout<<"'--'   '--'--'--' '--'--''--'   '--'--' --'  --'   ------'--' '--'"<<endl; 
}

//MENÚ BUSCAR ESPECIE
void wiki_buscar(){
    string tipoEspecie, nombreEspecie;
    
    tipoEspecie = seleccionConFlechas("Seleccione el tipo de especie\n", tiposEspecies, "horizontal");
    if( tipoEspecie == "" ) return;


    cout<<"\n\tIngresa el nombre de la especie: "; getline(cin,nombreEspecie);
    DatosEspecie *datosEspecie = extraerDatosEspecie( tipoEspecie, nombreEspecie);

    if ( datosEspecie == nullptr ) {
        cout << "\nNombre incorrecto" << endl << endl;
        _getch();
        return;
    }

    wiki_especies(nombreEspecie);
}

void wiki_especies(string nombreEspecie){
    if(nombreEspecie=="Tiburon de arrecife"){
        tiburon_arrecife();
    }
    else if(nombreEspecie=="Pez payaso"){
        pez_payaso();
    }
    else if(nombreEspecie=="Langosta comun"){
        langosta_comun();
    }
    else if(nombreEspecie=="Pez mariposa"){
        pez_mariposa();
    }
    else if(nombreEspecie=="Camaron Limpiador"){
        camaron_limpiador();
    }
    else if(nombreEspecie=="Algas coralinas"){
        algas_coralinas();
    }
    else if(nombreEspecie=="Pez Linterna"){
        pez_linterna();
    }
    else if(nombreEspecie=="Pez Vibora"){
        pez_vibora();
    }
    else if(nombreEspecie=="Medusa Peine"){
        medusa_peine();
    }
}

void wiki_seleccionarBioma(){
    string bioma, especieSeleccionada;

    vector<string> biomas = {"Arrecifes de coral", "Oceano profundo"}; // Agregar "Oceano profundo"
    vector<string> especiesArrecifeCoral = {"Tiburon de arrecife", "Pez payaso", "Langosta comun", "Pez mariposa", "Camaron Limpiador", "Algas coralinas"}; 
    vector<string> especiesOceanoProfundo = {"Pez Linterna", "Pez Vibora", "Medusa Peine"};

    bioma = seleccionConFlechas("Seleccione el bioma", biomas, "vertical");

    if ( bioma == "Arrecifes de coral" ) {
        especieSeleccionada = seleccionConFlechas("Seleccione la especie", especiesArrecifeCoral, "vertical");
        
    } else if ( bioma == "Oceano profundo" ) {
        especieSeleccionada = seleccionConFlechas("Seleccione la especie", especiesOceanoProfundo, "vertical");

    }else{
        return;
    }

    wiki_especies(especieSeleccionada);
}

//LISTA DE TODAS LAS ESPECIES
void wiki_lista(){
    cout << "FALTA HACER";
}

//ARRECIFE DE CORAL - ESPECIES
void tiburon_arrecife(){
    system("CLS");
    titulo_wikiwater();
    gotoxy(19,11);
    cout<<" ---------------------------";
    gotoxy(19,21);
    cout<<" ---------------------------";
    for(int y=11;y<=21;y++){
        gotoxy(19,y);
        cout<<"|"<<endl;
        gotoxy(47,y);
        cout<<"|"<<endl;
    }
    gotoxy(24,15);
    cout<<"  \\_____)\\_____      ";
    gotoxy(24,16);
    cout<<"  /--_____||__`_>    ";
    gotoxy(24,17);
    cout<<"          )/         ";
    gotoxy(24,18);
    cout<<"          '          "; 

    gotoxy(58,12);
    cout<<"Tiburon de Arrecife (Carcharhinus perezii)";
    gotoxy(62,14);
    cout<<"Familia biologica: Carcharhinidae";
    gotoxy(64,15);
    cout<<"Esperanza de vida: 100 anhos";
    gotoxy(64,16);
    cout<<"Inactividad reproductiva: 2";
    gotoxy(67,18);
    cout<<"Temperatura: 20 C - 28 C";
    gotoxy(69,19);
    cout<<"Salinidad: 24-27 ppt";
    gotoxy(73,20);
    cout<<"Oxigeno: 4-6";
}

void pez_payaso(){
    system("CLS");
    titulo_wikiwater();
    gotoxy(19,11);
    cout<<" ---------------------------";
    gotoxy(19,21);
    cout<<" ---------------------------";
    for(int y=11;y<=21;y++){
        gotoxy(19,y);
        cout<<"|"<<endl;
        gotoxy(47,y);
        cout<<"|"<<endl;
    }
    gotoxy(28,15);
    cout<<"    m  m"<<endl;
    gotoxy(28,16);
    cout<<"  ><(((('>"<<endl;

    gotoxy(64,12);
    cout<<"Pez Payaso (Amphiprioninae)";
    gotoxy(62,14);
    cout<<"Familia biologica: Pomacentridae";
    gotoxy(64,15);
    cout<<"Esperanza de vida: 6 anhos";
    gotoxy(64,16);
    cout<<"Inactividad reproductiva: 12";
    gotoxy(66,18);
    cout<<"Temperatura: 24 C - 28 C";
    gotoxy(68,19);
    cout<<"Salinidad: 30-34 ppt";
    gotoxy(73,20);
    cout<<"Oxigeno: 5";
}

void langosta_comun(){
    system("CLS");
    titulo_wikiwater();
    gotoxy(19,11);
    cout<<" ---------------------------";
    gotoxy(19,21);
    cout<<" ---------------------------";
    for(int y=11;y<=21;y++){
        gotoxy(19,y);
        cout<<"|"<<endl;
        gotoxy(47,y);
        cout<<"|"<<endl;
    }
    gotoxy(26,14);
    cout<<"          __         "<<endl;
    gotoxy(26,15);
    cout<<"   v  |  |           "<<endl;
    gotoxy(26,16);
    cout<<"   <((((())---       "<<endl;
    gotoxy(26,17);
    cout<<"   v  |  |__         "<<endl;

    gotoxy(61,12);
    cout<<"Langosta comun (Panulirus argus)";
    gotoxy(62,14);
    cout<<"Familia biologica: Palinuridae";
    gotoxy(64,15);
    cout<<"Esperanza de vida: 10 anhos";
    gotoxy(64,16);
    cout<<"Inactividad reproductiva: 1";
    gotoxy(66,18);
    cout<<"Temperatura: 20 C - 30 C";
    gotoxy(68,19);
    cout<<"Salinidad: 33-35 ppt";
    gotoxy(73,20);
    cout<<"Oxigeno: 4";
}

void pez_mariposa(){
    system("CLS");
    titulo_wikiwater();
    gotoxy(19,11);
    cout<<" ---------------------------";
    gotoxy(19,21);
    cout<<" ---------------------------";
    for(int y=11;y<=21;y++){
        gotoxy(19,y);
        cout<<"|"<<endl;
        gotoxy(47,y);
        cout<<"|"<<endl;
    }
    gotoxy(27,14);
    cout<<"    _____     "<<endl;
    gotoxy(27,15);
    cout<<"   (| | |)    "<<endl;
    gotoxy(27,16);
    cout<<"   (____o_>   "<<endl;
    gotoxy(27,17);
    cout<<"       v      "<<endl;

    gotoxy(64,12);
    cout<<"Pez mariposa (Chaetodontidae)";
    gotoxy(62,14);
    cout<<"Familia biologica: Chaetodontidae";
    gotoxy(64,15);
    cout<<"Esperanza de vida: 7.5 anhos";
    gotoxy(64,16);
    cout<<"Inactividad reproductiva: 1";
    gotoxy(66,18);
    cout<<"Temperatura: 22 C - 28 C";
    gotoxy(68,19);
    cout<<"Salinidad: 30-35 ppt";
    gotoxy(73,20);
    cout<<"Oxigeno: 4";
}

void camaron_limpiador(){
    system("CLS");
    titulo_wikiwater();
    gotoxy(19,11);
    cout<<" ---------------------------";
    gotoxy(19,21);
    cout<<" ---------------------------";
    for(int y=11;y<=21;y++){
        gotoxy(19,y);
        cout<<"|"<<endl;
        gotoxy(47,y);
        cout<<"|"<<endl;
    }
    gotoxy(27,14);
    cout<<"   |    |__ "<<endl;
    gotoxy(27,15);
    cout<<"  >((((:<__ "<<endl;
    gotoxy(27,16);
    cout<<"   |    |   "<<endl;
    gotoxy(27,17);

    gotoxy(59,12);
    cout<<"Camaron Limpiador (Lysmata amboinensis)";
    gotoxy(62,14);
    cout<<"Familia biologica: Hippolytidae";
    gotoxy(64,15);
    cout<<"Esperanza de vida: 2.5 anhos";
    gotoxy(64,16);
    cout<<"Inactividad reproductiva: 1.5";
    gotoxy(66,18);
    cout<<"Temperatura: 24 C - 28 C";
    gotoxy(68,19);
    cout<<"Salinidad: 30-35 ppt";
    gotoxy(73,20);
    cout<<"Oxigeno: 4";
}

void algas_coralinas(){
    system("CLS");
    titulo_wikiwater();
    gotoxy(19,11);
    cout<<" ---------------------------";
    gotoxy(19,21);
    cout<<" ---------------------------";
    for(int y=11;y<=21;y++){
        gotoxy(19,y);
        cout<<"|"<<endl;
        gotoxy(47,y);
        cout<<"|"<<endl;
    }
    gotoxy(26,14);
    cout<<"   vv vv vv   "<<endl;
    gotoxy(26,15);
    cout<<"  < <<  >>  >>"<<endl;
    gotoxy(26,16);
    cout<<"   vv vv  vv  "<<endl;
    gotoxy(26,17);

    gotoxy(58,12);
    cout<<"Algas coralinas (Familia Corallinaceae)";
    gotoxy(62,14);
    cout<<"Familia biologica: Corallinaceae";
    gotoxy(64,15);
    cout<<"Esperanza de vida: 100 anhos";
    gotoxy(64,16);
    cout<<"Inactividad reproductiva: 0";
    gotoxy(66,18);
    cout<<"Temperatura: 22 C - 28 C";
    gotoxy(68,19);
    cout<<"Salinidad: 30-35 ppt";
    gotoxy(73,20);
    cout<<"Oxigeno: 4";
}

void pez_linterna(){
    system("CLS");
    titulo_wikiwater();
    gotoxy(19,11);
    cout<<" ---------------------------";
    gotoxy(19,21);
    cout<<" ---------------------------";
    for(int y=11;y<=21;y++){
        gotoxy(19,y);
        cout<<"|"<<endl;
        gotoxy(47,y);
        cout<<"|"<<endl;
    }

    gotoxy(27,14);
    cout<<"        ___o     "<<endl;
    gotoxy(27,15);
    cout<<"    ___|__     "<<endl;
    gotoxy(27,16);
    cout<<"   (    o |    "<<endl;
    gotoxy(27,17);
    cout<<"   (_<___(   "<<endl;
    gotoxy(27,18);
    cout<<"       v      "<<endl;

    gotoxy(59,12);
    cout<<"Pez Linterna (Lampanyctodes hectoris)";
    gotoxy(62,14);
    cout<<"Familia biologica: Myctophidae";
    gotoxy(64,15);
    cout<<"Esperanza de vida: 3-4 anhos";
    gotoxy(64,16);
    cout<<"Inactividad reproductiva: 1";
    gotoxy(67,18);
    cout<<"Temperatura: 2 C - 8 C";
    gotoxy(68,19);
    cout<<"Salinidad: 34-36 ppt";
    gotoxy(72,20);
    cout<<"Oxigeno: 3-5";
}

void pez_vibora(){
    system("CLS");
    titulo_wikiwater();
    gotoxy(19,11);
    cout<<" ---------------------------";
    gotoxy(19,21);
    cout<<" ---------------------------";
    for(int y=11;y<=21;y++){
        gotoxy(19,y);
        cout<<"|"<<endl;
        gotoxy(47,y);
        cout<<"|"<<endl;
    }
    gotoxy(25,14);
    cout<<"         /"<<endl;
    gotoxy(24,15);
    cout<<"         /"<<endl;
    gotoxy(24,16);
    cout<<"  ><((((((((((')"<<endl;
    gotoxy(24,17);
    cout<<"          w"<<endl;

    gotoxy(64,12);
    cout<<"Pez Vibora (Chauliodus sloani)";
    gotoxy(65,14);
    cout<<"Familia biologica: Stomiidae";
    gotoxy(64,15);
    cout<<"Esperanza de vida: 15-20 anhos";
    gotoxy(66,16);
    cout<<"Inactividad reproductiva: 2";
    gotoxy(67,18);
    cout<<"Temperatura: 4 C - 5 C";
    gotoxy(69,19);
    cout<<"Salinidad: 35-37 ppt";
    gotoxy(73,20);
    cout<<"Oxigeno: 2-4";
}

void medusa_peine(){
    system("CLS");
    titulo_wikiwater();
    gotoxy(19,11);
    cout<<" ---------------------------";
    gotoxy(19,21);
    cout<<" ---------------------------";
    for(int y=11;y<=21;y++){
        gotoxy(19,y);
        cout<<"|"<<endl;
        gotoxy(47,y);
        cout<<"|"<<endl;
    }
    gotoxy(24,14);
    cout<<"    __________"<<endl;
    gotoxy(24,15);
    cout<<"   ( ---|--|- )"<<endl;
    gotoxy(24,16);
    cout<<"    (  --|--|  )"<<endl;
    gotoxy(24,17);
    cout<<"   (__________)  "<<endl;

    gotoxy(64,12);
    cout<<"Medusa Peine (Ctenophora spp.)";
    gotoxy(65,14);
    cout<<"Familia biologica: Ctenophora";
    gotoxy(67,15);
    cout<<"Esperanza de vida: 3 meses";
    gotoxy(66,16);
    cout<<"Inactividad reproductiva: 0";
    gotoxy(67,18);
    cout<<"Temperatura: 2 C - 30 C";
    gotoxy(69,19);
    cout<<"Salinidad: 32-35 ppt";
    gotoxy(73,20);
    cout<<"Oxigeno: 3-5";
}

#endif // WIKI_H