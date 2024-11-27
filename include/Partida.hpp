#ifndef PARTIDA_HPP
#define PARTIDA_HPP

#include "Tiempo.hpp"
#include "Bioma.hpp"

using namespace std;

struct Partida {
    string nombreJugador;
    Tiempo tiempoInicio;
    Tiempo tiempoTranscurrido;
    Bioma* bioma;
    string archivoInfo;
    string archivoEventos;
    string archivoConteoEventos;
};

Partida partidaActual;

void almacenarPartida(Partida partida){
    ofstream archivo( partida.archivoInfo );

    archivo << "INFO DE LA PARTIDA" << endl;
    archivo << "*******************************************************************************************************" << endl;
    archivo << partida.nombreJugador << endl;
    archivo << formatearTiempo( partida.tiempoInicio ) << endl;
    archivo << formatearTiempo( partida.tiempoTranscurrido ) << endl;
    archivo << partida.bioma->nombre << endl;
    archivo << partida.bioma->nivelOxigeno << endl;
    archivo << partida.bioma->nivelSalinidad << endl;
    archivo << partida.bioma->nivelTemperatura << endl;
    archivo << partida.bioma->nivelContaminacion << endl;
    archivo << partida.archivoEventos << endl;
    archivo << partida.archivoConteoEventos << endl;

    archivo.close();
}
    
Partida cargarPartida(string archivoInfo) {
    Partida partida;
    ifstream archivo(archivoInfo);
    string linea;

    if (!archivo) {
        cout << "Error al cargar la partida..." << endl;
        return partida;
    }

    // Ignorar encabezado
    getline(archivo, linea); // INFO DE LA PARTIDA
    getline(archivo, linea); // *******************************************************************************************************

    // Leer el resto de los datos en orden
    getline(archivo, partida.nombreJugador); // Nombre del jugador

    string strTiempoInicio, strTiempoTranscurrido;

    getline(archivo, strTiempoInicio);               // Tiempo de inicio (formateado como string)
    getline(archivo, strTiempoTranscurrido);         // Tiempo transcurrido (formateado como string)

    // Convertir las cadenas de tiempo a la estructura Tiempo
    partida.tiempoInicio = desformatearTiempo(strTiempoInicio);
    partida.tiempoTranscurrido = desformatearTiempo(strTiempoTranscurrido);

    // Crear un nuevo objeto Bioma para cargar sus datos
    partida.bioma = new Bioma();

    // Leer el nombre del bioma (con espacios si los hay)
    getline(archivo, partida.bioma->nombre);         // Nombre del bioma

    string nivelOxigeno, nivelSalinidad, nivelTemperatura, nivelContaminacion;

    // Leer los niveles de manera correcta, evitando problemas de espacio
    getline(archivo, nivelOxigeno);                  // Nivel de oxígeno (como string)
    getline(archivo, nivelSalinidad);                // Nivel de salinidad (como string)
    getline(archivo, nivelTemperatura);              // Nivel de temperatura (como string)
    getline(archivo, nivelContaminacion);            // Nivel de contaminación (como string)

    // Convertir los niveles de string a float
    partida.bioma->nivelOxigeno = stof(nivelOxigeno);
    partida.bioma->nivelSalinidad = stof(nivelSalinidad);
    partida.bioma->nivelTemperatura = stof(nivelTemperatura);
    partida.bioma->nivelContaminacion = stof(nivelContaminacion);

    // Leer archivos asociados
    getline(archivo, partida.archivoEventos);
    getline(archivo, partida.archivoConteoEventos);

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
