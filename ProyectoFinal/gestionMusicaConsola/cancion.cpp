#include "cancion.h"

Cancion::Cancion(int id, string artist_name, string track_name, string track_id, int popularity, int year,
                 string genre, double danceability, double energy, int key, double loudness, int mode,
                 double speechiness, double acousticness, double instrumentalness, double liveness,
                 double valence, double tempo, int duration_ms, int time_signature)
    : id(id), artist_name(artist_name), track_name(track_name), track_id(track_id), popularity(popularity),
      year(year), genre(genre), danceability(danceability), energy(energy), key(key), loudness(loudness),
      mode(mode), speechiness(speechiness), acousticness(acousticness), instrumentalness(instrumentalness),
      liveness(liveness), valence(valence), tempo(tempo), duration_ms(duration_ms), time_signature(time_signature) {}

void Cancion::imprimirDatos() {
    cout << "|" << setw(5) << this->id
         << "|" << setw(30) << this->artist_name
         << "|" << setw(30) << this->track_name
         << "|" << setw(30) << this->track_id
         << "|" << setw(5) << this->popularity
         << "|" << setw(5) << this->year
         << "|" << setw(10) << this->genre
         << "|" << setw(5) << this->danceability
         << "|" << setw(5) << this->energy
         << "|" << setw(5) << this->key
         << "|" << setw(5) << this->loudness
         << "|" << setw(5) << this->mode
         << "|" << setw(5) << this->speechiness
         << "|" << setw(5) << this->acousticness
         << "|" << setw(5) << this->instrumentalness
         << "|" << setw(5) << this->liveness
         << "|" << setw(5) << this->valence
         << "|" << setw(5) << this->tempo
         << "|" << setw(5) << this->duration_ms
         << "|" << setw(5) << this->time_signature
         << "|" << endl;
}

void Cancion::reproducirCancion() {
    cout << "Reproduciendo: " << this->track_name << " - " << this->artist_name << endl;
}
