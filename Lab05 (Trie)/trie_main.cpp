#include <iostream>
#include <fstream>
#include "my_trie.hpp"  // Asegúrate de incluir el encabezado correcto

int main() {
    Trie trie;  // Crear una instancia del Trie
    ifstream archivo("words.txt"); // Asegúrate de especificar la ruta correcta

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;  // Manejo de errores si no se puede abrir el archivo
        return 1;
    }

    string palabra;
    while (getline(archivo, palabra)) {  // Leer el archivo línea por línea
        trie.insertar(palabra);  // Insertar cada palabra en el Trie
    }

    archivo.close();  // Cerrar el archivo

    // Pruebas
    cout << "Buscar 'ZZZ': " << (trie.buscar("ZZZ") ? "Encontrado" : "No encontrado") << endl;
    cout << "Buscar 'world': " << (trie.buscar("world") ? "Encontrado" : "No encontrado") << endl;

    // Puedes descomentar la siguiente línea para imprimir todas las palabras en el Trie
    // trie.imprimirTrie();

    return 0;
}
