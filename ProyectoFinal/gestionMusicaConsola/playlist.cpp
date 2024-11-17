#include "playlist.h"
#include <random>
#include <iostream>
#include <iomanip>
#include <functional>
#include <algorithm>

using namespace std;

Node::Node(Cancion cancion) : cancion(cancion), next(nullptr), prev(nullptr) {}

PlayList::PlayList() : head(nullptr), tail(nullptr), size(0) {}

// Destructor para liberar la memoria de la lista
PlayList::~PlayList() {
    Node* actual = head;
    while (actual != nullptr) {
        Node* siguiente = actual->next;
        delete actual;
        actual = siguiente;
    }
    head = tail = nullptr;
    size = 0;
}


// Agregar una canción a la lista
void PlayList::agregarCancion(Cancion& cancion) {
    Node* newNode = new Node(cancion);

    if (!head) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
}

// Eliminar un nodo específico de la lista
void PlayList::eliminarCancion(Node* nodo) {
    if (!nodo) return;

    if (nodo == head) {
        head = nodo->next;
        if (head) head->prev = nullptr;
    } else {
        nodo->prev->next = nodo->next;
        if (nodo->next) nodo->next->prev = nodo->prev;
    }

    delete nodo;
    size--;
}

// Buscar canción por ID
Node* PlayList::buscarPorID(int id) {
    Node* current = head;
    while (current) {
        if (current->cancion.id == id) return current;
        current = current->next;
    }
    return nullptr;
}

// Buscar canciones por nombre
vector<Node*> PlayList::buscarNombreCancion(const string& track_name) {
    vector<Node*> resultados;
    Node* current = head;
    while (current) {
        if (current->cancion.track_name.find(track_name) != string::npos) {
            resultados.push_back(current);
        }
        current = current->next;
    }
    return resultados;
}

// Buscar canciones por artista
vector<Node*> PlayList::buscarNombreArtista(const string& artist_name) {
    vector<Node*> resultados;
    Node* current = head;
    while (current) {
        if (current->cancion.artist_name.find(artist_name) != string::npos) {
            resultados.push_back(current);
        }
        current = current->next;
    }
    return resultados;
}

// Actualizar información de una canción
void PlayList::actualizarCancion(Node* nodo, const Cancion& nuevaCancion) {
    if (!nodo) return;
    nodo->cancion = nuevaCancion;
}

void PlayList::cabecera(){
    cout << "|" << setw(5) << "id"
    << "|" << setw(30) << "artist_name"
    << "|" << setw(30) << "track_name"
    << "|" << setw(30) << "track_id"
    << "|" << setw(5) << "popularity"
    << "|" << setw(5) << "year"
    << "|" << setw(10) << "genre"
    << "|" << setw(5) << "danceability"
    << "|" << setw(5) << "energy"
    << "|" << setw(5) << "key"
    << "|" << setw(5) << "loudness"
    << "|" << setw(5) << "mode"
    << "|" << setw(5) << "speechiness"
    << "|" << setw(5) << "acousticness"
    << "|" << setw(5) << "liveness"
    << "|" << setw(5) << "instrumentalness"
    << "|" << setw(5) << "valence"
    << "|" << setw(5) << "tempo"
    << "|" << setw(5) << "duration_ms"
    << "|" << setw(5) << "time_signature"
    << "|" << endl;
}

// Imprimir todas las canciones en la lista desde head o tail
void PlayList::imprimirCanciones(bool puntoInicio) {
    cabecera();
    Node* current = puntoInicio ? tail : head;
    while (current) {
        const Cancion& c = current->cancion;
        cout << "|" << setw(5) << c.id
             << "|" << setw(30) << c.artist_name
             << "|" << setw(30) << c.track_name
             << "|" << setw(30) << c.track_id
             << "|" << setw(5) << c.popularity
             << "|" << setw(5) << c.year
             << "|" << setw(10) << c.genre
             << "|" << setw(5) << c.danceability
             << "|" << setw(5) << c.energy
             << "|" << setw(5) << c.key
             << "|" << setw(5) << c.loudness
             << "|" << setw(5) << c.mode
             << "|" << setw(5) << c.speechiness
             << "|" << setw(5) << c.acousticness
             << "|" << setw(5) << c.liveness
             << "|" << setw(5) << c.instrumentalness
             << "|" << setw(5) << c.valence
             << "|" << setw(5) << c.tempo
             << "|" << setw(5) << c.duration_ms
             << "|" << setw(5) << c.time_signature
             << "|" << endl;
        current = puntoInicio ? current->prev : current->next;
        if (current == (puntoInicio ? tail : head)) break; // Prevent infinite loop
    }
}

// Ordenar canciones por atributo usando Radix Sort
void PlayList::ordenarPorRadixSort(function<int(const Cancion&)> obtenerClave) {
    if (!head || !head->next) return; // Lista vacía o con un solo elemento

    int maxKey = obtenerMaxClave(obtenerClave);
    int exp = 1;

    while (maxKey / exp > 0) {
        realizarRadixSortPaso(obtenerClave, exp);
        exp *= 10;
    }
}

int PlayList::obtenerMaxClave(function<int(const Cancion&)> obtenerClave) {
    Node* current = head;
    int maxVal = obtenerClave(current->cancion);
    while (current) {
        maxVal = max(maxVal, obtenerClave(current->cancion));
        current = current->next;
    }
    return maxVal;
}

void PlayList::realizarRadixSortPaso(function<int(const Cancion&)> obtenerClave, int exp) {
    Node* buckets[10] = {nullptr};
    Node* tails[10] = {nullptr};

    Node* current = head;
    while (current) {
        int digit = (obtenerClave(current->cancion) / exp) % 10;
        if (!buckets[digit]) {
            buckets[digit] = tails[digit] = current;
        } else {
            tails[digit]->next = current;
            current->prev = tails[digit];
            tails[digit] = current;
        }
        current = current->next;
    }

    head = nullptr;
    Node* prevTail = nullptr;
    for (int i = 0; i < 10; ++i) {
        if (buckets[i]) {
            if (!head) {
                head = buckets[i];
            } else {
                prevTail->next = buckets[i];
                buckets[i]->prev = prevTail;
            }
            prevTail = tails[i];
        }
    }
    if (prevTail) prevTail->next = nullptr;
}


// Métodos de ordenación
void PlayList::ordenarPorPopularidad() {
    ordenarPorRadixSort([](const Cancion& cancion) { return cancion.popularity; });
}

void PlayList::ordenarPorDuracion() {
    ordenarPorRadixSort([](const Cancion& cancion) { return cancion.duration_ms; });
}

void PlayList::ordenarPorAnio() {
    ordenarPorRadixSort([](const Cancion& cancion) { return cancion.year; });
}

// Obtener canciones de un año específico
vector<Node*> PlayList::ordenarporDeterminadoAnio(int year) {
    vector<Node*> resultados;
    Node* current = head;
    while (current) {
        if (current->cancion.year == year) {
            resultados.push_back(current);
        }
        current = current->next;
    }
    return resultados;
}

// Reproducción aleatoria
void PlayList::reproduccionAleatoria() {
    if (size == 0) {
        cout << "La lista está vacía. No hay canciones para reproducir." << endl;
        return;
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, size);

    int idAleatorio = distrib(gen);
    Node* cancionAleatoria = buscarPorID(idAleatorio);
    if (cancionAleatoria) {
        cancionAleatoria->cancion.reproducirCancion();
    } else {
        cout << "No se encontró ninguna canción con el ID generado aleatoriamente." << endl;
    }
}

// Cargar canciones desde un archivo CSV
void PlayList::cargarCSV(const string& nombre_archivo) {
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

        // Crear un objeto Cancion y añadirlo a la lista
        Cancion cancion(id, artist_name, track_name, track_id, popularity, year, genre, danceability, energy, key, loudness, mode, speechiness, acousticness, instrumentalness, liveness, valence, tempo, duration_ms, time_signature);
        agregarCancion(cancion);
    }

    archivo.close();
}