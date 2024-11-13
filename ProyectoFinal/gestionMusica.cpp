#include "cabecera.cpp"
#include <conio.h>

int main() {
    ListaCanciones playlist2;
    cout<<"Leyendo datos..."<<endl;

    cargarCSV("spotify_data.csv", playlist2);

    cout<<"Termino de leer :D"<<endl;
    
    cout<<"Ordenando..."<<endl;
    playlist2.ordenarPorAnio();
    cout<<"Ordenamiento por año"<<endl;
    playlist2.imprimirLista();
    
    // vector<Node*> nodos = playlist2.buscarNombreArtista("Mo' Horizons");
    // for (auto i : nodos) {
    //     i->cancion.imprimirDatos();
    // }

    // Node *nod = playlist2.buscarPorID(playlist2.size);
    // nod->cancion.imprimirDatos();
    reproduccionAleatoria(playlist2);
    //getch();
    return 0;
}
