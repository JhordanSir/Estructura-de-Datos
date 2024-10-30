#include "b_tree.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    struct BTreeNode *root = NULL;

    // Cargar datos desde el archivo CSV en el árbol B
    loadCSVIntoBTree(&root, "random_numbers_1000000.csv", 10);
    // Imprimir el árbol B
    printf("Estructura del árbol B:\n");
    printBTree(root, 0);

    return 0;
}
