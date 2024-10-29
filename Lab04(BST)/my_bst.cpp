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
    Node* node = root;
    while (node != nullptr) {
        if (value == node->data) {
            return true;
        } else if (value < node->data) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return false;
}

// Devuelve el tamaño del árbol
unsigned int BST::getSize() const {
    return size;
}

// Agrega un valor al árbol
int BST::add(int value) {
    if (exists(value)) {
        return -1; // Valor ya existe
    }
    Node* newNode = new Node(value);
    if (root == nullptr) {
        root = newNode;
        size++;
        return 0; // Inserción exitosa
    }
    Node* current = root;
    Node* parent = nullptr;
    while (current != nullptr) {
        parent = current;
        if (value < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    if (value < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    size++;
    return 0; // Inserción exitosa
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
//valor minimo
int BST::findMin() {
    Node* current = root;

    // Si el árbol está vacío, no hay mínimo.
    if (current == nullptr) {
        return -1; // O cualquier otro valor que indique que no se encontró mínimo
    }

    // Buscamos el nodo más a la izquierda
    while (current->left != nullptr) {
        current = current->left;
    }

    return current->data; // Retornamos el valor del nodo mínimo
}
int BST::getBalance(Node* N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

int BST::height(Node* N) {
    if (N == NULL)
        return 0;

    int leftHeight = height(N->left);
    int rightHeight = height(N->right);

    if (leftHeight > rightHeight)
        return 1 + leftHeight;
    else
        return 1 + rightHeight;
}

bool BST::isBalanced() {
    return isBalanced(root);
}

bool BST::isBalanced(Node* N) {
    if (N == NULL)
        return true;

    int balance = getBalance(N);

    // Si el factor de balance no está entre -1 y 1, el árbol no está balanceado
    if (abs(balance) > 1)
        return false;

    // Verifica si los subárboles izquierdo y derecho están balanceados
    return isBalanced(N->left) && isBalanced(N->right);
}