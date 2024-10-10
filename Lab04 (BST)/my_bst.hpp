/*
 * Contiene información para una estructura de datos de árbol de búsqueda binaria (BST).
 * -Gian Piero Rodriguez Fadel
 * -Jhordan Steven Huamaní Huamaní
 * -Jorge Luis Ortiz Castañeda
 * Semestre: IV
 */
#ifndef MYBST_HPP
#define MYBST_HPP

#include <iostream>
#include <string>

// Usar para print_type en bst_print
#define INORDER "inorder"
#define PREORDER "preorder"
#define POSTORDER "postorder"
#define BREADTHFIRST "breadthfirst"

// Clase Node para almacenar datos dentro del BST. En nuestro caso, almacenaremos 'enteros'
class Node {
public:
    int data;             // Datos almacenados en el nodo
    Node* left;  // Puntero al nodo izquierdo
    Node* right; // Puntero al nodo derecho

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Clase BST que contiene el árbol de búsqueda binaria
class BST {
private:
    Node* root;   // Puntero al nodo raíz del BST
    unsigned int size; // Tamaño del BST

public:
    BST();  // Constructor para crear el BST
    ~BST(); // Destructor para liberar memoria

    bool exists(int value); // Comprueba si un valor existe en el árbol
    unsigned int getSize() const; // Retorna el tamaño del árbol
    int add(int value); // Agrega un valor al árbol
    void print(const std::string& print_type) const; // Imprime el árbol según el tipo de recorrido
    void free(); // Libera la memoria
    int findMin();
    bool isBalanced(Node* N);
    int getBalance(Node* N);
    bool isBalanced();
    int height(Node* N);
private:
    void printInOrder(Node* node) const; // Imprime el árbol en orden
    void printPreOrder(Node* node) const; // Imprime el árbol en preorden
    void printPostOrder(Node* node) const; // Imprime el árbol en postorden
    void freeNodes(Node* node); // Libera los nodos del árbol recursivamente
};

#endif
