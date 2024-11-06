#ifndef ASCII_ESPECIES_H
#define ASCII_ESPECIES_H

#include <iostream>
#include <sstream>
#include "utilidades.h"

using namespace std;

//Dibujos especies
string pezPayaso(){
        return  textoRGB(255,127,0) + " m  m\n" +
                textoRGB(255,127,0) + "><" + 
                textoRGB(255,255,255) + "(" + 
                textoRGB(255,127,0) + "(" +
                textoRGB(255,255,255) + "(" +
                textoRGB(255,127,0) + "(" +
                textoRGB(255,255,255) + "'>" +
                textoRGB(0,0,0);
}

 string tiburonDeArrecife(){
        return  textoRGB(9,12,187) + "\\_____)\\_____\n" +
                textoRGB(9,12,187) + "/--_____||__`_>\n" + 
                textoRGB(9,12,187) + "        )/     \n" + 
                textoRGB(9,12,187) + "        '        " +
                textoRGB(0,0,0);
}

 string langostaComun(){
        return  textoRGB(187,39,9) + "       __  \n" +
                textoRGB(187,39,9) + "v  |  |    \n" + 
                textoRGB(187,39,9) + "<((((())---\n" + 
                textoRGB(187,39,9) + "v  |  |__    " +
                textoRGB(0,0,0);
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
                textoRGB(0,0,0);
}

string camaronLimpiador(){
        return  textoRGB(255,255,255) + " |    |__\n" +
                textoRGB(247, 13, 74) + ">((((:<__\n" + 
                textoRGB(255,255,255) + " |    |  " +
                textoRGB(0,0,0);
}

string algasCoralinas(){
        return  textoRGB(195,50,231) + " vv vv vv   \n" +
                textoRGB(195,50,231) + "< <<  >>  >>\n" + 
                textoRGB(195,50,231) + "  vv vv  vv  " + 
                textoRGB(0,0,0);
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
                textoRGB(0,0,0);
}

string pezVibora(){
        return  textoRGB(255,255,255) + "       /      \n" +
                textoRGB(255,255,255) + "       /      \n" +
                textoRGB(65,61,122) + "><" + 
                textoRGB(111,81,117 ) + "((((((((((')\n" +
                textoRGB(65,61,122) + "        w       " +
                textoRGB(0,0,0);
}

string medusaPeine(){
        return  textoRGB(32,232,211) + " __________  \n" +
                textoRGB(32,232,211) + "( ---|--|- ) \n" +
                textoRGB(32,232,211) + " (  --|--|  )\n" + 
                textoRGB(32,232,211) + "(__________)   " +
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

    }

    return sprite;
}

#endif // asciiEspecies.hpp