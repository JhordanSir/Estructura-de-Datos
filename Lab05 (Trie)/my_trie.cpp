#include "my_trie.hpp"

// Constructor del Trie
Trie::Trie() {
    raiz = new NodoTrie();
}

// Método para insertar una palabra en el Trie
void Trie::insertar(const std::string& palabra) {
    NodoTrie* actual = raiz;

    for (char ch : palabra) {
        // Convertir a minúscula
        ch = tolower(ch);

        // Verificar si es un carácter válido
        if (ch < 'a' || ch > 'z') {
            continue;  // Ignorar caracteres no válidos
        }

        int indice = ch - 'a';  // Obtener el índice correspondiente
        if (actual->hijos[indice] == nullptr) {
            actual->hijos[indice] = new NodoTrie();  // Crear nuevo nodo si no existe
        }
        actual = actual->hijos[indice];  // Avanzar al siguiente nodo
    }
    actual->es_hoja = true;  // Marcar el final de la palabra
}

// Método para buscar una palabra en el Trie
bool Trie::buscar(const std::string& palabra) {
    NodoTrie* actual = raiz;

    for (char ch : palabra) {
        // Convertir a minúscula
        ch = tolower(ch);

        // Asegurarse de que solo se manejan letras del alfabeto
        if (ch < 'a' || ch > 'z') {
            return false;  // Si se encuentra un carácter inválido, la palabra no está en el Trie
        }

        int indice = ch - 'a';  // Obtener el índice correspondiente
        if (actual->hijos[indice] == nullptr) {
            return false;  // Si no hay nodo, la palabra no está en el Trie
        }
        actual = actual->hijos[indice];  // Avanzar al siguiente nodo
    }

    return actual->es_hoja;  // Verificar si es una palabra completa
}

// Método auxiliar para imprimir el Trie (para depuración)
void Trie::imprimirTrieAux(NodoTrie* nodo, string prefijo) {
    if (nodo->es_hoja) {
        cout << prefijo << endl;  // Imprimir la palabra si es una hoja
    }
    for (int i = 0; i < TAMAÑO_ALFABETO; i++) {
        if (nodo->hijos[i] != nullptr) {
            imprimirTrieAux(nodo->hijos[i], prefijo + char('a' + i));  // Llamada recursiva para imprimir los hijos
        }
    }
}

// Método para imprimir el Trie
void Trie::imprimirTrie() {
    imprimirTrieAux(raiz, "");  // Iniciar la impresión desde la raíz
}
