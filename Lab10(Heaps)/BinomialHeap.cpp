#include "BinomialHeap.h"
#include <iostream>
#include <stdexcept>
using namespace std;

BinomialHeap::BinomialHeap() : head(nullptr) {}

BinomialTree* BinomialHeap::mergeTrees(BinomialTree* t1, BinomialTree* t2) {
    if (t1->valor > t2->valor)
        swap(t1, t2);
    t2->padre = t1;
    t2->hermano = t1->hijo;
    t1->hijo = t2;
    t1->k++;
    return t1;
}

BinomialTree* BinomialHeap::mergeHeap(BinomialTree* h1, BinomialTree* h2) {
    if (!h1) return h2;
    if (!h2) return h1;

    BinomialTree* newHead = nullptr;
    BinomialTree** current = &newHead;

    while (h1 && h2) {
        if (h1->k <= h2->k) {
            *current = h1;
            h1 = h1->hermano;
        } else {
            *current = h2;
            h2 = h2->hermano;
        }
        current = &((*current)->hermano);
    }

    if (h1) *current = h1;
    if (h2) *current = h2;

    return newHead;
}

void BinomialHeap::unionHeap(BinomialHeap& other) {
    head = mergeHeap(head, other.head);
    other.head = nullptr;

    if (!head) return;

    BinomialTree* prev = nullptr;
    BinomialTree* curr = head;
    BinomialTree* next = head->hermano;

    while (next) {
        if ((curr->k != next->k) || (next->hermano && next->hermano->k == curr->k)) {
            prev = curr;
            curr = next;
        } else {
            if (curr->valor <= next->valor) {
                curr->hermano = next->hermano;
                mergeTrees(curr, next);
            } else {
                if (prev) {
                    prev->hermano = next;
                } else {
                    head = next;
                }
                mergeTrees(next, curr);
                curr = next;
            }
        }
        next = curr->hermano;
    }
}

void BinomialHeap::insert(int valor) {
    BinomialTree* newTree = new BinomialTree(valor);
    if (!head) {
        head = newTree;
    } else {
        newTree->hermano = head;
        head = newTree;
    }
}

int BinomialHeap::getMin() {
    if (!head) throw runtime_error("Esta vacio");

    BinomialTree* minNode = head;
    BinomialTree* current = head->hermano;

    while (current) {
        if (current->valor < minNode->valor) {
            minNode = current;
        }
        current = current->hermano;
    }

    return minNode->valor;
}

int BinomialHeap::extractMin() {
    if (!head) throw runtime_error("Heap is empty");

    BinomialTree* minNode = head;
    BinomialTree* minNodePrev = nullptr;
    BinomialTree* current = head->hermano;
    BinomialTree* prev = head;

    while (current) {
        if (current->valor < minNode->valor) {
            minNode = current;
            minNodePrev = prev;
        }
        prev = current;
        current = current->hermano;
    }

    if (minNodePrev) {
        minNodePrev->hermano = minNode->hermano;
    } else {
        head = minNode->hermano;
    }

    BinomialTree* child = minNode->hijo;
    BinomialHeap tempHeap;
    while (child) {
        BinomialTree* next = child->hermano;
        child->hermano = tempHeap.head;
        tempHeap.head = child;
        child = next;
    }

    unionHeap(tempHeap);

    int minValue = minNode->valor;
    delete minNode;
    return minValue;
}

void BinomialHeap::printTree(BinomialTree* tree, int indent) const {
    if (!tree) return;
    for (int i = 0; i < indent; ++i) cout << "  ";
    cout << tree->valor << endl;
    printTree(tree->hijo, indent + 1);
}

void BinomialHeap::print() const {
    BinomialTree* current = head;
    while (current) {
        cout << "Tree of degree " << current->k << ":" << endl;
        printTree(current, 0);
        current = current->hermano;
    }
}