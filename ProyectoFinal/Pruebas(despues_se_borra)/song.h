#ifndef SONG_H
#define SONG_H

#include <QString>

class Song {
public:
    QString artistName;
    QString trackName;
    QString trackId;
    int popularity;
    int year;
    QString genre;
    float danceability;
    float energy;
    int key;
    float loudness;
    int mode;
    float speechiness;
    float acousticness;
    float instrumentalness;
    float liveness;
    float valence;
    float tempo;
    int durationMs;
    int timeSignature;

    Song(const QString &artistName, const QString &trackName, const QString &trackId, int popularity, int year,
         const QString &genre, float danceability, float energy, int key, float loudness, int mode,
         float speechiness, float acousticness, float instrumentalness, float liveness, float valence,
         float tempo, int durationMs, int timeSignature);

};

#endif // SONG_H
