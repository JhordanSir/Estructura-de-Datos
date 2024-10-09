#include "my_trie.hpp"

// Función que crea un nuevo nodo en el Trie
NodoTrie* crear_nodo_trie(char dato) {
    NodoTrie* nodo = (NodoTrie*) calloc(1, sizeof(NodoTrie)); //calloc es para separar espacios de memoria e inicializarlo en 0
    nodo->dato = dato; // asignamos el dato al atributo dato de la raiz
    nodo->es_hoja = false; // 
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

void buscar_palabras(NodoTrie* nodo, string prefijo, vector<string>& resultados, string actual) {
    if (nodo->es_hoja) {
        resultados.emplace_back(prefijo + actual);
    }
    for (NodoTrie* hijo : nodo->hijos) {
        if (hijo) {
            buscar_palabras(hijo, prefijo, resultados, actual + hijo->dato);
        }
    }
}

vector<string> buscar_por_prefijo(NodoTrie* raiz, string prefijo) {
    NodoTrie* nodo = raiz;
    for (char c : prefijo) {
        nodo = encontrar_hijo(nodo, c);
        if (nodo == nullptr) {
            return {};
        }
    }
    vector<string> resultados;
    buscar_palabras(nodo, prefijo, resultados, "");
    return resultados;
}

bool eliminar_palabra(NodoTrie* &nodo, const string &palabra, int profundidad = 0) {
    if (!nodo) return false;

    if (profundidad == palabra.size()) {
        if (!nodo->es_hoja) return false; // La palabra no existe
        nodo->es_hoja = false; // Marcar el final de la palabra como no hoja
        return nodo->hijos.empty(); //Si el nodo actual no tiene hijos, retornamos true para indicar que el nodo debe eliminarse
    }

    NodoTrie* hijo = encontrar_hijo(nodo, palabra[profundidad]);
    if (!hijo) return false;

    bool debe_eliminarse = eliminar_palabra(hijo, palabra, profundidad + 1);

    // Si el hijo debe eliminarse, eliminarlo del vector de hijos
    if (debe_eliminarse) {
        auto it = remove(nodo->hijos.begin(), nodo->hijos.end(), hijo);
        nodo->hijos.erase(it, nodo->hijos.end());
        free(hijo); // Liberar la memoria del nodo hijo

        // Si el nodo actual no es hoja y no tiene más hijos, debe eliminarse
        return !nodo->es_hoja && nodo->hijos.empty();
    }

    return false;
}

// Función para insertar una palabra en el Trie
NodoTrie* insertar_trie(NodoTrie* raiz, string palabra) {
    NodoTrie* temp = raiz;
    for (char c : palabra) {
        if (encontrar_hijo(temp, c) == nullptr) {
            temp->hijos.emplace_back(crear_nodo_trie(c));
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
