#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include "datosEspecie.h" // header de la estructura
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

const string animal = "catalogo/animales.json";
const string vegetal = "catalogo/vegetal.json";
const string bioma = "catalogo/bioma.json";

void menu();
void agregarEspecie();
void modificarEspecie();
void eliminarEspecie();
void escribirArchivo(const string&, const json&);
json leerArchivo(const string&);
int seleccionarTipoEspecie();
DatosEspecie extraerDatosEspecie();
float leerFloat();

int main() {
    int op;

    do {
        system("cls");
        menu();
        cin >> op;

        switch (op) {
            case 1:
                agregarEspecie();
                break;
            case 2:
                modificarEspecie();
                break;
            case 3:
                eliminarEspecie();
                break;
            case 4:
                extraerDatosEspecie(); // para extraer datos de la especie dada
                break;
            default:
                cout << "Saliendo..." << endl;
                break;
        }

        system("pause");
    } while (op != 0);

    return 0;
}

//*******************************************************************************

void menu() {
    cout << "MENU DE ARCHIVOS" << endl << endl;
    cout << "1. Crear especie" << endl;
    cout << "2. Modificar especie" << endl;
    cout << "3. Eliminar especie" << endl;
    cout << "4. Extraer datos de especie" << endl; 
    cout << "0. SALIR" << endl;
    cout << "Elige tu opcion-->";
}

//*******************************************************************************************************

void agregarEspecie() {
    string nombre, nombrecientifico, familia, biomaa;
    float esperanza, tasar, inact, salinidadMax, salinidadMin, oxigenoMax, oxigenoMin, tempMax, tempMin;

    int ops = seleccionarTipoEspecie();

    cout << "Nombre-->";
    fflush(stdin);
    getline(cin, nombre);

    cout << "Nombre Cientifico-->";
    getline(cin, nombrecientifico);

    cout << "Familia Biologica-->";
    getline(cin, familia);

    cout << "Bioma nativo-->";
    getline(cin, biomaa);

    fflush(stdin);
    cout << "Esperanza de vida-->";
    esperanza = leerFloat();

    fflush(stdin);
    cout << "Taza de reproduccion-->";
    tasar = leerFloat();

    fflush(stdin);
    cout << "Inactividad reproductiva-->";
    inact = leerFloat();

    // Para el rango de salinidad
    fflush(stdin);
    cout << "Rango salinidad maximo-->";
    salinidadMax = leerFloat();
    fflush(stdin);
    cout << "Rango salinidad minimo-->";
    salinidadMin = leerFloat();

    // Para el rango de oxigeno
    fflush(stdin);
    cout << "Rango oxigeno maximo-->";
    oxigenoMax = leerFloat();
    fflush(stdin);
    cout << "Rango oxigeno minimo-->";
    oxigenoMin = leerFloat();

    // Para el rango de temperatura
    fflush(stdin);
    cout << "Rango temperatura maximo-->";
    tempMax = leerFloat();
    fflush(stdin);
    cout << "Rango temperatura minimo-->";
    tempMin = leerFloat();

    json especie = {
        {"nombre comun", nombre},
        {"nombre cientifico", nombrecientifico},
        {"familia biologica", familia},
        {"bioma nativo", biomaa},
        {"esperanza de vida", esperanza},
        {"tasa de reproduccion", tasar},
        {"inactividad reproductiva", inact},
        {"rango salinidad", {salinidadMax, salinidadMin}}, 
        {"rango oxigeno", {oxigenoMax, oxigenoMin}},       
        {"rango temperatura", {tempMax, tempMin}}        
    };

    json especies;
	
	if (ops == 1) { // Animal
	    especies = leerArchivo(animal);
	    especies.push_back(especie);
	    escribirArchivo(animal, especies);
	} else if (ops == 2) { // Vegetal
	    especies = leerArchivo(vegetal);
	    especies.push_back(especie);
	    escribirArchivo(vegetal, especies);
	} else if (ops == 3) { // Bioma
	    especies = leerArchivo(bioma);
	    especies.push_back(especie);
	    escribirArchivo(bioma, especies);
	}
}

//****************************************************************************************

void modificarEspecie() {
    json especies;
    string nombreBuscado;

    int ops = seleccionarTipoEspecie();
    
	if (ops == 1) { // Animal
	    especies = leerArchivo(animal);
	} else if (ops == 2) { // Vegetal
	    especies = leerArchivo(vegetal);
	} else if (ops == 3) { // Bioma
	    especies = leerArchivo(bioma);
	}

    cout << "Ingresa el nombre de la especie a buscar: ";
    cin.ignore();
    getline(cin, nombreBuscado);

    for (auto& especie : especies) {
        if (especie["nombre comun"] == nombreBuscado) {
            cout << "Especie encontrada:"<<endl;
            cout << "Nombre comun: " << especie["nombre comun"]<<endl;
            cout << "Nombre cientifico: " << especie["nombre cientifico"]<<endl;
            cout << "Familia biologica: " << especie["familia biologica"] <<endl;
            cout << "Bioma nativo: " << especie["bioma nativo"] <<endl;
            cout << "Esperanza de vida: " << especie["esperanza de vida"] <<endl;
            cout << "Tasa de reproduccion: " << especie["tasa de reproduccion"] <<endl;
            cout << "Inactividad reproductiva: " << especie["inactividad reproductiva"] <<endl;
            cout << "Rango salinidad: [" << especie["rango salinidad"][0] << ", " << especie["rango salinidad"][1] << "]"<<endl;
            cout << "Rango oxigeno: [" << especie["rango oxigeno"][0] << ", " << especie["rango oxigeno"][1] << "]"<<endl;
            cout << "Rango temperatura: [" << especie["rango temperatura"][0] << ", " << especie["rango temperatura"][1]<<"]"<<endl<<endl;

            
            
            cout << "Modificar nombre: ";
            string nuevoNombre;
            getline(cin, nuevoNombre);
            if (!nuevoNombre.empty()) {
                especie["nombre comun"] = nuevoNombre;
            }

            cout << "Modificar nombre cientifico: ";
            string nuevoNombreCientifico;
            getline(cin, nuevoNombreCientifico);
            if (!nuevoNombreCientifico.empty()) {
                especie["nombre cientifico"] = nuevoNombreCientifico;
            }

            cout << "Modificar familia: ";
            string nuevaFamilia;
            getline(cin, nuevaFamilia);
            if (!nuevaFamilia.empty()) {
                especie["familia biologica"] = nuevaFamilia;
            }

            cout << "Modificar bioma: ";
            string nuevoBioma;
            getline(cin, nuevoBioma);
            if (!nuevoBioma.empty()) {
                especie["bioma nativo"] = nuevoBioma;
            }

            cout << "Modificar esperanza de vida: ";
            float nuevaEsperanza;
            nuevaEsperanza = leerFloat();
            especie["esperanza de vida"] = nuevaEsperanza;

            cout << "Modificar tasa de reproduccion: ";
            float nuevaTasa;
            nuevaTasa = leerFloat();
            especie["tasa de reproduccion"] = nuevaTasa;

            cout << "Modificar inactividad reproductiva: ";
            float nuevaInact;
            nuevaInact = leerFloat();
            especie["inactividad reproductiva"] = nuevaInact;

            cout << "Modificar rango salinidad (maximo): ";
            float nuevoSalMax;
            nuevoSalMax = leerFloat();
            cout << "Modificar rango salinidad (minimo): ";
            float nuevoSalMin;
            nuevoSalMin = leerFloat();
            especie["rango salinidad"] = {nuevoSalMax, nuevoSalMin};

            cout << "Modificar rango oxigeno (maximo): ";
            float nuevoOxMax;
            nuevoOxMax = leerFloat();
            cout << "Modificar rango oxigeno (minimo): ";
            float nuevoOxMin;
            nuevoOxMin = leerFloat();
            especie["rango oxigeno"] = {nuevoOxMax, nuevoOxMin};

            cout << "Modificar rango temperatura (maximo): ";
            float nuevaTempMax;
            nuevaTempMax = leerFloat();
            cout << "Modificar rango temperatura (minimo): ";
            float nuevaTempMin;
            nuevaTempMin = leerFloat();
            especie["rango temperatura"] = {nuevaTempMax, nuevaTempMin};

			if (ops == 1) { // Animal
			    escribirArchivo(animal, especies);
			} else if (ops == 2) { // Vegetal
			    escribirArchivo(vegetal, especies);
			} else if (ops == 3) { // Bioma
			    escribirArchivo(bioma, especies);
			}
			
			cout << "Especie actualizada correctamente.\n";
			return;
        }
    }

    cout << "Especie no encontrada.\n";
}

//********************************************************************************************

DatosEspecie extraerDatosEspecie() {
    json especies;
    string nombreBuscado;
    DatosEspecie especieEncontrada; // Variable para la estructura

    int ops = seleccionarTipoEspecie();
    
    if (ops == 1) { // Animal
    	especies = leerArchivo(animal);
	} else if (ops == 2) { // Vegetal
	    especies = leerArchivo(vegetal);
	} else if (ops == 3) { // Bioma
	    especies = leerArchivo(bioma);
	}

    cout << "Ingresa el nombre de la especie para extraer los datos: ";
    cin.ignore();
    getline(cin, nombreBuscado);

    for (const auto& especie : especies) {
        if (especie["nombre comun"] == nombreBuscado) {
            // Asignamos los datos a la estructura
            especieEncontrada.nombreComun = especie["nombre comun"];
            especieEncontrada.nombreCientifico = especie["nombre cientifico"];
            especieEncontrada.familiaBiologica = especie["familia biologica"];
            especieEncontrada.biomaNativo = especie["bioma nativo"];
            especieEncontrada.esperanzaVida = especie["esperanza de vida"];
            especieEncontrada.tasaReproduccion = especie["tasa de reproduccion"];
            especieEncontrada.inactividadReproductiva = especie["inactividad reproductiva"];
            especieEncontrada.salinidadMax = especie["rango salinidad"][0];
            especieEncontrada.salinidadMin = especie["rango salinidad"][1];
            especieEncontrada.oxigenoMax = especie["rango oxigeno"][0];
            especieEncontrada.oxigenoMin = especie["rango oxigeno"][1];
            especieEncontrada.tempMax = especie["rango temperatura"][0];
            especieEncontrada.tempMin = especie["rango temperatura"][1];

            // Mostramos los datos
            cout << endl;
            cout << "DATOS DE LA ESPECIE:\n";
            cout << "Nombre comun: " << especieEncontrada.nombreComun <<endl;
            cout << "Nombre cientifico: " << especieEncontrada.nombreCientifico <<endl;
            cout << "Familia biologica: " << especieEncontrada.familiaBiologica <<endl;
            cout << "Bioma nativo: " << especieEncontrada.biomaNativo <<endl;
            cout << "Esperanza de vida: " << especieEncontrada.esperanzaVida <<endl;
            cout << "Tasa de reproduccion: " << especieEncontrada.tasaReproduccion <<endl;
            cout << "Inactividad reproductiva: " << especieEncontrada.inactividadReproductiva <<endl;
            cout << "Rango salinidad: [" << especieEncontrada.salinidadMax << ", " << especieEncontrada.salinidadMin << "]"<<endl;
            cout << "Rango oxigeno: [" << especieEncontrada.oxigenoMax << ", " << especieEncontrada.oxigenoMin << "]"<<endl;
            cout << "Rango temperatura: [" << especieEncontrada.tempMax << ", " << especieEncontrada.tempMin << "]"<<endl;

            return especieEncontrada; // Retornamos la estructura con los datos
        }
    }

    cout << "Especie no encontrada.\n";
    return DatosEspecie(); //Damos una estruct vacia si no se encuentra
}

//*****************************************************************************************

void eliminarEspecie() {
    string nombre;
    int ops = seleccionarTipoEspecie();
    json especies;

	if (ops == 1) {
	    especies = leerArchivo(animal);
	} else if (ops == 2) {
	    especies = leerArchivo(vegetal);
	} else if (ops == 3) {
	    especies = leerArchivo(bioma);
	}

    cout << "Ingrese el nombre de la especie: ";
    cin.ignore();
    getline(cin, nombre);

    for (auto it = especies.begin(); it != especies.end(); ++it) {
        if ((*it)["nombre comun"] == nombre) {
            especies.erase(it);
            
			if (ops == 1) {
			    escribirArchivo(animal, especies);
			} else if (ops == 2) {
			    escribirArchivo(vegetal, especies);
			} else if (ops == 3) {
			    escribirArchivo(bioma, especies);
			}
			cout << "Especie eliminada exitosamente." << endl;
			return;
        }
    }

    cout << "Especie no encontrada." << endl;
}

//*******************************************************************************
float leerFloat() {
    float valor;
    string entrada;
    while (true) {
        getline(cin, entrada); 
        try {
            valor = stof(entrada); // Convertir a float
            return valor; // Si tiene exito, devuelve el valor
        } catch (const invalid_argument&) {
            cout << "Entrada invalida. Por favor, ingresa un numero decimal: ";
        } catch (const out_of_range&) {
            cout << "Numero fuera de rango. Intenta nuevamente: ";
        }
    }
}

//*******************************************************************************
int seleccionarTipoEspecie() {
    int ops;
    do {
        system("cls");
        cout << "1. Animal" << endl;
        cout << "2. Vegetal" << endl;
        cout << "3. Bioma" << endl;
        cout << "Tu opcion-->";
        cin >> ops;

        if (ops < 1 || ops > 3) {
            cout << "Opcion invalida" << endl;
            getch();
        }
    } while (ops < 1 || ops > 3);
    return ops;
}

//*******************************************************************************
json leerArchivo(const string& nombreArchivo) {
    json especies;
    ifstream archivo(nombreArchivo);
    if (archivo) {
        archivo >> especies;
        archivo.close();
    } else {
        especies = json::array();
    }
    return especies;
}

//*******************************************************************************
void escribirArchivo(const string& nombreArchivo, const json& especies) {
    ofstream salida(nombreArchivo);
    salida << especies.dump(4) << endl;
    salida.close();
}
