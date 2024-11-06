#ifndef ASCII_MENU_HPP
#define ASCII_MENU_HPP

#include <iostream>
#include <sstream>
#include "utilidades.h"

using namespace std;

// --------------------------------------------------- MENU WIKIWATER ---------------------------------------------------

string asciiBuscarPorNombre() {
    return
    "\n _  _  _  _  _  _  _  _  _  _  _  _  _ "
    "\n(_)(_)(_)(_)(_)(_)(_)(_)(_)(_)(_)(_)(_)"
    "\n(_)                                 (_)"
    "\n(_)      ><(((('>   ><(((('>        (_)"
    "\n(_)                                 (_)"
    "\n(_)  ><(((('>  ><(((('>  ><(((('>   (_)"
    "\n(_)                                 (_)"
    "\n(_)      ><(((('>   ><(((('>        (_)"
    "\n(_)                                 (_)"
    "\n(_)  ><(((('>  ><(((('>  ><(((('>   (_)"
    "\n(_)                                 (_)"
    "\n(_)  POR NOMBRE COMÚN O CIENTÍFICO  (_)"
    "\n(_) _  _  _  _  _  _  _  _  _  _  _ (_)"
    "\n(_)(_)(_)(_)(_)(_)(_)(_)(_)(_)(_)(_)(_)";
}

string asciiBuscarPorBioma() {
    return
    "\n _  _  _  _  _  _  _  _  _  _  _  _  _ "
    "\n(_)(_)(_)(_)(_)(_)(_)(_)(_)(_)(_)(_)(_)"
    "\n(_)                        \\ | /    (_)"
    "\n(_)                       --(_)--   (_)"
    "\n(_)                        / | \\    (_)"
    "\n(_)                                 (_)"
    "\n(_) ~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~ (_)"
    "\n(_)    - ^ - ^ -      - ^ - ^ -     (_)"
    "\n(_) ^ ~ ^ ~       >(('>      ^ ~ ^  (_)"
    "\n(_)         >(('>      >(('>        (_)"
    "\n(_) ^ ~ ^ ~                  ^ ~ ^  (_)"
    "\n(_)            POR BIOMA            (_)"
    "\n(_) _  _  _  _  _  _  _  _  _  _  _ (_)"
    "\n(_)(_)(_)(_)(_)(_)(_)(_)(_)(_)(_)(_)(_)";
}

string asciiBuscarPorFamilia() {
    return
    "\n _  _  _  _  _  _  _  _  _  _  _  _  _ "
    "\n(_)(_)(_)(_)(_)(_)(_)(_)(_)(_)(_)(_)(_)"
    "\n(_)                                 (_)"
    "\n(_)           o                     (_)"
    "\n(_)      \\\\    o            o       (_)"
    "\n(_)  >><(((('> °                    (_)"
    "\n(_)      //          \\\\\\\\__   o     (_)"
    "\n(_)              \\\\_/     o\\ ° o    (_)"
    "\n(_)              // \\__+___/        (_)"
    "\n(_)                    |/           (_)"
    "\n(_)                                 (_)"
    "\n(_)           POR FAMILIA           (_)"
    "\n(_) _  _  _  _  _  _  _  _  _  _  _ (_)"
    "\n(_)(_)(_)(_)(_)(_)(_)(_)(_)(_)(_)(_)(_)";
}

// ---------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------- POR VERIFICAR ---------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

//Dibujos Opciones

string ASCIagregarEspecie(){
        return  textoRGB(255,255,255) + "─────▀▄▀─────▄─────▄\n" +
                textoRGB(255,255,255) + "──▄███████▄──▀██▄██▀\n" +
                textoRGB(255,255,255) + "▄█████▀█████▄──▄█\n" +
                textoRGB(255,255,255) + "███████▀████████▀\n" +
                textoRGB(255,255,255) + "─▄▄▄▄▄▄███████▀  \n";
}

//Funcion doble uso -> ASCI de "Enlistar Especies" (Opcion de simulación) y de "Por Nombre" (Opción de WikiWater)
string dibujoArrecife(){
        return  "><(((('>  ><(((('>  ><(((('>\n"
                "     ><(((('>  ><(((('> \n"
                "><(((('>  ><(((('>  ><(((('>\n";
}

//Funcion doble uso -> ASCI de "Salinidad" (Opcion de "Modificar Factores") y de "Por Bioma" (Opción de WikiWater)
string dibujoSalinidad(){
        return  "────▄████▄─────\n"
                "─▄██▀─▀▀─▀██▄──\n"
                "███───────███─█\n"
                "███─█─█───███─▀\n"
                "─▀██▄─█─▄██▀──▄\n"
                "───▀████▀─────\n";    
}

//Funcion de "Por Listado" (Opción de WikiWater)
string dibujoLista(){
        return  "█████████████████████\n"
                "█       LISTA       █\n"
                "█   █████████████   █\n"
                "█   █           █   █\n"
                "█   █  ><((('>  █   █\n"
                "█   █████████████   █\n"
                "█                   █\n"
                "█████████████████████\n";       
}

string ASCImostrarDatosEspecie(){
        return  textoRGB(255,255,255) + "█████████████████████\n" +
                textoRGB(255,255,255) + "█       DATOS       █\n" +
                textoRGB(255,255,255) + "█   █████████████   █\n" +
                textoRGB(255,255,255) + "█   █           █   █\n" +
                textoRGB(255,255,255) + "█   █  ><((('>  █   █\n" +
                textoRGB(255,255,255) + "█   █████████████   █\n" +
                textoRGB(255,255,255) + "█                   █\n" +
                textoRGB(255,255,255) + "█████████████████████\n";       
}

string ASCImodificarFactores(){
        return  textoRGB(255,255,255) + "─▀▀▌───────▐▀▀\n" +
                textoRGB(255,255,255) + "─▄▀░◌░░░░░░░▀▄\n" +
                textoRGB(255,255,255) + "▐░░◌░▄▀██▄█░░░▌\n" +
                textoRGB(255,255,255) + "▐░░░▀████▀▄░░░▌\n" +
                textoRGB(255,255,255) + "═▀▄▄▄▄▄▄▄▄▄▄▄▀═\n";    
 }

string ASCImodificarFactoresX(){
        return  textoRGB(255,255,255) + "█▓▒░X░▒▓█   \n";            
}

//Dibujos Modificar Factores

string ASCIoxigeno(){
        return  textoRGB(255,255,255) + "○\n" +
                textoRGB(255,255,255) + "○    ○\n" +
                textoRGB(255,255,255) + "   ○    ○\n" +
                textoRGB(255,255,255) + "○    ○    ○\n" +
                textoRGB(255,255,255) + "   ○    ○\n";    
 }

string ASCItemperatura(){
        return  textoRGB(255,255,255) + " \\ | / \n" +
                textoRGB(255,255,255) + "-- ☼ -- \n" +
                textoRGB(255,255,255) + " / | \\n";
}

string ASCIcontaminacion(){
        return  textoRGB(255,255,255) + "▄▀▀▄▀▀▄▀▀▄▀▀▄▀▀▄\n" +
                textoRGB(255,255,255) + "▀▄▄▀▄▄▀▄▄▀▄▄▀▄▄▀\n" +
                textoRGB(255,255,255) + "▄▀▀▄▀▀▄▀▀▄▀▀▄▀▀▄\n" +
                textoRGB(255,255,255) + "▀▄▄▀▄▄▀▄▄▀▄▄▀▄▄▀\n";
}

//Dibujo Códigos
string ASCIcodigos(){
        return  textoRGB(255,255,255) + "──▄▀▀▀▄───────────────\n" +
                textoRGB(255,255,255) + "──█───█───────────────\n" +
                textoRGB(255,255,255) + "─███████─────────▄▀▀▄─\n" +
                textoRGB(255,255,255) + "░██───██░░█▀█▀▀▀▀█░░█░\n" +
                textoRGB(255,255,255) + "░███▄███░░▀░▀░░░░░▀▀░░ \n";  
}


#endif // asciiMenu.hpp