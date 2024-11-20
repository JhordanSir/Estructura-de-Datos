#include "Menu.h"
#include <iostream>
using namespace std;

void Menu::displayMenu() {
    cout << "1. Insertar" << endl;
    cout << "2. Obtener Minimo" << endl;
    cout << "3. Extraer Minimo" << endl;
    cout << "4. Imprimir Heap" << endl;
    cout << "5. Salir" << endl;
    cout << "Elija una: ";
}

void Menu::handleInsert() {
    int value;
    cout << "Ingrese el valor a insertar: ";
    cin >> value;
    heap.insert(value);
    cout << "Valor insertado." << endl;
}

void Menu::handleGetMin() {
    try {
        int minValue = heap.getMin();
        cout << "Valor minimo: " << minValue << endl;
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }
}

void Menu::handleExtractMin() {
    try {
        int minValue = heap.extractMin();
        cout << "Valor minimo extraido: " << minValue << endl;
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }
}

void Menu::handlePrint() {
    cout << "Estructura del Heap:" << endl;
    heap.print();
}

void Menu::run() {
    int choice;
    do {
        displayMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                handleInsert();
                break;
            case 2:
                handleGetMin();
                break;
            case 3:
                handleExtractMin();
                break;
            case 4:
                handlePrint();
                break;
            case 5:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Esa no cuenta joven, prueba de nuevo." << endl;
        }
    } while (choice != 5);
}