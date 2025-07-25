
/* ------------------------------------------------------------------------------------------------------------------
NOMBRE DEL PROYECTO:    Laboratorio 1
                                                                                                                   
OBJETIVO:               Calculo del perímetro, area y volumen del círculo/esfera                                   
                                                                                                                   
AUTOR:                  DAVID ORTEGA LOZANO                                            
                                                                                                                   
FECHA DE CREACIÓN:      13/09/2022                                                                                 
------------------------------------------------------------------------------------------------------------------ */

//BIBLIOTECAS
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

//Declaro que empleo lenguaje tipo estandar
using namespace std;

//Declaro constantes glovales
const double PI = M_PI;                                                              //Constante del número pi

//Funciones matemáticas

    //Operación para calcular el volumen
void calculoDelVolumen(double radio)
{
    double volumen = (((double)(4) / 3) * PI * radio * radio * radio);              //Cálculo del volumen de la esfera
    cout << endl << endl << "El volumen de la esfera es: " << volumen << endl;      //Mesaje a consola
}

    //Operación para calcular el area
void calculoDelArea(double radio)
{
    double area = (PI * radio * radio);                                             //Cálculo del area del círculo
    cout << "El área del círculo es: " << area << endl;                             //Mensaje a consola
}

    //Operación para calcular el perímetro
void calculoDelPerímetro(double radio)
{
    double perimetro = (2 * PI * radio);                                            //Cálculo del perímetro del círculo
    cout << "El perímetro del círculo es: " << perimetro << endl << endl;           //Mensaje a consola
}



int main( )
{
    double radio;
                                                                                    //Mensaje inicial que pide que introduzcas el radio
    cout << "Para calcular el área, perímetro y volumen de un círculo/esfera, introduce su radio en cm: ";  
    cin >> radio;                                                                   //Introducción del radio

    calculoDelVolumen(radio);                                                       //Llamada a la función del cálculo del volumen de la esfera
    
    calculoDelArea(radio);                                                          //Llamada a la función del cálculo del area del círculo
    
    calculoDelPerímetro(radio);                                                     //Llamada a la función del cálculo del perímetro del círculo

    return 0;
}