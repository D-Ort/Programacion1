
/* *********************************************************************************************************************************************
NOMBRE DEL PROYECTO: Laboratorio 2

OBJETIVO:            Creación de un array de 50 números enteros aleatorios, ordenar con padelshort identificar el máximo y mínimo y calcular 
					la media total

AUTOR: 				 MARIO FERNANDEZ FERNANDEZ & DAVID ORTEGA LOZANO

FECHA DE CREACIÓN:	 11/10/2022
********************************************************************************************************************************************* */

//Bibliotecas:
#include <iostream>												//Incluyo la biblioteca de espacios de nombres
    using namespace std;											//Seleccionamos el espacio de nombres estándar
#include <cstdlib>                                              //Incluyo la biblioteca de creación de números aleatorios
#include <ctime>                                                //Incluyo la biblioteca de uso del reloj

//Constantes:
const int LimSup = 2000, LimInf = 0, N_Caracteres = 50;			//Delimito entre que valores son los nº aletorios y la longitud de la serie


//INICIALIZACIÓN DE FUNCIONES Y PROCEDIMIENTOS:

//Función que genera un número aleatorio
int generarNAleatorio();

//Función que otorga valores a la serie
void valoresSerie(int serie[N_Caracteres]);

//Función que identifica el valor máximo de la serie
int maximo(int serie[N_Caracteres]);

//Función que identifica el valor mínimo de la serie
int minimo(int serie[N_Caracteres]);



int main()
{
	srand(time(NULL));          //Empleo el valor de la hora de la biblioteca "ctime" como semilla de los números aleatorios

	//Variables locales:
	int serie[N_Caracteres];									//Inicializo el array

	valoresSerie(serie);										//Doy valores a todos los espacios del array

	cout << "El número máximo de la serie es " << maximo(serie) << endl;
	cout << "El número mínimo de la serie es " << minimo(serie) << endl;
}




//IMPLEMENTACIÓN DE FUNCIONES Y PROCEDIMIENTOS:

//----------------------------------------------------------------------------------------------------------------------------------------------
//Función que genera un número aleatorio
int generarNAleatorio() {

	//Delimito el valor del número "aleatorio"
	return LimInf + rand() % (LimSup + 1 - LimInf);
}

//----------------------------------------------------------------------------------------------------------------------------------------------
//Función que otorga valores a la serie
void valoresSerie(int serie[N_Caracteres]){

	cout << "Los valores de la serie son: ";
	for (int i = 0; i < N_Caracteres; i++) {
		serie[i] = generarNAleatorio();
		if (i < (N_Caracteres - 2)) {
			cout << serie[i] << ", ";
		}
		else if (i == (N_Caracteres - 2)) {
			cout << serie[i] << " y ";
		}
		else {
			cout << serie[i] << endl;
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------------------------------
//Función que identifica el valor máximo de la serie
int maximo(int serie[N_Caracteres]) {
	int nMax = serie[0];
	int aux;
	for (int i = 1; i < N_Caracteres; i++) {
		if (aux > nMax) {
			nMax = aux;
		}
	}

	return nMax;
}

//----------------------------------------------------------------------------------------------------------------------------------------------
//Función que identifica el valor mínimo de la serie
int minimo(int serie[N_Caracteres]) {
	int nMin = serie[0];
	int aux;
	for (int i = 1; i < N_Caracteres; i++) {
		if (aux < nMin) {
			nMin = aux;
		}
	}

	return nMin;
}

//----------------------------------------------------------------------------------------------------------------------------------------------
//Función que ordena los valores de la serie
void orden(int serie[N_Caracteres]) {
	do {
		for ()
	}
}