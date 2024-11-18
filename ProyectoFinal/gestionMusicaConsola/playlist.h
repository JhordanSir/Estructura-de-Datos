#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "cancion.h"
#include <functional>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>

class Node {
public:
    Cancion cancion;
    Node* next;
    Node* prev;

    Node(Cancion cancion);
};

class PlayList {
public:
    Node* head;
    Node* tail;
    long long size;

    PlayList();
    ~PlayList();

    void agregarCancion(Cancion& cancion);
    void eliminarCancion(Node* nodo);
    Node* buscarPorID(int id);
    vector<Node*> buscarNombreCancion(const string& track_name);
    vector<Node*> buscarNombreArtista(const string& artist_name);
    void actualizarCancion(Node* nodo, const Cancion& nuevaCancion);
    void ordenarPorArtista();
    void ordenarPorPopularidad();
    void ordenarPorAnio();
    void ordenarPorDuracion();
    void ordenarPorID();
    vector<Node*> ordenarporDeterminadoAnio(int year);
    void reproduccionAleatoria();
    void cargarCSV(const string& nombre_archivo);
    void imprimirCanciones(bool puntoInicio);
private:
    void cabecera();
    void ordenarPorRadixSort(function<int(const Cancion&)> obtenerClave);
    int obtenerMaxClave(function<int(const Cancion&)> obtenerClave);
    void realizarRadixSortPaso(function<int(const Cancion&)> obtenerClave, int exp);
};



#endif // PLAYLIST_H
