/**
 * Funciones de impresión de árboles.
 * -Gian Piero Rodriguez Fadel
 * -Jhordan Steven Huamaní Huamaní
 * -Jorge Luis Ortiz Castañeda
 * Semestre: IV
 */
#include "my_bst.hpp"
#include <iostream>

void BST::printInOrder(Node* node) const {
    if (node == nullptr) return;
    printInOrder(node->left);
    std::cout << node->data << " ";
    printInOrder(node->right);
}

void BST::printPreOrder(Node* node) const {
    if (node == nullptr) return;
    std::cout << node->data << " ";
    printPreOrder(node->left);
    printPreOrder(node->right);
}

void BST::printPostOrder(Node* node) const {
    if (node == nullptr) return;
    printPostOrder(node->left);
    printPostOrder(node->right);
    std::cout << node->data << " ";
}

// Imprime el árbol según el tipo de impresión especificado
void BST::print(const std::string& print_type) const {
    if (print_type == INORDER) {
        printInOrder(root);
    } else if (print_type == PREORDER) {
        printPreOrder(root);
    } else if (print_type == POSTORDER) {
        printPostOrder(root);
    } else {
        std::cerr << "Tipo de impresión no válido" << std::endl;
    }
    std::cout << std::endl;
}
