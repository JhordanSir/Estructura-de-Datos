#include "playlist.h"
#include <algorithm>

void Playlist::addSong(const Song &song) {
    songs.append(song);
}

void Playlist::removeSong(const QString &trackId) {
    for (int i = 0; i < songs.size(); ++i) {
        if (songs[i].trackId == trackId) {
            songs.removeAt(i);
            return;
        }
    }
}

void Playlist::changeOrder(int currentPos, int newPos) {
    if (currentPos >= 0 && currentPos < songs.size() && newPos >= 0 && newPos < songs.size()) {
        Song song = songs.takeAt(currentPos);
        songs.insert(newPos, song);
    }
}

QList<Song> Playlist::getSongs() const {
    return songs;
}
