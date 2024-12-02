#include "Trie.h"

Trie::Trie() {
    root = new TrieNode();  // Crear la raíz del Trie
}

Trie::~Trie() {
    deleteTrie(root);  // Liberar memoria de los nodos del Trie
}

void Trie::deleteTrie(TrieNode* node) {
    for (auto& pair : node->children) {
        deleteTrie(pair.second); 
    }
    delete node;  
}


bool Trie::findWordsWithPrefix(const string& prefix) {
   TrieNode* node = root;

    // Recorrer cada caracter del prefijo
    for (char c : prefix) {
        // Si no existe el carácter en el nodo actual, el prefijo no es válido
        if (node->children.find(c) == node->children.end()) {
            return false;
        }
        // Avanzar al siguiente nodo
        node = node->children[c];
    }

    // Si hemos recorrido todo el prefijo sin problemas, significa que existe
    return true;
}

