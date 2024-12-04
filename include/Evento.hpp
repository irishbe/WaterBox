#ifndef EVENTO_HPP
#define EVENTO_HPP

#include <random>
#include "utilidades.hpp"
#include "Partida.hpp"

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

    Partida* partida = nullptr;
    Especie* especie1 = nullptr;
    Especie* especie2 = nullptr;
    Especie* especie3 = nullptr;
    Evento* sgteEvento = nullptr;
};

// Listas globales para la pila y las colas
Evento* pilaEventos = nullptr;
Evento* colaEventos = nullptr;

// Archivo de eventos .txt
const string ARCHIVO_CONTEO_GENERAL = "contadorEventosGeneral.txt";

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

void almacenarConteoGeneral(Evento *nuevoEvento) {
    string tipoEventoStr = TipoEventoToString(nuevoEvento->tipo) + " = ";
    string linea, contenido;

    // Abrir el archivo para lectura, si no existe lo inicializamos
    ifstream archivoLectura(ARCHIVO_CONTEO_GENERAL);

    if (!archivoLectura) {
        // Crear archivo con valores iniciales
        ofstream archivoEscritura(ARCHIVO_CONTEO_GENERAL);

        archivoEscritura << "CONTEO GENERAL DE LOS EVENTOS OCURRIDOS EN EL SIMULADOR" << endl;
        archivoEscritura << "*******************************************************************************************************" << endl;
        archivoEscritura << TipoEventoToString(AGREGAR_ESPECIE) << " = 0" << endl;
        archivoEscritura << TipoEventoToString(ELIMINAR_ESPECIE) << " = 0" << endl;
        archivoEscritura << TipoEventoToString(MODIFICAR_FACTORES) << " = 0" << endl;
        archivoEscritura << TipoEventoToString(REPRODUCCION) << " = 0" << endl;
        archivoEscritura << TipoEventoToString(DEPREDACION) << " = 0" << endl;
        archivoEscritura << TipoEventoToString(CAZA) << " = 0" << endl;
        archivoEscritura << TipoEventoToString(ENFERMEDAD) << " = 0" << endl;
        archivoEscritura << TipoEventoToString(CREAR_ESPECIE_ADMIN) << " = 0" << endl;
        archivoEscritura << TipoEventoToString(ELIMINAR_ESPECIE_ADMIN) << " = 0" << endl;
        archivoEscritura << TipoEventoToString(EDITAR_ESPECIE_ADMIN) << " = 0" << endl;
        archivoEscritura << TipoEventoToString(CREAR_BIOMA_ADMIN) << " = 0" << endl;
        archivoEscritura << TipoEventoToString(ELIMINAR_BIOMA_ADMIN) << " = 0" << endl;
        archivoEscritura << TipoEventoToString(EDITAR_BIOMA_ADMIN) << " = 0" << endl;

        archivoEscritura.close();

        // Leer el archivo inicializado para actualizar contenido
        archivoLectura.open(ARCHIVO_CONTEO_GENERAL);
    }

    // Leer todo el archivo y actualizar el conteo
    while (getline(archivoLectura, linea)) {
        if (linea.find(tipoEventoStr) == 0) { // Encontrar el tipo de evento
            int valorActual = stoi(linea.substr(tipoEventoStr.size())); // Extraer valor actual
            linea = tipoEventoStr + to_string(valorActual + 1);         // Incrementar valor
        }
        contenido += linea + "\n"; // Guardar la línea (modificada o no)
    }
    archivoLectura.close();

    // Escribir el contenido actualizado
    ofstream archivoEscritura(ARCHIVO_CONTEO_GENERAL);
    archivoEscritura << contenido;
    archivoEscritura.close();
}

void almacenarConteoPartida(Evento *nuevoEvento) {
    string tipoEventoStr = TipoEventoToString(nuevoEvento->tipo) + " = ";
    string linea, contenido;

    // Abrir el archivo para lectura, si no existe lo inicializamos
    ifstream archivoLectura(nuevoEvento->partida->archivoConteoEventos);

    if (!archivoLectura) {
        // Crear archivo con valores iniciales
        ofstream archivoEscritura(nuevoEvento->partida->archivoConteoEventos);

        archivoEscritura << "CONTEO DE EVENTOS EN LA PARTIDA " << nuevoEvento->partida->nombreJugador << endl;
        archivoEscritura << "*******************************************************************************************************" << endl;
        archivoEscritura << TipoEventoToString(AGREGAR_ESPECIE) << " = 0" << endl;
        archivoEscritura << TipoEventoToString(ELIMINAR_ESPECIE) << " = 0" << endl;
        archivoEscritura << TipoEventoToString(MODIFICAR_FACTORES) << " = 0" << endl;
        archivoEscritura << TipoEventoToString(REPRODUCCION) << " = 0" << endl;
        archivoEscritura << TipoEventoToString(DEPREDACION) << " = 0" << endl;
        archivoEscritura << TipoEventoToString(CAZA) << " = 0" << endl;
        archivoEscritura << TipoEventoToString(ENFERMEDAD) << " = 0" << endl;
        archivoEscritura << TipoEventoToString(CREAR_ESPECIE_ADMIN) << " = 0" << endl;
        archivoEscritura << TipoEventoToString(ELIMINAR_ESPECIE_ADMIN) << " = 0" << endl;
        archivoEscritura << TipoEventoToString(EDITAR_ESPECIE_ADMIN) << " = 0" << endl;
        archivoEscritura << TipoEventoToString(CREAR_BIOMA_ADMIN) << " = 0" << endl;
        archivoEscritura << TipoEventoToString(ELIMINAR_BIOMA_ADMIN) << " = 0" << endl;
        archivoEscritura << TipoEventoToString(EDITAR_BIOMA_ADMIN) << " = 0" << endl;

        archivoEscritura.close();

        // Reabrir para lectura
        archivoLectura.open(nuevoEvento->partida->archivoConteoEventos);
    }

    // Leer todo el archivo y actualizar el conteo
    while (getline(archivoLectura, linea)) {
        if (linea.find(tipoEventoStr) == 0) { // Encontrar el tipo de evento
            int valorActual = stoi(linea.substr(tipoEventoStr.size())); // Extraer valor actual
            linea = tipoEventoStr + to_string(valorActual + 1);         // Incrementar valor
        }
        contenido += linea + "\n"; // Guardar la línea (modificada o no)
    }
    archivoLectura.close();

    // Escribir el contenido actualizado
    ofstream archivoEscritura(nuevoEvento->partida->archivoConteoEventos);
    archivoEscritura << contenido;
    archivoEscritura.close();
}

// Almacenar eventos en los archivos de partida y general
void almacenarEventos(Evento* nuevoEvento) {
    ofstream archivo( nuevoEvento->partida->archivoEventos, ios::app);
    
    if ( !archivo ) {
        archivo.close();
        archivo.open(nuevoEvento->partida->archivoEventos, ios::out);

        // Escribir encabezado
        archivo << "PARTIDA: " << nuevoEvento->partida->nombreJugador << endl;
        archivo << "FECHA DE LA PARTIDA: " << formatearFecha(nuevoEvento->partida->tiempoInicio) << endl;
        archivo << "BIOMA DE LA PARTIDA: " << nuevoEvento->partida->bioma << endl;
        archivo << "EVENTOS REGISTRADOS:" << endl;
        archivo << "*******************************************************************************************************" << endl;

        archivo.close();
        archivo.open(nuevoEvento->partida->archivoEventos, ios::app);
    }

    archivo << "Tipo de Evento: " << TipoEventoToString(nuevoEvento->tipo) << endl;
    archivo << "Descripción: " << nuevoEvento->descripcion << endl;
    if (nuevoEvento->especie1) archivo << "Especie 1: " << nuevoEvento->especie1->datosEspecie->nombreComun << endl;
    if (nuevoEvento->especie2) archivo << "Especie 2: " << nuevoEvento->especie2->datosEspecie->nombreComun << endl;
    archivo << "*******************************************************************************************************" << endl;

    archivo.close();

    almacenarConteoGeneral(nuevoEvento);
    almacenarConteoPartida(nuevoEvento);
}

void registrarEvento(TipoEvento tipo, Partida* partida = nullptr, Especie* especie1 = nullptr, Especie* especie2 = nullptr, Especie* especie3 = nullptr) {
    Evento* nuevoEvento = new Evento();
    string descripcion = formatearTiempo( getTiempoActual() );

    // Generar la descripción del evento según el tipo
    switch (tipo) {
        case AGREGAR_ESPECIE:
            descripcion += " Agregaste a la nueva especie " + especie1->datosEspecie->nombreComun +
                           " con ID " + especie1->id;
            break;
        case ELIMINAR_ESPECIE:
            descripcion += " Eliminaste a la especie " + especie1->datosEspecie->nombreComun +
                           " con ID " + especie1->id;
            break;
        case MODIFICAR_FACTORES:
            descripcion += " Modificaste los factores del bioma " + partida->bioma->nombre + " " +
                           "[o:" + to_string(partida->bioma->nivelOxigeno)       + "," +
                           "s:"  + to_string(partida->bioma->nivelSalinidad)     + "," +
                           "t:"  + to_string(partida->bioma->nivelTemperatura)   + "," +
                           "c:"  + to_string(partida->bioma->nivelContaminacion) + "]";
            break;
        case REPRODUCCION:
            descripcion += " Los " + especie1->datosEspecie->nombreComun + " con ID's " + 
                            especie1->id + " y " + especie2->id + " se reproducieron, " +
                            "generando a la especie con ID " + especie3->id;
            break;
        case ENFERMEDAD:
            descripcion += " La especie " + especie1->datosEspecie->nombreComun + " con ID " + 
                           especie1->id + " se ha enfermado por los factores del bioma, perdiendo " + 
                           to_string( 100 - especie1->vida) + " de vida";
            break;       
        case CREAR_ESPECIE_ADMIN:
            descripcion += " Creaste una nueva especie " + especie1->datosEspecie->nombreComun;
            break;
        case EDITAR_ESPECIE_ADMIN:
            descripcion += " Editaste la especie " + especie1->datosEspecie->nombreComun;
            break;
        case ELIMINAR_ESPECIE_ADMIN:
            descripcion += " Eliminaste la especie " + especie1->datosEspecie->nombreComun;
            break;
        case CREAR_BIOMA_ADMIN:
            descripcion += " Creaste un nuevo bioma " + partida->bioma->nombre;
            break;
        case EDITAR_BIOMA_ADMIN:
            descripcion += " Editaste el bioma " + partida->bioma->nombre;
            break;
        case ELIMINAR_BIOMA_ADMIN:
            descripcion += " Eliminaste el bioma " + partida->bioma->nombre;
            break;
        default:
            descripcion += " Evento ??? registrado.";
            break;
    }

    // Configurar el evento
    nuevoEvento->tipo = tipo;
    nuevoEvento->descripcion = descripcion;
    nuevoEvento->partida = partida;
    nuevoEvento->especie1 = especie1;
    nuevoEvento->especie2 = especie2;
    nuevoEvento->especie3 = especie3;
    nuevoEvento->sgteEvento = nullptr;
    
    if( nuevoEvento->tipo == AGREGAR_ESPECIE || nuevoEvento->tipo == ELIMINAR_ESPECIE || nuevoEvento->tipo == MODIFICAR_FACTORES ){
        push(pilaEventos, nuevoEvento);
    }else{
        enqueue(colaEventos, nuevoEvento);
    }

    almacenarEventos(nuevoEvento);
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

//FUNCION AÑADIDA KEVIN


// Función para generar un número aleatorio dentro de un rango
int generarNumeroAleatorio(int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

Poblacion* poblacionAleatoria(){
    if ( partidaActual->listaPoblaciones == nullptr ) return nullptr;

    Poblacion* poblacionAleatoria = partidaActual->listaPoblaciones;
    int contadorPoblaciones = 0;

    while (poblacionAleatoria != nullptr) {
        contadorPoblaciones++;
        poblacionAleatoria = poblacionAleatoria->sgtePoblacion;
    }

    
    poblacionAleatoria = partidaActual->listaPoblaciones;

    // Seleccionar una población aleatoria
    int indicePoblacion = generarNumeroAleatorio(0, contadorPoblaciones - 1);

    while (indicePoblacion-- > 0 && poblacionAleatoria) {
        poblacionAleatoria = poblacionAleatoria->sgtePoblacion;
    }

    return poblacionAleatoria;
}

Especie* especieAleatoria(Poblacion* poblacion){
    if (poblacion == nullptr) return nullptr;

    Especie* especieAleatoria = poblacion->listaEspecies;

    // Seleccionar una especie aleatoria
    int indiceEspecie = generarNumeroAleatorio(0, poblacion->contadorEspecies - 1);

    while (indiceEspecie-- > 0 && especieAleatoria) {
        especieAleatoria = especieAleatoria->sgteEspecie;
    }

    return especieAleatoria;
}

/*
//Función para seleccionar una especie aleatoria de una población
void generarEventoAleatorio() {
    Evento* eventoAleatorio = new Evento();

    switch (tipoEvento) {
        case AGREGAR_ESPECIE:
            vector<string> nombresEspecies;
            Especie* nuevaEspecie = new Especie();
            int index;

            if( generarNumeroAleatorio(1,2) == 1 ) ? nuevaEspecie->tipoEspecie = "Animal" : nuevaEspecie->tipoEspecie = "Vegetal";

            nombresEspecies = extraerNombres(nuevaEspecie->tipoEspecie);
            index = generarNumeroAleatorio(0, nombresEspecies.size() - 1);
            nuevaEspecie->datosEspecie = extraerDatosEspecie( nuevaEspecie->tipoEspecie, nombresEspecies[index] );

            agregarEspecieEnPoblacion(nuevaEspecie);
            registrarEvento(AGREGAR_ESPECIE, partidaActual, nuevaEspecie);
            break;

        case ELIMINAR_ESPECIE:
            especie1 = seleccionarEspecieAleatoria(poblacionSeleccionada);
            if (especie1) {
                descripcionEvento = "Especie eliminada aleatoriamente: " + especie1->datosEspecie->nombreComun;
                eliminarEspecie(); // Función existente para eliminar especie
                registrarEvento(ELIMINAR_ESPECIE, descripcionEvento, especie1, nullptr, poblacionSeleccionada->bioma);
                cout << descripcionEvento << endl;
            }
            break;

        case MODIFICAR_FACTORES:
            {
                int factor = generarNumeroAleatorio(0, 3);
                float nuevoValor;

                switch (factor) {
                    case 0: // Salinidad
                        nuevoValor = generarNumeroAleatorio(salinidadMin, salinidadMax);
                        partidaActual.bioma->nivelSalinidad = nuevoValor;
                        descripcionEvento = "Modificando salinidad a nivel " + to_string(nuevoValor) + " g/L.";
                        registrarEvento(MODIFICAR_FACTORES, descripcionEvento, nullptr, nullptr, partidaActual.bioma);
                        break;
                    case 1: // Oxígeno
                        nuevoValor = generarNumeroAleatorio(oxigenoMin, oxigenoMax);
                        partidaActual.bioma->nivelOxigeno = nuevoValor;
                        descripcionEvento = "Modificando oxígeno a nivel " + to_string(nuevoValor) + " mg/L.";
                        registrarEvento(MODIFICAR_FACTORES, descripcionEvento, nullptr, nullptr, partidaActual.bioma);
                        break;
                    case 2: // Temperatura
                        nuevoValor = generarNumeroAleatorio(temperaturaMin, temperaturaMax);
                        partidaActual.bioma->nivelTemperatura = nuevoValor;
                        descripcionEvento = "Modificando temperatura a nivel " + to_string(nuevoValor) + " °C.";
                        registrarEvento(MODIFICAR_FACTORES, descripcionEvento, nullptr, nullptr, partidaActual.bioma);
                        break;
                }
                cout << descripcionEvento << endl;
            }
            break;

        case REPRODUCCION:
            especie1 = seleccionarEspecieAleatoria(poblacionSeleccionada);
            especie2 = seleccionarEspecieAleatoria(poblacionSeleccionada);
            if (especie1 && especie2 && especie1 != especie2) {
                descripcionEvento = "Reproducción exitosa entre: " + especie1->datosEspecie->nombreComun +
                                    " (hembra) y " + especie2->datosEspecie->nombreComun + " (macho).";
                registrarEvento(REPRODUCCION, descripcionEvento, especie1, especie2, poblacionSeleccionada->bioma);
                cout << descripcionEvento << endl;
            }
            break;

        case DEPREDACION:
            especie1 = seleccionarEspecieAleatoria(poblacionSeleccionada);
            especie2 = seleccionarEspecieAleatoria(poblacionSeleccionada);
            if (especie1 && especie2 && especie1 != especie2) {
                descripcionEvento = "El depredador " + especie1->datosEspecie->nombreComun +
                                    " ha atacado a " + especie2->datosEspecie->nombreComun;
                registrarEvento(DEPREDACION, descripcionEvento, especie1, especie2, poblacionSeleccionada->bioma);
                cout << descripcionEvento << endl;
            }
            break;

        case CAZA:
            especie1 = seleccionarEspecieAleatoria(poblacionSeleccionada);
            especie2 = seleccionarEspecieAleatoria(poblacionSeleccionada);
            if (especie1 && especie2 && especie1 != especie2) {
                descripcionEvento = "La especie " + especie1->datosEspecie->nombreComun +
                                    " ha sido cazada por " + especie2->datosEspecie->nombreComun;
                registrarEvento(CAZA, descripcionEvento, especie1, especie2, poblacionSeleccionada->bioma);
                cout << descripcionEvento << endl;
            }
            break;

        case ENFERMEDAD:
            especie1 = seleccionarEspecieAleatoria(poblacionSeleccionada);
            if (especie1) {
                bool fueraRango = especie1->datosEspecie->salinidadMax < partidaActual.bioma->nivelSalinidad ||
                                  especie1->datosEspecie->oxigenoMin > partidaActual.bioma->nivelOxigeno ||
                                  especie1->datosEspecie->temperaturaMax < partidaActual.bioma->nivelTemperatura;

                if (fueraRango) {
                    descripcionEvento = "La especie " + especie1->datosEspecie->nombreComun +
                                        " ha muerto debido a factores ambientales.";
                } else {
                    descripcionEvento = "La especie " + especie1->datosEspecie->nombreComun +
                                        " no ha sido afectada por factores ambientales.";
                }
                registrarEvento(ENFERMEDAD, descripcionEvento, especie1, nullptr, poblacionSeleccionada->bioma);
                cout << descripcionEvento << endl;
            }
            break;
    }
}
*/


#endif // EVENTO_HPP