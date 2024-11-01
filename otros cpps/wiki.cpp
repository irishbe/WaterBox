#include "utilidades.h"

using namespace std;

vector<string> especies = {"Tiburon de arrecife", "Pez Payaso", "Langosta comun", "Pez mariposa", "Camaron Limpiador", "Algas coralinas"};

//Color de texto
const int BACKGROUND_CYAN = BACKGROUND_BLUE | BACKGROUND_GREEN;

//FUNCION COLOR DE FONDO Y TEXTO
void setColor(int textColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, textColor);
}

void wiki_opc_1();
void wiki_opc_2();
void wiki_opc_3();
void wiki_buscar();
void wiki_especies(string nombreEspecie);
void wiki_bioma_opc1();
void wiki_especies_arrecife_opc1();
void wiki_especies_arrecife_opc2();
void wiki_especies_arrecife_opc3();
void wiki_especies_arrecife_opc4();
void wiki_especies_arrecife_opc5();
void wiki_especies_arrecife_opc6();
void wiki_lista();
void tiburon_arrecife();
void pez_payaso();
void langosta_comun();
void pez_mariposa();
void camaron_limpiador();
void algas_coralinas();

int main(){
    wiki_opc_1();
    getch();
    return 0;
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

//OPCIONES MENÚ WIKI
void wiki_opc_1(){
    int tecla;
    system("CLS");
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout<<"\n   Seleccione la opcion: "<<endl;
    cout << "\n\n";
  	setColor(FOREGROUND_BLUE);
    cout<<"\t1. Buscar" <<endl;
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout<<"\t2. Bioma" <<endl;
    cout<<"\t3. Lista" <<endl;

    //Se utilizan 2 getch() cuando se quiere usar flechas para evitar el valor basura (224)
	//Forma de detectar una tecla normal y una flecha sin tener que pedir siempre otro valor (en que caso que no sea flecha)
	tecla= getch();
	if(tecla==224){
		tecla= getch();
	}
	//Teclas posibles
	switch (tecla){
		case 72: wiki_opc_3();break; //Flecha arriba
		case 80: wiki_opc_2();break; //Flecha abajo
		case 13: wiki_buscar();break; //Enter
		default: wiki_opc_1(); break;
	}

}

void wiki_opc_2(){
    int tecla;
    system("CLS");
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout<<"\n   Seleccione la opcion: "<<endl;
    cout << "\n\n";
    cout<<"\t1. Buscar" <<endl;
    setColor(FOREGROUND_BLUE);
    cout<<"\t2. Bioma" <<endl;
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout<<"\t3. Lista" <<endl;

    //Se utilizan 2 getch() cuando se quiere usar flechas para evitar el valor basura (224)
	//Forma de detectar una tecla normal y una flecha sin tener que pedir siempre otro valor (en que caso que no sea flecha)
	tecla= getch();
	if(tecla==224){
		tecla= getch();
	}
	//Teclas posibles
	switch (tecla){
		case 72: wiki_opc_1();break; //Flecha arriba
		case 80: wiki_opc_3();break; //Flecha abajo
		case 13: wiki_bioma_opc1();break; //Enter
		default: wiki_opc_2(); break;
	}

}

void wiki_opc_3(){
    int tecla;
    system("CLS");
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout<<"\n   Seleccione la opcion: "<<endl;
    cout << "\n\n";
    cout<<"\t1. Buscar" <<endl;
    cout<<"\t2. Bioma" <<endl;
    setColor(FOREGROUND_BLUE);
    cout<<"\t3. Lista" <<endl;
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

    //Se utilizan 2 getch() cuando se quiere usar flechas para evitar el valor basura (224)
	//Forma de detectar una tecla normal y una flecha sin tener que pedir siempre otro valor (en que caso que no sea flecha)
	tecla= getch();
	if(tecla==224){
		tecla= getch();
	}
	//Teclas posibles
	switch (tecla){
		case 72: wiki_opc_2();break; //Flecha arriba
		case 80: wiki_opc_1();break; //Flecha abajo
		case 13: wiki_lista();break; //Enter
		default: wiki_opc_3(); break;
	}

}


//MENÚ BUSCAR ESPECIE
void wiki_buscar(){
    bool band=false;
    string nombreEspecie;
    system("CLS");

    cout<<"\n   Ingresa el nombre de la especie: "<<endl;
    moverCursor(5, 4);
    getline(cin,nombreEspecie);

    for (int i = 0; i < especies.size(); i++) {
        if(especies[i]==nombreEspecie){
            wiki_especies(nombreEspecie);
            band=true;
            break;
        }
    }
    if(band==false){
        moverCursor(5, 6);
        cout<<"Nombre incorrecto"<<endl<<endl;
        system("pause");
        wiki_buscar();
    }

}

void wiki_especies(string nombreEspecie){
    if(nombreEspecie=="Tiburon de arrecife"){
        tiburon_arrecife();
    }
    else if(nombreEspecie=="Pez Payaso"){
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
}


//MENÚ BIOMAS
void wiki_bioma_opc1(){
    int tecla;
    system("CLS");
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout<<"\n   Seleccione el bioma: "<<endl;
    cout << "\n\n";
  	setColor(FOREGROUND_BLUE);
    cout<<"\t1. Arrecifes de coral" <<endl;
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

    //Se utilizan 2 getch() cuando se quiere usar flechas para evitar el valor basura (224)
	//Forma de detectar una tecla normal y una flecha sin tener que pedir siempre otro valor (en que caso que no sea flecha)
	tecla= getch();
	if(tecla==224){
		tecla= getch();
	}
	//Teclas posibles
	switch (tecla){
		case 72: wiki_bioma_opc1();break; //Flecha arriba
		case 80: wiki_bioma_opc1();break; //Flecha abajo
		case 13: wiki_especies_arrecife_opc1();break; //Enter
		default: wiki_bioma_opc1(); break;
	}
}

void wiki_especies_arrecife_opc1(){
    int tecla;
    system("CLS");
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout<<"\n   ARRECIFE DE CORAL: "<<endl;
    cout << "\n\n";
  	setColor(FOREGROUND_BLUE);
    cout<<"\t1. Tiburon de arrecife" <<endl;
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout<<"\t2. Pez Payaso" <<endl;
    cout<<"\t3. Langosta comun" <<endl;
    cout<<"\t4. Pez mariposa" <<endl;
    cout<<"\t5. Camaron Limpiador" <<endl;
    cout<<"\t6. Algas coralinas" <<endl;

    //Se utilizan 2 getch() cuando se quiere usar flechas para evitar el valor basura (224)
	//Forma de detectar una tecla normal y una flecha sin tener que pedir siempre otro valor (en que caso que no sea flecha)
	tecla= getch();
	if(tecla==224){
		tecla= getch();
	}
	//Teclas posibles
	switch (tecla){
		case 72: wiki_especies_arrecife_opc6();break; //Flecha arriba
		case 80: wiki_especies_arrecife_opc2();break; //Flecha abajo
		case 13: tiburon_arrecife();break; //Enter
		default: wiki_especies_arrecife_opc1(); break;
	}
}

void wiki_especies_arrecife_opc2(){
    int tecla;
    system("CLS");
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout<<"\n   ARRECIFE DE CORAL: "<<endl;
    cout << "\n\n";
    cout<<"\t1. Tiburon de arrecife" <<endl;
    setColor(FOREGROUND_BLUE);
    cout<<"\t2. Pez Payaso" <<endl;
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout<<"\t3. Langosta comun" <<endl;
    cout<<"\t4. Pez mariposa" <<endl;
    cout<<"\t5. Camaron Limpiador" <<endl;
    cout<<"\t6. Algas coralinas" <<endl;

    //Se utilizan 2 getch() cuando se quiere usar flechas para evitar el valor basura (224)
	//Forma de detectar una tecla normal y una flecha sin tener que pedir siempre otro valor (en que caso que no sea flecha)
	tecla= getch();
	if(tecla==224){
		tecla= getch();
	}
	//Teclas posibles
	switch (tecla){
		case 72: wiki_especies_arrecife_opc1();break; //Flecha arriba
		case 80: wiki_especies_arrecife_opc3();break; //Flecha abajo
		case 13: pez_payaso();break; //Enter
		default: wiki_especies_arrecife_opc2(); break;
	}
}

void wiki_especies_arrecife_opc3(){
    int tecla;
    system("CLS");
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout<<"\n   ARRECIFE DE CORAL: "<<endl;
    cout << "\n\n";
    cout<<"\t1. Tiburon de arrecife" <<endl;
    cout<<"\t2. Pez Payaso" <<endl;
    setColor(FOREGROUND_BLUE);
    cout<<"\t3. Langosta comun" <<endl;
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout<<"\t4. Pez mariposa" <<endl;
    cout<<"\t5. Camaron Limpiador" <<endl;
    cout<<"\t6. Algas coralinas" <<endl;

    //Se utilizan 2 getch() cuando se quiere usar flechas para evitar el valor basura (224)
	//Forma de detectar una tecla normal y una flecha sin tener que pedir siempre otro valor (en que caso que no sea flecha)
	tecla= getch();
	if(tecla==224){
		tecla= getch();
	}
	//Teclas posibles
	switch (tecla){
		case 72: wiki_especies_arrecife_opc2();break; //Flecha arriba
		case 80: wiki_especies_arrecife_opc4();break; //Flecha abajo
		case 13: langosta_comun();break; //Enter
		default: wiki_especies_arrecife_opc3(); break;
	}
}

void wiki_especies_arrecife_opc4(){
    int tecla;
    system("CLS");
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout<<"\n   ARRECIFE DE CORAL: "<<endl;
    cout << "\n\n";
    cout<<"\t1. Tiburon de arrecife" <<endl;
    cout<<"\t2. Pez Payaso" <<endl;
    cout<<"\t3. Langosta comun" <<endl;
    setColor(FOREGROUND_BLUE);
    cout<<"\t4. Pez mariposa" <<endl;
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout<<"\t5. Camaron Limpiador" <<endl;
    cout<<"\t6. Algas coralinas" <<endl;

    //Se utilizan 2 getch() cuando se quiere usar flechas para evitar el valor basura (224)
	//Forma de detectar una tecla normal y una flecha sin tener que pedir siempre otro valor (en que caso que no sea flecha)
	tecla= getch();
	if(tecla==224){
		tecla= getch();
	}
	//Teclas posibles
	switch (tecla){
		case 72: wiki_especies_arrecife_opc3();break; //Flecha arriba
		case 80: wiki_especies_arrecife_opc5();break; //Flecha abajo
		case 13: pez_mariposa();break; //Enter
		default: wiki_especies_arrecife_opc4(); break;
	}
}

void wiki_especies_arrecife_opc5(){
    int tecla;
    system("CLS");
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout<<"\n   ARRECIFE DE CORAL: "<<endl;
    cout << "\n\n";
    cout<<"\t1. Tiburon de arrecife" <<endl;
    cout<<"\t2. Pez Payaso" <<endl;
    cout<<"\t3. Langosta comun" <<endl;
    cout<<"\t4. Pez mariposa" <<endl;
    setColor(FOREGROUND_BLUE);
    cout<<"\t5. Camaron Limpiador" <<endl;
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout<<"\t6. Algas coralinas" <<endl;

    //Se utilizan 2 getch() cuando se quiere usar flechas para evitar el valor basura (224)
	//Forma de detectar una tecla normal y una flecha sin tener que pedir siempre otro valor (en que caso que no sea flecha)
	tecla= getch();
	if(tecla==224){
		tecla= getch();
	}
	//Teclas posibles
	switch (tecla){
		case 72: wiki_especies_arrecife_opc4();break; //Flecha arriba
		case 80: wiki_especies_arrecife_opc6();break; //Flecha abajo
		case 13: camaron_limpiador();break; //Enter
		default: wiki_especies_arrecife_opc5(); break;
	}
}

void wiki_especies_arrecife_opc6(){
    int tecla;
    system("CLS");
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout<<"\n   ARRECIFE DE CORAL: "<<endl;
    cout << "\n\n";
    cout<<"\t1. Tiburon de arrecife" <<endl;
    cout<<"\t2. Pez Payaso" <<endl;
    cout<<"\t3. Langosta comun" <<endl;
    cout<<"\t4. Pez mariposa" <<endl;
    cout<<"\t5. Camaron Limpiador" <<endl;
    setColor(FOREGROUND_BLUE);
    cout<<"\t6. Algas coralinas" <<endl;
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

    //Se utilizan 2 getch() cuando se quiere usar flechas para evitar el valor basura (224)
	//Forma de detectar una tecla normal y una flecha sin tener que pedir siempre otro valor (en que caso que no sea flecha)
	tecla= getch();
	if(tecla==224){
		tecla= getch();
	}
	//Teclas posibles
	switch (tecla){
		case 72: wiki_especies_arrecife_opc5();break; //Flecha arriba
		case 80: wiki_especies_arrecife_opc1();break; //Flecha abajo
		case 13: algas_coralinas();break; //Enter
		default: wiki_especies_arrecife_opc6(); break;
	}
}

//LISTA DE TODAS LAS ESPECIES
void wiki_lista(){
    cout<<"FALTA HACER";
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