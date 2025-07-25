
//David Ortega Lozano   Ing. Inf

#include <iostream>
using namespace std;
#include <fstream>
#include <Windows.h>

const int N_MAX_ALUMNO = 100;

typedef struct {
    int id;
    int notaExamen;
    int notaPracticas;
    int notaClase;
    int nFaltas;
    int nFinal;
}Alumno;

typedef struct {
    Alumno lista[N_MAX_ALUMNO];
    int contador;
}Clase;

int menu();
bool cargaDatos(Clase&c);
int buscaAlumno(Clase c);
void guiones();
void informeIndividual(Alumno a);
void informeGeneral(Clase c);
double porcentaje(Alumno a);
void generarInforme(Clase c);

int main()
{
    Clase c;
    int opcion;
    bool si;
    si = cargaDatos(c);
    if (si) {
        opcion = menu();
        switch (opcion) {
        case 1:
            informeIndividual(c.lista[buscaAlumno(c)]);
            break;
        case 2:
            informeGeneral(c);
            break;
        case 3:
            generarInforme(c);
        }
    }
    
}

int menu() {
    int opcion;
    bool continuar;

    system("CLS");
    cout << "Hola querida María, elige entre una de las siguientes opciones:" << endl << endl;
    cout << "1. Informe Individual" << endl;
    cout << "2. Informe General" << endl;
    cout << "3. Alumnos que pueden presentarse" << endl;

    do {
        continuar = true;
        cin >> opcion;
        if (opcion < 1 || opcion > 3) {
            continuar = false;
            cout << "Opción no disponible,introduce una opción entre el 1 y el 3" << endl;
        }
    } while (!continuar);

    return opcion;
}

//---------------------------------------------------------------------------------------------------------------------------------------------

bool cargaDatos(Clase& c) {
    Alumno a;
    bool continuar = false;
    int nAlumnos;
    bool abierto = true;

    ifstream archivo;
    archivo.open("alumnos.txt");
    if (archivo.is_open()) {
        do {
            archivo >> nAlumnos;
            for (int i = 0; i < nAlumnos; i++) {
                archivo >> a.id >> a.notaPracticas >> a.notaClase >> a.notaExamen >> a.nFaltas;
                a.nFinal = ((a.notaClase * 0.1) + (a.notaPracticas * 0.3) + (a.notaExamen * 0.6));
                c.lista[i] = a;
            }
        } while (!continuar);
    }
    else {
        cout << "A habido un problema al abrir el fichero" << endl;
        abierto = false;
    }
    archivo.close();

    return abierto;
}

//----------------------------------------------------------------------------------------------------------------

int buscaAlumno(Clase c) {
    int idAlumno;
    int posicion = -1;

    cout << "Introduce el ID del alumno:" << endl;
    cin >> idAlumno;

    for (int i = 0; i < c.contador; i++) {
        if (c.lista[i].id == idAlumno) {
            posicion = i;
            i = c.contador;
        }
    }

    return posicion;
}

//---------------------------------------------------------------------------------------------------------------

void informeIndividual(Alumno a) {
    string nombre;

    cout << "Introduce el nombre del alumno:";
    cin >> nombre;
    guiones();
    cout << "INFORME INDIVIDUAL: " << nombre << endl;
    guiones();
    cout << "Nota Prácticas: " << a.notaPracticas << endl;
    cout << "Nota Clase: " << a.notaClase << endl;
    cout << "Nota Examen: " << a.notaExamen << endl;
    cout << "Porcentaje asistencia: " << porcentaje(a) << endl;
    cout << "Nota final: " << a.nFinal << endl;
}

//-------------------------------------------------------------------------------------------------------------

void informeGeneral(Clase c) {
    int j = 0;
    int k = 0;
    int x = 0;
    int z = 0;
    int y = 0;

    guiones();
    cout << "INFORME GENERAL PROGRAMACIÓN 1" << endl;
    guiones();
    cout << "La clase tiene " << c.contador << " alumnos." << endl;
    for (int i = 0; i < c.contador; i++) {
        if (c.lista[i].notaPracticas >= 5) 
            j++;
        if (c.lista[i].notaExamen >= 5)
            k++;
        if (porcentaje(c.lista[i]) < 0.8)
            x++;
        if (c.lista[i].nFinal >= 5)
            z++;
        y += c.lista[i].nFinal;
    }
    cout << "El " << j / c.contador << "% ha aprobado las prácticas" << endl;
    cout << "El " << k / c.contador << "% ha aprobado el examen final" << endl;
    cout << "El " << x / c.contador << "% no se ha podido presentar al examen" << endl;
    cout << "El " << z / c.contador << "% ha aprobado" << endl;
    cout << "La nota media de la clase es: " << y / c.contador << endl;
}

//-------------------------------------------------------------------------------------------------------------

void generarInforme(Clase c) {
    ofstream archivo2;
    archivo2.open("Informe.txt");
    if (archivo2.is_open()) {
        for (int i = 0; i < c.contador; i++) {
            if (porcentaje(c.lista[i]) >= 0.8)
                archivo2 << c.lista[i].id << ' ' << porcentaje(c.lista[i]) << "puede" << endl;
            else
                archivo2 << c.lista[i].id << ' ' << porcentaje(c.lista[i]) << "no puede" << endl;
        }
    }
    else cout << "A habido unj error al crear el archivo" << endl;
    archivo2.close();
}

//-------------------------------------------------------------------------------------------------------------
void guiones() {
    for (int i = 0; i < 10; i++) {
        cout << '-';
    }
    cout << endl;
}

//-------------------------------------------------------------------------------------------------------------

double porcentaje(Alumno a) {
    double porcentaje;
    porcentaje = a.nFaltas / 60;
    return porcentaje;
}