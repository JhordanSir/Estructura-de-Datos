#include <iostream>
#include <vector>
#include <list>

using namespace std;

class HashTable {
public:
    HashTable(int size) : tablaTam(size), margen(0.8) {
        table = new list<int>[size];
        colisiones = 0;
    }

    ~HashTable() {
        delete[] table;
    }

    void insertar(int key) {
        int indice = hashFunction(key);
        table[indice].push_back(key);
        colisiones += table[indice].size() > 1;
        if (static_cast<double>(size()) / tablaTam >= margen) {
            rehash();
        }
    }

    void eliminar(int key) {
        int indice = hashFunction(key);
        table[indice].remove(key);
    }

    bool buscar(int key) {
        int indice = hashFunction(key);
        for (auto it = table[indice].begin(); it != table[indice].end(); ++it) {
            if (*it == key)
                return true;
        }
        return false;
    }

    int contarColisiones() {
        return colisiones;
    }

    void mostrar() {
        for (int i = 0; i < tablaTam; i++) {
            cout << "Índice " << i << ": ";
            for (auto it = table[i].begin(); it != table[i].end(); ++it) {
                cout << *it << " ";
            }
            cout << endl;
        }
    }

    void vaciar() {
        for (int i = 0; i < tablaTam; i++) {
            table[i].clear();
        }
    }

private:
    int tablaTam;
    list<int> *table;
    int colisiones;
    double margen;

    int hashFunction(int key) {
        return (key * 31) % tablaTam;
    }

    void rehash() {
        int previoTam = tablaTam;
        tablaTam *= 2;
        list<int>* newTable = new list<int>[tablaTam];

        for (int i = 0; i < previoTam; ++i) {
            for (auto it = table[i].begin(); it != table[i].end(); ++it) {
                int nuevoIndice = hashFunction(*it);
                newTable[nuevoIndice].push_back(*it);
            }
        }

        delete[] table;
        table = newTable;
    }

    int size() {
        int count = 0;
        for (int i = 0; i < tablaTam; ++i) {
            count += table[i].size();
        }
        return count;
    }
};

int main() {
    HashTable ht(100);  // Tamaño de la tabla

    ht.insertar(123);
    ht.insertar(76);
    
    for (int i=0;i<1000;i++){
        ht.insertar(rand() % 10000000);
    }
    
    if (ht.buscar(76)) {
        cout << "El elemento 76 fue encontrado" << endl;
    } else {
        cout << "El elemento 76 no fue encontrado" << endl;
    }
    ht.mostrar();
    ht.eliminar(76);
    ht.vaciar();
    if (ht.buscar(76)) {
        cout << "El elemento 76 fue encontrado" << endl;
    } else {
        cout << "El elemento 76 no fue encontrado" << endl;
    }

    cout<<"Colisiones: "<<ht.contarColisiones()<<endl;

    return 0;
} 