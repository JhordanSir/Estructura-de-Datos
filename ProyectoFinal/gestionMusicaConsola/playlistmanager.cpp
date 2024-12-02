#include "playlistmanager.h"
PlaylistManager::PlaylistManager() {
    std::cout << "Iniciando mapa de Playlist\n";
}

PlaylistManager::~PlaylistManager() {
    std::cout << "Destruyendo PlaylistManager...\n";
}

void PlaylistManager::LlenarMapaDePlaylist(const PlayList& playlistrecibida, const std::string& name) {
    auto result = mapadeplaylists.insert({name, playlistrecibida});
    std::cout << "Nueva playlist creada con nombre " << name << ". Ahora tienes " << mapadeplaylists.size() << " playlists." << std::endl;
}

PlayList& PlaylistManager::obtenerPlaylist(const std::string& name) {
    auto it = mapadeplaylists.find(name);
    if (it != mapadeplaylists.end()) {
        return it->second;  
    } else {
        throw std::out_of_range("La playlist no existe: " + name); 
    }
}

