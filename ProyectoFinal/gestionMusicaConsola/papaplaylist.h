#ifndef PAPAPLAYLIST_H
#define PAPAPLAYLIST_H

#include "playlist.h"
#include "cancion.h"
#include "btree.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <random>
#include <map>

class PapaPlayList {
public:
    std::map<std::string, PlayList> MapaDePlayList; // Mapa para almacenar Playlist
    void agregarPlayList(const::string& nombre, const::PlayList& playlis);
    PlayList* buscarPlayList(const std::string& nombre);
};

#endif // PAPAPLAYLIST_H
