// playlist.cpp
#include "playlist.h"
#include <iostream>
#include <algorithm>
#include <execution> 

PlayList::PlayList(int t) {
    btree = new BTree(t);
}

PlayList::~PlayList() {
    delete btree;
}

void PlayList::agregarCancion(Cancion& cancion) {
    btree->insert(cancion);
    todasLasCanciones.push_back(cancion); // Añadir la canción al vector
}

vector<Cancion> PlayList::buscarPorNombre(const std::string& nombre, bool searchByArtist) {
    vector<Cancion> resultados;
    btree->searchAll(nombre, searchByArtist, resultados);
    return resultados;
}

void PlayList::cargarCSV(const std::string& nombre_archivo) {
    ifstream archivo(nombre_archivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo " << nombre_archivo << endl;
        return;
    }

    string linea;
    getline(archivo, linea);  // Leer la cabecera del CSV
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string token;

        auto leerCampo = [&ss]() {
            string campo;
            char ch;
            bool dentroComillas = false;

            while (ss.get(ch)) {
                if (ch == '"' && !dentroComillas) {
                    dentroComillas = true;
                } else if (ch == '"' && dentroComillas) {
                    if (ss.peek() == ',') {
                        ss.get();
                        break;
                    }
                    dentroComillas = false;
                } else if (ch == ',' && !dentroComillas) {
                    break;
                } else {
                    campo += ch;
                }
            }
            return campo;
        };

        int id = stoi(leerCampo());
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

        Cancion cancion(id, artist_name, track_name, track_id, popularity, year, genre, danceability, energy, key, loudness, mode, speechiness, acousticness, instrumentalness, liveness, valence, tempo, duration_ms, time_signature);
        agregarCancion(cancion);
    }

    archivo.close();
}

void PlayList::imprimirCanciones() {
    btree->traverse();
}

void PlayList::ordenarPorAtributo(const std::string& atributo) {
    auto comparar = [&atributo](const Cancion& a, const Cancion& b) {
        if (atributo == "popularidad") {
            return a.popularity < b.popularity;
        } else if (atributo == "anio") {
            return a.year < b.year;
        } else if (atributo == "artista") {
            return a.artist_name < b.artist_name;
        } else if (atributo == "cancion") {
            return a.track_name < b.track_name;
        } else if (atributo == "genero") {
            return a.genre < b.genre;
        } else if (atributo == "duracion") {
            return a.duration_ms < b.duration_ms;
        } else if (atributo == "tempo") {
            return a.tempo < b.tempo;
        }
        return false;
    };

    sort(std::execution::par,todasLasCanciones.begin(), todasLasCanciones.end(), comparar);

    // cout << "Canciones después de ordenar por " << atributo << ":" << endl;
    // for (const auto& cancion : todasLasCanciones) {
    //     if (atributo == "popularidad") {
    //         cout << cancion.popularity << " - " << cancion.track_name << endl;
    //     } else if (atributo == "anio") {
    //         cout << cancion.year << " - " << cancion.track_name << endl;
    //     } else if (atributo == "artista") {
    //         cout << cancion.artist_name << " - " << cancion.track_name << endl;
    //     } else if (atributo == "cancion") {
    //         cout << cancion.track_name << endl;
    //     } else if (atributo == "genero") {
    //         cout << cancion.genre << " - " << cancion.track_name << endl;
    //     } else if (atributo == "duracion") {
    //         cout << cancion.duration_ms << " ms - " << cancion.track_name << endl;
    //     } else if (atributo == "tempo") {
    //         cout << cancion.tempo << " - " << cancion.track_name << endl;
    //     }
    // }
}

void PlayList::reproduccionAleatoria() {
    if (todasLasCanciones.empty()) {
        cout << "No hay canciones en la lista de reproducción." << endl;
        return;
    }

    static bool seeded = false;
    if (!seeded) {
        srand(time(0));
        seeded = true;
    }

    int indiceAleatorio = rand() % todasLasCanciones.size();
    todasLasCanciones[indiceAleatorio].reproducirCancion();
}

bool PlayList::actualizarCancion(int id, const Cancion& nuevaCancion) {
    for (auto it = todasLasCanciones.begin(); it != todasLasCanciones.end(); ++it) {
        if (it->id == id) {
            *it = nuevaCancion; // Actualizar la canción en el vector
            btree->insert(nuevaCancion); // Insertar la nueva versión de la canción en el B-Tree
            return true;
        }
    }
    return false;
}