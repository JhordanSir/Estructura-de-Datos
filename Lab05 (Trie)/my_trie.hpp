#ifndef MY_TRIE_HPP
#define MY_TRIE_HPP

#include <iostream>
#include <string>
using namespace std;
#define TAMAÑO_ALFABETO 26

struct NodoTrie {
    NodoTrie* hijos[TAMAÑO_ALFABETO];
    bool es_hoja;

    NodoTrie() {
        es_hoja = false;
        for (int i = 0; i < TAMAÑO_ALFABETO; i++) {
            hijos[i] = nullptr;
        }
    }
};

class Trie {
public:
    NodoTrie* raiz;

    Trie();  // Constructor
    void insertar(const std::string& palabra);  // Método para insertar una palabra
    bool buscar(const std::string& palabra);  // Método para buscar una palabra
    void imprimirTrie();  // Método para imprimir el Trie
    void imprimirTrieAux(NodoTrie* nodo, string prefijo);  // Método auxiliar para imprimir el Trie
};

#endif // MY_TRIE_HPP
