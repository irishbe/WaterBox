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

void crearPartida(){
    Partida nuevaPartida;

    int x = 10, y = 3, opcion = -1;
    y += imprimirTexto( tituloWaterBox(), x, y, true) + 3;

    fflush(stdin);
    moverCursor(x, y); cout << "INGRESE SU NOMBRE DE JUGADOR:";
    moverCursor(x, y + 1); getline(cin, nuevaPartida.nombreJugador);
    
    nuevaPartida.tiempoInicio = getTiempoActual();
    nuevaPartida.tiempoTranscurrido = calcularTiempoTranscurrido( nuevaPartida.tiempoInicio );
    nuevaPartida.archivoInfo = "infoPartida[" + nuevaPartida.nombreJugador + "].txt";
    nuevaPartida.archivoEventos = "eventosPartida[" + nuevaPartida.nombreJugador + "].txt";
    nuevaPartida.archivoConteoEventos = "conteoEventosPartida[" + nuevaPartida.nombreJugador + "].txt";

    // Seleccionando el bioma
    vector<string> dibujos = {
        ASCIIBiomaArrecifeCoral(),
        ASCIIBiomaOceanoProfundo(),
        "Marismas salinas"
    };
        
    opcion = seleccionarConDibujos(dibujos, tituloBiomas(), "SELECCIONE UN BIOMA");
    system("cls");

    switch(opcion){
        case 1: nuevaPartida.bioma = extraerBioma("Arrecifes de Coral"); fondoRGB(0, 109, 198); break;
        case 2: nuevaPartida.bioma = extraerBioma("Oceano profundo"); fondoRGB(2, 4, 37); break;
        case 3: nuevaPartida.bioma = extraerBioma("Marismas salinas"); break;
        case -1: break;
    }

    almacenarPartida(nuevaPartida);
    partidaActual = nuevaPartida;
}

void seleccionarPartida(){
    string opcion = seleccionarConFlechas( obtenerPartidas(), tituloWaterBox(), "SELECCIONE UNA PARTIDA");

    if( opcion.empty() ){
        return;
    }

    partidaActual = cargarPartida(opcion);
}

// Función para iniciar el simulador
void iniciarSimulador() {

    if( partidaActual.nombreJugador.empty() ){
        menuPartidasSimulador();
    }

    menuOpcionesSimulador();
}

void menuPartidasSimulador(){
    int opcion = -1;

    vector<string> dibujos = {
        "NUEVA PARTIDA",
        "CARGAR PARTIDA"
    };

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
            case -1: break;
        }

        system("cls");

    } while (opcion != -1);

    fondoRGB(7, 25, 82);
}

void mostrarTodosCuadros() {
    cout << "Partida: " << partidaActual.nombreJugador << endl;
    cout << "Bioma: " << partidaActual.bioma->nombre << endl << endl;

    // Cálculo de los porcentajes según los valores ingresados
    int porcentajeOxigeno = (partidaActual.bioma->nivelOxigeno - oxigenoMin) * 100 / (oxigenoMax - oxigenoMin);
    int porcentajeSalinidad = (partidaActual.bioma->nivelSalinidad - salinidadMin) * 100 / (salinidadMax - salinidadMin);
    int porcentajeTemperatura = (partidaActual.bioma->nivelTemperatura - temperaturaMin) * 100 / (temperaturaMax - temperaturaMin);
    int porcentajeContaminacion = (partidaActual.bioma->nivelTemperatura - contaminacionMin) * 100 / (contaminacionMax - contaminacionMin);

    // Mostrar barras de progreso
    imprimirBarra("Oxígeno", porcentajeOxigeno); cout << "\t";
    imprimirBarra("Salinidad", porcentajeSalinidad); cout << "\t";
    imprimirBarra("Temperatura", porcentajeTemperatura); cout << "\t";
    imprimirBarra("Contaminación", porcentajeContaminacion); cout << endl;
}

void imprimirPoblaciones() {
    Poblacion* poblacionActual = listaPoblaciones;
    
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
    
    vector<string> dibujos = {
        ASCIIOxigeno(),
        ASCIISalinidad(),
        ASCIIModificarFactores(),
        ASCIIContaminacion()
    };
    
    do {
        
        opcion = seleccionarConDibujos( dibujos, tituloModificarFactores(), "SELECCIONE UN FACTOR A MODIFICAR");

        switch (opcion) {
            case 1: // Oxígeno
                cout << "Ingrese el nivel de oxígeno (Mín. 0 / Máx. 14 mg/L): ";
                cin >> partidaActual.bioma->nivelOxigeno;
                if (partidaActual.bioma->nivelOxigeno < oxigenoMin || partidaActual.bioma->nivelOxigeno > oxigenoMax) {
                    cout << "Valor fuera de rango. Debe estar entre " << oxigenoMin << " y " << oxigenoMax << " mg/L." << endl;
                    getch();
                }
                break;
            case 2: // Salinidad
                cout << "Ingrese el nivel de salinidad (Mín. 0 / Máx. 330 ups): ";
                cin >> partidaActual.bioma->nivelSalinidad;
                if (partidaActual.bioma->nivelSalinidad < salinidadMin || partidaActual.bioma->nivelSalinidad > salinidadMax) {
                    cout << "Valor fuera de rango. Debe estar entre " << salinidadMin << " y " << salinidadMax << " ups." << endl;
                    getch();
                }
                break;
            case 3: // Temperatura
                cout << "Ingrese la temperatura (Mín. 0 / Máx. 40 °C): ";
                cin >> partidaActual.bioma->nivelTemperatura;
                if (partidaActual.bioma->nivelTemperatura < temperaturaMin || partidaActual.bioma->nivelTemperatura > temperaturaMax) {
                    cout << "Valor fuera de rango. Debe estar entre " << temperaturaMin << " y " << temperaturaMax << " °C." << endl;
                    getch();
                }
                break;
            case 4: // Contaminación
                cout << "Ingrese el nivel de contaminación (Mín. 0 / Máx. 100 %): ";
                cin >> partidaActual.bioma->nivelContaminacion;
                if (partidaActual.bioma->nivelContaminacion < contaminacionMin || partidaActual.bioma->nivelContaminacion > contaminacionMax) {
                    cout << "Valor fuera de rango. Debe estar entre " << contaminacionMin << " y " << contaminacionMax << " %." << endl;
                    getch();
                }
                break;
            case -1: break;
        }

        registrarEvento(MODIFICAR_FACTORES, partidaActual);
        system("cls");

    } while (opcion != -1);
}

#endif // SIMULADOR_H