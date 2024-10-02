#include "my_trie.hpp"

// Función que crea un nuevo nodo en el Trie
NodoTrie* crear_nodo_trie(char dato) {
    NodoTrie* nodo = (NodoTrie*) calloc(1, sizeof(NodoTrie));
    nodo->dato = dato;
    nodo->es_hoja = false;
    return nodo;
}

// Función para liberar la memoria del Trie
void liberar_trie(NodoTrie* &nodo) {
    
    if (nodo == nullptr) {
        return;
    }
    for (int i = 0; i < nodo->hijos.size(); i++) {
        liberar_trie(nodo->hijos[i]);
    }
    free(nodo);
}

// Función para buscar una palabra en el Trie
bool buscar(NodoTrie* nodo, string palabra) {
    if (nodo == nullptr) {
        return false;
    }
    NodoTrie* temp = nodo;
    for (int i = 0; i < palabra.size(); i++) {
        bool encontrado = false;
        for (int j = 0; j < temp->hijos.size(); j++) {
            if (temp->hijos[j]->dato == palabra[i]) {
                temp = temp->hijos[j];
                encontrado = true;
                break;
            }
        }
        if (!encontrado) {
            return false;
        }
    }
    return temp->es_hoja;
}

// Función para insertar una palabra en el Trie
NodoTrie* insertar_trie(NodoTrie* raiz, string palabra) {
    if (raiz == nullptr) {
        raiz = crear_nodo_trie(palabra[0]);
    }
    if (buscar(raiz, palabra)) {
        // La palabra ya existe en el Trie
        return raiz;
    }
    NodoTrie* temp = raiz;
    for (int i = 0; i < palabra.size(); i++) {
        bool encontrado = false;
        for (int j = 0; j < temp->hijos.size(); j++) {
            if (temp->hijos[j]->dato == palabra[i]) {
                temp = temp->hijos[j];
                encontrado = true;
                break;
            }
        }
        if (!encontrado) {
            NodoTrie* nuevo_nodo = crear_nodo_trie(palabra[i]);
            temp->hijos.push_back(nuevo_nodo);
            temp = nuevo_nodo;
        }
    }
    temp->es_hoja = true;
    return raiz;
}

// Función para imprimir los nodos del Trie
void imprimir_trie(NodoTrie* raiz) {
    if (!raiz)
        return;
    NodoTrie* temp = raiz;
    printf("%c -> ", temp->dato);
    for (int i = 0; i < temp->hijos.size(); i++) {
        imprimir_trie(temp->hijos[i]);
    }
}

// Función para leer un archivo de texto e insertar sus palabras en el Trie
void leerTXT(NodoTrie* &nodo, string archivo) {
    ifstream file(archivo); // Asegúrate de especificar la ruta correcta

    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;  // Manejo de errores si no se puede abrir el archivo
    }

    string palabra;
    while (getline(file, palabra)) {  // Leer el archivo línea por línea
        nodo = insertar_trie(nodo, palabra);  // Insertar cada palabra en el Trie
    }

    file.close();
}
