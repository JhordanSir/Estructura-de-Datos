#include "b_tree.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>

NodoArbolB::NodoArbolB(int max_claves) : num_claves(0), max_claves(max_claves) {
    claves.resize(max_claves);
    hijos.resize(max_claves + 1, nullptr);
}

double redondearADecimales(double valor, int decimales) {
    double factor = pow(10, decimales);
    return round(valor * factor) / factor;
}

NodoArbolB *crearNodo(int max_claves) {
    return new NodoArbolB(max_claves);
}

void dividirHijo(NodoArbolB *padre, int indice, int max_claves) {
    NodoArbolB *hijo = padre->hijos[indice];
    NodoArbolB *nuevoHijo = crearNodo(max_claves);

    int mitad = (max_claves - 1) / 2;

    for (int i = 0; i < max_claves - mitad - 1; i++) {
        nuevoHijo->claves[i] = hijo->claves[mitad + 1 + i];
    }

    if (hijo->hijos[0] != nullptr) {
        for (int i = 0; i <= max_claves - mitad - 1; i++) {
            nuevoHijo->hijos[i] = hijo->hijos[mitad + 1 + i];
        }
    }

    nuevoHijo->num_claves = max_claves - mitad - 1;
    hijo->num_claves = mitad;

    for (int i = padre->num_claves; i >= indice + 1; i--) {
        padre->hijos[i + 1] = padre->hijos[i];
    }
    padre->hijos[indice + 1] = nuevoHijo;

    for (int i = padre->num_claves - 1; i >= indice; i--) {
        padre->claves[i + 1] = padre->claves[i];
    }
    padre->claves[indice] = hijo->claves[mitad];
    padre->num_claves++;
}

void insertarClave(NodoArbolB *nodo, double clave) {
    int i = nodo->num_claves - 1;
    while (i >= 0 && nodo->claves[i] > clave) {
        nodo->claves[i + 1] = nodo->claves[i];
        i--;
    }
    nodo->claves[i + 1] = clave;
    nodo->num_claves++;
}

void insertarNoLleno(NodoArbolB *nodo, double clave, int max_claves) {
    if (nodo == nullptr) {
        cout << "Nodo nulo en insertarNoLleno." << endl;
        return;
    }

    int i = nodo->num_claves - 1;

    if (nodo->hijos[0] == nullptr) {  // Si es una hoja
        insertarClave(nodo, clave);
        return;
    }

    while (i >= 0 && nodo->claves[i] > clave) {
        i--;
    }
    i++;

    if (nodo->hijos[i] != nullptr && nodo->hijos[i]->num_claves == max_claves) {
        dividirHijo(nodo, i, max_claves);
        if (nodo->claves[i] < clave) {
            i++;
        }
    }

    if (i > nodo->num_claves) {
        i = nodo->num_claves;
    }

    if (nodo->hijos[i] != nullptr) {
        insertarNoLleno(nodo->hijos[i], clave, max_claves);
    } else {
        cout << "Nodo hijo nulo en insertarNoLleno." << endl;
    }
}

void insertar(NodoArbolB **raiz, double clave, int max_claves) {
    if (*raiz == nullptr) {
        *raiz = crearNodo(max_claves);
        (*raiz)->claves[0] = clave;
        (*raiz)->num_claves = 1;
    } else {
        if ((*raiz)->num_claves == max_claves) {
            NodoArbolB *nuevaRaiz = crearNodo(max_claves);
            nuevaRaiz->hijos[0] = *raiz;
            dividirHijo(nuevaRaiz, 0, max_claves);
            *raiz = nuevaRaiz;
        }
        insertarNoLleno(*raiz, clave, max_claves);
    }
}

void cargarCSVEnArbolB(NodoArbolB **raiz, const string &nombre_archivo, int decimales, int max_claves) {
    ifstream archivo(nombre_archivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo " << nombre_archivo << "." << endl;
        return;
    }

    string linea;
    getline(archivo, linea);  // Ignorar el encabezado

    while (getline(archivo, linea)) {
        istringstream ss(linea);
        string token;

        getline(ss, token, ',');  // Ignorar la primera columna

        while (getline(ss, token, ',')) {
            double clave = redondearADecimales(stod(token), decimales);
            insertar(raiz, clave, max_claves);
        }
    }

    archivo.close();
    cout << "Datos cargados desde " << nombre_archivo << " al árbol B." << endl;
}

void imprimirArbolB(NodoArbolB *nodo, int nivel) {
    if (nodo == nullptr) return;

    for (int i = 0; i < nivel; i++) {
        cout << "  ";
    }

    for (int i = 0; i < nodo->num_claves; i++) {
        cout << nodo->claves[i] << " ";
    }
    cout << endl;

    for (int i = 0; i <= nodo->num_claves; i++) {
        imprimirArbolB(nodo->hijos[i], nivel + 1);
    }
}
