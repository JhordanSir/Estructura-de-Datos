#ifndef MENU_H
#define MENU_H

#include "BinomialHeap.h"

class Menu {
private:
    BinomialHeap heap;

    void displayMenu();
    void handleInsert();
    void handleGetMin();
    void handleExtractMin();
    void handlePrint();

public:
    void run();
};

#endif // MENU_H