#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

struct Cancion {
    string id;
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

    Cancion(string id, string artist_name, string track_name, string track_id, int popularity, int year,
            string genre, double danceability, double energy, int key, double loudness, int mode,
            double speechiness, double acousticness, double instrumentalness, double liveness,
            double valence, double tempo, int duration_ms, int time_signature)
        : id(id), artist_name(artist_name), track_name(track_name), track_id(track_id), popularity(popularity),
          year(year), genre(genre), danceability(danceability), energy(energy), key(key), loudness(loudness),
          mode(mode), speechiness(speechiness), acousticness(acousticness), instrumentalness(instrumentalness),
          liveness(liveness), valence(valence), tempo(tempo), duration_ms(duration_ms), time_signature(time_signature) {}
};

void cargarCSV(const string& nombre_archivo, vector<Cancion>& playlist) {
    ifstream archivo(nombre_archivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo " << nombre_archivo << endl;
        return;
    }

    string linea;
    getline(archivo, linea);  // Leer la cabecera del CSV (esta línea ya no es necesaria)
    int i=0;
    while (getline(archivo, linea)) {
        cout<<i<<endl;
        stringstream ss(linea);
        string token;

        // Función para manejar campos entre comillas, con comas dentro
        auto leerCampo = [&ss]() {
            string campo;
            char ch;
            bool dentroComillas = false;

            while (ss.get(ch)) {
                if (ch == '"' && !dentroComillas) {
                    dentroComillas = true; // Entrar en modo de lectura con comillas
                } else if (ch == '"' && dentroComillas) {
                    if (ss.peek() == ',') {
                        ss.get(); // Saltar la coma después de las comillas de cierre
                        break; // Salir del campo de comillas
                    }
                    dentroComillas = false; // Salir del modo con comillas
                } else if (ch == ',' && !dentroComillas) {
                    break; // Coma fuera de las comillas, se termina el campo
                } else {
                    campo += ch; // Agregar al campo
                }
            }
            return campo;
        };

        // Leer cada campo del CSV
        string id = leerCampo();
        string artist_name = leerCampo();
        string track_name = leerCampo();
        string track_id = leerCampo();
        int popularity = stoi(leerCampo());
        int year = stoi(leerCampo());
        string genre = leerCampo();
        double danceability = stod(leerCampo());
        double energy = stod(leerCampo());
        int key = stoi(leerCampo());
        double loudness = stod(leerCampo());
        int mode = stoi(leerCampo());
        double speechiness = stod(leerCampo());
        double acousticness = stod(leerCampo());
        double instrumentalness = stod(leerCampo());
        double liveness = stod(leerCampo());
        double valence = stod(leerCampo());
        double tempo = stod(leerCampo());
        int duration_ms = stoi(leerCampo());
        int time_signature = stoi(leerCampo());
        i++;
        // Crear un objeto Cancion y añadirlo al vector de playlist
        playlist.emplace_back(id, artist_name, track_name, track_id, popularity, year, genre,
                             danceability, energy, key, loudness, mode, speechiness,
                             acousticness, instrumentalness, liveness, valence, tempo,
                             duration_ms, time_signature);
    }

    archivo.close();
}

int main() {
    vector<Cancion> playlist;
    cargarCSV("spotify_data.csv", playlist);
    
    return 0;
}
