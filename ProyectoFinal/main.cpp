#include "gestionMusica.cpp"
#include <conio.h>
#include <chrono>
int main() {
    ListaCanciones playlist2;
    //===============================LECTURA DEL CSV=========================================================
    cout<<"Leyendo datos..."<<endl;
    auto start = std::chrono::high_resolution_clock::now();
    // cargarCSV("Pruebas.csv", playlist2);
    cargarCSV("Pruebas.csv", playlist2);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
    cout << "Tiempo de lectura: " << duration << " segundos" << endl;
    cout<<"Termino de leer :D"<<endl;
    //===============================ORDENAMIENTO=========================================================
    cout<<"Ordenamiento por año"<<endl;
    
    auto start3 = std::chrono::high_resolution_clock::now();

    cout<<"Ordenando..."<<endl;
    playlist2.ordenarPorAnio();
    
    auto end3 = std::chrono::high_resolution_clock::now();
    auto duration3 = std::chrono::duration_cast<std::chrono::seconds>(end3 - start3).count();
    cout << "Tiempo de ejecución: " << duration3 << " segundos" << endl;
    cout<<"Ordenamiento por año"<<endl;
    //===============================iMPRESION DE FORMA ASCENDENTE Y DESCENDENTE=========================================================
    imprimirNodeRecursivoReversa(playlist2.head);
    cout<<endl<<endl;
    imprimirNodeRecursivo(playlist2.head);
    //vector<Node*> nodos = playlist2.ordenarporDeterminadoAnio(2000);

    // for (auto i : nodos) {
    //     i->cancion.imprimirDatos();
    // }

    //===============================bUSQUEDA=========================================================
    // Node *nod = playlist2.buscarPorID(playlist2.size);
    // nod->cancion.imprimirDatos();

    //===============================rEPRODUCCIÓN ALEATORIA=========================================================
    //reproduccionAleatoria(playlist2);

    //getch();
    return 0;
}
