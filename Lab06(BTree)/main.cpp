#include "b_tree.cpp"
#include <chrono>


int main() {
    ofstream archivoLectura("tiempos_lectura.txt");
    ofstream archivoBusqueda("tiempos_busqueda.txt");
    for (int i=1;i<=5;i++){//cantida de keys
        double lectura=0;
        double busqueda=0;
        archivoLectura<<i+3<<" ";
        archivoBusqueda<<i+3<<" ";
        for (int j=1;j<=5;j++){//promedios
            int max_claves=i+3;
            NodoArbolB *raiz = nullptr;
            auto inicio = chrono::high_resolution_clock::now();

            cargarCSVEnArbolB(&raiz, "random_numbers_1000000.csv", 10, max_claves);

            auto fin = chrono::high_resolution_clock::now();
            chrono::duration<double> duracion = fin - inicio;
            lectura+=duracion.count();
            archivoLectura<<duracion.count()<<" ";
            auto inicio2 = chrono::high_resolution_clock::now();

            cout<<buscarClave(raiz, 0.9218232253882106)<<endl;
            
            auto fin2 = chrono::high_resolution_clock::now();
            chrono::duration<double> duracion2 = fin2 - inicio2;
            busqueda+=duracion2.count();
            archivoBusqueda<<duracion2.count()<<" ";
        }

        archivoLectura<<lectura/5<<endl;
        archivoBusqueda<<busqueda/5<<endl;
    }
    return 0;
}