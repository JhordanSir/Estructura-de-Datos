#include "gestionMusica.h"
#include <random>

ListaCanciones::~ListaCanciones() {
    // Liberar memoria de cada nodo de la lista
    Node* actual = head;
    while (actual != nullptr) {
        Node* siguiente = actual->next; // Guardar el siguiente nodo
        delete actual;                  // Liberar el nodo actual
        actual = siguiente;             // Avanzar al siguiente nodo
    }
    head = tail = nullptr;
    size = 0; // Reiniciar el tamaño de la lista
}

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

void Cancion::reproducirCancion(){
    cout<<"Reproduciendo: "<<this->track_name<<" - "<<this->artist_name<<endl;
}

void ListaCanciones::agregarCancion(Cancion cancion) {
    Node* newNode = new Node(cancion);

    if (!head) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    this->size++;  // Incrementar el tamaño aquí
}

void cabecera(){
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

void imprimirNodeRecursivo(Node *playlist) {
    if (!playlist) {
        cout << "La lista está vacía." << endl;
        return;
    }
    playlist->cancion.imprimirDatos();
    imprimirNodeRecursivo(playlist->next);
}

void imprimirNodeRecursivoReversa(Node *playlist) {
    if (!playlist) {
        cout << "La lista está vacía." << endl;
        return;
    }
    imprimirNodeRecursivoReversa(playlist->next);
    playlist->cancion.imprimirDatos();
}

void ListaCanciones::eliminarCancion(Node* nodo) {
    if (!nodo) return;

    if (nodo == head) {
        head = nodo->next;
        if (head) {
            head->prev = nullptr;
        }
    } else {
        nodo->prev->next = nodo->next;
        if (nodo->next) {
            nodo->next->prev = nodo->prev;
        }
    }

    delete nodo;
    size--;
}
//Busqeuda por id de canciones
Node* ListaCanciones::buscarPorID(int id) {
    if (!head) {  // Verificar si la lista está vacía
        cout << "La lista está vacía. No se encontró el ID: " << id << endl;
        return nullptr;
    }

    if (head->cancion.id == id) return head;
    if (tail->cancion.id == id) return tail;

    Node* current = head->next;
    Node* reverse = tail->prev;
    while (current && reverse && current != reverse && current->next != reverse) {
        if (current->cancion.id == id) return current;
        if (reverse->cancion.id == id) return reverse;
        current = current->next;
        reverse = reverse->prev;
    }

    if (current && current->cancion.id == id) return current;

    return nullptr;
}

//Búsqueda de cancions por nombre de la cancion
vector<Node*> ListaCanciones::buscarNombreCancion(const string& track_name) {
    vector<Node*> resultados;
    Node* current = head;
    while (current) {
        // Verifica si el nombre de la canción contiene la subcadena track_name
        if (current->cancion.track_name.find(track_name) != string::npos) {
            resultados.push_back(current);
        }
        current = current->next;
    }
    return resultados;
}

//busqueda de canciones por nombre de artista
vector<Node*> ListaCanciones::buscarNombreArtista(const string& artist_name) {
    vector<Node*> resultados;
    Node* current = head;
    while (current) {
        if (current->cancion.artist_name == artist_name) {
            resultados.push_back(current);
        }
        current = current->next;
    }
    return resultados;
}

void ListaCanciones::actualizarCancion(Node* nodo, int nuevoId, const string& nuevoArtistName, const string& nuevoTrackName,const string& nuevoTrackId, int nuevaPopularidad, int nuevoAnio, const string& nuevoGenero,double nuevaDanceability, double nuevaEnergy, int nuevaKey, double nuevaLoudness,int nuevoModo, double nuevaSpeechiness, double nuevaAcousticness, double nuevaInstrumentalness,double nuevaLiveness, double nuevaValence, double nuevoTempo, int nuevaDuracionMs,int nuevoTimeSignature) 
{
    nodo->cancion.id = nuevoId;
    nodo->cancion.artist_name = nuevoArtistName;
    nodo->cancion.track_name = nuevoTrackName;
    nodo->cancion.track_id = nuevoTrackId;
    nodo->cancion.popularity = nuevaPopularidad;
    nodo->cancion.year = nuevoAnio;
    nodo->cancion.genre = nuevoGenero;
    nodo->cancion.danceability = nuevaDanceability;
    nodo->cancion.energy = nuevaEnergy;
    nodo->cancion.key = nuevaKey;
    nodo->cancion.loudness = nuevaLoudness;
    nodo->cancion.mode = nuevoModo;
    nodo->cancion.speechiness = nuevaSpeechiness;
    nodo->cancion.acousticness = nuevaAcousticness;
    nodo->cancion.instrumentalness = nuevaInstrumentalness;
    nodo->cancion.liveness = nuevaLiveness;
    nodo->cancion.valence = nuevaValence;
    nodo->cancion.tempo = nuevoTempo;
    nodo->cancion.duration_ms = nuevaDuracionMs;
    nodo->cancion.time_signature = nuevoTimeSignature;
}

void ListaCanciones::ordenarPorRadixSort(function<int(Cancion)> obtenerClave) {
    if (!head || !head->next) return; // Lista vacía o con un solo elemento

    int maxKey = obtenerMaxClave(obtenerClave); // Encontrar el valor máximo del atributo
    int exp = 1; // Exponente inicial (unidades, decenas, etc.)

    while (maxKey / exp > 0) {
        realizarRadixSortPaso(obtenerClave, exp);
        exp *= 10;
    }
}

int ListaCanciones::obtenerMaxClave(function<int(Cancion)> obtenerClave) {
    Node* actual = head;
    int maxVal = obtenerClave(actual->cancion);
    while (actual) {
        maxVal = max(maxVal, obtenerClave(actual->cancion));
        actual = actual->next;
    }
    return maxVal;
}

void ListaCanciones::realizarRadixSortPaso(function<int(Cancion)> obtenerClave, int exp) {
    Node* buckets[10] = {nullptr}; // Lista de buckets para dígitos 0-9
    Node* tails[10] = {nullptr};

    Node* actual = head;

    // Distribuir los elementos en los buckets según el dígito actual
    while (actual) {
        int digit = (obtenerClave(actual->cancion) / exp) % 10;
        if (!buckets[digit]) {
            buckets[digit] = tails[digit] = actual;
        } else {
            tails[digit]->next = actual;
            tails[digit] = actual;
        }
        actual = actual->next;
    }

    // Reconstruir la lista enlazada a partir de los buckets
    head = nullptr;
    Node* prevTail = nullptr;

    for (int i = 0; i < 10; ++i) {
        if (buckets[i]) {
            if (!head) {
                head = buckets[i];
            } else {
                prevTail->next = buckets[i];
            }
            prevTail = tails[i];
        }
    }

    if (prevTail) prevTail->next = nullptr; // Terminar la lista
}

void ListaCanciones::ordenarPorPopularidad() {
    ordenarPorRadixSort([](Cancion a) { return a.popularity; });
}

void ListaCanciones::ordenarPorDuracion() {
    ordenarPorRadixSort([](Cancion a) { return a.duration_ms; });
}

void ListaCanciones::ordenarPorAnio() {
    ordenarPorRadixSort([](Cancion a) { return a.year; });
}

vector<Node*> ListaCanciones::ordenarporDeterminadoAnio(int year) {
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

void reproducirEspecifico(ListaCanciones &playlist){//implementar xd



}

void reproduccionAleatoria(ListaCanciones &playlist) {
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> distrib(0, playlist.size);

    int numeroAleatorio = distrib(gen);

    Node *cancionALeatoria = playlist.buscarPorID(numeroAleatorio);
    if (!cancionALeatoria) {  // Verificar si se encontró el nodo
        cout << "No se encontró ninguna canción con ID: " << numeroAleatorio << endl;
        return;
    }
    cancionALeatoria->cancion.reproducirCancion();
}

void cargarCSV(const string& nombre_archivo, ListaCanciones &playlist) {

    ifstream archivo(nombre_archivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo " << nombre_archivo << endl;
        return;
    }

    string linea;
    getline(archivo, linea);  // Leer la cabecera del CSV (esta línea ya no es necesaria)
    vector<string> atributos;
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
        // Crear un objeto Cancion y añadirlo al vector de playlist
        Cancion cancion(id, artist_name, track_name, track_id, popularity, year, genre,danceability, energy, key, loudness, mode, speechiness,
                             acousticness, instrumentalness, liveness, valence, tempo,
                             duration_ms, time_signature);
        playlist.agregarCancion(cancion);
    }

    archivo.close();
}
