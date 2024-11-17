#include "playlist.h"
#include <chrono>
#include <iostream>

using namespace std;

int main() {
    PlayList playlist;

    // =============================== LECTURA DEL CSV ===============================
    cout << "Leyendo datos desde archivo CSV..." << endl;
    auto inicioLectura = chrono::high_resolution_clock::now();
    
    playlist.cargarCSV("spotify_data.csv"); // Cambia el nombre del archivo según sea necesario

    auto finLectura = chrono::high_resolution_clock::now();
    auto duracionLectura = chrono::duration_cast<chrono::seconds>(finLectura - inicioLectura).count();
    cout << "Archivo cargado en " << duracionLectura << " segundos." << endl;

    // =============================== ORDENAMIENTO POR AÑO ===============================
    cout << "Ordenando canciones por año..." << endl;
    auto inicioOrdenamiento = chrono::high_resolution_clock::now();
    
    playlist.ordenarPorAnio();

    auto finOrdenamiento = chrono::high_resolution_clock::now();
    auto duracionOrdenamiento = chrono::duration_cast<chrono::seconds>(finOrdenamiento - inicioOrdenamiento).count();
    cout << "Ordenamiento completado en " << duracionOrdenamiento << " segundos." << endl;

    // =============================== IMPRESIÓN ASCENDENTE Y DESCENDENTE ===============================
    cout << "Impresión de canciones en orden ascendente:" << endl;
    playlist.imprimirCanciones(false); // False para imprimir desde `head` (orden ascendente)

    cout << "\nImpresión de canciones en orden descendente:" << endl;
    playlist.imprimirCanciones(true); // True para imprimir desde `tail` (orden descendente)

    // =============================== BÚSQUEDA POR AÑO ===============================
    int anioBusqueda = 2000;
    cout << "\nBuscando canciones del año " << anioBusqueda << "..." << endl;
    vector<Node*> cancionesAnio = playlist.ordenarporDeterminadoAnio(anioBusqueda);

    if (!cancionesAnio.empty()) {
        cout << "Canciones encontradas del año " << anioBusqueda << ":\n";
        for (Node* nodo : cancionesAnio) {
            nodo->cancion.imprimirDatos();
        }
    } else {
        cout << "No se encontraron canciones del año " << anioBusqueda << ".\n";
    }

    // =============================== BÚSQUEDA POR ID ===============================
    int idBusqueda = playlist.size; // Buscar última canción por ID
    cout << "\nBuscando canción por ID: " << idBusqueda << "..." << endl;
    Node* cancionID = playlist.buscarPorID(idBusqueda);

    if (cancionID) {
        cout << "Canción encontrada:\n";
        cancionID->cancion.imprimirDatos();
    } else {
        cout << "No se encontró una canción con el ID " << idBusqueda << ".\n";
    }

    // =============================== ACTUALIZACIÓN DE CANCIÓN ===============================
    int idActualizacion = 1; // Actualizar primera canción
    cout << "\nActualizando canción con ID " << idActualizacion << "..." << endl;
    Node* cancionActualizar = playlist.buscarPorID(idActualizacion);
    if (cancionActualizar) {
        playlist.actualizarCancion(cancionActualizar, Cancion(idActualizacion, "Nuevo Artista", "Nueva Canción", "ID12345", 85, 2022, "Pop", 0.8, 0.7, 5, -3.0, 1, 0.05, 0.1, 0.0, 0.15, 0.6, 120.0, 210000, 4));
        cout << "Canción actualizada:\n";
        cancionActualizar->cancion.imprimirDatos();
    } else {
        cout << "No se encontró una canción con el ID " << idActualizacion << " para actualizar.\n";
    }

    // =============================== REPRODUCCIÓN ALEATORIA ===============================
    cout << "\nReproduciendo canción aleatoria..." << endl;
    playlist.reproduccionAleatoria();

    return 0;
}
