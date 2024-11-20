#include "Menu.h"
#include <iostream>
using namespace std;

void Menu::displayMenu() {
    cout << "1. Insert" << endl;
    cout << "2. Get Minimum" << endl;
    cout << "3. Extract Minimum" << endl;
    cout << "4. Print Heap" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
}

void Menu::handleInsert() {
    int value;
    cout << "Enter value to insert: ";
    cin >> value;
    heap.insert(value);
    cout << "Value inserted." << endl;
}

void Menu::handleGetMin() {
    try {
        int minValue = heap.getMin();
        cout << "Minimum value: " << minValue << endl;
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }
}

void Menu::handleExtractMin() {
    try {
        int minValue = heap.extractMin();
        cout << "Extracted minimum value: " << minValue << endl;
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }
}

void Menu::handlePrint() {
    cout << "Heap structure:" << endl;
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
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);
}