
/* **********************************************************************************************************************
NOMBRE DEL PROYECTO:	Práctica 2 implementada como Práctica 3

OBJETIVO:		Práctica 2: Desarrollar el juego "Cuatro en línea".
			Práctica 3: Implementar el guardado de datos de la partida.

AUTOR: 			MARIO FERNANDEZ FERNANDEZ & DAVID ORTEGA LOZANO

FECHA DE CREACIÓN:	08/11/2022
********************************************************************************************************************** */

/*
  ·	Como las instrucciones no lo especifican, he decidido que el archivo txt en el que se guardan los datos tenga un
	centinela: "***"
  ·	Cuando no se encuentra el archivo se crea solo para la siguiente partida
*/

//-----------------------------------------------------------------------------------------------------------------------
//BIBLIOTECAS:
#include <iostream>							//Biblioteca de espacios de caracteres
	using namespace std;						//Espacio de nombres estándar
#include <windows.h>							//Biblioteca de herramientas de consola de windows
#include <string>							//Biblioteca de funciones de texto
#include <fstream>							//Biblioteca de entrada y salida de flujos a archivos externos


//-----------------------------------------------------------------------------------------------------------------------
//CONSTANTES:
	//CONSTANTES DE LAS DIMENSIONES DEL TABLERO:
const int MAX_H = 33;							//Número de caracteres que tiene el tablero de ancho.

/*Ten en cuenta que si quieres ampliar el tablero a lo ancho, tendrás que sumarle de cuatro en cuatro a la
constante "MAXH".*/

const int MAX_V = 28;							//Número de caracteres que tiene el tablero de alto.

/*Para ampliar el tablero a lo alto ocurre lo mismo que a lo ancho pero tendrá que tener en cuenta las
últimas tres líneas que están fuera de la cuadricula y corresponden la primera a la numeración de las
columnas y las dos últimas a los mensajes de victoria y error.*/

const int DIST = 4;							//Número de caracteres entre casillas.

/*La distancia es fija independientemente del número de columnas y filas que haya, corresponde a las medidas
cuadradas de las celdas más uno.*/

const int L_MENSAJE = 3;						//Líneas debajo del tablero dedicadas a enviar mensajes de 
														//victoria o error.

/*La primera son los números de las columnas que desaparecen al intentar colocar una ficha cuando la
respectiva columna está llena.*/


//CONSTANTES ESTABLECIDAS PARA ASEGURAR QUE SUS VALORES NO VARÍEN Y EVIRTAR LOS "MAGIC NUMBERS":
const int N_COLUM = (MAX_H - 1) / DIST;					//Número de Columnas.
const int N_FILAS = (MAX_V - L_MENSAJE - 1) / DIST;			//Número de Filas.
const int N1 = 49;							//Caracter '1'.
const int OBJETIVO = 4;							//Número de fichas consecutivas necesarias para ganar el juego.
const int MAX_J = 20;							//Número máximo de jugadores que se pueden registrar.


//CONSTANTES DE LOS CARACTERES ESPECIALES ASCII EMPLEADOS EN LA ESTRUCTURA DEL TABLERO:
const int GH = 196, GV = 179;						//Caracter de guiones horizontales y verticales.

const int ENCRUZ_4 = 197;						//Caracter de encrucijada de cuatro puntas.

const int ENCRUZ_3_AR = 194;						//Caracter de encrucijada de tres puntas hacia abajo.
const int ENCRUZ_3_AB = 193;						//Caracter de encrucijada de tres puntas hacia arriba.
const int ENCRUZ_3_I = 195;						//Caracter de encrucijada de tres puntas hacia la derecha.
const int ENCRUZ_3_D = 180;						//Caracter de encrucijada de tres puntas hacia la izquierda.

const int ESQUINA_AR_I = 218;						//Caracter de esquina superior izquierda.
const int ESQUINA_AB_I = 192;						//Caracter de esquina inferior izquierda.
const int ESQUINA_AR_D = 191;						//Caracter de esquina superior derecha.
const int ESQUINA_AB_D = 217;						//Caracter de esquina inferior derecha.

//CONSTANTES DE LOS MENSAJES QUE APARECEN EN PANTALLA CON LONGITUD COMÚN:
const string error1  = "Nº de columna no disponible";			//Primera linea del mensaje de error por seleccionar una columna 
									//llena o no incluida en el tablero.
const string error2  = "   Introduce otra opcion   ";			//Segunda linea del mensaje de error por elección de una columna
									//llena o no incluida en el tablero.
const string ganado1 = "        Felicidades        ";			//Mensaje superior de victoria.
const string ganado2 = "  El Jugador 2 ha ganado   ";			//Mensaje inferior de victoria que establece quien ha ganado la 
									//partida.
const string mTurno  = "   Turno del Jugador 1:    ";			//Mensaje inicial de turno.
const string vacio   = "                           ";			//Mensaje vacío para borrar los mensajes escritos anteriormente.
const string instruc = "  Selecciona una columna:  ";			//Mensaje que da la instrucción de seleccionar una columna.
const string empate1 = "          EMPATE           ";			//Mensaje de empate de arriba.
const string empate2 = "      Nadie ha ganado      ";			//Mensaje de empate superior de abajo.
const string empate3 = "    La próxima vez será    ";			//Mensaje de empate inferior de abajo.


//-----------------------------------------------------------------------------------------------------------------------
//DATOS ENUMERADOS:
enum Casilla { VACIO, JUGADOR1, JUGADOR2 };				//Definición del dato "Casilla" con las opciones Vacío(0), 
									//Jugador1(1) y Jugador2 (2).


//-----------------------------------------------------------------------------------------------------------------------
//TIPOS DE DATOS ESTRUCTURADOS:
typedef struct {							//Definición del tipo de dato "Tablero" que cuenta con una matriz
	char matriz[(MAX_H + 1)][(MAX_V + 1)];				//de la dimensiones del tablero, un conatador de espacios en 
	int contador;							//blanco y una matriz de tipo "Casilla" con las dimensiones del 
	Casilla casillas[(N_COLUM + 1)][(N_FILAS + 1)];			//número columnas y filas.
} Tablero;

typedef struct {							//Definición del tipo de dato "Jugador" que cuenta con el nombre,
	string ID;							//el número de partidas ganadas y el número de partidas perdidas.
	int pGanadas;
	int pPerdidas;
} Player;

/*He decidido llamarlo "Player" porque ya empleo variables auxiliares con el nobre de "j" y así el tipo de dato y el
nombre de la variable siguen guardando relación.*/

typedef struct {							//Definición del tipo de dato "DatosPartida" que se compone por:
	Player lista[MAX_J];						//la lista de jugadores registrados de tipo "Player", el nº de 
	int nJugadores;							//jugadores registrados y la posición de los jugadores que están 
	int j1;								//jugando.
	int j2;
} DatosPartida;

/*Para almacenar la posición de los 2 jugadores durante toda la partida, he decidido que se guarden como un dato más de
la variable datos partida, ya que su posición es más útil que sus IDs, ya que me ahorro tener que estar implementando la
función "buscaJugador".*/


//-----------------------------------------------------------------------------------------------------------------------
//INICIALIZACIÓN DE FUNCIONES:

//Procedimiento que inicializa la "matriz", el "contador" y las "casillas" de la variable t de tipo Tablero.
void inicializaTablero(Tablero& t);
//Función que carga los datos de los jugadores.
bool cargaDatos(DatosPartida& d);
//Función que solicita el registro del jugador y lo crea en caso de que no exista.
bool iniciarSesion(DatosPartida& d);
//Función que muestra la lista de opciones.
int menu();
//Función que busca al jugador en la lista.
int buscaJugador(DatosPartida d, string nick);
//Función que añade un nuevo jugador dando mensaje de error si no cabe.
bool guardarJugadorNuevo(DatosPartida& d, Player p);
//Procedimiento que muestra la información del jugador con el nick especificado.
void muestraInfo(DatosPartida d, int jugador);
//Procedimiento que muestra la información de todos los jugadores.
void infoJugadores(DatosPartida d);
//Procedimiento que lleva a cabo la ejecución del programa.
void juegoConecta4 (Tablero& t);
//Procedimiento que muestra en consola la "matriz" de la variable "t" de tipo "Tablero".
void muestraTablero(const Tablero t);
//Función que comprueba si quedan espacios libres en el tablero.
bool quedanHuecos(const Tablero t);
//Función que comprueba que la columna seleccionada no esté completa.
bool columnaLlena(const Tablero t, int columna);
//Procedimiento que coloca la ficha del color correspondiente a cada jugador.
void muestraCharColor(Casilla c);
//Función que recoge la columna en la que se coloca la ficha y devuelve la fila vacía más baja. 
int	 ponerFicha(const Tablero t, int columna);
//Función que comprueba si el último jugador en colocar ficha ha ganado por recursividad.
bool ganador(const Tablero t, int fila, int columna, int x, int y, int direccion, int puntos);
//Procedimiento que actualiza la lista de jugadores.
void actualizaJugador(DatosPartida& d, int jugador);
//Procedimiento que imprime mensajes en la matriz caracter a caracter.
void printEnPantalla(int finMensaje, Tablero& t, int inicioMensaje, string mensaje, int linea);
//Procedimiento que guarda los datos de todos los jugadores registrados en el archivo "jugadores.txt".
void guardaDatos(DatosPartida d);


/*_______________________________________________________________________________________________________________________
	FUNCIÓN PRINCIPAL DEL CÓDOGO:
-----------------------------------------------------------------------------------------------------------------------*/
int main() {

	//VARIABLES LOCALES:
	Tablero t;							//Se inicia la variable "t" de tipo "Tablero".
	DatosPartida d;							//Se inicia la variable "d" de tipo "DatosPartida".
	int opcion;							//Variable que recoge la opción seleccionada en el menú.
	string nombre;							//Variable que recoge el nombre del que se busca información.
	int posicion;							//Variable que recoge la posición en el array del jugador.
	bool continuar;							//Variable auxiliar de comprobación para salir de bucles.


	if (cargaDatos(d)) {						//Se cargan los datos y en caso de que no se pueda abrir el 
									//archivo se termina el programa.

		if (iniciarSesion(d)) {					//Se inicia sesión y en caso de que la lista esté llena y se 
									//quiera salir se pone fin al programa.
			do {
				continuar = true;			//Se inicializa la variable continuar a true como salto de fe.

				opcion = menu();			//Se recoge la opción seleccionada en el menú.
				switch (opcion) {
				case 0:					//Si se quiere salir se procede a guardar datos.

					break;

				case 1:					//Para jugar se dispone el tablero, se limpia la consola y se 
									//inicia el juego.

					inicializaTablero(t);		//Se rellena la matriz que se imprime como tablero.
					system("CLS");			//Se borra todo lo que haya en consola.
					juegoConecta4(t);		//Se desarrolla el juego.
					break;

				case 2:					//Para mostrar la información de los jugadores activos, se 
									//presentan y se busca su información con las posiciones 
									//guardadas en los datos de la partida.

					cout << endl << " Información del jugador 1:" << endl;
					muestraInfo(d, d.j1);
					cout << endl << " Información del jugador 2:" << endl;
					muestraInfo(d, d.j2);
					break;

				case 3:					//Para mostrar los datos de todos los jugadores, se accede a la
									//función que muestra su información.

					infoJugadores(d);
					break;

				case 4:					//Para buscar información sobre un jugador concreto, se solicita 
									//su nombre, se busca si existe y su posición, en caso de que 
									//exista se muestra su información y en caso contrario se muestra 
									//un mensaje de error y se vuelve a mostrar el menú.

					cout << " Introduce el ID del jugador que quieres buscar:" << endl;
					cin >> nombre;
					if (posicion = buscaJugador(d, nombre), posicion != -1) {

						muestraInfo(d, posicion);
					}
					else {
						cout << endl << " Error, Jugador no registrado" << endl << endl;
						continuar = false;
					}
				}
			} while (!continuar);
		}
	}
	guardaDatos(d);
	
	return 0;							//Se devuelve "0" para comprobar que todo ha ido bien.
}

//-----------------------------------------------------------------------------------------------------------------------
//Procedimiento que establece la "matriz", el "contador" y las "casillas" de la variable "t" de tipo "Tablero":

void inicializaTablero(Tablero& t) {

	//VARIABLES LOCALES:
	int k = N1;							//Variable que recoge el caracter '1'.

	t.contador = N_COLUM * N_FILAS;					//Se inicializa el valor del "contador" de espacios vacíos al 
									//número total de casillas.

	for (int i = 0; i <= N_COLUM; i++) {				//Se inicializa "casillas" de la variable "t" del tipo de dato 
		for (int j = 0; j < N_FILAS; j++) {			//"Tablero", llenándola con el valor "0" del tipo "Casilla".
			t.casillas[i][j] = Casilla(0);			//En la matriz de tipo casilla tan solo se usan las casillas a 
		}							//partir del (1,1) obviando la fila y columna 0 para simplificar
	}								//el codigo.

	for (int i = 0; i <= MAX_H; i++) {				//Se  la matriz de la variable "t" del tipo "Tablero",
		for (int j = 0; j <= MAX_V; j++) {			//para ello la lleno con el caracter espacio.
			t.matriz[i][j] = ' ';
		}
	}

	for (int i = 1; i <= MAX_H; i += DIST) {			//A continuación se pintan todas las barras horizontales formando
		for (int j = 1; j <= MAX_V - 3; j++) {			//columnas separadas por 3 espacios.
			t.matriz[i][j] = char(GV);
		}
	}
	for (int i = 1; i <= MAX_V - L_MENSAJE; i += DIST) {		//A continuación se pintan todos los guiones formando una 
		for (int j = 1; j <= MAX_H; j++) {			//cuadrícula junto con las columnas, dejando casillas de 3x3.
			t.matriz[j][i] = char(GH);
		}
	}
									//Una vez hecha la cuadricula, se pintan las interseciones entre
	for (int i = 5; i < MAX_H - (DIST - 1);i += DIST) {		//filas y columnas internas con encrucijadas en forma de cruz.
		for (int j = 5; j < MAX_V - L_MENSAJE; j += DIST) {
			t.matriz[i][j] = char(ENCRUZ_4);
		}
	}
									//Después se pintan las encrucijadas del marco que tienen forma 
	for (int i = 5; i < MAX_H; i += DIST) {				//de "T" cuidando que la parte plana corresponda con el exterior
		t.matriz[i][1] = char(ENCRUZ_3_AR);			//del marco.
		t.matriz[i][MAX_V - L_MENSAJE] = char(ENCRUZ_3_AB);
	}
	for (int i = 5; i < MAX_V - L_MENSAJE; i += DIST) {
		t.matriz[1][i] = char(ENCRUZ_3_I);
		t.matriz[MAX_H][i] = char(ENCRUZ_3_D);
	}

	t.matriz[1][1] = char(ESQUINA_AR_I);				//Por último se pintan las cuatro esquinas del marco.
	t.matriz[1][MAX_V - L_MENSAJE] = char(ESQUINA_AB_I);
	t.matriz[MAX_H][1] = char(ESQUINA_AR_D);
	t.matriz[MAX_H][MAX_V - L_MENSAJE] = char(ESQUINA_AB_D);

	for (int j = 3; j <= MAX_H; j += DIST) {			//Al final, dejando dos lineas en blanco por debajo, se escribe a 
		t.matriz[j][MAX_V - 2] = char(k);			//continuación de la cuadrícula de forma centrada el número de la 
		k++;							//columna correspondiente.
	}
}

//-----------------------------------------------------------------------------------------------------------------------
//Función que carga los datos de los jugadores y devuelve si se ha abierto el archivo:

bool cargaDatos(DatosPartida& d) {
	/*He decidido hacer esta función de tipo bool para que me devuelva si se ha abierto el archivo o no y así poder poner
	fin al juego.*/

	//VARIABLES LOCALES:
	Player p;							//Se inicia una variable "p" de tipo "Jugador" en la que guardo 
									//los datos registrados temporalmente.
	int i = 0;							//Contador del número de jugadores registrados.
	bool abierto = true;						//Variable bool que recoge lo que devuelve la función.


	ifstream dJ;							//Selecciono la función de lectura del archivo datos del Jugador 
	dJ.open("jugadores.txt");					//e intento abrir el archivo.

	if (dJ.is_open()) {						//Si el archivo se ha abierto, entonces guardo sus datos en la 
									//variable "d".

									//(Sé que no te gusta, pero me ahorra bastante código y una 
		while (dJ >> p.ID, p.ID != "***" && i < MAX_J) {	//variable bool de comprobación).

			dJ >> p.pGanadas >> p.pPerdidas;		//Guardo los datos de cada jugador en "p" para después copiarla  
			d.lista[i] = p;					//en su corespondiente posición del array de "d".
			i++;
		}
		d.nJugadores = i;					//Sumo 1 al contador y lo copio como el número de jugadores 
									//registrados.

		dJ.close();						//Solo en caso de que se haya abierto el archivo lo cierro.
	}
	else {								//Si el archivo no llega a abrirse devuelvo false y envío un 
		abierto = false;					//mensaje de error a consola.
		cout << " A habido un problema al abrir el archivo" << endl;
	}

	return abierto;							//Devuelvo la variable bool "abierto".
}

//-----------------------------------------------------------------------------------------------------------------------
//Función que solicita el registro del jugador y lo crea en caso de que no exista:

bool iniciarSesion(DatosPartida& d) {
	/*Esta función nos decías que devolviera un dato de tipo "Player", pero como tienen que iniciar sesión dos jugadores,
	he pensado que sería más útil guardar su posición dentro del array en el dato de tipo "DatosPartida", y así me evito
	tener que poner más referencias en el resto de funciones. Además, para el caso de que se intente guardar un jugador
	con la lista llena, y después se trate de salir, se puede indicar devolviendo false.

	También habías puesto referencia al nick en esta función, pero creo que queda más ordenado que se solicite el nick
	dentro.*/

	//VARIABLES LOCALES:
	Player p;							//Variable auxiliar que recoge los datos del nuevo jugador o el 
									//ID de jugadores ya existentes.
	int opcion;							//Variable que recoge como proseguir en caso de error.
	bool continuar;							//Variable auxiliar que dicta la salida del bucle.
	bool todoHaIdoBien = true;					//Variable auxiliar que se devuelve al final de la función.
	int posicion;							//Variable que recoge la posición de los jugadores en el array.

	for (int i = 1; i <= 2; i++) {	 				//Se repite el bucle dos veces para registrar a ambos jugadores.

		do {							//Se solicita el Id del jugador y se le da la bienvenida.
			opcion = 0;
			cout << endl << " Buenos días jugador " << i << ", por favor, introduce tu nombre sin espacios" << endl;
			cin >> p.ID;
			cout << " Bienvenido " << p.ID << endl;
									//Se comprueba si el jugador ya está registrado.
			if (posicion = buscaJugador(d, p.ID), posicion == -1) {
				p.pGanadas = 0;				//En caso de que no, se inicializa el número de partidas ganadas 
				p.pPerdidas = 0;			//y perdidas para registrarlo.

				if (!guardarJugadorNuevo(d, p)) {	//Si la lista ya está llena, se anuncia y se le da la opción de 
									//probar con otro nombre o de salir.
					cout << " No estás registrado y no hemos podido registrarte por falta de espacio." << endl;
					cout << " Indica que quieres hacer a continuación:" << endl << endl;
					cout << " 1. Salir" << endl;
					cout << " 2. Introducir otro nombre" << endl;

					do {				//Antes de continuar, se comprueba que la opción introducida esté
						continuar = true;	//entre los valores posibles, en caso contrario, se muestra 
						cin >> opcion;		//mensaje de error y se solicita de nuevo.
						if (opcion != 1 && opcion != 2) {
							cout << " Opcion no valida, introduce una de las dos opciones:" << endl;
							continuar = false;
						}
					} while (!continuar);

					if (opcion == 1) {		//En caso de que se desee salir, se devolverá "false" y se le da 
						todoHaIdoBien = false;	//un valor a "i" para salir del bucle.
						i = 3;
					}
				}					//Si todo ha ido bien se anuncia en pantalla que el nuevo jugador 
				else {					//ya ha sido registrado.
					cout << " Te has registrado correctamente" << endl << endl;
					posicion = (d.nJugadores - 1);	//La posición del jugador será 1 menos que el nº de jugadores
				}					//registrados.
			}
			else {						//Si el jugador ya se había registrado se le da la bienvenida.
				cout << " Cuanto tiempo, buena suerte" << endl << endl;
			}						//En caso de que el jugador quiera probar con otro ID ya que la
		} while (opcion == 2);					//lista estaba llena, se repite la solicitud.

		if (i == 1) {						//Se guarda la posición de ambos jugadores en el dato 
			d.j1 = posicion;				//estruccturado "DatosPartida".
			cout << " Turno del jugador 2" << endl;
		}
		else if (i == 2)
			d.j2 = posicion;
	}

	return todoHaIdoBien;						//Se devuelve si todo ha ido bien o si se quiere salir.
}

//-----------------------------------------------------------------------------------------------------------------------
//Función que muestra la lista de opciones:

int menu() {
	/*He decidido hacer esta función para hacer más ordenado el código*/

	//VARIABLES LOCALES:
	int opcion;							//Variable auxilar que recoge la opción que devuelve la función.
	bool continuar = true;						//Variable auxiliar que dicta la salida del bucle.

									//Se muestran las opciones del menú.
	cout << " Seleccione una de las siguientes opciones: " << endl;
	cout << " 0. Salir" << endl;
	cout << " 1. Jugar" << endl;
	cout << " 2. Ver mi información" << endl;
	cout << " 3. Ver información de los jugadores" << endl;
	cout << " 4. Buscar información de un jugador" << endl;

	do {
		continuar = true;					//Se da un salto de fe y se dice que se va a continuar.

		cin >> opcion;						//Se solicita la opción seleccionada.

		if (opcion < 0 || opcion > 4) {				//Se comprueba que la opción es valida y en caso de que no lo sea
			continuar = false;				//se niega continuar y se envía mensaje de error solicitandolo de 
									//nuevo.
			cout << " La opción introducida no es posible, seleccione otra opción:" << endl;
		}
	} while (!continuar);
	return opcion;
}

//-----------------------------------------------------------------------------------------------------------------------
//Función que busca al jugador en la lista:

int buscaJugador(DatosPartida d, string nick) {

	//VARIABLE LOCALES:
	int linea = -1;							//Variable auxiliar que guarda el valor que devuelve la función
									//inicializada a -1 para el caso de que no encuentre el jugador.

	if (d.nJugadores != 0) {
		for (int i = 0; i < d.nJugadores; i++) {		//Se recorre toda la lista de jugadores registrados buscando 
			if (d.lista[i].ID == nick) {			//alguno que coincida con el que se busca, en cuyo caso se 
				linea = i;				//devuelve su posición y se establece un valor a "i" para 
				i = d.nJugadores;			//salir del bucle.
			}
		}
	}
	return linea;							//Se devuelve el valor de la variable "linea".
}

//-----------------------------------------------------------------------------------------------------------------------
//Función que añade un nuevo jugador dando mensaje de error si no cabe:

bool guardarJugadorNuevo(DatosPartida& d, Player p) {

	//VARIABLES LOCALES:
	bool hayHueco = true;						//Variable auxiliar que recoge lo que devuelve la función.

	if (d.nJugadores < 20) {					//Se Comprueba que la lista no esté llena.

		d.lista[d.nJugadores] = p;				//Se guarda el nuevo jugador tras el último jugador registrado y
		d.nJugadores++;						//se le suma 1 al numero de jugadores registrados.
	}
	else {								//En caso de que no haya hueco, se devuelve false y se envía un 
		hayHueco = false;					//mensaje de error.
		cout << " ERROR, lista de jugadores llena" << endl;
	}
	return hayHueco;						//Se devuelve si a habido hueco para guardar al nuevo jugador.
}

//-----------------------------------------------------------------------------------------------------------------------
//Procedimiento que imprime mensajes en la matriz caracter a caracter:

void printEnPantalla(int finMensaje, Tablero& t, int inicioMensaje, string mensaje, int linea) {

	/*He hecho esta función para poder copiar en la matriz mensajes y que estos queden centrados respecto a la cuadrícula
	los mensajes tienen una longitud comun "finMensaje" y se colocan a partir de la posición "inicioMensaje" en una
	"línea" entre la 0 o las dos finales.*/

	for (int i = 0; i < finMensaje; i++) {				//Se recorre la longitud del mensaje copiando caracter a caracter 
		t.matriz[inicioMensaje + i][linea] = mensaje[i];	//sumandole a las cordenadas del tablero "InicioMensaje". 
	}
}

//-----------------------------------------------------------------------------------------------------------------------
//Procedimiento que muestra la información del jugador con el nick especificado:

void muestraInfo(DatosPartida d, int jugador) {
	/*Ya se ha buscado la posición a la que pertenecen los ID de los jugadores, me parece más eficiente trabajar con esos
	datos antes que con sus nombres y así ahorrarme tener que buscarlos de nuevo. Además, de este modo hago que la
	función sea más versatil y valga para las tres opciones que buscan información en el registro.*/


	cout << "     ID: " << d.lista[jugador].ID << endl;		//Se muestra el ID y el nº de partidas ganadas y perdidas.
	cout << "     Nº de partidas ganadas: " << d.lista[jugador].pGanadas << endl;
	cout << "     Nº de partidas perdidas: " << d.lista[jugador].pPerdidas << endl;
}

//-----------------------------------------------------------------------------------------------------------------------
//Procedimiento que muestra la información de todos los jugadores:

void infoJugadores(DatosPartida d) {

	for (int i = 0; i < d.nJugadores; i++) {			//Se recorre el registro de jugadores, mostrando su información.
		cout << endl << " Información de jugador nº " << i + 1 << ":" << endl;
		muestraInfo(d, i);
	}
}

//-----------------------------------------------------------------------------------------------------------------------
//Procedimiento que lleva a cabo la ejecución del programa:

void juegoConecta4(DatosPartida& d, Tablero& t) {

	/*He decidido cambiar el parametro "t" de tipo "Tablero" a una referencia variable en vez de una constante ya que el
	código se desarroya por coordenadas.*/

	/*En la Práctica 3 no he empleado la referencia al dato player ya que he guardado la posición de los jugadores en el
	array dentro de los datos de la partida, de modo que hago referencia a todo el dato en vez de  únicamente al array
	para tener acceso a estas.*/

	//VARIABLES LOCALES:
	bool continuar = true;						//Variable que recoge si se debe continuar o no.
	int columna;							//Variable que recoge el número de la columna.
	int x = 0, y = 0;						//Variables que recogen las coordenadas de la última ficha. 
	int jTurno = 1;							//Variable aux que alterna el turno.

	int esp = error1.length();					//Espacio del cuadro de texto.
	int inMensaje = (MAX_H - (esp)) / 2 + 1;			//Posición del primer carcter de los mensajes.
	int turno = inMensaje + 21;					//Posición del número del jugador al que le toca jugar.
	int jGanador = inMensaje + 13;					//Posición del número del jugador ganador.

									//Se coloca centrado sobre la cuadrícula el texto del turno.
	printEnPantalla(esp, t, inMensaje, mTurno, 0);			//Se coloca centrado debajo de la cuadricula las instrucciones.
	printEnPantalla(esp, t, inMensaje, instruc, MAX_V - 1);

	do {
		if (quedanHuecos(t)) {					//Se comprueba si siguen quedando casillas libres y quito un
			t.contador--;					//hueco dando por hecho que se colocará una ficha.

			do {						//En un bucle con la salida de seleccionar una columna existente
									//o no llena:
				system("CLS");				//Se borra todo lo de la pantalla.
				muestraTablero(t);			//Se muestra la última actualización de la matriz de la variable 
									//"t".

				cin >> columna;				//Se solicita una columna y se comprueba que esté dentro de las
									//opciones.
				if (columna >= 1 && N_COLUM >= columna) {
					x = columna;
					continuar = true;
					if (columnaLlena(t, x)) {	//Se comprueba que la columna correspondiente no esté llena.
						t.matriz[x * DIST - 1][MAX_V - 2] = ' ';
						continuar = false;
					}
				}
				else continuar = false;
									//Si no se cumple 1 de las 2 o ambas, se envían mensajes de error
				if (!continuar) {			//a consola y se repite la solicitud.
					printEnPantalla(esp, t, inMensaje, error1, MAX_V - 1);
					printEnPantalla(esp, t, inMensaje, error2, MAX_V);
				}
				else {					//Si se cumplen ambas, borro posible mensaje de error.
					printEnPantalla(esp, t, inMensaje, instruc, MAX_V - 1);
					printEnPantalla(esp, t, inMensaje, vacio, MAX_V);
				}
			} while (continuar == false);

			y = ponerFicha(t, x);				//Se emplea la función poner ficha para recivir en que fila de la 
			if (jTurno == 1)				//columna se coloca la ficha.
				t.casillas[x][y] = Casilla(1);		//Se comprueba quien está colocando la ficha para saber a quien 
			else t.casillas[x][y] = Casilla(2);		//adjudicarsela.
			t.matriz[x * DIST - 1][(y + 1) * DIST - 1] = char(4);//Y por último, se pinta la ficha en la matriz.

			if (ganador(t, y, x, 0, 0, 1, 0)) {		//Se compruebo si el último jugador ha ganado y en caso que sí lo 
									//anuncio en la consola y se niega continuar.
				printEnPantalla(esp, t, inMensaje, ganado1, 0);
				printEnPantalla(esp, t, inMensaje, ganado2, MAX_V - 1);

				actualizaJugador(d, jTurno);		//Se actualiza la lista de jugadores

														
				if (jTurno == 1)			//Para anunciar el ganador, se comprueba quien fue el último
					t.matriz[jGanador][MAX_V - 1] = char(N1);
				system("CLS");				//Se borra todo lo de la pantalla.
				muestraTablero(t);			//Se muestra la última actualización de la matriz del tablero se
				continuar = false;			//ponge fin al juego negando continuar.
			}
			else {						//Si nadie ha ganado, se continua el juego.

				jTurno *= -1;				//Se multiplica por -1 la variable del turno para alternarlo y se
				if (jTurno == 1)			//actualiza en la matriz. 
					t.matriz[turno][0] = N1;
				else t.matriz[turno][0] = N1 + 1;
			}
		}
		else {							//En caso de que ya no queden huecos, se niega "continuar" y se
			continuar = false;				//anuncia que han empatado.

			printEnPantalla(esp, t, inMensaje, empate1, 0);
			printEnPantalla(esp, t, inMensaje, empate2, MAX_V - 1);
			printEnPantalla(esp, t, inMensaje, empate3, MAX_V);

			system("CLS");					//Se borra todo lo de la pantalla.
			muestraTablero(t);				//Se muestra la última actualización de la matriz del tablero
		}							//dando fin al juego.
	} while (continuar);
}

//-----------------------------------------------------------------------------------------------------------------------
//Procedimiento que muestra en consola la "matriz" de la variable "t" de tipo "Tablero":

void muestraTablero(const Tablero t) {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);		//Se establece la herramienta para cambiar el color en que se 
									//imprime en pantalla.
	//VARIABLES LOCALES:
	int x, y;							//Variables que recogen las coordenadas de las fichas 
									//correspondientes a la matriz de tipo "Casilla".

	for (int j = 0; j <= MAX_V; j++) {				//Se recorre toda la matriz, mostrandola en pantalla y haciendo 
		for (int i = 0; i <= MAX_H; i++) {			//un salto de linea al acabar cada fila.
			if (t.matriz[i][j] == char(4) && j < (MAX_V - L_MENSAJE) && j >= (DIST - 1)) {
									//Las dos últimas comprobaciones de "j" están para evitar una 
									//advertencia, aunque nunca podría haber una ficha ubicada en ese
									//marjen que de error.

				x = (i + 1) / DIST;			//Se comprueba si lo que se va a mostrar en pantalla es una ficha
				y = (j + 1) / DIST - 1;			//y de quien es, cambiando el color en que se muestra a través de 
				muestraCharColor(t.casillas[x][y]);	//la función "muestraCharColor".
			}
			cout << t.matriz[i][j];				//Se muestra el caracter y por si se cambió el color en que se 
			SetConsoleTextAttribute(hConsole, 15);		//escribe en la consola, se reestablece.
		}
		cout << endl;
	}
}

//-----------------------------------------------------------------------------------------------------------------------
//Función que comprueba si quedan espacios libres en el tablero:

bool quedanHuecos(const Tablero t) {

	//VARIABLES LOCALES:
	bool continuar;							//Variable local que recoge el valor que se devuelve.

	if (t.contador == 0) 						//Se comprueba que el contador no haya llegado a 0 todavía, se
		continuar = false;					//niega "continuar" en caso de que sea cierto y se afirma en caso 
	else continuar = true;						//contrario.

	return continuar;						//Se devuelve "continuar".
}

//-----------------------------------------------------------------------------------------------------------------------
//Función que comprueba que la columna seleccionada no esté completa:

bool columnaLlena(const Tablero t, int columna) {

	//VARIABLES LOCALES:
	bool continuar;							//Variable local que recoge el valor que se devuelve.

	if (t.casillas[columna][0] != Casilla(0))			//Se compruebo si la casilla superior está "Vacía", en caso de  
		continuar = true;					//que se cumpla, se afirma "continuar", si no, se niega.
	else continuar = false;

	return continuar;						//Se devuelve "continuar".
}

//-----------------------------------------------------------------------------------------------------------------------
//Función que recoge la columna en la que se coloca la ficha y la coloca en la casilla vacía de más abajo:

int ponerFicha(const Tablero t, int columna) {

	//VARIABLES LOCALES:
	int fila = 0;							//Variable que recoge la fila en la que se coloca la ficha y se 
									//inicializa por si no llega a entrar en el bucle.

	for (int i = N_FILAS; i >= 0; i--) {				//Se busca empezando por abajo hacia arriba cual es la primera 
		if (t.casillas[columna][i] == Casilla(0)) {		//casilla libre, y si se encuentra, se da un valor imposible a
			fila = i;					//"i" para salir del bucle.
			i = -1;
		}
	}
	return fila;							//Se devuelve la fila en la que se coloca la ficha.
}

//-----------------------------------------------------------------------------------------------------------------------
//Función que comprueba si el último jugador en colocar ficha ha ganado:

bool ganador(const Tablero t, int fila, int columna, int x, int y, int direccion, int puntos) {
	/*He hecho de la función "ganador" una recursiva para lo que he añadido los parámetros de "x" e "y", para guardar la
	casilla consecutiva que he de comprobar respecto de la original; el parámetro de "direccion", para guardar que
	sentido y dirección estoy comprobando; y el parámetro de "puntos", para guardar el nº de casillas consecutivas que
	llevo en la misma dirección.*/

	//VARIABLES LOCALES:
	bool ganado = false;						//Variable auxilir que recoge si ha ganado alguien, se inicializa 
									//negandola y el es el valor que se devuleve al final.

	if (t.casillas[columna][fila] == t.casillas[columna - x][fila - y])
		puntos++;						//Es una función recursiva, comienza en cero puntos en la primera 
	else {								//vez que se comprueba, por lo que se mira si la casilla es igual
		x = 0;							//a sí misma, pero en adelante, se empieza en 1 punto y 
		y = 0;							//comprobando la casilla consecutiva, cada vez que se cambia de 
		direccion++;						//dirección pero no de sentido, se resetean los puntos.
		if (direccion % 2 == 0)
			puntos = 1;
	}

	if (puntos == 4) 						//Cuando se obtienen cuatro puntos en línea, entonces se afirma 
		ganado = true;						//"ganado" y no se hacen más comprobaciones.

	else {								//En el caso contrario, se continua con la comprobación de forma 
		switch (direccion) {					//recursiva, guadando si se ha ganado o no en "ganado".
		case 1:
			y--;						//1ª dirección, vertical, caso 1:
			break;						//No se comprueba la dirección vertical ascendente ya que la 
		case 2:							//última ficha colocada es obligatoriamente la de arriba.
			x++;
			break;						//2ª dirección, horizontal, caso 2 y 3:
		case 3:
			x--;
			break;
		case 4:
			x++; y++;
			break;						//3ª dirección, diagonal ascendente izquierda, caso 4 y 5:
		case 5:
			x--; y--;
			break;
		case 6:
			x--; y++;
			break;						//4ª dirección, diagonal ascendente derecha, caso 6 y 7:
		case 7:
			x++; y--;
			break;
		case 8:
			ganado = false;					//En el caso de haber recorrido todas las direcciones y no haber 
		}							//cuatro en línea se niega "ganado".
		if (direccion <= 7)
			ganado = ganador(t, fila, columna, x, y, direccion, puntos);
	}
	return ganado;							//Se devuelve "ganado".
}

//-----------------------------------------------------------------------------------------------------------------------
//Procedimiento que actualiza la lista de jugadores:

void actualizaJugador(DatosPartida& d, int jugador) {
	/*Al igual que con otras funciones, me parece más eficiente guardar solo la posición en el array de los jugadores por
	lo que la referencia del turno es suficiente para identificarles, ya que su posición está guardada en los datos de la
	partida.*/

	if (jugador == 1) {						//En el caso de que gane el jugador 1, se le suma 1 a partidas 
		d.lista[d.j1].pGanadas++;				//ganadas y a jugador 2 se le suma 1 a partidas perdidas.
		d.lista[d.j2].pPerdidas++;
	}
	else if (jugador == -1) {					//En caso contrario, se hace lo inverso.
		d.lista[d.j2].pGanadas++;
		d.lista[d.j1].pPerdidas++;
	}
}

//-----------------------------------------------------------------------------------------------------------------------
//Procedimiento que coloca la ficha del color correspondiente en la casilla seleccionada:

void muestraCharColor(Casilla c) {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);		//Se establezce la herramienta para cambiar el color en que se 
									//imprime a pantalla.
	if (c == Casilla(1))
		SetConsoleTextAttribute(hConsole, 6);			//Si la ficha es del jugador 1, se imprime de color amarillo.
	else if (c == Casilla(2))
		SetConsoleTextAttribute(hConsole, 4);			//Si la ficha es del jugador 2, se imprime de color rojo.
}

//-----------------------------------------------------------------------------------------------------------------------
//Procedimiento que guarda los datos de todos los jugadores registrados en el archivo "jugadores.txt":

void guardaDatos(DatosPartida d) {

	ofstream dJ;							//Se selecciona la función de lectura del archivo datos del 
	dJ.open("jugadores.txt");					//Jugador y se abre el archivo.

									//Se guardan todos los datos de cada jugador en líneas separadas.
	for (int i = 0; i < d.nJugadores; i++) {
		dJ << d.lista[i].ID << ' ' << d.lista[i].pGanadas << ' ' << d.lista[i].pPerdidas << endl;
	}

	dJ << "***";							//Y al final de todos los datos se añade un centinela.

	dJ.close();							//Solo en caso de que se haya abierto el archivo, se cierra.
}
