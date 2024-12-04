#ifndef CRUD_PARTIDAS_HPP
#define CRUD_PARTIDAS_HPP

#include "Partida.hpp"
#include "crudDatos.hpp"

void almacenarEspecies(Especie* listaEspecies, ofstream& archivo) {
    archivo << "ESPECIES" << endl;
    while (listaEspecies != nullptr) {
        archivo << "ID Especie = " << listaEspecies->id << endl;
        archivo << "Tipo Especie = " << listaEspecies->tipoEspecie << endl;
        archivo << "Vida = " << listaEspecies->vida << endl;

        // Almacenar los hijos si es necesario
        Especie* hijo = listaEspecies->primerHijo;
        while (hijo != nullptr) {
            archivo << "Hijo de Especie ID = " << hijo->id << endl;
            hijo = hijo->sgteHijo;
        }

        listaEspecies = listaEspecies->sgteEspecie;
    }
}

void almacenarPoblaciones(Poblacion* listaPoblaciones, ofstream& archivo) {
    archivo << "POBLACIONES" << endl;
    while (listaPoblaciones != nullptr) {
        archivo << "ID Poblacion = " << listaPoblaciones->id << endl;
        archivo << "Tipo Especie = " << listaPoblaciones->tipoEspecie << endl;
        archivo << "Nombre Especie = " << listaPoblaciones->nombreEspecie << endl;
        archivo << "Contador Especies = " << listaPoblaciones->contadorEspecies << endl;

        // Guardar las especies dentro de esta población
        almacenarEspecies(listaPoblaciones->listaEspecies, archivo);
        
        listaPoblaciones = listaPoblaciones->sgtePoblacion;
    }
}

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
    
    // Almacenar poblaciones y especies
    almacenarPoblaciones(partida->listaPoblaciones, archivo);

    archivo.close();
}

Especie* cargarEspecies(string nombreEspecie, ifstream& archivo) {
    Especie* listaEspecies = nullptr;
    Especie* ultimaEspecie = nullptr;

    string linea, vida;

    while (getline(archivo, linea)) {
        if (linea.find("ID Especie") != string::npos) { // Procesar cada especie
            Especie* nuevaEspecie = new Especie();
            nuevaEspecie->id = linea.substr(linea.find('=') + 2); // Extraer ID

            getline(archivo, linea);
            nuevaEspecie->tipoEspecie = linea.substr(linea.find('=') + 2); // Tipo

            getline(archivo, linea);
            if (linea.find("Vida") != string::npos) {
                vida = linea.substr(linea.find('=') + 2);
                nuevaEspecie->vida = stoi(vida); // Convertir vida a entero
            } else {
                cerr << "Error al leer Vida: " << linea << endl;
            }

            nuevaEspecie->datosEspecie = extraerDatosEspecie(nuevaEspecie->tipoEspecie, nombreEspecie);

            // IMPRESIÓN: MOSTRAR INFORMACIÓN DE LA ESPECIE CARGADA
            cout << "Cargando especie: ID = " << nuevaEspecie->id 
                 << ", Tipo = " << nuevaEspecie->tipoEspecie 
                 << ", Vida = " << nuevaEspecie->vida
                 << ", Datos especie = " << to_string(nuevaEspecie->datosEspecie == nullptr) << endl;

            if (ultimaEspecie == nullptr) {
                listaEspecies = nuevaEspecie;
            } else {
                ultimaEspecie->sgteEspecie = nuevaEspecie;
            }
            ultimaEspecie = nuevaEspecie;
        } else if (linea.find("POBLACIONES") != string::npos || linea.empty()) {
            // Salir si se encuentra el siguiente bloque
            break;
        }
    }

    return listaEspecies;
}

Poblacion* cargarPoblaciones(ifstream& archivo) {
    Poblacion* listaPoblaciones = nullptr;
    Poblacion* ultimaPoblacion = nullptr;

    string linea, contadorEspecies;

    while (getline(archivo, linea)) {
        if (linea.find("ID Poblacion") != string::npos) { // Procesar cada población
            Poblacion* nuevaPoblacion = new Poblacion();
            nuevaPoblacion->id = linea.substr(linea.find('=') + 2);

            getline(archivo, linea);
            nuevaPoblacion->tipoEspecie = linea.substr(linea.find('=') + 2);

            getline(archivo, linea);
            nuevaPoblacion->nombreEspecie = linea.substr(linea.find('=') + 2);

            getline(archivo, linea);
            if (linea.find("Contador Especies") != string::npos) {
                contadorEspecies = linea.substr(linea.find('=') + 2);
                nuevaPoblacion->contadorEspecies = stoi(contadorEspecies);
            } else {
                cerr << "Error al leer Contador Especies: " << linea << endl;
            }

            // IMPRESIÓN: MOSTRAR INFORMACIÓN DE LA POBLACIÓN CARGADA
            cout << "Cargando población: ID = " << nuevaPoblacion->id 
                 << ", Tipo = " << nuevaPoblacion->tipoEspecie 
                 << ", Nombre = " << nuevaPoblacion->nombreEspecie 
                 << ", Contador Especies = " << nuevaPoblacion->contadorEspecies << endl;

            // Cargar especies de la población
            nuevaPoblacion->listaEspecies = cargarEspecies(nuevaPoblacion->nombreEspecie, archivo);

            if (ultimaPoblacion == nullptr) {
                listaPoblaciones = nuevaPoblacion;
            } else {
                ultimaPoblacion->sgtePoblacion = nuevaPoblacion;
            }
            ultimaPoblacion = nuevaPoblacion;
        } else if (linea.find("INFO DE LA PARTIDA") != string::npos || linea.empty()) {
            // Salir si se encuentra el final del bloque
            break;
        }
    }

    return listaPoblaciones;
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

    // Cargar las poblaciones
    partida->listaPoblaciones = cargarPoblaciones(archivo);

    archivo.close();

    getch();
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
