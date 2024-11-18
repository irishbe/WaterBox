#ifndef CRUD_DATOS_H
#define CRUD_DATOS_H

#include <iostream>
#include <fstream>
#include <cctype>
#include "DatosEspecie.hpp"
#include "Bioma.hpp"
#include "Evento.hpp"
#include "utilidades.hpp"
#include "LibreriasExternas/json.hpp"

using json = nlohmann::json;
using namespace std;

const string animalesJson = "catalogo/animales.json";
const string vegetalesJson = "catalogo/vegetal.json";
const string biomasJson = "catalogo/bioma.json";

const vector<string> categorias = {"Animal", "Vegetal", "Bioma"};
const vector<string> tiposEspecies = {"Animal", "Vegetal"};
    

void menu();

void crearDatosCategoria();
void modificarDatosCategoria();
void eliminarDatosCategoria();
void extraerDatosCategoria();

void escribirArchivo(const string&, const json&);
json leerArchivo(const string&);
float leerFloat();

// Funcionalidades auxiliares en el simulador
DatosEspecie* extraerDatosEspecie();
Bioma* extraerDatosBioma();
vector<string> extraerNombres(string categoria);

void iniciarCrudJson() {
    int opcion;

    do {
        system("cls");
        menu();
        cin >> opcion;

        switch (opcion) {
            case 1:
                crearDatosCategoria();
                system("pause");
                break;
            case 2:
                modificarDatosCategoria();
                system("pause");
                break;
            case 3:
                eliminarDatosCategoria();
                system("pause");
                break;
            case 4:
                extraerDatosCategoria();
                system("pause");
                break;
            case 0:
                break;
            default:
                cout << "Saliendo..." << endl;
                system("pause");
                break;
        }

        system("cls");

    } while (opcion != 0);

}

void menu() {
    cout << "MENU DE ARCHIVOS" << endl << endl;
    cout << "1. Crear datos de una categoria" << endl;
    cout << "2. Modificar datos de una categoria" << endl;
    cout << "3. Eliminar datos de una categoria" << endl;
    cout << "4. Extraer datos de una categoria" << endl;
    cout << "0. SALIR" << endl;
    
    cout << "\nElige tu opcion--> ";
}

//*******************************************************************************************************

void crearDatosCategoria() {
    json datosJson;
    string categoria = seleccionConFlechas(categorias, tituloWaterBox(), "SELECCIONE UNA CATEGORIA A CREAR");

    if ( categoria == "Bioma" ){
        Bioma *bioma;
        
        cout << "Creando " << categoria << endl;

        fflush(stdin);
        cout<<"Nombre--> ";
        getline(cin, bioma->nombre);
        
        fflush(stdin);
        cout<<"Nivel Salinidad--> ";
        bioma->nivelSalinidad = leerFloat();
        
        fflush(stdin);
        cout<<"Nivel Oxigeno--> ";
        bioma->nivelOxigeno = leerFloat();
        
        fflush(stdin);
        cout<<"Nivel Temperatura--> ";
        bioma->nivelTemperatura = leerFloat();
        
        fflush(stdin);
        cout<<"Nivel Contaminacion--> ";
        bioma->nivelContaminacion = leerFloat();
        
        json datosBioma = {
            {"nombre", bioma->nombre},
            {"nivelSalinidad", bioma->nivelSalinidad},
            {"nivelOxigeno", bioma->nivelOxigeno},
            {"nivelTemperatura", bioma->nivelTemperatura},
            {"nivelContaminacion", bioma->nivelContaminacion}
        };

        datosJson = leerArchivo(biomasJson);
        datosJson.push_back(datosBioma);
        escribirArchivo(biomasJson, datosJson);

        registrarEvento(CREAR_BIOMA_ADMIN, bioma);
        cout << "\nBioma creado con exito " << endl;

    }else if ( categoria == "Animal" || categoria == "Vegetal" ){
        DatosEspecie *datosEspecie = new DatosEspecie();
        
        cout << "Creando " << categoria << endl;

        fflush(stdin);
        cout << "Nombre--> ";
        getline(cin, datosEspecie->nombreComun);

        fflush(stdin);
        cout << "Nombre Cientifico--> ";
        getline(cin, datosEspecie->nombreCientifico);

        fflush(stdin);
        cout << "Familia Biologica--> ";
        getline(cin, datosEspecie->familiaBiologica);

        fflush(stdin);
        cout << "Bioma nativo--> ";
        getline(cin, datosEspecie->biomaNativo);

        fflush(stdin);
        cout << "Esperanza de vida--> ";
        datosEspecie->esperanzaVida = leerFloat();

        fflush(stdin);
        cout << "Taza de reproduccion--> ";
        datosEspecie->tasaReproduccion = leerFloat();

        fflush(stdin);
        cout << "Inactividad reproductiva--> ";
        datosEspecie->inactividadReproductiva = leerFloat();

        // Para el rango de salinidad
        fflush(stdin);
        cout << "Rango salinidad maximo--> ";
        datosEspecie->salinidadMax = leerFloat();

        fflush(stdin);
        cout << "Rango salinidad minimo--> ";
        datosEspecie->salinidadMin = leerFloat();

        // Para el rango de oxigeno
        fflush(stdin);
        cout << "Rango oxigeno maximo--> ";
        datosEspecie->oxigenoMax = leerFloat();

        fflush(stdin);
        cout << "Rango oxigeno minimo--> ";
        datosEspecie->oxigenoMin = leerFloat();

        // Para el rango de temperatura
        fflush(stdin);
        cout << "Rango temperatura maximo--> ";
        datosEspecie->temperaturaMax = leerFloat();

        fflush(stdin);
        cout << "Rango temperatura minimo--> ";
        datosEspecie->temperaturaMin = leerFloat();

        json especie = {
            {"nombre comun", datosEspecie->nombreComun},
            {"nombre cientifico", datosEspecie->nombreCientifico},
            {"familia biologica", datosEspecie->familiaBiologica},
            {"bioma nativo", datosEspecie->biomaNativo},
            {"esperanza de vida", datosEspecie->esperanzaVida},
            {"tasa de reproduccion", datosEspecie->tasaReproduccion},
            {"inactividad reproductiva", datosEspecie->inactividadReproductiva},
            {"rango salinidad", {datosEspecie->salinidadMax , datosEspecie->salinidadMin }}, 
            {"rango oxigeno", {datosEspecie->oxigenoMax , datosEspecie->oxigenoMin}},       
            {"rango temperatura", {datosEspecie->temperaturaMax, datosEspecie->temperaturaMin}}        
        };
        
        if ( categoria == "Animal" ) { // Animal
            datosJson = leerArchivo(animalesJson);
            datosJson.push_back(especie);
            escribirArchivo(animalesJson, datosJson);

        } else { // Vegetal
            datosJson = leerArchivo(vegetalesJson);
            datosJson.push_back(especie);
            escribirArchivo(vegetalesJson, datosJson);
        }

        Especie *e = new Especie();
        e->datosEspecie = datosEspecie;

        registrarEvento(CREAR_ESPECIE_ADMIN, nullptr, e);
        cout << "\nEspecie creada con exito " << endl;
    }

}

//****************************************************************************************

void modificarDatosCategoria() {
    json datosJson;
    string categoria, nombreBuscado;

    categoria = seleccionConFlechas(categorias, tituloWaterBox(), "SELECCIONE UNA CATEGORIA");
    
	if ( categoria == "Animal" ) { // Animal
	    datosJson = leerArchivo(animalesJson);
	
    } else if ( categoria == "Vegetal" ) { // Vegetal
	    datosJson = leerArchivo(vegetalesJson);
	
    } else if ( categoria == "Bioma") { // Bioma
	    datosJson = leerArchivo(biomasJson);
	
    }else{
        return;
    }

    cout << "Ingrese el nombre del "<< categoria <<" a buscar: ";
    cin.ignore();
    getline(cin, nombreBuscado);

    if ( categoria == "Bioma" ){
        Bioma *bioma;

        for (auto& biomaEncontrado : datosJson) {
            if (biomaEncontrado["nombre"] == nombreBuscado) {
                cout << "Bioma encontrado:" << endl;
                cout << "Nombre: " << biomaEncontrado["nombre"] << endl;
                cout << "Nivel de salinidad: " << biomaEncontrado["nivelSalinidad"] << endl;
                cout << "Nivel de oxígeno: " << biomaEncontrado["nivelOxigeno"] << endl;
                cout << "Nivel de temperatura: " << biomaEncontrado["nivelTemperatura"] << endl;
                cout << "Nivel de contaminación: " << biomaEncontrado["nivelContaminacion"] << endl << endl;

                // DATOS TEXTUALES
                // NOMBRE
                cout << "Modificar nombre: ";
                getline(cin, bioma->nombre);
                if (!bioma->nombre.empty()) {
                    biomaEncontrado["nombre"] = bioma->nombre;
                }

                // NIVELES (FLOAT)
                // SALINIDAD
                cout << "Modificar nivel de salinidad: ";
                bioma->nivelSalinidad = leerFloat();
                biomaEncontrado["nivelSalinidad"] = bioma->nivelSalinidad;

                // OXÍGENO
                cout << "Modificar nivel de oxígeno: ";
                bioma->nivelOxigeno = leerFloat();
                biomaEncontrado["nivelOxigeno"] = bioma->nivelOxigeno;

                // TEMPERATURA
                cout << "Modificar nivel de temperatura: ";
                bioma->nivelTemperatura = leerFloat();
                biomaEncontrado["nivelTemperatura"] = bioma->nivelTemperatura;

                // CONTAMINACIÓN
                cout << "Modificar nivel de contaminación: ";
                bioma->nivelContaminacion = leerFloat();
                biomaEncontrado["nivelContaminacion"] = bioma->nivelContaminacion;

                escribirArchivo(biomasJson, datosJson);

                registrarEvento(EDITAR_BIOMA_ADMIN, bioma);
                cout << "Bioma actualizado correctamente.\n";
                return;
            }
        }

        cout << "Bioma no encontrado.\n";

    } else{
        DatosEspecie *datosEspecie = new DatosEspecie();
    
        for (auto& especie : datosJson) {
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

                // DATOS TEXTUALES
                // NOMBRE COMUN

                cout << "Modificar nombre: ";
                getline(cin, datosEspecie->nombreComun);

                if ( !datosEspecie->nombreComun.empty()) {
                    especie["nombre comun"] = datosEspecie->nombreComun;
                }

                // NOMBRE CIENTIFICO

                cout << "Modificar nombre cientifico: ";
                getline(cin, datosEspecie->nombreCientifico);

                if ( !datosEspecie->nombreCientifico.empty()) {
                    especie["nombre cientifico"] = datosEspecie->nombreCientifico;
                }

                // FAMILIA BIOLOGICA

                cout << "Modificar familia biologica: ";
                getline(cin, datosEspecie->familiaBiologica);

                if ( !datosEspecie->familiaBiologica.empty() ) {
                    especie["familia biologica"] = datosEspecie->familiaBiologica;
                }

                // BIOMA NATIVO

                cout << "Modificar bioma nativo: ";
                getline(cin, datosEspecie->biomaNativo);

                if ( !datosEspecie->biomaNativo.empty() ) {
                    especie["bioma nativo"] = datosEspecie->biomaNativo;
                }

                // DATOS DE TIEMPO (float)
                // ESPERANZA DE VIDA

                cout << "Modificar esperanza de vida: ";
                datosEspecie->esperanzaVida = leerFloat();
                especie["esperanza de vida"] = datosEspecie->esperanzaVida;

                // TASA DE REPRODUCCION

                cout << "Modificar tasa de reproduccion: ";
                datosEspecie->tasaReproduccion = leerFloat();
                especie["tasa de reproduccion"] = datosEspecie->tasaReproduccion;

                // INACTIVIDAD REPRODUCTIVA

                cout << "Modificar inactividad reproductiva: ";
                datosEspecie->inactividadReproductiva = leerFloat();
                especie["inactividad reproductiva"] = datosEspecie->inactividadReproductiva;

                // RANGO DE NIVELES
                // SALINIDAD

                cout << "Modificar rango salinidad (maximo): ";
                datosEspecie->salinidadMax = leerFloat();

                cout << "Modificar rango salinidad (minimo): ";
                datosEspecie->salinidadMin = leerFloat();

                especie["rango salinidad"] = {datosEspecie->salinidadMax, datosEspecie->salinidadMin};

                // OXIGENO
                cout << "Modificar rango oxigeno (maximo): ";
                datosEspecie->oxigenoMax = leerFloat();

                cout << "Modificar rango oxigeno (minimo): ";
                datosEspecie->oxigenoMin = leerFloat();
                
                especie["rango oxigeno"] = {datosEspecie->oxigenoMax, datosEspecie->oxigenoMin};

                // TEMPERATURA
                cout << "Modificar rango temperatura (maximo): ";
                datosEspecie->temperaturaMax = leerFloat();

                cout << "Modificar rango temperatura (minimo): ";
                datosEspecie->temperaturaMin = leerFloat();

                especie["rango temperatura"] = {datosEspecie->temperaturaMax, datosEspecie->temperaturaMin};

                if ( categoria == "Animal" ) {
                    escribirArchivo(animalesJson, datosJson);

                } else{ // Vegetal
                    escribirArchivo(vegetalesJson, datosJson);
                }

                Especie *e = new Especie();
                e->datosEspecie = datosEspecie;

                registrarEvento(EDITAR_ESPECIE_ADMIN, nullptr, e);
                cout << "\nEspecie actualizada correctamente.\n";

                return;
            }
        }
    
        cout << "Especie no encontrada.\n";
    }
}

//********************************************************************************************

void extraerDatosCategoria() {
    json datosJson;
    string nombreBuscado, categoria;

    categoria = seleccionConFlechas(categorias, tituloWaterBox(), "SELECCIONE UNA CATEGORIA");

    if ( categoria == "Animal" ) { // Animal
    	datosJson = leerArchivo(animalesJson);

	} else if( categoria == "Vegetal" ){ // Vegetal
	    datosJson = leerArchivo(vegetalesJson);

	} else if( categoria == "Bioma" ){ // Bioma
        datosJson = leerArchivo(biomasJson);

    }else{
        return;
    }

    cout << "Ingresa el nombre del " << categoria <<" para extraer los datos: ";
    cin.ignore();
    getline(cin, nombreBuscado);

    if ( categoria == "Bioma" ){
        Bioma bioma;

        for (auto& biomaEncontrado : datosJson) {
            if (biomaEncontrado["nombre"] == nombreBuscado) {
            	bioma.nombre = biomaEncontrado["nombre"];
            	bioma.nivelSalinidad = biomaEncontrado["nivelSalinidad"];
                bioma.nivelOxigeno = biomaEncontrado["nivelOxigeno"];
                bioma.nivelTemperatura = biomaEncontrado["nivelTemperatura"];
                bioma.nivelContaminacion = biomaEncontrado["nivelContaminacion"];
            	
                cout << "Bioma encontrado:" << endl;
                cout << "Nombre: " << bioma.nombre << endl;
                cout << "Nivel de salinidad: " << bioma.nivelSalinidad << endl;
                cout << "Nivel de oxígeno: " << bioma.nivelOxigeno << endl;
                cout << "Nivel de temperatura: " << bioma.nivelTemperatura << endl;
                cout << "Nivel de contaminación: " << bioma.nivelContaminacion << endl << endl;
                
                return;
            }
        }

        cout << "Bioma no encontrado.\n";

    } else{
        DatosEspecie especieEncontrada;

        for (const auto& especie : datosJson) {
            if ( especie["nombre comun"] == nombreBuscado ) {
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
                especieEncontrada.temperaturaMax = especie["rango temperatura"][0];
                especieEncontrada.temperaturaMin = especie["rango temperatura"][1];

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
                cout << "Rango temperatura: [" << especieEncontrada.temperaturaMax << ", " << especieEncontrada.temperaturaMin << "]"<<endl;
                
                return;
            }
        }

        cout << "Especie no encontrada.\n";
    }

}

//******************************** AÑADIDO POR WHENDAVI *********************************************************

DatosEspecie* extraerDatosEspecie(string tipoEspecie, string nombreBuscado) {
    json especies;
    DatosEspecie* especieEncontrada = new DatosEspecie();

    if( tipoEspecie == "Animal" ){
        especies = leerArchivo(animalesJson);
    }else if( tipoEspecie == "Vegetal" ){
        especies = leerArchivo(vegetalesJson);
    }

    for (const auto& especie : especies) {
        if (especie["nombre comun"] == nombreBuscado) {
            // Asignamos los datos a la estructura
            especieEncontrada->nombreComun = especie["nombre comun"];
            especieEncontrada->nombreCientifico = especie["nombre cientifico"];
            especieEncontrada->familiaBiologica = especie["familia biologica"];
            especieEncontrada->biomaNativo = especie["bioma nativo"];
            especieEncontrada->esperanzaVida = especie["esperanza de vida"];
            especieEncontrada->tasaReproduccion = especie["tasa de reproduccion"];
            especieEncontrada->inactividadReproductiva = especie["inactividad reproductiva"];
            especieEncontrada->salinidadMax = especie["rango salinidad"][0];
            especieEncontrada->salinidadMin = especie["rango salinidad"][1];
            especieEncontrada->oxigenoMax = especie["rango oxigeno"][0];
            especieEncontrada->oxigenoMin = especie["rango oxigeno"][1];
            especieEncontrada->temperaturaMax = especie["rango temperatura"][0];
            especieEncontrada->temperaturaMin = especie["rango temperatura"][1];

            return especieEncontrada;
        }
    }

    delete especieEncontrada;
    return nullptr;
}

Bioma* extraerBioma(string nombreBuscado){
	Bioma *biomaEncontrado = new Bioma();		//para la info del biomita
	json biomas;     			                //variable para sacar info total del json
	
	ifstream archivo(biomasJson);
    if (archivo){
        archivo>>biomas;	//extraer
        archivo.close();
    } 
	else{
        biomas = json::array();	
    }
	
	//****************************************************************************
	for (const auto& bioma : biomas) {
        if (bioma["nombre"] == nombreBuscado) {
            // Asignamos los datos a la estructura
            biomaEncontrado->nombre = bioma["nombre"];
            biomaEncontrado->nivelSalinidad = bioma["nivelSalinidad"];
            biomaEncontrado->nivelOxigeno = bioma["nivelOxigeno"];
            biomaEncontrado->nivelTemperatura = bioma["nivelTemperatura"];
            biomaEncontrado->nivelContaminacion = bioma["nivelContaminacion"];

            return biomaEncontrado; // Retornamos el bioma con los datos
        }
    }

    cout << "Bioma no encontrado.\n";
    return biomaEncontrado; //Damos una estruct vacia si no se encuentra
}

vector<string> extraerNombres(string categoria){
    json datosJson;
    vector<string> nombres;
    
    if( categoria == "Animal" ){
        datosJson = leerArchivo(animalesJson);

    }else if( categoria == "Vegetal" ){
        datosJson = leerArchivo(vegetalesJson);

    }else if( categoria == "Bioma"){
        datosJson = leerArchivo(biomasJson);

    }else{
        return nombres;
    }

    if ( categoria == "Bioma" ){

        for (const auto& bioma : datosJson) {
            nombres.push_back( bioma["nombre"] );
        }

    } else{

        for (const auto& especie : datosJson) {
            nombres.push_back(especie["nombre comun"]);
        }

    }

    return nombres;
}

//*****************************************************************************************

void eliminarDatosCategoria() {
    json datosJson;
    string nombre, categoria;

    categoria = seleccionConFlechas(categorias, tituloWaterBox(), "SELECCIONE UNA CATEGORIA");

	if ( categoria == "Animal" ) {
	    datosJson = leerArchivo(animalesJson);
	
    } else if ( categoria == "Vegetal" ) {
	    datosJson = leerArchivo(vegetalesJson);
	
    } else if ( categoria == "Bioma" ) {
	    datosJson = leerArchivo(biomasJson);
	} else{
        return;
    }

    cout << "Ingrese el nombre del " << categoria << " a eliminar: ";

    cin.ignore();
    getline(cin, nombre);

    if ( categoria == "Bioma" ){

        for (auto it = datosJson.begin(); it != datosJson.end(); ++it) {
            if ((*it)["nombre"] == nombre) {
                datosJson.erase(it);
                
                escribirArchivo(biomasJson, datosJson);

                Bioma *bioma;
                bioma->nombre = nombre;

                registrarEvento(ELIMINAR_BIOMA_ADMIN, bioma);
                cout << "Bioma eliminado exitosamente." << endl;
                return;
            }
        }

        cout << "\nBioma no encontrado." << endl;
    }else{

        for (auto it = datosJson.begin(); it != datosJson.end(); ++it) {
            if ((*it)["nombre comun"] == nombre) {
                datosJson.erase(it);
                
                if ( categoria == "Animal" ) {
                    escribirArchivo(animalesJson, datosJson);
                } else{
                    escribirArchivo(vegetalesJson, datosJson);
                }

                Especie *e = new Especie();
                e->datosEspecie = new DatosEspecie();
                e->datosEspecie->nombreComun = nombre;

                registrarEvento(ELIMINAR_ESPECIE_ADMIN, nullptr, e);
                cout << "\nEspecie eliminada exitosamente." << endl;
                
                return;
            }
        }

        cout << "\nEspecie no encontrada." << endl;
    }
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
json leerArchivo(const string& nombreArchivo) {
    json datosJson;
    ifstream archivo(nombreArchivo);
    if (archivo) {
        archivo >> datosJson;
        archivo.close();
    } else {
        datosJson = json::array();
    }

    return datosJson;
}

//*******************************************************************************
void escribirArchivo(const string& nombreArchivo, const json& datosJson) {
    ofstream salida(nombreArchivo);
    salida << datosJson.dump(4) << endl;
    salida.close();
}

#endif // CRUD_DATOS.H
