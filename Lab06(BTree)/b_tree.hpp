#ifndef MI_ARBOL_B_H
#define MI_ARBOL_B_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

struct NodoArbolB {
    int num_claves;
    int max_claves;
    vector<double> claves;
    vector<NodoArbolB *> hijos;

    NodoArbolB(int max_claves);
};

// Funciones para manejo del árbol B
NodoArbolB *crearNodo(int max_claves);
void dividirHijo(NodoArbolB *padre, int indice, int max_claves);
void insertarClave(NodoArbolB *nodo, double clave);
void insertarNoLleno(NodoArbolB *nodo, double clave, int max_claves);
void insertar(NodoArbolB **raiz, double clave, int max_claves);
void cargarCSVEnArbolB(NodoArbolB **raiz, const string &nombre_archivo, int decimales, int max_claves);
void imprimirArbolB(NodoArbolB *nodo, int nivel);
double redondearADecimales(double valor, int decimales);

#endif
