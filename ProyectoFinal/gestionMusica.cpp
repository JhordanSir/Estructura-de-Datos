#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

struct Cancion {
    int id;
    string artist_name;
    string track_name;
    string track_id;
    double popularity;
    int year;
    string genre;
    double danceability;
    double energy;
    double key;
    double loudness;
    double mode;
    double speechiness;
    double acousticness;
    double instrumentalness;
    double liveness;
    double valence;
    double tempo;
    int duration_ms;
    int time_signature;
};

struct NodoArbolB {
    int num_claves;
    int max_claves;
    vector<Cancion> playlist;
    vector<NodoArbolB*> hijos;

    NodoArbolB(int max_claves);
};

NodoArbolB::NodoArbolB(int max_claves) : num_claves(0), max_claves(max_claves) {
    playlist.resize(max_claves);
    hijos.resize(max_claves + 1, nullptr);
}

NodoArbolB* crearNodo(int max_claves) {
    return new NodoArbolB(max_claves);
}

void dividirHijo(NodoArbolB* padre, int indice, int max_claves) {
    NodoArbolB* hijo = padre->hijos[indice];
    NodoArbolB* nuevoHijo = crearNodo(max_claves);

    int mitad = (max_claves - 1) / 2;

    for (int i = 0; i < max_claves - mitad - 1; i++) {
        nuevoHijo->playlist[i] = hijo->playlist[mitad + 1 + i];
    }

    if (hijo->hijos[0] != nullptr) {
        for (int i = 0; i <= max_claves - mitad - 1; i++) {
            nuevoHijo->hijos[i] = hijo->hijos[mitad + 1 + i];
        }
    }

    nuevoHijo->num_claves = max_claves - mitad - 1;
    hijo->num_claves = mitad;

    for (int i = padre->num_claves; i >= indice + 1; i--) {
        padre->hijos[i + 1] = padre->hijos[i];
    }
    padre->hijos[indice + 1] = nuevoHijo;

    for (int i = padre->num_claves - 1; i >= indice; i--) {
        padre->playlist[i + 1] = padre->playlist[i];
    }
    padre->playlist[indice] = hijo->playlist[mitad];
    padre->num_claves++;
}

void insertarCancion(NodoArbolB* nodo, Cancion cancion) {
    int i = nodo->num_claves - 1;
    while (i >= 0 && nodo->playlist[i].id > cancion.id) {
        nodo->playlist[i + 1] = nodo->playlist[i];
        i--;
    }
    nodo->playlist[i + 1] = cancion;
    nodo->num_claves++;
}

void insertarNoLleno(NodoArbolB* nodo, Cancion cancion, int max_claves) {
    if (nodo == nullptr) {
        cout << "Nodo nulo en insertarNoLleno." << endl;
        return;
    }

    int i = nodo->num_claves - 1;

    if (nodo->hijos[0] == nullptr) {  // Si es una hoja
        insertarCancion(nodo, cancion);
        return;
    }

    while (i >= 0 && nodo->playlist[i].id > cancion.id) {
        i--;
    }
    i++;

    if (nodo->hijos[i] != nullptr && nodo->hijos[i]->num_claves == max_claves) {
        dividirHijo(nodo, i, max_claves);
        if (nodo->playlist[i].id < cancion.id) {
            i++;
        }
    }

    if (i > nodo->num_claves) {
        i = nodo->num_claves;
    }

    if (nodo->hijos[i] != nullptr) {
        insertarNoLleno(nodo->hijos[i], cancion, max_claves);
    } else {
        cout << "Nodo hijo nulo en insertarNoLleno." << endl;
    }
}

void insertar(NodoArbolB** raiz, Cancion cancion, int max_claves) {
    if (*raiz == nullptr) {
        *raiz = crearNodo(max_claves);
        (*raiz)->playlist[0] = cancion;
        (*raiz)->num_claves = 1;
    } else {
        if ((*raiz)->num_claves == max_claves) {
            NodoArbolB* nuevaRaiz = crearNodo(max_claves);
            nuevaRaiz->hijos[0] = *raiz;
            dividirHijo(nuevaRaiz, 0, max_claves);
            *raiz = nuevaRaiz;
        }
        insertarNoLleno(*raiz, cancion, max_claves);
    }
}

// Función para leer correctamente los campos de CSV con comas dentro de comillas
// Función para leer correctamente los campos de CSV con comas dentro de comillas
string leerCampoConComillas(stringstream& ss) {
    string campo;
    char c;
    if (ss.peek() == '"') {  // Si empieza con comillas
        ss.get();  // Consumir la comilla inicial
        while (ss.get(c) && c != '"') {
            campo += c;
        }
        // Consumir la comilla final
        return campo;
    } else {
        getline(ss, campo, ',');
        return campo;
    }
}
// Función para convertir cadena a número de tipo double de manera segura
double convertirAdecimal(const string& str) {
    try {
        return stod(str);
    } catch (const invalid_argument& e) {
        cerr << "Error al convertir a double: " << str << endl;
        return 0.0;  // Valor predeterminado si no se puede convertir
    }
}

// Función para convertir cadena a entero de manera segura
int convertirAentero(const string& str) {
    try {
        return stoi(str);
    } catch (const invalid_argument& e) {
        cerr << "Error al convertir a int: " << str << endl;
        return 0;  // Valor predeterminado si no se puede convertir
    }
}


void cargarCSVEnArbolB(NodoArbolB** raiz, const string& nombre_archivo, int max_claves) {
    ifstream archivo(nombre_archivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo " << nombre_archivo << endl;
        return;
    }

    string linea;
    // Eliminamos la línea que lee la cabecera del archivo
    getline(archivo, linea);  // Leer la cabecera del CSV (esta línea ya no es necesaria)
    int i;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string campo;
        Cancion cancion;
        cout<<i<<endl;
        // Leer los campos del CSV y asignar a la estructura Cancion
        cancion.id = stoi(leerCampoConComillas(ss));
        cancion.artist_name = leerCampoConComillas(ss);
        cancion.track_name = leerCampoConComillas(ss);
        cancion.track_id = leerCampoConComillas(ss);
        cancion.popularity = convertirAdecimal(leerCampoConComillas(ss));
        cancion.year = convertirAentero(leerCampoConComillas(ss));
        cancion.genre = leerCampoConComillas(ss);
        cancion.danceability = convertirAdecimal(leerCampoConComillas(ss));
        cancion.energy = convertirAdecimal(leerCampoConComillas(ss));
        cancion.key = stod(leerCampoConComillas(ss));
        cancion.loudness = stod(leerCampoConComillas(ss));
        cancion.mode = stod(leerCampoConComillas(ss));
        cancion.speechiness = stod(leerCampoConComillas(ss));
        cancion.acousticness = stod(leerCampoConComillas(ss));
        cancion.instrumentalness = stod(leerCampoConComillas(ss));
        cancion.liveness = stod(leerCampoConComillas(ss));
        cancion.valence = stod(leerCampoConComillas(ss));
        cancion.tempo = stod(leerCampoConComillas(ss));
        cancion.duration_ms = stod(leerCampoConComillas(ss));
        cancion.time_signature = stod(leerCampoConComillas(ss));
        i++;
        insertar(raiz, cancion, max_claves);
    }

    archivo.close();
}

void imprimirArbolB(NodoArbolB* nodo, int nivel) {
    if (nodo == nullptr) return;

    for (int i = 0; i < nivel; i++) {
        cout << "  ";
    }

    for (int i = 0; i < nodo->num_claves; i++) {
        cout << nodo->playlist[i].id << " ";
    }
    cout << endl;

    for (int i = 0; i <= nodo->num_claves; i++) {
        imprimirArbolB(nodo->hijos[i], nivel + 1);
    }
}

bool buscarCancion(NodoArbolB* nodo, int id) {
    if (nodo == nullptr) return false;

    int i = 0;
    while (i < nodo->num_claves && nodo->playlist[i].id < id) {
        i++;
    }

    if (i < nodo->num_claves && nodo->playlist[i].id == id) {
        return true; // Canción encontrada
    }

    // Buscar en los hijos
    if (nodo->hijos[i] != nullptr) {
        return buscarCancion(nodo->hijos[i], id);
    }

    return false;
}

int main() {
    NodoArbolB* raiz = nullptr;
    int max_claves = 3;

    cargarCSVEnArbolB(&raiz, "spotify_data.csv", max_claves);

    imprimirArbolB(raiz, 0);

    int id_buscar = 48;
    if (buscarCancion(raiz, id_buscar)) {
        cout << "Canción con id " << id_buscar << " encontrada." << endl;
    } else {
        cout << "Canción con id " << id_buscar << " no encontrada." << endl;
    }

    return 0;
}
