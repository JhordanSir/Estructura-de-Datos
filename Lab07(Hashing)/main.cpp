#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <algorithm>

using namespace std;

class TablaHash {
public:
    TablaHash(function<int(int)> funcionHash, int tamaño = 10) 
        : funcionHash(funcionHash), tamaño(tamaño), cubetas(tamaño) {}

    void insertar(int valor) {
        int indice = funcionHash(valor);
        cubetas[indice].push_back(valor);
    }

    void eliminar(int valor) {
        int indice = funcionHash(valor);
        auto& lista = cubetas[indice];
        lista.erase(remove(lista.begin(), lista.end(), valor), lista.end());
    }

    bool encontrar(int valor) {
        int indice = funcionHash(valor);
        const auto& lista = cubetas[indice];
        return find(lista.begin(), lista.end(), valor) != lista.end();
    }

private:
    function<int(int)> funcionHash;
    int tamaño;
    vector<vector<int>> cubetas;
};

function<int(int)> FuncionHashAleatoria(int rango, int tamaño = 10) {
    vector<int> tablaHash(rango);
    random_device rd;
    mt19937 generador(rd());
    uniform_int_distribution<> distribucion(0, tamaño - 1);

    for (int i = 0; i < rango; ++i) {
        tablaHash[i] = distribucion(generador);
    }

    return [tablaHash, rango](int valor) {
        return tablaHash[valor % rango];
    };
}

int main() {
    int rango = 1000;  // Define el rango para FuncionHashAleatoria
    auto funcionHashAleatoria = FuncionHashAleatoria(rango, 10);  // Crea la instancia de FuncionHashAleatoria
    TablaHash tablaHash(funcionHashAleatoria, 10);  // Usa funcionHashAleatoria como la función de hash

    int x = 123;
    int y = 76;

    tablaHash.insertar(y);
    tablaHash.insertar(x);

    cout << (tablaHash.encontrar(x) ? "Verdadero" : "Falso") << endl;  // Debería imprimir "Verdadero"

    return 0;
}
