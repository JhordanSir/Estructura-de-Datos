/** Implementación de la estructura de datos BST
 * -Gian Piero Rodriguez Fadel
 * -Jhordan Steven Huamaní Huamaní
 * -Jorge Luis Ortiz Castañeda
 * Semestre: IV
 */
#include "my_bst.hpp"

// Constructor para crear el BST
BST::BST() : root(nullptr), size(0) {}

// Destructor para liberar la memoria del árbol
BST::~BST() {
    free();
}

// Comprueba si el valor existe en el árbol
bool BST::exists(int value) {
    // Implementación pendiente
    return false;
}

// Devuelve el tamaño del árbol
unsigned int BST::getSize() const {
    return size;
}

// Agrega un valor al árbol
int BST::add(int value) {
    // Implementación pendiente
    return 0;
}

// Libera la memoria asignada para el árbol
void BST::free() {
    freeNodes(root);
}

// Libera los nodos de forma recursiva
void BST::freeNodes(Node* node) {
    if (node != nullptr) {
        freeNodes(node->left);
        freeNodes(node->right);
        delete node;
    }
}

// Crea un nuevo BST
BST* create_bst() {
    return new BST();
}