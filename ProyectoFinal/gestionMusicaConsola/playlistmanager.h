#ifndef PLAYLIST_MANAGER_H
#define PLAYLIST_MANAGER_H

#include "playlist.h"
#include <map>
#include <iostream>
#include <stdexcept>

class PlaylistManager {
public:
    std::map<std::string, PlayList> mapadeplaylists;
    
    PlaylistManager();
    ~PlaylistManager();

    void LlenarMapaDePlaylist(const PlayList& platlistrecibida, const std::string& name);
    PlayList& obtenerPlaylist(const std::string &name);
};

#endif // PLAYLIST_MANAGER_H
