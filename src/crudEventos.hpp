#include "Evento.hpp"
#include "crudDatos.hpp"
#include "crudEspecies.hpp"

// Función para generar un número aleatorio dentro de un rango
int generarNumeroAleatorio(int min, int max) {
    // Semilla para la generación de números aleatorios
    std::srand(static_cast<unsigned>(std::time(0))); // Usar el tiempo actual como semilla

    // Generar un número aleatorio entre [minimo, maximo]
    return min + std::rand() % (max - min + 1);
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


void generarEventoAleatorio() {
    Evento* eventoAleatorio = new Evento();
    int num = generarNumeroAleatorio(1, 4); // Enum TipoEvento
    TipoEvento tipoEvento;

    switch (num){
        case 1: tipoEvento = AGREGAR_ESPECIE; break;
        case 2: tipoEvento = ELIMINAR_ESPECIE; break;
        case 3: tipoEvento = MODIFICAR_FACTORES; break;
        case 4: tipoEvento = REPRODUCCION; break;
    }

    switch (tipoEvento) {
        case AGREGAR_ESPECIE: {
            Especie* nuevaEspecie = new Especie();
            vector<string> nombresEspecies;
            int index;

            // Determinar tipo de especie (Animal o Vegetal)
            nuevaEspecie->tipoEspecie = (generarNumeroAleatorio(1, 2) == 1) ? "Animal" : "Vegetal";

            // Obtener nombres posibles y seleccionar uno
            nombresEspecies = extraerNombres(nuevaEspecie->tipoEspecie);

            if (nombresEspecies.empty()) {
                delete nuevaEspecie;
                return;
            }

            index = generarNumeroAleatorio(0, nombresEspecies.size() - 1);
            nuevaEspecie->datosEspecie = extraerDatosEspecie(nuevaEspecie->tipoEspecie, nombresEspecies[index]);

            // Agregar la nueva especie a una población
            agregarEspecieEnPoblacion(nuevaEspecie);
            registrarEvento(AGREGAR_ESPECIE, partidaActual, nuevaEspecie);
            break;
        }

        case ELIMINAR_ESPECIE: {
            Poblacion* poblacionSeleccionada = poblacionAleatoria();
            if (!poblacionSeleccionada) {
                return;
            }

            Especie* especie1 = especieAleatoria(poblacionSeleccionada);
            if (especie1) {
                procesoEliminarEspecie(poblacionSeleccionada, especie1);
            }
            break;
        }

        case MODIFICAR_FACTORES:
            switch( generarNumeroAleatorio(1, 4) ){
                case 1: partidaActual->bioma->nivelOxigeno = generarNumeroAleatorio(0,14); break;
                case 2: partidaActual->bioma->nivelSalinidad = generarNumeroAleatorio(0,330); break;
                case 3: partidaActual->bioma->nivelTemperatura = generarNumeroAleatorio(0,40); break;
                case 4: partidaActual->bioma->nivelContaminacion = generarNumeroAleatorio(0,100); break;
            }

            registrarEvento(MODIFICAR_FACTORES, partidaActual);
            evaluarCambioFactores();
            break;

        case REPRODUCCION: {
            Poblacion* poblacionSeleccionada = poblacionAleatoria();

            if (!poblacionSeleccionada) {
                return;
            }

            Especie* especie1 = especieAleatoria(poblacionSeleccionada);
            Especie* especie2 = especieAleatoria(poblacionSeleccionada);

            if (especie1 && especie2 && especie1 != especie2) {
                procesoReproduccion(especie1, especie2, poblacionSeleccionada);
            }
            break;
        }
    }
}