
/* *********************************************************************************************************************************************
NOMBRE DEL PROYECTO: Laboratorio 3

OBJETIVO:            Detectar Palíndromos

AUTOR: 				 MARIO FERNANDEZ FERNANDEZ & DAVID ORTEGA LOZANO

FECHA DE CREACIÓN:   25-10-2022
********************************************************************************************************************************************* */

//Bibliotecas:
#include <iostream>												//Incluyo la biblioteca de espacios de nombres
    using namespace std;										//Seleccionamos el espacio de nombres estándar

//Iniciación de funcioness:
                                                                //función que comprueba de forma iterativa
bool polindromoIterativo(string palabra, int longitud, int tIntento, char& x, char& y);
                                                                //función que comprueba de forma recursiva
bool polindromoRecursivo(string palabra, int longitud, int tIntento, int& intento, char& a, char& b);

int main()
{
    //Variables locales:
    string palabra;                                             //Variable que recoge la Palabra/Frase a comprobar introducida por la pantalla
    bool comprobacion1, comprobacion2;                          //Variables que recogen la comprobación por ambos métodos
    int longitud;                                               //Variable que recoge la longitud de la Palabra/Frase
    int tIntento;                                               //Variable que recoge el total de veces que hay que comparar las letras
    int intento = 0;                                            //Variable que recoge por que comparación vas en la recursiva
    char a, b;                                                  //Variables que recogen los caracteres que se comprueban en la recursiva
    char x, y;                                                  //Variables que recogen los caracteres que se comprueban en la iterativa

                                                                //Solicitamos que introduzca una Pañlabra/Frase
    cout << "Hola, introduce una palabra o una frase y veamos es políndroma" << endl;
    cin >> palabra;

    longitud = palabra.length();                                //Recogemos su longitud

                                                                //Compruebo que no haya espacios
    palabra.erase(remove(palabra.begin(), palabra.end(), ' '), palabra.end());

    tIntento = longitud / 2;                                    //Recogemos cuantas comprobaciones hay que hacer en total

                                                                //Realizamos la comprobación por recursibidad
    comprobacion1 = polindromoIterativo(palabra, longitud, tIntento, x, y);
                                                                //Realizamos la comprobación por iteratividad
    comprobacion2 = polindromoRecursivo(palabra, longitud, tIntento, intento, a, b);

    cout << "La primera comprobación ya se ha realizano, ";     //Anunciamos la primera comprobación
    if (comprobacion1 == true) {
        cout << "¡¡¡Muy bien, " << palabra << " es palíndroma!!!" << endl;
    }
    else if (comprobacion1 == false) {
        cout << "Lo siento pero " << palabra << " no es palíndroma, ya que la letra " << x << " no coincide con la letra " << y << endl;
    }
                                                                //Anunciamos la segunda comprobación
    cout << "Ahora realizaremos la segunda comprobación por otro método para asegurarnos, ";
    if (comprobacion2 == true) {
        cout << "¡¡¡Muy bien, " << palabra << " es palíndroma!!!" << endl;
    }
    else if (!comprobacion2 == false) {
        cout << "Lo siento pero " << palabra << " no es palíndroma, ya que la letra " << a << " no coincide con la letra " << b << endl;
    }

}
bool polindromoIterativo(string palabra, int longitud, int tIntento, char& x, char& y) {

    for (int i = 0; i <= tIntento; i++) {                       //Compruebo tantas veces como sea necesario

        x = palabra[i];                                         //Recojo el caracter por la izquierda
        y = palabra[(longitud - 1 - i)];                            //Recojo el caracter por la derecha
        cout << i;
        if (x != y) {                                           //En caso de que no sean iguales, niego que sea palíndroma
            return false;
        }
    }                                                           //En caso de que se realicen todas las comprobaciones y no haya habido ningún 
    return true;                                                //error, afirmo que es palíndroma
}
bool polindromoRecursivo(string palabra, int longitud, int tIntento, int& intento, char& a, char& b) {

    if (tIntento >= 1) {                                        //Compruebo si ya he hecho todas las comprobaciones necesarias

        a = palabra[intento];                                   //Recojo el valor por la izquierda
        b = palabra[longitud - 1 - intento];                        //Recojo el valor por la derecha

        if (a == b) {                                           //En caso de que sean iguales
            intento++;                                          //Sumo uno a las veces que lo he intentado
            tIntento--;                                         //Y le resto uno a las comprobaciones que me quedan
                                                                //Y vuelvo a llamar a la función
            polindromoRecursivo(palabra, longitud, tIntento, intento, a, b);
        }
        else {                                                  //En caso contrario niego que sea palíndroma
            return false;
        }
    }
    return true;                                                //Cuando acabe las comprobaciones devuelvo que es cierto
}