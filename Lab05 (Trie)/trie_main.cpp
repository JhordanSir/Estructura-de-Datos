#include "my_trie.cpp"  // Asegúrate de incluir el encabezado correcto

int main() {
    NodoTrie* trie = crear_nodo_trie('\0');  // Crear el Trie con un nodo raíz vacío
    leerTXT(trie, "words.txt");  // Leer palabras desde el archivo y construir el Trie
    imprimir_trie(trie);  // Imprimir los nodos del Trie
    return 0;
}
