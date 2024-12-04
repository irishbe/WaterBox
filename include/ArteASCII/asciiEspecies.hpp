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
        return  textoRGB(255, 127, 0) + " m  m\n" +
                textoRGB(255, 127, 0) + "><" + 
                textoRGB(255, 255, 255) + "(" + 
                textoRGB(255, 127, 0) + "(" +
                textoRGB(255, 255, 255) + "(" +
                textoRGB(255, 127, 0) + "(" +
                textoRGB(255, 255, 255) + "'>" +
                textoRGB(255,255,255);
}

 string tiburonDeArrecife(){
        return  textoRGB(134, 141, 252) + "\\_____)\\_____\n" +
                textoRGB(134, 141, 252) + "/--_____||__`_>\n" + 
                textoRGB(134, 141, 252) + "        )/     \n" + 
                textoRGB(134, 141, 252) + "        '        " +
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

string hierbaMarina(){
        return textoRGB(38,178,31) + "    | || | | \n" +
               textoRGB(38,178,31) + "    / | | / |  \n" +
               textoRGB(38,178,31) + "    | | | | |  \n" +
               textoRGB(38,178,31) + " _\\|_\\_||_\n" +
               textoRGB(255,255,255);
}

string anguilaEuropea(){
        return  textoRGB(34,35,28) + "  ________________\n" +
                textoRGB(196,202,79) + "   /-|||||||||||||`_"+
                textoRGB(34,35,28) + ">\n" + 
                textoRGB(196,202,79) + " /--------------\n" + 
                textoRGB(255,255,255);
}

string almejaDeMarisma(){
        return textoRGB(242,243,208) + "  /---------\\\n" +
               textoRGB(242,243,208) + " ("+
               textoRGB(209,192,169) + "|||||||||" +
               textoRGB(242,243,208) + ")\n" +
               textoRGB(242,243,208) + "   \\_      _/  \n" +
               textoRGB(242,243,208) + "   \\----/  \n" +
               textoRGB(255,255,255);
}

string robaloComun(){
        return textoRGB(130,176,178) + "     __/`--/`-._  \n" +
               textoRGB(130,176,178) + " >>/---------o \\\n" +
               textoRGB(130,176,178) + "   >>\\_ __ ______/  \n" +
               textoRGB(130,176,178) + "    \\'  '\\     \n" +
               textoRGB(255,255,255);
}

string tilapiaMozambiquena(){
        return textoRGB(95,182,184) + "     /////////  \n" +
               textoRGB(94,156,157) + "  >>||||||||_o)\n" +
               textoRGB(192,219,220) + "  >>\\________/  \n" +
               textoRGB(255,255,255);
}

string espinosoDeTresEspinas(){
        return  textoRGB(236,234,203) + " ,; ,; ,;\n" +
                textoRGB(175,168,29) + "  >))))))))o>\n" + 
                textoRGB(236,234,203) + "V     V" +
                textoRGB(255,255,255);
}

string salicorniaEuropea(){
        return textoRGB(63,199,76) + "  |  | | | \n" +
               textoRGB(63,199,76) + "  \\|/\\|/|/|/  \n" +
               textoRGB(63,199,76) + "  \\|/\\|/|/|/ \n" +
               textoRGB(63,199,76) + "_\\|__|_|_|_\n" +
               textoRGB(255,255,255);
}

//Funcion para seleccionar el dibujo de una especie
string obtenerSprite(string nombreEspecie) {
    string sprite = "";

    if( nombreEspecie == "Tiburon de arrecife" ){
        sprite = tiburonDeArrecife();

    } else if (nombreEspecie == "Pez payaso") {
        sprite = pezPayaso();

    } else if( nombreEspecie == "Langosta comun" ){
        sprite = langostaComun();

    } else if( nombreEspecie == "Pez mariposa" ){
        sprite = pezMariposa();

    } else if( nombreEspecie == "Camaron Limpiador" ){
        sprite = camaronLimpiador();

    } else if( nombreEspecie == "Pez Linterna" ){
        sprite = pezLinterna();
    
    } else if( nombreEspecie == "Medusa Peine" ){
        sprite = medusaPeine();

    } else if( nombreEspecie == "Pez Vibora" ){
        sprite = pezVibora();

    } else if( nombreEspecie == "Anguila Europea" ){
        sprite = anguilaEuropea();

    } else if( nombreEspecie == "Cangrejo Azul" ){
        sprite = cangrejoAzul();

    } else if( nombreEspecie == "Almeja de Marisma" ){
        sprite = almejaDeMarisma();
    
    } else if( nombreEspecie == "Róbalo Común" ){
        sprite = robaloComun();

    } else if( nombreEspecie == "Tilapia Mozambiqueña" ){
        sprite = tilapiaMozambiquena();
    
    } else if( nombreEspecie == "Espinoso de Tres Espinas" ){
        sprite = espinosoDeTresEspinas();

    } else if( nombreEspecie == "Pez Arquero" ){
        sprite = pezArquero();

    } else if( nombreEspecie == "Estrella de Mar Roja" ){
        sprite = estrellaDeMarRoja();

    } else if( nombreEspecie == "Algas coralinas" ){
        sprite = algasCoralinas();

    } else if( nombreEspecie == "Hierba Marina" ){
        sprite = hierbaMarina();

    } else if( nombreEspecie == "Salicornia Europea" ){
        sprite = salicorniaEuropea();

    } else{
        sprite = "???";

    }


    return sprite;
}

#endif // asciiEspecies.hpp