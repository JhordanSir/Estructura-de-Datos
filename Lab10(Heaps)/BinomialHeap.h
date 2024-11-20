#ifndef BINOMIALHEAP_H
#define BINOMIALHEAP_H

#include "BinomialTree.h"

class BinomialHeap {
private:
    BinomialTree* head;

    BinomialTree* mergeTrees(BinomialTree* t1, BinomialTree* t2);
    BinomialTree* mergeHeap(BinomialTree* h1, BinomialTree* h2);
    void unionHeap(BinomialHeap& other);
    void printTree(BinomialTree* tree, int indent) const;

public:
    BinomialHeap();
    void insert(int valor);
    int getMin();
    int extractMin();
    void print() const;
};

#endif // BINOMIALHEAP_H