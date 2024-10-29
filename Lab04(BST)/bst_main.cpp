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
    cout << "=============================================" << endl;
    cout << "          Binary Search Tree Example         " << endl;
    cout << "=============================================" << endl;
    BST* bst = create_bst();
    if (bst == nullptr) {
        cout << "Error al crear el BST" << endl;
    }
     // Insert some nodes
    
    bst->add(50);
    bst->add(30);
    bst->add(20);
    bst->add(40);
    bst->add(70);
    bst->add(60);
    bst->add(80);
    bst->add(81);
    bst->add(82);
    // Print the BST in different traversals
    cout << "---------------------------------------------" << endl;
    cout << "         Printing the Binary Search Tree        " << endl;
    bst->print("inorder");
    bst->print("preorder");
    bst->print("postorder");
    
    //function
    int valor=50;
    if (bst->exists(valor)){
      cout<<"El valor "<<valor<<" existe"<<endl;
    }
    else {
      cout<<"El valor "<<valor<<" no existe"<<endl;
    }
    valor=56;
    if (bst->exists(valor)){
      cout<<"El valor "<<valor<<" existe"<<endl;
    }
    else {
      cout<<"El valor "<<valor<<" no existe"<<endl;
    }
    
    cout<<"La cantidad de nodos del arbol es: "<<bst->getSize()<<endl;
    
    // Realiza más pruebas con bst si es necesario
    int minValue = bst->findMin();
    cout << "El elemento mínimo es: " << minValue << endl;
    
    bool balanced = bst->isBalanced();
    balanced? cout << "Sí, está balanceado" : cout << "No está balanceado";
    
    cout<<"\n\tCompila :D"<<endl;
    delete bst;  // Libera la memoria
    return 0;
}
