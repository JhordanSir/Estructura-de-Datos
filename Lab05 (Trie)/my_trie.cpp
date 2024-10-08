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

NodoTrie* encontrar_hijo(NodoTrie* nodo, char caracter) {
    for (NodoTrie* hijo : nodo->hijos) {
        if (hijo && hijo->dato == caracter) {
            return hijo;
        }
    }
    return nullptr;
}

// Función para buscar una palabra en el Trie
bool buscar(NodoTrie* nodo, string palabra) {
    for (char c : palabra) {
        nodo = encontrar_hijo(nodo, c);
        if (nodo == nullptr) {
            return false;
        }
    }
    return nodo->es_hoja;
}

// Función para insertar una palabra en el Trie
NodoTrie* insertar_trie(NodoTrie* raiz, string palabra) {
    NodoTrie* temp = raiz;
    for (char c : palabra) {
        if (encontrar_hijo(temp, c) == nullptr) {
            temp->hijos.push_back(crear_nodo_trie(c));
            temp = temp->hijos.back();
        } else {
            temp = encontrar_hijo(temp, c);
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
