#ifndef EVENTO_HPP
#define EVENTO_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Especie.hpp"
#include "Tiempo.hpp"
#include "Bioma.hpp"

using namespace std;

// Enum para los tipos de eventos
enum TipoEvento {
    AGREGAR_ESPECIE,
    ELIMINAR_ESPECIE,
    MODIFICAR_FACTORES,
    REPRODUCCION,
    DEPREDACION,
    CAZA,
    ENFERMEDAD,
    CREAR_ESPECIE_ADMIN,
    ELIMINAR_ESPECIE_ADMIN,
    EDITAR_ESPECIE_ADMIN,
    CREAR_BIOMA_ADMIN,
    ELIMINAR_BIOMA_ADMIN,
    EDITAR_BIOMA_ADMIN
};

string TipoEventoToString(TipoEvento tipo) {
    switch (tipo) {
        case ELIMINAR_ESPECIE_ADMIN: return "ELIMINAR_ESPECIE_ADMIN";
        case AGREGAR_ESPECIE: return "AGREGAR_ESPECIE";
        case ELIMINAR_ESPECIE: return "ELIMINAR_ESPECIE";
        case MODIFICAR_FACTORES: return "MODIFICAR_FACTORES";
        case REPRODUCCION: return "REPRODUCCION";
        case DEPREDACION: return "DEPREDACION";
        case CAZA: return "CAZA";
        case ENFERMEDAD: return "ENFERMEDAD";
        case CREAR_ESPECIE_ADMIN: return "CREAR_ESPECIE_ADMIN";
        case EDITAR_ESPECIE_ADMIN: return "EDITAR_ESPECIE_ADMIN";
        case CREAR_BIOMA_ADMIN: return "CREAR_BIOMA_ADMIN";
        case ELIMINAR_BIOMA_ADMIN: return "ELIMINAR_BIOMA_ADMIN";
        case EDITAR_BIOMA_ADMIN: return "EDITAR_BIOMA_ADMIN";
        default: return "DESCONOCIDO";
    }
}

// Estructura del evento
struct Evento {
    TipoEvento tipo;
    string descripcion;
    Tiempo tiempo;
    Bioma* biomaOcurrencia;
    Especie* especie1;
    Especie* especie2;
    Evento* sgteEvento;
};

// Listas globales para la pila y las colas
Evento* pilaEventos = nullptr;
Evento* colaEventos = nullptr;

// Archivo de eventos .txt
const string ARCHIVO_EVENTOS_HOY = "eventos[" + formatearFecha( getTiempoActual() ) + "].txt";
const string ARCHIVO_CONTEO_EVENTOS = "contadorEventos.txt";

// Función para agregar evento a la pila
void push(Evento*& pilaEventos, Evento* nuevoEvento) {
    nuevoEvento->sgteEvento = pilaEventos;
    pilaEventos = nuevoEvento;
}

// Función para remover el último evento de la pila
Evento* pop(Evento*& pilaEventos) {
    if (!pilaEventos) return nullptr;

    Evento* eventoEliminado = pilaEventos;
    pilaEventos = pilaEventos->sgteEvento;
    eventoEliminado->sgteEvento = nullptr;

    return eventoEliminado;
}

// Función para agregar evento al final de la cola
void enqueue(Evento*& colaEventos, Evento* nuevoEvento) {
    if (!colaEventos) {
        colaEventos = nuevoEvento;
    } else {
        Evento* temp = colaEventos;
        while (temp->sgteEvento) {
            temp = temp->sgteEvento;
        }
        temp->sgteEvento = nuevoEvento;
    }
}

// Funcion para ordenar los eventos por fecha
void ordenarEventosPorTiempo(vector<Evento>& eventos) {
    int n = eventos.size();
    
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (!compararFecha(eventos[j].descripcion, eventos[j + 1].descripcion)) {
                Evento temp = eventos[j];
                eventos[j] = eventos[j + 1];
                eventos[j + 1] = temp;
            }
        }
    }
}

// Juntar y extrer todos los eventos de la cola y la pila ordenados por tiempo
vector<Evento> eventosPilaCola(){
    vector<Evento> eventos;

    // Agregar eventos de la pila al vector
    Evento* temp = pilaEventos;

    while (temp != nullptr) {
        eventos.push_back(*temp);
        temp = temp->sgteEvento;
    }

    // Agregar eventos de la cola al vector
    temp = colaEventos;
    
    while (temp != nullptr) {
        eventos.push_back(*temp);
        temp = temp->sgteEvento;
    }

    ordenarEventosPorTiempo(eventos);

    return eventos;
}

void actualizarConteoEventos(Evento *nuevoEvento) {
    ifstream archivoEventos(ARCHIVO_EVENTOS_HOY);
    string tipoEventoStr1 = "Tipo de Evento: " + TipoEventoToString(nuevoEvento->tipo); 
    string linea;
    int contadorEvento = 0;

    // Verificar si se pudo abrir el archivo de eventos
    if (!archivoEventos) {
        cerr << "No se pudo abrir el archivo " << ARCHIVO_EVENTOS_HOY << endl;
        return;
    }

    // Contar el número de eventos del tipo especificado
    while (getline(archivoEventos, linea)) {
        if (linea.substr(0, tipoEventoStr1.length()) == tipoEventoStr1) {
            contadorEvento++;
        }
    }

    archivoEventos.close();

    // Verificar si el archivo de conteo existe
    ifstream archivoConteoLectura(ARCHIVO_CONTEO_EVENTOS);
    bool archivoExistente = archivoConteoLectura.good();
    archivoConteoLectura.close();

    if (!archivoExistente) {
        // Si el archivo no existe, lo creamos y escribimos los valores iniciales
        ofstream archivoConteoEscritura(ARCHIVO_CONTEO_EVENTOS);
        if (!archivoConteoEscritura) {
            cerr << "No se pudo crear el archivo " << ARCHIVO_CONTEO_EVENTOS << endl;
            return;
        }

        archivoConteoEscritura << "Conteo de Tipos de Eventos" << endl;
        archivoConteoEscritura << "Tipo de Evento " << TipoEventoToString(AGREGAR_ESPECIE) << " = 0" << endl;
        archivoConteoEscritura << "Tipo de Evento " << TipoEventoToString(ELIMINAR_ESPECIE) << " = 0" << endl;
        archivoConteoEscritura << "Tipo de Evento " << TipoEventoToString(MODIFICAR_FACTORES) << " = 0" << endl;
        archivoConteoEscritura << "Tipo de Evento " << TipoEventoToString(REPRODUCCION) << " = 0" << endl;
        archivoConteoEscritura << "Tipo de Evento " << TipoEventoToString(DEPREDACION) << " = 0" << endl;
        archivoConteoEscritura << "Tipo de Evento " << TipoEventoToString(CAZA) << " = 0" << endl;
        archivoConteoEscritura << "Tipo de Evento " << TipoEventoToString(ENFERMEDAD) << " = 0" << endl;
        archivoConteoEscritura << "Tipo de Evento " << TipoEventoToString(CREAR_ESPECIE_ADMIN) << " = 0" << endl;
        archivoConteoEscritura << "Tipo de Evento " << TipoEventoToString(ELIMINAR_ESPECIE_ADMIN) << " = 0" << endl;
        archivoConteoEscritura << "Tipo de Evento " << TipoEventoToString(EDITAR_ESPECIE_ADMIN) << " = 0" << endl;
        archivoConteoEscritura << "Tipo de Evento " << TipoEventoToString(CREAR_BIOMA_ADMIN) << " = 0" << endl;
        archivoConteoEscritura << "Tipo de Evento " << TipoEventoToString(ELIMINAR_BIOMA_ADMIN) << " = 0" << endl;
        archivoConteoEscritura << "Tipo de Evento " << TipoEventoToString(EDITAR_BIOMA_ADMIN) << " = 0" << endl;

        archivoConteoEscritura.close();
    }

    // Ahora, leemos el archivo existente y actualizamos el conteo
    ifstream archivoConteoLecturaActualizado(ARCHIVO_CONTEO_EVENTOS);
    string tipoEventoStr2 = "Tipo de Evento " + TipoEventoToString(nuevoEvento->tipo) + " = ";
    string contenido;

    while (getline(archivoConteoLecturaActualizado, linea)) {
        // Si la línea comienza con la cadena exacta
        if (linea.substr(0, tipoEventoStr2.length()) == tipoEventoStr2) {
            contenido += tipoEventoStr2 + to_string(contadorEvento) + "\n";
        } else {
            contenido += linea + "\n";
        }
    }

    archivoConteoLecturaActualizado.close();

    // Escribir el contenido actualizado en el archivo
    ofstream archivoConteoEscritura(ARCHIVO_CONTEO_EVENTOS);
    if (!archivoConteoEscritura) {
        cerr << "No se pudo escribir en el archivo " << ARCHIVO_CONTEO_EVENTOS << endl;
        return;
    }
    archivoConteoEscritura << contenido;
    archivoConteoEscritura.close();
}

// Crear y escribir en "eventos[FECHA].txt"
void guardarEventoArchivo(Evento* nuevoEvento) {
    ofstream archivo(ARCHIVO_EVENTOS_HOY, ios::app);
    if (!archivo) {
        cerr << "Error al abrir el archivo" << endl;
        return;
    }

    archivo << "Tipo de Evento: " << TipoEventoToString(nuevoEvento->tipo) << endl;
    archivo << "Descripción: " << nuevoEvento->descripcion << endl;
    archivo << "Bioma de Ocurrencia: " << nuevoEvento->biomaOcurrencia->nombre << endl;
    if (nuevoEvento->especie1) archivo << "Especie 1: " << nuevoEvento->especie1->datosEspecie->nombreComun << endl;
    if (nuevoEvento->especie2) archivo << "Especie 2: " << nuevoEvento->especie2->datosEspecie->nombreComun << endl;
    archivo << "-----------------------" << endl;

    archivo.close();

    actualizarConteoEventos(nuevoEvento);
}

void registrarEvento(TipoEvento tipo, Bioma* bioma = nullptr, Especie* especie1 = nullptr, Especie* especie2 = nullptr) {
    Evento* nuevoEvento = new Evento;
    string descripcion = formatearTiempo( getTiempoActual() );

    // Generar la descripción del evento según el tipo
    switch (tipo) {
        case AGREGAR_ESPECIE:
            descripcion += " Agregaste una especie " + (especie1 ? especie1->datosEspecie->nombreComun : "") +
                           " al bioma " + bioma->nombre;
            break;
        case ELIMINAR_ESPECIE:
            descripcion += " Eliminaste una especie " + (especie1 ? especie1->datosEspecie->nombreComun : "") +
                           " del bioma " + bioma->nombre;
            break;
        case MODIFICAR_FACTORES:
            descripcion += " Modificaste los factores del bioma " + bioma->nombre + " " +
                           "[o:" + to_string(bioma->nivelOxigeno)       + "," +
                           "s:"  + to_string(bioma->nivelSalinidad)     + "," +
                           "t:"  + to_string(bioma->nivelTemperatura)   + "," +
                           "c:"  + to_string(bioma->nivelContaminacion) + "]";
            break;
        case CREAR_ESPECIE_ADMIN:
            descripcion += " Creaste una nueva especie " + (especie1 ? especie1->datosEspecie->nombreComun : "");
            break;
        case EDITAR_ESPECIE_ADMIN:
            descripcion += " Editaste la especie " + (especie1 ? especie1->datosEspecie->nombreComun : "");
            break;
        case ELIMINAR_ESPECIE_ADMIN:
            descripcion += " Eliminaste la especie " + (especie1 ? especie1->datosEspecie->nombreComun : "");
            break;
        case CREAR_BIOMA_ADMIN:
            descripcion += " Creaste un nuevo bioma " + bioma->nombre;
            break;
        case EDITAR_BIOMA_ADMIN:
            descripcion += " Editaste el bioma " + bioma->nombre;
            break;
        case ELIMINAR_BIOMA_ADMIN:
            descripcion += " Eliminaste el bioma " + bioma->nombre;
            break;
        default:
            descripcion += " Evento ??? registrado.";
            break;
    }

    // Configurar el evento
    nuevoEvento->tipo = tipo;
    nuevoEvento->descripcion = descripcion;
    nuevoEvento->biomaOcurrencia = bioma;
    nuevoEvento->especie1 = especie1;
    nuevoEvento->especie2 = especie2;
    nuevoEvento->sgteEvento = nullptr;
    
    if( nuevoEvento->tipo == AGREGAR_ESPECIE || nuevoEvento->tipo == ELIMINAR_ESPECIE || nuevoEvento->tipo == MODIFICAR_FACTORES ){
        push(pilaEventos, nuevoEvento);
    }else{
        enqueue(colaEventos, nuevoEvento);
    }

    guardarEventoArchivo(nuevoEvento);
}

// Función para mostrar los eventos registrados en pantalla
void mostrarEventos() {
    cout << "\nHistorial de eventos :" << endl << endl;

    // Mostramos los eventos en el orden adecuado
    vector<Evento> eventos = eventosPilaCola();
    for(int i=0; i < eventos.size(); i++) {
        cout << eventos[i].descripcion << endl;
    }
}

#endif // EVENTO_HPP