#ifndef ASCII_MENU_HPP
#define ASCII_MENU_HPP

#include <iostream>
#include <sstream>

using namespace std;

// ------------------------------------------- MENU PRINCIPAL -------------------------------------------

string ASCIICodigos() {
    return
    ".oOo.oOo.oOo.oOo.oOo.oOo."
    "\n:    ______             :"
    "\n:   |_,.,--\\           :"
    "\n:     ||                :"
    "\n:     ||     CÓDIGOS    :"
    "\n:     ##                :"
    "\n:     ##                :"
    "\n.oOo.oOo.oOo.oOo.oOo.oOo.";
}

string ASCIISimulador() {
    return
    ".oOo.oOo.oOo.oOo.oOo.oOo."
    "\n: |   .   SIMULADOR . | :"
    "\n: |.  /     .  °  .   | :"
    "\n: |\\  | |  o    .   .| :"
    "\n: | | |/   _ °    <>< | :"
    "\n: |  \\|  ><_>        | :"
    "\n: ∙---!--------;;--;;-∙ :"
    "\n.oOo.oOo.oOo.oOo.oOo.oOo.";
}

// ------------------------------------------- MENU WIKIWATER -------------------------------------------

string ASCIIBuscarPorNombre() {
    return
    ".oOo.oOo.oOo.oOo.oOo.oOo."
    "\n:                       :"
    "\n: ><(((('>  ><(((('>    :"
    "\n:                       :"
    "\n:   ><(((('>   ><(((('> :"
    "\n:                       :"
    "\n:   POR NOMBRE COMÚN    :"
    "\n:     O CIENTÍFICO      :"
    "\n.oOo.oOo.oOo.oOo.oOo.oOo.";
}

string ASCIIBuscarPorBioma() {
    return
    ".oOo.oOo.oOo.oOo.oOo.oOo."
    "\n:               \\ | /   :"
    "\n:              --(_)--  :"
    "\n:               / | \\   :"
    "\n:^~^~^~^~^~^~^~^~^~^~^~^:"
    "\n: ^ ~    >(('>     ~ ^  :"
    "\n:   >(('>      >(('>    :"
    "\n:      POR BIOMA        :"
    "\n.oOo.oOo.oOo.oOo.oOo.oOo.";
}

string ASCIIBuscarPorFamilia() {
    return
    ".oOo.oOo.oOo.oOo.oOo.oOo."
    "\n:     \\\\ °   o     o    :"
    "\n: >><(((('> °           :"
    "\n:     //    \\\\\\\\__   o  :"
    "\n:       \\\\_/     o\\ ° o :"
    "\n:       // \\__+___/     :"
    "\n:             |/        :"
    "\n:      POR FAMILIA      :"
    "\n.oOo.oOo.oOo.oOo.oOo.oOo.";
}

// ------------------------------------------- MENU SIMULADOR -------------------------------------------

string ASCIIAgregarEspecie() {
    return
    ".oOo.oOo.oOo.oOo.oOo.oOo."
    "\n:    AGREGAR ESPECIE    :"
    "\n:               .       :"
    "\n:    _    \\_____)\\_____ :"
    "\n:  _| |_  /--v____ __`< :"
    "\n: |_   _|         )/    :"
    "\n:   |_|           '     :"
    "\n.oOo.oOo.oOo.oOo.oOo.oOo.";
}

string ASCIIEliminarEspecie() {
    return
    ".oOo.oOo.oOo.oOo.oOo.oOo."
    "\n:   ELIMINAR ESPECIE    :"
    "\n:              .        :"
    "\n:        \\_____)\\_____  :"
    "\n: __ __  /--v____ __`<  :"
    "\n: \\ \' /          )/     :"
    "\n: /_\'_\\          '      :"
    "\n.oOo.oOo.oOo.oOo.oOo.oOo.";
}

string ASCIIModificarFactores() {
    return
    ".oOo.oOo.oOo.oOo.oOo.oOo."
    "\n:       \\   |   /       :"
    "\n:         .---.         :"
    "\n:    --  /     \\  --    :"
    "\n: ^~^~^~^~^~^~^~^~^~^~^ :"
    "\n:  MODIFICAR  FACTORES  :"
    "\n:   ~^~    ~^~    ~^~   :"
    "\n.oOo.oOo.oOo.oOo.oOo.oOo.";
}

string ASCIIEnlistarEspecies() {
    return
    ".oOo.oOo.oOo.oOo.oOo.oOo."
    "\n: ,._.-._.-=-._.-=-._., :"
    "\n: |                   | :"
    "\n: | ENLISTAR ESPECIES | :"
    "\n: |    ∙ ---------    | :"
    "\n: |    ∙ ---------    | :"
    "\n: \'.-._.-=-._.-=-._.-.\' :"
    "\n.oOo.oOo.oOo.oOo.oOo.oOo.";
}

string ASCIIBuscarWikiwater() {
    return
    ".oOo.oOo.oOo.oOo.oOo.oOo."
    "\n:   .______________.    :"
    "\n:  / \\             \\   °:"
    "\n: |._|   BUSCAR EN  |°  :"
    "\n:°   |   WIKIWATER  | o :"
    "\n:  o |  .___________|_. :"
    "\n:    \\_/_____________/  :"
    "\n.oOo.oOo.oOo.oOo.oOo.oOo.";
}

// ---------------------------------------- MENU MODIFICAR FACTORES ----------------------------------------

string ASCIISalinidad() {
    return
    ".oOo.oOo.oOo.oOo.oOo.oOo."
    "\n:       SALINIDAD       :"
    "\n:         ______        :"
    "\n:      ._/_____/|_.     :"
    "\n:    _/_|______|/_/|_.  :"
    "\n:  _/______|______|/_/| :"
    "\n: |______|_____|_____|/ :"
    "\n.oOo.oOo.oOo.oOo.oOo.oOo.";
}

string ASCIIOxigeno() {
    return
    ".oOo.oOo.oOo.oOo.oOo.oOo."
    "\n:        OXÍGENO        :"
    "\n:      °             o  :"
    "\n:   ( )   o   °    o    :"
    "\n:          ( )       °  :"
    "\n:  o              o     :"
    "\n:      ( )         ( )  :"
    "\n.oOo.oOo.oOo.oOo.oOo.oOo.";
}

string ASCIIContaminacion() {
    return
    ".oOo.oOo.oOo.oOo.oOo.oOo."
    "\n:     CONTAMINACIÓN     :"
    "\n:      [!!!!!!!!!]      :"
    "\n:       |  .-.  |       :"
    "\n:       |,(o.o).|       :"
    "\n:       |` `\"` `|       :"
    "\n:       `\"\"\"\"\"\"\"`       :"
    "\n.oOo.oOo.oOo.oOo.oOo.oOo.";
}
 
string ASCIITemperatura() {
    return
    ".oOo.oOo.oOo.oOo.oOo.oOo."
    "\n:      TEMPERATURA      :"
    "\n:  ∙─────────────────∙  :"
    "\n:  │   .   .   .   ºC│  :"
    "\n:  │(:=¡=!=¡=!=¡=!=∙ │  :"
    "\n:  │     '   '   ' ºF│  :"
    "\n:  ∙─────────────────∙  :"
    "\n.oOo.oOo.oOo.oOo.oOo.oOo.";
}

#endif // ASCIIMenu.hpp