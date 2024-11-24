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

    Cancion() : id(0), popularity(0), year(0), danceability(0.0), energy(0.0), key(0), loudness(0.0), mode(0), speechiness(0.0), acousticness(0.0), instrumentalness(0.0), liveness(0.0), valence(0.0), tempo(0.0), duration_ms(0), time_signature(0) {}

    Cancion(int id, string artist_name, string track_name, string track_id, int popularity, int year,
                 string genre, double danceability, double energy, int key, double loudness, int mode,
                 double speechiness, double acousticness, double instrumentalness, double liveness,
                 double valence, double tempo, int duration_ms, int time_signature);

    void imprimirDatos();
    void reproducirCancion();
};

#endif // CANCION_H
