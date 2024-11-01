#ifndef WIKI_H
#define WIKI_H

#include <iostream>
#include "utilidades.h"
#include "crudDatos.hpp"

using namespace std;

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
    moverCursor(23,2);                                                                    
    cout<<",--.   ,--.,--.,--. ,--.,--.,--.   ,--.  ,---. ,--------.,------.,------."<<endl;
    moverCursor(23,3);
    cout<<"|  |   |  ||  ||  .\'   /|  ||  |   |  | /  O  \\\'--.  .--\'|  .---\'|  .--. '"<<endl; 
    moverCursor(23,4);   
    cout<<"|  |.\'.|  ||  ||  .   \' |  ||  |.\'.|  ||  .-.  |  |  |   |  `--, |  \'--\'.\'"<<endl; 
    moverCursor(23,5);   
    cout<<"|   ,\'.   ||  ||  |\\   \\|  ||   ,\'.   ||  | |  |  |  |   |  `---.|  |\\  \\"<<endl;  
    moverCursor(23,6);   
    cout<<"\'--\'   \'--\'`--\'`--\' \'--\'`--\'\'--\'   \'--\'`--\' `--\'  `--\'   `------\'`--\' \'--\'"<<endl;
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
    moverCursor(19,11);
    cout<<" ---------------------------";
    moverCursor(19,21);
    cout<<" ---------------------------";
    for(int y=11;y<=21;y++){
        moverCursor(19,y);
        cout<<"|"<<endl;
        moverCursor(47,y);
        cout<<"|"<<endl;
    }
    moverCursor(24,15);
    cout<<"  \\_____)\\_____      ";
    moverCursor(24,16);
    cout<<"  /--_____||__`_>    ";
    moverCursor(24,17);
    cout<<"          )/         ";
    moverCursor(24,18);
    cout<<"          '          "; 

    moverCursor(58,12);
    cout<<"Tiburon de Arrecife (Carcharhinus perezii)";
    moverCursor(62,14);
    cout<<"Familia biologica: Carcharhinidae";
    moverCursor(64,15);
    cout<<"Esperanza de vida: 100 anhos";
    moverCursor(64,16);
    cout<<"Inactividad reproductiva: 2";
    moverCursor(67,18);
    cout<<"Temperatura: 20 C - 28 C";
    moverCursor(69,19);
    cout<<"Salinidad: 24-27 ppt";
    moverCursor(73,20);
    cout<<"Oxigeno: 4-6";
}

void pez_payaso(){
    system("CLS");
    titulo_wikiwater();
    moverCursor(19,11);
    cout<<" ---------------------------";
    moverCursor(19,21);
    cout<<" ---------------------------";
    for(int y=11;y<=21;y++){
        moverCursor(19,y);
        cout<<"|"<<endl;
        moverCursor(47,y);
        cout<<"|"<<endl;
    }
    moverCursor(28,15);
    cout<<"    m  m"<<endl;
    moverCursor(28,16);
    cout<<"  ><(((('>"<<endl;

    moverCursor(64,12);
    cout<<"Pez Payaso (Amphiprioninae)";
    moverCursor(62,14);
    cout<<"Familia biologica: Pomacentridae";
    moverCursor(64,15);
    cout<<"Esperanza de vida: 6 anhos";
    moverCursor(64,16);
    cout<<"Inactividad reproductiva: 12";
    moverCursor(66,18);
    cout<<"Temperatura: 24 C - 28 C";
    moverCursor(68,19);
    cout<<"Salinidad: 30-34 ppt";
    moverCursor(73,20);
    cout<<"Oxigeno: 5";
}

void langosta_comun(){
    system("CLS");
    titulo_wikiwater();
    moverCursor(19,11);
    cout<<" ---------------------------";
    moverCursor(19,21);
    cout<<" ---------------------------";
    for(int y=11;y<=21;y++){
        moverCursor(19,y);
        cout<<"|"<<endl;
        moverCursor(47,y);
        cout<<"|"<<endl;
    }
    moverCursor(26,14);
    cout<<"          __         "<<endl;
    moverCursor(26,15);
    cout<<"   v  |  |           "<<endl;
    moverCursor(26,16);
    cout<<"   <((((())---       "<<endl;
    moverCursor(26,17);
    cout<<"   v  |  |__         "<<endl;

    moverCursor(61,12);
    cout<<"Langosta comun (Panulirus argus)";
    moverCursor(62,14);
    cout<<"Familia biologica: Palinuridae";
    moverCursor(64,15);
    cout<<"Esperanza de vida: 10 anhos";
    moverCursor(64,16);
    cout<<"Inactividad reproductiva: 1";
    moverCursor(66,18);
    cout<<"Temperatura: 20 C - 30 C";
    moverCursor(68,19);
    cout<<"Salinidad: 33-35 ppt";
    moverCursor(73,20);
    cout<<"Oxigeno: 4";
}

void pez_mariposa(){
    system("CLS");
    titulo_wikiwater();
    moverCursor(19,11);
    cout<<" ---------------------------";
    moverCursor(19,21);
    cout<<" ---------------------------";
    for(int y=11;y<=21;y++){
        moverCursor(19,y);
        cout<<"|"<<endl;
        moverCursor(47,y);
        cout<<"|"<<endl;
    }
    moverCursor(27,14);
    cout<<"    _____     "<<endl;
    moverCursor(27,15);
    cout<<"   (| | |)    "<<endl;
    moverCursor(27,16);
    cout<<"   (____o_>   "<<endl;
    moverCursor(27,17);
    cout<<"       v      "<<endl;

    moverCursor(64,12);
    cout<<"Pez mariposa (Chaetodontidae)";
    moverCursor(62,14);
    cout<<"Familia biologica: Chaetodontidae";
    moverCursor(64,15);
    cout<<"Esperanza de vida: 7.5 anhos";
    moverCursor(64,16);
    cout<<"Inactividad reproductiva: 1";
    moverCursor(66,18);
    cout<<"Temperatura: 22 C - 28 C";
    moverCursor(68,19);
    cout<<"Salinidad: 30-35 ppt";
    moverCursor(73,20);
    cout<<"Oxigeno: 4";
}

void camaron_limpiador(){
    system("CLS");
    titulo_wikiwater();
    moverCursor(19,11);
    cout<<" ---------------------------";
    moverCursor(19,21);
    cout<<" ---------------------------";
    for(int y=11;y<=21;y++){
        moverCursor(19,y);
        cout<<"|"<<endl;
        moverCursor(47,y);
        cout<<"|"<<endl;
    }
    moverCursor(27,14);
    cout<<"   |    |__ "<<endl;
    moverCursor(27,15);
    cout<<"  >((((:<__ "<<endl;
    moverCursor(27,16);
    cout<<"   |    |   "<<endl;
    moverCursor(27,17);

    moverCursor(59,12);
    cout<<"Camaron Limpiador (Lysmata amboinensis)";
    moverCursor(62,14);
    cout<<"Familia biologica: Hippolytidae";
    moverCursor(64,15);
    cout<<"Esperanza de vida: 2.5 anhos";
    moverCursor(64,16);
    cout<<"Inactividad reproductiva: 1.5";
    moverCursor(66,18);
    cout<<"Temperatura: 24 C - 28 C";
    moverCursor(68,19);
    cout<<"Salinidad: 30-35 ppt";
    moverCursor(73,20);
    cout<<"Oxigeno: 4";
}

void algas_coralinas(){
    system("CLS");
    titulo_wikiwater();
    moverCursor(19,11);
    cout<<" ---------------------------";
    moverCursor(19,21);
    cout<<" ---------------------------";
    for(int y=11;y<=21;y++){
        moverCursor(19,y);
        cout<<"|"<<endl;
        moverCursor(47,y);
        cout<<"|"<<endl;
    }
    moverCursor(26,14);
    cout<<"   vv vv vv   "<<endl;
    moverCursor(26,15);
    cout<<"  < <<  >>  >>"<<endl;
    moverCursor(26,16);
    cout<<"   vv vv  vv  "<<endl;
    moverCursor(26,17);

    moverCursor(58,12);
    cout<<"Algas coralinas (Familia Corallinaceae)";
    moverCursor(62,14);
    cout<<"Familia biologica: Corallinaceae";
    moverCursor(64,15);
    cout<<"Esperanza de vida: 100 anhos";
    moverCursor(64,16);
    cout<<"Inactividad reproductiva: 0";
    moverCursor(66,18);
    cout<<"Temperatura: 22 C - 28 C";
    moverCursor(68,19);
    cout<<"Salinidad: 30-35 ppt";
    moverCursor(73,20);
    cout<<"Oxigeno: 4";
}

void pez_linterna(){
    system("CLS");
    titulo_wikiwater();
    moverCursor(19,11);
    cout<<" ---------------------------";
    moverCursor(19,21);
    cout<<" ---------------------------";
    for(int y=11;y<=21;y++){
        moverCursor(19,y);
        cout<<"|"<<endl;
        moverCursor(47,y);
        cout<<"|"<<endl;
    }

    moverCursor(27,14);
    cout<<"        ___o     "<<endl;
    moverCursor(27,15);
    cout<<"    ___|__     "<<endl;
    moverCursor(27,16);
    cout<<"   (    o |    "<<endl;
    moverCursor(27,17);
    cout<<"   (_<___(   "<<endl;
    moverCursor(27,18);
    cout<<"       v      "<<endl;

    moverCursor(59,12);
    cout<<"Pez Linterna (Lampanyctodes hectoris)";
    moverCursor(62,14);
    cout<<"Familia biologica: Myctophidae";
    moverCursor(64,15);
    cout<<"Esperanza de vida: 3-4 anhos";
    moverCursor(64,16);
    cout<<"Inactividad reproductiva: 1";
    moverCursor(67,18);
    cout<<"Temperatura: 2 C - 8 C";
    moverCursor(68,19);
    cout<<"Salinidad: 34-36 ppt";
    moverCursor(72,20);
    cout<<"Oxigeno: 3-5";
}

void pez_vibora(){
    system("CLS");
    titulo_wikiwater();
    moverCursor(19,11);
    cout<<" ---------------------------";
    moverCursor(19,21);
    cout<<" ---------------------------";
    for(int y=11;y<=21;y++){
        moverCursor(19,y);
        cout<<"|"<<endl;
        moverCursor(47,y);
        cout<<"|"<<endl;
    }
    moverCursor(25,14);
    cout<<"         /"<<endl;
    moverCursor(24,15);
    cout<<"         /"<<endl;
    moverCursor(24,16);
    cout<<"  ><((((((((((')"<<endl;
    moverCursor(24,17);
    cout<<"          w"<<endl;

    moverCursor(64,12);
    cout<<"Pez Vibora (Chauliodus sloani)";
    moverCursor(65,14);
    cout<<"Familia biologica: Stomiidae";
    moverCursor(64,15);
    cout<<"Esperanza de vida: 15-20 anhos";
    moverCursor(66,16);
    cout<<"Inactividad reproductiva: 2";
    moverCursor(67,18);
    cout<<"Temperatura: 4 C - 5 C";
    moverCursor(69,19);
    cout<<"Salinidad: 35-37 ppt";
    moverCursor(73,20);
    cout<<"Oxigeno: 2-4";
}

void medusa_peine(){
    system("CLS");
    titulo_wikiwater();
    moverCursor(19,11);
    cout<<" ---------------------------";
    moverCursor(19,21);
    cout<<" ---------------------------";
    for(int y=11;y<=21;y++){
        moverCursor(19,y);
        cout<<"|"<<endl;
        moverCursor(47,y);
        cout<<"|"<<endl;
    }
    moverCursor(24,14);
    cout<<"    __________"<<endl;
    moverCursor(24,15);
    cout<<"   ( ---|--|- )"<<endl;
    moverCursor(24,16);
    cout<<"    (  --|--|  )"<<endl;
    moverCursor(24,17);
    cout<<"   (__________)  "<<endl;

    moverCursor(64,12);
    cout<<"Medusa Peine (Ctenophora spp.)";
    moverCursor(65,14);
    cout<<"Familia biologica: Ctenophora";
    moverCursor(67,15);
    cout<<"Esperanza de vida: 3 meses";
    moverCursor(66,16);
    cout<<"Inactividad reproductiva: 0";
    moverCursor(67,18);
    cout<<"Temperatura: 2 C - 30 C";
    moverCursor(69,19);
    cout<<"Salinidad: 32-35 ppt";
    moverCursor(73,20);
    cout<<"Oxigeno: 3-5";
}

#endif // WIKI_H