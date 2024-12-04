#ifndef PARTIDA_HPP
#define PARTIDA_HPP

#include "Tiempo.hpp"
#include "Bioma.hpp"
#include "Poblacion.hpp"

using namespace std;

struct Partida {
    string nombreJugador;
    Tiempo tiempoInicio;
    Tiempo tiempoTranscurrido;
    string archivoInfo;
    string archivoEventos;
    string archivoConteoEventos;
    
    Bioma* bioma = nullptr;
    Poblacion* listaPoblaciones = nullptr;
};

Partida* partidaActual = nullptr;

void almacenarPartida(Partida* partida) {
    ofstream archivo(partida->archivoInfo);

    archivo << "INFO DE LA PARTIDA" << endl;
    archivo << "*******************************************************************************************************" << endl;
    archivo << "Nombre jugador = " << partida->nombreJugador << endl;
    archivo << "Tiempo inicio = " << formatearTiempo(partida->tiempoInicio) << endl;
    archivo << "Tiempo transcurrido = " << formatearTiempo(partida->tiempoTranscurrido) << endl;
    archivo << "Bioma = " << partida->bioma->nombre << endl;
    archivo << "Nivel oxígeno = " << partida->bioma->nivelOxigeno << endl;
    archivo << "Nivel salinidad = " << partida->bioma->nivelSalinidad << endl;
    archivo << "Nivel temperatura = " << partida->bioma->nivelTemperatura << endl;
    archivo << "Nivel contaminación = " << partida->bioma->nivelContaminacion << endl;
    archivo << "Archivo eventos = " << partida->archivoEventos << endl;
    archivo << "Archivo conteo eventos = " << partida->archivoConteoEventos << endl;

    archivo.close();
}
    
Partida* cargarPartida(string archivoInfo) {
    Partida* partida = new Partida();
    ifstream archivo(archivoInfo);
    string linea;

    if (!archivo) {
        cout << "Error al cargar la partida..." << endl;
        return partida;
    }

    // Ignorar encabezado
    getline(archivo, linea); // INFO DE LA PARTIDA
    getline(archivo, linea); // *******************************************************************************************************

    // Leer cada línea con formato "Etiqueta = Valor"
    getline(archivo, linea);
    partida->nombreJugador = linea.substr(linea.find('=') + 2);

    string strTiempoInicio, strTiempoTranscurrido;

    getline(archivo, linea);
    strTiempoInicio = linea.substr(linea.find('=') + 2);

    getline(archivo, linea);
    strTiempoTranscurrido = linea.substr(linea.find('=') + 2);

    // Convertir las cadenas de tiempo a la estructura Tiempo
    partida->tiempoInicio = desformatearTiempo(strTiempoInicio);
    partida->tiempoTranscurrido = desformatearTiempo(strTiempoTranscurrido);

    // Crear un nuevo objeto Bioma para cargar sus datos
    partida->bioma = new Bioma();

    getline(archivo, linea);
    partida->bioma->nombre = linea.substr(linea.find('=') + 2);

    string nivelOxigeno, nivelSalinidad, nivelTemperatura, nivelContaminacion;

    // Leer niveles con etiquetas y convertirlos a float
    getline(archivo, linea);
    nivelOxigeno = linea.substr(linea.find('=') + 2);

    getline(archivo, linea);
    nivelSalinidad = linea.substr(linea.find('=') + 2);

    getline(archivo, linea);
    nivelTemperatura = linea.substr(linea.find('=') + 2);

    getline(archivo, linea);
    nivelContaminacion = linea.substr(linea.find('=') + 2);

    partida->bioma->nivelOxigeno = stof(nivelOxigeno);
    partida->bioma->nivelSalinidad = stof(nivelSalinidad);
    partida->bioma->nivelTemperatura = stof(nivelTemperatura);
    partida->bioma->nivelContaminacion = stof(nivelContaminacion);

    // Leer archivos asociados
    getline(archivo, linea);
    partida->archivoEventos = linea.substr(linea.find('=') + 2);

    getline(archivo, linea);
    partida->archivoConteoEventos = linea.substr(linea.find('=') + 2);

    archivo.close();
    return partida;
}


bool esArchivoValido(const string& nombreArchivo) {
    // Verifica si el nombre tiene el formato "infoPartida[nombre].txt"
    return nombreArchivo.substr(0, 12) == "infoPartida[" && 
           nombreArchivo[nombreArchivo.size() - 4] == '.' &&
           nombreArchivo.substr(nombreArchivo.size() - 3) == "txt" && 
           nombreArchivo.find(']') != string::npos;  // Asegura que hay un corchete de cierre
}

vector<string> obtenerPartidas(){
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;

    vector<string> partidas;
    string ruta = "./*"; // Ruta con comodín para buscar todos los archivos
    hFind = FindFirstFile(ruta.c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        cout << "No se pudieron listar los archivos en la ruta especificada." << endl;
        getch();
        return partidas;
    }

    do {
        string nombreArchivo = findFileData.cFileName;

        // Ignorar directorios
        if ( !(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ) {
            if ( esArchivoValido(nombreArchivo) ) {
                partidas.push_back( nombreArchivo );
            }
        }

    } while (FindNextFile(hFind, &findFileData) != 0);

    // Cerrar el handle
    FindClose(hFind);
    return partidas;
}

#endif // PARTIDA_HPP
