#ifndef ASCII_ESPECIES_H
#define ASCII_ESPECIES_H

#include <iostream>
#include <sstream>

using namespace std;

string textoRGB(int r, int g, int b) {
    return "\033[38;2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m";
}

//Dibujos especies
string pezPayaso(){
        return  textoRGB(255,127,0) + " m  m\n" +
                textoRGB(255,127,0) + "><" + 
                textoRGB(255,255,255) + "(" + 
                textoRGB(255,127,0) + "(" +
                textoRGB(255,255,255) + "(" +
                textoRGB(255,127,0) + "(" +
                textoRGB(255,255,255) + "'>" +
                textoRGB(255,255,255);
}

 string tiburonDeArrecife(){
        return  textoRGB(9,12,187) + "\\_____)\\_____\n" +
                textoRGB(9,12,187) + "/--_____||__`_>\n" + 
                textoRGB(9,12,187) + "        )/     \n" + 
                textoRGB(9,12,187) + "        '        " +
                textoRGB(255,255,255);
}

 string langostaComun(){
        return  textoRGB(187,39,9) + "       __  \n" +
                textoRGB(187,39,9) + "v  |  |    \n" + 
                textoRGB(187,39,9) + "<((((())---\n" + 
                textoRGB(187,39,9) + "v  |  |__    " +
                textoRGB(255,255,255);
}

string pezMariposa(){
        return  textoRGB(255,255,255) + " _____  \n" +
                textoRGB(0,0,0) + "(" + 
                textoRGB(247,223,71) + "| " + 
                textoRGB(0,0,0) + "| " +
                textoRGB(247,223,71) + "|" +
                textoRGB(255,255,255) + ") \n" +
                textoRGB(0,0,0) + "(" +
                textoRGB(247,223,71) + "__" +
                textoRGB(0,0,0) + "__" +
                textoRGB(247,223,71) + "o_" +
                textoRGB(255,255,255) + "> \n" +
                textoRGB(0,0,0) + "     v    " +
                textoRGB(255,255,255);
}

string camaronLimpiador(){
        return  textoRGB(255,255,255) + " |    |__\n" +
                textoRGB(247, 13, 74) + ">((((:<__\n" + 
                textoRGB(255,255,255) + " |    |  " +
                textoRGB(255,255,255);
}

string algasCoralinas(){
        return  textoRGB(195,50,231) + " vv vv vv   \n" +
                textoRGB(195,50,231) + "< <<  >>  >>\n" + 
                textoRGB(195,50,231) + "  vv vv  vv  " + 
                textoRGB(255,255,255);
}

string pezLinterna(){
        return  textoRGB(255,255,255) + "     ___o\n" +
                textoRGB(51,21,32) + " ___" +
                textoRGB(255,255,255) + "|" + 
                textoRGB(51,21,32) + "__  \n" +
                textoRGB(51,21,32) + "(    o | \n" +
                textoRGB(51,21,32) + "(_" +
                textoRGB(255,255,255) + "<" +
                textoRGB(51,21,32) + "___(  \n" +
                textoRGB(255,255,255) + "    v      " +
                textoRGB(255,255,255);
}

string pezVibora(){
        return  textoRGB(255,255,255) + "       /      \n" +
                textoRGB(255,255,255) + "       /      \n" +
                textoRGB(65,61,122) + "><" + 
                textoRGB(111,81,117) + "((((((((((')\n" +
                textoRGB(65,61,122) + "        w       " +
                textoRGB(255,255,255);
}

string medusaPeine(){
        return  textoRGB(32,232,211) + " __________  \n" +
                textoRGB(32,232,211) + "( ---|--|- ) \n" +
                textoRGB(32,232,211) + " (  --|--|  )\n" + 
                textoRGB(32,232,211) + "(__________)   " +
                textoRGB(255,255,255);
}

string cangrejoAzul(){
        return textoRGB(30,144,255) + "    _\\_____/_     \n" +
               textoRGB(30,144,255) + "   |(o)_(o)|   \n" +
               textoRGB(30,144,255) + "  / /._____.\\  \\  \n" +
               textoRGB(30,144,255) + "  | | /     \\|  |  \n" +
               textoRGB(255,255,255);
}

string pezArquero(){
        return textoRGB(100,149,237) + "    /`----.___  \n" +
               textoRGB(100,149,237) + "  >>| | | |> o)\n" +
               textoRGB(100,149,237) + "   >>\\________/  \n" +
               textoRGB(255,255,255);
}

string estrellaDeMarRoja(){
        return textoRGB(232,32,32) + "      /\\      \n" +
               textoRGB(232,32,32) + " ___/  \\___ \n" +
               textoRGB(232,32,32) + "  \\_      _/ \n" +
               textoRGB(232,32,32) + "  /  __  \\  \n" +
               textoRGB(232,32,32) + "   /__/  \\__\\   " +
               textoRGB(255,255,255);
}

//planta
string hierbaMarina(){
        return textoRGB(38,178,31) + "    | || | | \n" +
               textoRGB(38,178,31) + "    / | | / |  \n" +
               textoRGB(38,178,31) + "    | | | | |  \n" +
               textoRGB(38,178,31) + " _\\|_\\_||_\n" +
               textoRGB(255,255,255);
}

//Funcion para seleccionar el dibujo de una especie
string obtenerSprite(string nombreEspecie) {
    string sprite = "";

    if (nombreEspecie == "Pez payaso") {
        sprite = pezPayaso();

    } else if( nombreEspecie == "Tiburon de arrecife" ){
        sprite = tiburonDeArrecife();

    } else if( nombreEspecie == "Langosta comun" ){
        sprite = langostaComun();

    } else if( nombreEspecie == "Pez mariposa" ){
        sprite = pezMariposa();

    } else if( nombreEspecie == "Camaron Limpiador" ){
        sprite = camaronLimpiador();

    } else if( nombreEspecie == "Algas coralinas" ){
        sprite = algasCoralinas();
    
    } else if( nombreEspecie == "Pez Linterna" ){
        sprite = pezLinterna();
    
    } else if( nombreEspecie == "Pez Vibora" ){
        sprite = pezVibora();
    
    } else if( nombreEspecie == "Medusa Peine" ){
        sprite = medusaPeine();

    } else if( nombreEspecie == "Cangrejo Azul"){
        sprite = cangrejoAzul();

    } else if( nombreEspecie == "Pez Arquero" ){
        sprite = pezArquero();
    } else if( nombreEspecie == "Estrella de Mar Roja" ){
        sprite = estrellaDeMarRoja();

    }else if( nombreEspecie == "Hiberna Marina"){
        sprite = hierbaMarina();
    
    }else{
        sprite = "???";

    }


    return sprite;
}

#endif // asciiEspecies.hpp