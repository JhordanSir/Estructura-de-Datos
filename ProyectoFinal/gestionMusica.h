#include <iostream>
#include <functional>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>
#include <locale>
#include <stdexcept>
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
            double valence, double tempo, int duration_ms, int time_signature)
        : id(id), artist_name(artist_name), track_name(track_name), track_id(track_id), popularity(popularity),
          year(year), genre(genre), danceability(danceability), energy(energy), key(key), loudness(loudness),
          mode(mode), speechiness(speechiness), acousticness(acousticness), instrumentalness(instrumentalness),
          liveness(liveness), valence(valence), tempo(tempo), duration_ms(duration_ms), time_signature(time_signature) {}
    ~Cancion();
    void imprimirDatos();
    void reproducirCancion();
};

class Node {
public:
    Cancion cancion;
    Node* next;
    Node* prev;

    Node(Cancion cancion) : cancion(cancion), next(nullptr), prev(nullptr) {}
};

class ListaCanciones {
public:
    Node* head;
    Node* tail;
    long long size=0;

    ListaCanciones() : head(nullptr) {}
    
    void agregarCancion(Cancion cancion);

    void eliminarCancion(Node* nodo);

    Node* buscarPorID(int id);

    vector<Node*> buscarNombreCancion(const string& track_name);

    vector<Node*> buscarNombreArtista(const string& artist_name);

    void actualizarCancion(Node* nodo, int nuevoId, const string& nuevoArtistName, const string& nuevoTrackName,const string& nuevoTrackId, int nuevaPopularidad, int nuevoAnio, const string& nuevoGenero,double nuevaDanceability, double nuevaEnergy, int nuevaKey, double nuevaLoudness,int nuevoModo, double nuevaSpeechiness, double nuevaAcousticness, double nuevaInstrumentalness,double nuevaLiveness, double nuevaValence, double nuevoTempo, int nuevaDuracionMs,int nuevoTimeSignature);
    
    void imprimirLista();

    void ordenarPorPopularidad();

    void ordenarPorAnio();

    // void ordenarPorEstado() {
    //     head = mergeSort(head, [](Cancion a, Cancion b) {
    //         return a.estado < b.estado;
    //     });
    // }

    void ordenarPorDuracion();

private:
    Node* split(Node* head);

    Node* merge(Node* first, Node* second, function<bool(Cancion, Cancion)> compare);

    Node* mergeSort(Node* head, function<bool(Cancion, Cancion)> compare);
};

void cargarCSV(const string& nombre_archivo, vector<Cancion>& playlist);
