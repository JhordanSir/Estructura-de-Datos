#include "b_tree.cpp"

int main() {
    int max_claves = 4;  // Cambia este valor para probar con diferentes números de claves
    NodoArbolB *raiz = nullptr;

    cargarCSVEnArbolB(&raiz, "Pruebas.csv", 10, max_claves);
    cout << "Estructura del árbol B:" << endl;
    imprimirArbolB(raiz, 0);

    return 0;
}