#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "cancion.h"
#include "btree.h"
#include "trie.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <random>

class PlayList {
public:
    BTree* btree;
    std::vector<Cancion> todasLasCanciones;
    Trie cancionesTrie;
    Trie artistasTrie;

    PlayList(int t);
    ~PlayList();

    void agregarCancion(Cancion& cancion);
    vector<Cancion> buscarPorNombre(const std::string& nombre, bool searchByArtist);
    void cargarCSV(const std::string& nombre_archivo);
    void imprimirCanciones();
    void ordenarPorAtributo(const std::string& atributo);
    Cancion reproduccionAleatoria();
    bool actualizarCancion(int id, const Cancion& nuevaCancion);
};

#endif // PLAYLIST_H