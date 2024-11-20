#include <iostream>
#include <memory>
using namespace std;

// Estructura de un árbol binomial
struct BinomialTree {
    int valor;
    int k;
    BinomialTree* hijo;
    BinomialTree* padre;
    BinomialTree* hermano;

    BinomialTree(int v) : valor(v), k(0), hijo(nullptr), padre(nullptr), hermano(nullptr) {}
};

// Clase para representar un heap binomial
class BinomialHeap {
private:
    BinomialTree* head;

    // Función auxiliar para fusionar dos árboles binomiales del mismo grado
    BinomialTree* mergeTrees(BinomialTree* t1, BinomialTree* t2) {
        if (t1->valor > t2->valor)
            swap(t1, t2);
        t2->padre = t1;
        t2->hermano = t1->hijo;
        t1->hijo = t2;
        t1->k++;
        return t1;
    }

    // Función para fusionar dos listas de árboles
    BinomialTree* mergeHeap(BinomialTree* h1, BinomialTree* h2) {
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
        *current = h1 ? h1 : h2;
        return newHead;
    }

    // Función para combinar los árboles del heap después de una fusión
    void combineTrees() {
        if (!head) return;

        BinomialTree* prev = nullptr;
        BinomialTree* curr = head;
        BinomialTree* next = head->hermano;

        while (next) {
            if (curr->k != next->k || (next->hermano && next->hermano->k == curr->k)) {
                prev = curr;
                curr = next;
            } else {
                if (curr->valor <= next->valor) {
                    curr->hermano = next->hermano;
                    curr = mergeTrees(curr, next);
                } else {
                    if (prev)
                        prev->hermano = next;
                    else
                        head = next;
                    curr = mergeTrees(next, curr);
                }
            }
            next = curr->hermano;
        }
    }

public:
    BinomialHeap() : head(nullptr) {}

    // Enqueue para insertar un elemento en el heap
    void enqueue(int valor, int k) {
        BinomialTree* newNode = new BinomialTree(valor);
        BinomialHeap tempHeap;
        tempHeap.head = newNode;
        head = mergeHeap(head, tempHeap.head);
        combineTrees();
    }

    // Visualizar los elementos del heap
    void display() const {
        BinomialTree* current = head;
        while (current) {
            cout << "Valor: " << current->valor << ", Grado: " << current->k << endl;
            current = current->hermano;
        }
    }
};

int main() {
    BinomialHeap heap;

    // Insertar elementos en el heap
    heap.enqueue(13, 0);
    heap.enqueue(7, 0);
    heap.enqueue(25, 0);
    heap.enqueue(3, 0);

    // Mostrar los elementos del heap
    cout << "Elementos en el heap:" << endl;
    heap.display();

    return 0;
}
