
/* *********************************************************************************************************************************************
NOMBRE DEL PROYECTO:

OBJETIVO:

AUTOR: 				 MARIO FERNANDEZ FERNANDEZ & DAVID ORTEGA LOZANO

FECHA DE CREACIÓN:
********************************************************************************************************************************************* */


//BIBLIOTECAS
#include <iostream>												//Incluyo la biblioteca de espacios de nombres
using namespace std;											//Seleccionamos el espacio de nombres estándar
#include <fstream>												//Biblioteca de archivos externos

const int LONGITUD = 50;

void guardarLista(string texto[LONGITUD]);
void mostrarLista(string texto[LONGITUD]);
bool encontrarPalabra(string texto[LONGITUD], int & k);
int contarVeces(string texto[LONGITUD], string & palabra);
string longitudMayorQue(string texto[LONGITUD]);

int main()
{
	int opcion;
	bool seguir;
	string texto[LONGITUD];
	
	guardarLista(texto);

	do {
		int k = 0;
		string palabra;

		cout << "Selecciona que opción quieres hacer:" << endl << endl;
		cout << "1. Mostrar la lista" << endl;
		cout << "2. Encontrar una palabra" << endl;
		cout << "3. Contar número de veces que aparece una palabra" << endl;
		cout << "4. Primera palabra de longitud mayor que n" << endl;
		cout << "5. Desplazar la lista y guardar" << endl;
		cout << "6. Salir";
		do {
			cin >> opcion;
			if (opcion > 0 && opcion < 7) {
				seguir = true;
				system("CLS");									//Borra todo lo de la pantalla
			}
			else{
				seguir = false;
				cout << "error, esa opción no es posible, introduce otra opción" << endl;
			}
		} while (seguir);
		switch (opcion) {
		case 1:
			mostrarLista(texto);
			break;
		case 2:
			if (encontrarPalabra(texto, k))
				cout << "Encontrada en la posición " << k << endl;
			else cout << "Palabra no encontrada" << endl;
			break;
		case 3:
			k = contarVeces(texto, palabra);
			if (k==1)
				cout << palabra << " aparece " << k << "vez" << endl;
			else cout << palabra << " aparece " << k << "veces" << endl;
			break;
		case 4:

		}

	} while (opcion != 6);
}

void guardarLista(string texto[LONGITUD]) {
	string palabra;
	ifstream lista;

	bool seguir;
	int i = 0;
	string p;

	lista.open("palabras.txt");
	if (lista.is_open()) {
		lista >> palabra;
		do {
			p = palabra;

			if (p == "XXX")
				seguir = false;
			else
				seguir = true;

			texto[i] = p;
			i++;
		} while (false);
	}
}

void mostrarLista(string texto[LONGITUD]) {
	cout << "Opción 1:" << endl;
	int i = 0;
	bool seguir = true;
	do {
		if (texto[i] != "XXX")
			cout << i + 1 << ' ' << texto[i] << endl;
		else seguir = false;
	} while (seguir);
}

bool encontrarPalabra(string texto[LONGITUD], int & k) {
	string palabra;
	bool seguir = true;
	
	cout << "Opción 2:" << endl;
	cout << "Introduce le palabra que quieres buscar en la lista:";
	cin >> palabra;
	do {
		if (texto[k] != "XXX") {
			if (texto[k] == palabra)
				return true;
		}
		else seguir = false;
	} while (seguir);
	return false;
}

int contarVeces(string texto[LONGITUD], string & palabra) {

	bool seguir = true;
	int i = 0;
	int veces = 0;

	cout << "Opción 3:" << endl;
	cout << "Introduce una palabra para buscar cuantas veces aparece en la lista:" << endl;
	cin >> palabra;

	do {
		if (texto[i] == "XXX")
			seguir = false;
		else {
			if (texto[i] == palabra) {
				veces++;
				i++;
			}
		}
	} while (seguir);

	return veces;
}
string longitudMayorQue(string texto[LONGITUD]) {
	bool seguir = true;
	int i = 0;
	string palabra1;
	int k;

	cout << "Opción 4:" << endl;
	cout << "Longitud a superar: " << endl;
	cin >> k;

	do {
		if (texto[i] == "XXX")
	} while (seguir);
}