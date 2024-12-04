#ifndef SIMULADOR_HPP
#define SIMULADOR_HPP

#include "crudEspecies.hpp"
#include "utilidades.hpp"
#include "Evento.hpp"
#include "Partida.hpp"

using namespace std;

const float oxigenoMin = 0, oxigenoMax = 14;
const float salinidadMin = 0, salinidadMax = 330;
const float temperaturaMin = 0, temperaturaMax = 40;
const float contaminacionMin = 0, contaminacionMax = 100;

// Declaraciones de funciones
void mostrarTodosCuadros();
void modificarFactor();
void imprimirPoblaciones();
void menuPartidasSimulador();
void menuOpcionesSimulador();
int mostrarMenuFactores();
void evaluarCambioFactores();

void crearPartida(){
    Partida* nuevaPartida = new Partida();

    int x = 10, y = 3, opcion = -1;
    y += imprimirTexto( tituloWaterBox(), x, y, true) + 3;

    fflush(stdin);
    moverCursor(x, y); cout << "INGRESE SU NOMBRE DE JUGADOR:";
    moverCursor(x, y + 1); getline(cin, nuevaPartida->nombreJugador);
    
    nuevaPartida->tiempoInicio = getTiempoActual();
    nuevaPartida->tiempoTranscurrido = calcularTiempoTranscurrido( nuevaPartida->tiempoInicio );
    nuevaPartida->archivoInfo = "infoPartida[" + nuevaPartida->nombreJugador + "].txt";
    nuevaPartida->archivoEventos = "eventosPartida[" + nuevaPartida->nombreJugador + "].txt";
    nuevaPartida->archivoConteoEventos = "conteoEventosPartida[" + nuevaPartida->nombreJugador + "].txt";

    // Seleccionando el bioma
    vector<string> dibujos = {
        ASCIIBiomaArrecifeCoral(),
        ASCIIBiomaOceanoProfundo(),
        ASCIIBiomaMarismasSalinas()
    };
        
    opcion = seleccionarConDibujos(dibujos, tituloBiomas(), "SELECCIONE UN BIOMA");
    system("cls");

    switch(opcion){
        case 1: nuevaPartida->bioma = extraerBioma("Arrecifes de Coral"); fondoRGB(0, 109, 198); break;
        case 2: nuevaPartida->bioma = extraerBioma("Oceano profundo"); fondoRGB(2, 4, 37); break;
        case 3: nuevaPartida->bioma = extraerBioma("Marismas salinas"); break;
        case -1: break;
    }

    almacenarPartida(nuevaPartida);
    partidaActual = nuevaPartida;
}

void seleccionarPartida() {
    vector<string> partidas = obtenerPartidas();

    // Validar si hay partidas antes de proceder
    if (partidas.empty()) {
        cout << "No hay partidas disponibles para seleccionar." << endl;
        getch();
        return;
    }

    string opcion = seleccionarConFlechas(partidas, tituloWaterBox(), "SELECCIONE UNA PARTIDA");

    if (opcion.empty()) {
        return;
    }

    partidaActual = cargarPartida(opcion);
}

// Función para iniciar el simulador
void iniciarSimulador() {
    menuPartidasSimulador();
    menuOpcionesSimulador();
}

void menuPartidasSimulador(){
    int opcion = -1;

    vector<string> dibujos = {
        "NUEVA PARTIDA",
        "CARGAR PARTIDA"
    };

    do{
        opcion = seleccionarConDibujos( dibujos, tituloWaterBox(), "SELECCIONE UNA OPCION");

        if( opcion == -1 ){
            return;
        }

        system("cls");

        switch (opcion){
            case 1: crearPartida(); break;
            case 2: seleccionarPartida(); break;
            case -1: break;
        }

    }while(partidaActual == nullptr);
}

void menuOpcionesSimulador(){
    bool desplegarCuadros = true;
    int opcion = -1;

    vector<string> dibujos = {
        ASCIIAgregarEspecie(),
        ASCIIEnlistarEspecies(),
        ASCIIModificarFactores(),
        ASCIIEliminarEspecie(),
        ASCIIReproduccion(),
        ASCIIArbolPoblacion()
    };

    do {

        if (desplegarCuadros){
            mostrarTodosCuadros();
            imprimirPoblaciones();
            mostrarEventos();
            getch();
        }

        opcion = seleccionarConDibujos( dibujos, tituloWaterBox(), "SELECCIONE UNA OPCION");

        system("cls");

        switch (opcion){
            case 1: agregarEspecie(); desplegarCuadros = true; break;
            case 2: enlistarEspecies(); desplegarCuadros = false; getch(); break;
            case 3: modificarFactor(); desplegarCuadros = true; break;
            case 4: eliminarEspecie(); desplegarCuadros = true; break;
            case 5: reproducirEspecies(); desplegarCuadros = true; break;
            case 6: imprimirArbolDePoblacion(); desplegarCuadros = false; break;
            //generarEventoAleatorio(); 
            case -1: break;
        }

        system("cls");

    } while (opcion != -1);

    fondoRGB(7, 25, 82);
}

void mostrarTodosCuadros() {
    cout << "Partida: " << partidaActual->nombreJugador << endl;
    cout << "Bioma: " << partidaActual->bioma->nombre << endl << endl;

    // Cálculo de los porcentajes según los valores ingresados
    int porcentajeOxigeno = (partidaActual->bioma->nivelOxigeno - oxigenoMin) * 100 / (oxigenoMax - oxigenoMin);
    int porcentajeSalinidad = (partidaActual->bioma->nivelSalinidad - salinidadMin) * 100 / (salinidadMax - salinidadMin);
    int porcentajeTemperatura = (partidaActual->bioma->nivelTemperatura - temperaturaMin) * 100 / (temperaturaMax - temperaturaMin);
    int porcentajeContaminacion = (partidaActual->bioma->nivelTemperatura - contaminacionMin) * 100 / (contaminacionMax - contaminacionMin);

    // Mostrar barras de progreso
    imprimirBarra("Oxígeno", porcentajeOxigeno); cout << "\t";
    imprimirBarra("Salinidad", porcentajeSalinidad); cout << "\t";
    imprimirBarra("Temperatura", porcentajeTemperatura); cout << "\t";
    imprimirBarra("Contaminación", porcentajeContaminacion); cout << endl;
}

void imprimirPoblaciones() {
    Poblacion* poblacionActual = partidaActual->listaPoblaciones;
    
    // Variables locales para las posiciones
    int x = 15, y = 5;  // Posición inicial en Y
    const int anchoCuadro = 30; // Ancho del cuadro
    const int limiteX = 130;    // Límite máximo de la pantalla en X
    const int espacioEntreCuadros = 3; // Espacio adicional entre cuadros

    while (poblacionActual != nullptr) {
        // Imprimir la población actual en la posición actual
        imprimirPoblacion( obtenerSprite(poblacionActual->nombreEspecie), "MEDIANO", x, y, poblacionActual);

        // Actualizar las posiciones
        if (x + anchoCuadro + espacioEntreCuadros <= limiteX) {
            x += anchoCuadro + espacioEntreCuadros;
        } else {
            x = 15;  // Reiniciar a la posición inicial X
            y += 8;  // Mover hacia abajo para la nueva fila
        }

        // Avanzar a la siguiente población
        poblacionActual = poblacionActual->sgtePoblacion;
    }
}

void modificarFactor() {
    int opcion = -1;
    float oxigeno, salinidad, temperatura, contaminacion;
    
    vector<string> dibujos = {
        ASCIIOxigeno(),
        ASCIISalinidad(),
        ASCIITemperatura(),
        ASCIIContaminacion()
    };
    
    do {
        
        opcion = seleccionarConDibujos( dibujos, tituloModificarFactores(), "SELECCIONE UN FACTOR A MODIFICAR");

        switch (opcion) {
            case 1: // Oxígeno
                oxigeno = partidaActual->bioma->nivelOxigeno;

                cout << "Ingrese el nivel de oxígeno (Mín. 0 / Máx. 14 mg/L): ";
                cin >> oxigeno;
                if (oxigeno < oxigenoMin || oxigeno > oxigenoMax) {
                    cout << "Valor fuera de rango. Debe estar entre " << oxigenoMin << " y " << oxigenoMax << " mg/L." << endl;
                    getch();
                }
                break;
            case 2: // Salinidad
                salinidad = partidaActual->bioma->nivelSalinidad;

                cout << "Ingrese el nivel de salinidad (Mín. 0 / Máx. 330 ups): ";
                cin >> salinidad;
                if (salinidad < salinidadMin || salinidad > salinidadMax) {
                    cout << "Valor fuera de rango. Debe estar entre " << salinidadMin << " y " << salinidadMax << " ups." << endl;
                    getch();
                }
                break;
            case 3: // Temperatura
                temperatura = partidaActual->bioma->nivelTemperatura;

                cout << "Ingrese la temperatura (Mín. 0 / Máx. 40 °C): ";
                cin >> temperatura;
                if (temperatura < temperaturaMin || temperatura > temperaturaMax) {
                    cout << "Valor fuera de rango. Debe estar entre " << temperaturaMin << " y " << temperaturaMax << " °C." << endl;
                    getch();
                }
                break;
            case 4: // Contaminación
                contaminacion = partidaActual->bioma->nivelContaminacion;

                cout << "Ingrese el nivel de contaminación (Mín. 0 / Máx. 100 %): ";
                cin >> contaminacion;
                if (contaminacion < contaminacionMin || contaminacion > contaminacionMax) {
                    cout << "Valor fuera de rango. Debe estar entre " << contaminacionMin << " y " << contaminacionMax << " %." << endl;
                    getch();
                }
                break;
            case -1: break;
        }

        system("cls");

    } while (opcion != -1);

    registrarEvento(MODIFICAR_FACTORES, partidaActual);
    evaluarCambioFactores();
}

void evaluarCambioFactores(){
    Poblacion* pActual = partidaActual->listaPoblaciones;

    while( pActual != nullptr ){
        Especie* eActual = pActual->listaEspecies;

        while( eActual != nullptr ){
            verificarRangoFactores(eActual, partidaActual->bioma);
            eActual = eActual->sgteEspecie;
        }

        pActual = pActual->sgtePoblacion;
    }
}

#endif // SIMULADOR_H