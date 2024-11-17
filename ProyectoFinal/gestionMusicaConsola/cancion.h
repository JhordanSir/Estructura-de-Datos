#ifndef CANCION_H
#define CANCION_H

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class Cancion {
public:
    int id;
    string artist_name;
    string track_name;
    string track_id;
    int popularity;
    int year;
    string genre;
    double danceability;
    double energy;
    int key;
    double loudness;
    int mode;
    double speechiness;
    double acousticness;
    double instrumentalness;
    double liveness;
    double valence;
    double tempo;
    int duration_ms;
    int time_signature;

    Cancion(int id, string artist_name, string track_name, string track_id, int popularity, int year,
                 string genre, double danceability, double energy, int key, double loudness, int mode,
                 double speechiness, double acousticness, double instrumentalness, double liveness,
                 double valence, double tempo, int duration_ms, int time_signature);

    void imprimirDatos();
    void reproducirCancion();
};

#endif // CANCION_H
