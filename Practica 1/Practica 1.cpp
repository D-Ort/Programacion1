
/************************************************************************************************************************
NOMBRE DEL PROYECTO:	Práctica 1

OBJETIVO:		Desarrollar el juego de los "Chinos" con múltiples funciones

AUTOR:			MARIO FERNÁNDEZ FERNÁNDEZ & DAVID ORTEGA LOZANO

FECHA DE CREACIÓN:	27/09/2022
************************************************************************************************************************/

//-----------------------------------------------------------------------------------------------------------------------
//BIBLIOTECAS:
#include <iostream>							//Se incluye la biblioteca de espacios de nombres
	using namespace std;						//Se selecciona el espacio de nombres estándar
#include <cstdlib>							//Se incluye la biblioteca de creación de números aleatorios
#include <ctime>							//Se incluye la biblioteca de uso del reloj


//-----------------------------------------------------------------------------------------------------------------------
//INICIALIZACIÓN DE FUNCIONES Y PROCEDIMIENTOS:

//Función que genera un número aleatorio
int generarNumeroAleatorio(int limSuperior, int limInferior);

//Función que pregunta el nº máx de piedras por jugador y el nº de rondas
int setup(int& nRondas);

//Función que solicita al jugador el número de piedras que quiere usar
int jugada(int nMax);

//Función que lleva a cabo la jugada de la Máquina
int jugadaBot(int nMax);

//Función que recibe y verifica la apuesta del jugador
int apuesta(int piedrasJ, int nMax);

//Función que realiza la apuesta de la máquina
int apuestaBot(int piedrasBot, int nMax);

//Función que lleva a cabo el desarrollo del juego
bool juegoChinos(int nRondas, int nMax, int& puntosB, int& puntosJ, int desempate);

//Función que dicta el ganador de la ronda
void ganador(int totalJ, int totalM, int total, int& puntosJ, int& puntosBot);


/*_______________________________________________________________________________________________________________________
	FUNCIÓN PRINCIPAL DEL CÓDOGO:
-----------------------------------------------------------------------------------------------------------------------*/
int main() {

	//VARIABLES LOCALES: 
	int nRondas = 0, nMax;					//Variables de la función "setup"
	int puntosB = 0, puntosJ = 0;				//Variables de marcador
	bool desempate = false;					//Variable que comprueba el desempate


								//Se da la bienvenida y se inicializan los parámetros con la función "setup"
	cout << "¡Bienvenido al juego de los chinos!" << endl;
	nMax = setup(nRondas);					
											
								//Se juegan todas las rondas establecidas
	desempate = juegoChinos(nRondas, nMax, puntosB, puntosJ, 0); 

	while (desempate) {					//En caso de empate y que el jugador haya solicitado desempatar se juega 
								//otra ronda hasta que las condiciones anteriores cambien
		desempate = juegoChinos(1, nMax, puntosB, puntosJ, 1);
	}

	cout << "¡Hasta la próxima! " << endl;			//Se finaliza el juego con una despedida 

	return 0;						//Se devuelve "0" para comprobar que todo ha ido bien.
}


/*-----------------------------------------------------------------------------------------------------------------------
	IMPLEMENTACIÓN DE FUNCIONES Y PROCEDIMIENTOS:
-----------------------------------------------------------------------------------------------------------------------*/
//Función que genera un número aleatorio:

int generarNumeroAleatorio(int limSuperior, int limInferior) {

	srand(time(NULL));					//Se emplea el valor de la hora de la biblioteca "ctime" como semilla de los 
								//números aleatorios

								//Se delimita el valor del número "aleatorio" y se devuelve
	return limInferior + rand() % (limSuperior + 1 - limInferior); 
}

//-----------------------------------------------------------------------------------------------------------------------
//Función que pregunta el nº máx de piedras por jugador y el nº de rondas:

int setup(int& nRondas) {

	//VARIABLES LOCALES:
	int piedrasMax;						//Variable que recoge el número max de piedras


	cout << "Elige el número total de piedras que tenemos cada uno (máx. 10): ";
	cin >> piedrasMax;					//Se solicita el número máximo de piedras que el jugador quiere usar:

								//Se comprueba que se encuentra entre los límites
	while (piedrasMax > 10 || piedrasMax < 1) {
		cout << "Número incorrecto de piedras. Elige el número total de piedras que tenemos cada uno(máx. 10): ";
		cin >> piedrasMax;
	}

	cout << "¿Cuántas rondas quieres jugar (máx. 10)? "; 
	cin >> nRondas;						//Se solicita el número de rondas que el jugador quiere jugar:

								//Se comprueba que se encuentra entre los límites
	while (nRondas > 10 || nRondas < 1) {
		cout << "Número incorrecto de rondas. Elige el número de rondas que quieres jugar(máx 10).";
		cin >> nRondas;
	}

	return piedrasMax;					//Se devuelve el nº máximo de piedras 
}

//-----------------------------------------------------------------------------------------------------------------------
//Función que solicita al jugador el número de piedras que quiere usar:

int jugada(int nMax) {

	//VARIABLES LOCALES:
	int nPiedras;						//Variable que recoge el nº de piedras del jugador 


	cout << "Tu turno. Con cuántas piedras juegas? Elige un número entre 0 y " << nMax << ": ";
	cin >> nPiedras;					//Se solicita cuantas piedras quiere el jugador

								//Se comprueba que se encuentra entre los límites
	while (nPiedras > nMax || nPiedras < 0) {
		cout << "Número correcto de piedras, por favor introduzca un número entre 0 y " << nMax << ": ";
		cin >> nPiedras;
	}

	return nPiedras;					//Se devuelve el nº de piedras del jugador
}

//-----------------------------------------------------------------------------------------------------------------------
//Función que lleva a cabo la jugada de la Máquina:

int jugadaBot(int nMax) {
	//Hemos empleado esta función para organizar mejor el código y así poder ver mejor en que consiste la jugada de la 
	//Máquina.
	 
	return generarNumeroAleatorio(nMax, 0);			//Se devuelvo el nº de piedras de la máquina
}

//-----------------------------------------------------------------------------------------------------------------------
//Función que recibe y verifica la apuesta del jugador:

int apuesta(int piedrasJ, int nMax) {
	//VARIABLES LOCALES:
	int apuesta;						//Variable que recoge el nº de piedras que apuesta el jugador


	cout << "¿Cuántas piedras hay? ";			//Se solicita el número estimado de piedras que el jugador quiere apostar
	cin >> apuesta;

	while (apuesta > (piedrasJ + nMax) || apuesta < piedrasJ) { 
		if (apuesta < piedrasJ) {		//Se comprueba que se encuentra dentro de los límites:
			cout << "Ey, no hagas trampa, apuesta de nuevo:";
		}
		else {
			cout << "No se puedo apostar más de " << nMax + piedrasJ << " vuelve a apostar : ";
		}
		cin >> apuesta;
	}

	return apuesta;						//Se devuelve la apuesta del jugador
}

//-----------------------------------------------------------------------------------------------------------------------
//Función que realiza la apuesta de la máquina:

int apuestaBot(int piedrasBot, int nMax) {
	//Hemos empleado esta función para organizar mejor el código y así poder ver
	//mejor en que consiste la apuesta de la Máquina.
	
								//Se devuelve como apuesta de la máquina la suma de un nº aleatorio < que el 
								//nº max de piedras y las piedras de la mano de la Máquina
	return piedrasBot + generarNumeroAleatorio(nMax, 0);
}

//-----------------------------------------------------------------------------------------------------------------------
//Función que lleva a cabo el desarrollo del juego:

bool juegoChinos(int nRondas, int nMax, int& puntosB, int& puntosJ, int desempatando) {
	//Hemos añadido los dos punteros del marcador que recorgen los puntos de la máquina y el jugador y el bool de 
	//desempate para poder hacer rondas de desempate
	
	//VARIABLES LOCALES:
	int piedrasJ;						//Variable que recoge el nº de piedras que tiene el jugador
	int piedrasBot;						//Varaible que recoge el nº de piedras que tiene la Máquina 
	int piedrasTot;						//Variable que recoge el total de piedras empleadas
	int apuestaJ;						//Variable que recoge la apuesta del jugador
	int apuestaB;						//Variable que recoge la apuesta de la Máquina
	int ganadorR;						//Variable que recoge quien ha ganado la ronda


	for (int ronda = 1; ronda <= nRondas; ronda++) {
								//Se repite el juego tantas veces como rondas haya
		cout << "Ronda ";				//Se dice en que ronda se está y en caso de desempate lo especifico
		if (desempatando == 1) {
			cout << " de desempate" << endl;
		}
		else {
			cout << ronda << endl;
		}

		piedrasJ = jugada(nMax);			//Se llama a las funciones que realizan la jugada del jugador y la Máquina
		piedrasBot = jugadaBot(nMax);
		piedrasTot = piedrasJ + piedrasBot;

		if (ronda % 2 == 1) {				//En las rondas impares empieza el jugador haciendo la apuesta
			apuestaJ = apuesta(piedrasJ, nMax);

			do {					//Se comprueba que la apuesta de la Máquina no coincida con la del jugador
				apuestaB = apuestaBot(piedrasBot, nMax);
			} while (apuestaB == apuestaJ);

			cout << "Yo creo que hay " << apuestaB << " en total." << endl;

		}
		else {						//En las rondas pares empieza la Máquina haciendo la apuesta
			apuestaB = apuestaBot(piedrasBot, nMax);
			cout << "Yo creo que hay " << apuestaB << " en total." << endl;

			do {					//Se comprueba que la apuesta del jugador no coincida con la de la Máquina
				apuestaJ = apuesta(piedrasJ, nMax);
			} while (apuestaB == apuestaJ);
		}
								//Se muestran ambas apuestas y el número de piedras total
		cout << "Tú has apostado: " << piedrasJ << ", y yo : " << piedrasBot << " y en total eran " << piedrasTot << endl;

								//Se llama a la función que anuncia el ganador
		ganador(apuestaJ, apuestaB, piedrasTot, puntosJ, puntosB); 
	}
	
	while (puntosJ == puntosB) {				//En caso de empate se propone una ronda de desempate
		cout << "Hemos empatado, ¿quieres una ronda de desempate? " << endl << "0.- No " << endl << "1.- Sí" << endl;
		cin >> desempatando;

		if (desempatando == 0) {			//Si no quiere desempatar simplemente se pone fin al juego
			return false;
		}
		else if (desempatando == 1) {			//Si es al contrario, se comenzará una ronda extra de desempate
			return true;
		}
		else {						//Si se selecciona una opción no válida, se envía mensaje de error
			cout << "Eso no es un input correcto. " << endl;
		}
	}
								//En caso que haya un ganador se anuncia y se finaliza el juego
	cout << "Fin del juego. Resultados: " << endl; 
	cout << "Ganadas por ti: " << puntosJ << endl;
	cout << "Ganadas por mi: " << puntosB << endl;

	if (puntosJ > puntosB) {				//Si gana el jugador:
		cout << "¡ENHORABUENA! Has ganado el juego :) " << endl;
	}							//Si gana la Máquina:
	else if (puntosB > puntosJ) {
		cout << "Has perdido el juego :(" << endl;
	}
	return false;						//Se devuelve false para que termine el juego.
}

//-----------------------------------------------------------------------------------------------------------------------
//Función que dicta el ganador de la ronda:

void ganador(int totalJ, int totalM, int total, int& puntosJ, int& puntosBot) {
	//Hemos cambiado el tipo de función y añadido los punteros del marcador que recogen los puntos del jugador y la 
	//máquina para evitar repetir un swich que realizara la comprobación

		if (totalJ == total) {				//Se comprueba quien ha ganado la ronda y se le suma un punto al ganador
			cout << "Tú ganas la ronda. " << endl;
			puntosJ += 1;
		}
		else if (totalM == total) {
			cout << "Gano la ronda" << endl;
			puntosBot += 1;
		}
		else {						//En caso de empate, se anuncia y no se le suma punto a nadie
			cout << "Nadie ha acertado " << endl;
		}
}
