#ifndef BINOMIALTREE_H
#define BINOMIALTREE_H

struct BinomialTree {
    int valor;
    int k;
    BinomialTree* hijo;
    BinomialTree* padre;
    BinomialTree* hermano;

    BinomialTree(int v) : valor(v), k(0), hijo(nullptr), padre(nullptr), hermano(nullptr) {}
};

#endif // BINOMIALTREE_H