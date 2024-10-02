#ifndef MI_TRIE_HPP
#define MI_TRIE_HPP

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

typedef struct NodoTrie NodoTrie;

struct NodoTrie {
    char dato;  // Caracter que representa el nodo
    vector<NodoTrie*> hijos;  // Lista de nodos hijos
    bool es_hoja;  // Indica si el nodo es una hoja (final de una palabra)
};

#endif // MI_TRIE_HPP
