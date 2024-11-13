#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "song.h"
#include <QList>
#include <QString>

class Playlist {
public:
    void addSong(const Song &song);
    void removeSong(const QString &trackId);
    void changeOrder(int currentPos, int newPos);
    QList<Song> getSongs() const;

private:
    QList<Song> songs;
};

#endif // PLAYLIST_H
