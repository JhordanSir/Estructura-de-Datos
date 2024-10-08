#include "my_trie.cpp"  // Asegúrate de incluir el encabezado correcto

int main() {
    NodoTrie* trie = crear_nodo_trie('\0');  // Crear el Trie con un nodo raíz vacío
    cout<<"Leyendo archivo txt..."<<endl;
    leerTXT(trie, "words.txt");  // Leer palabras desde el archivo y construir el Trie
    cout<<"Se terminó de leer el archivo"<<endl;

    vector<string> resultados = buscar_por_prefijo(trie, "acc");
    for (string palabra : resultados) {
        cout << palabra << endl;
    }
    cout << endl;
    eliminar_palabra(trie, "acc.");

    resultados = buscar_por_prefijo(trie, "acc");
    for (string palabra : resultados) {
        cout << palabra << endl;
    }

    cout << endl;
    cout<<"Eliminando noditos..."<<endl;
    liberar_trie(trie);
    return 0;
}
