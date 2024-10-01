/**
 * -Gian Piero Rodriguez Fadel
 * -Jhordan Steven Huamaní Huamaní
 * -Jorge Luis Ortiz Castañeda
 * Semestre: IV
 */
#include <iostream>
#include "my_bst.hpp"
#include "my_bst.cpp"
#include "my_bst_printer.cpp"
using namespace std;

int main() {
    BST* bst = create_bst();
    if (bst == nullptr) {
        cout << "Error al crear el BST" << endl;
    }
    
    // Realiza más pruebas con bst si es necesario

    delete bst;  // Libera la memoria
    return 0;
}
