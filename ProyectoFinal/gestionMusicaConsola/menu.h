#include "playlistmanager.h"
#include <iostream>
#include <chrono>

using namespace std;

class Menu {
public:
    PlayList playlist;
    PlaylistManager mapadeplaylists;
    Menu() : playlist(5), mapadeplaylists() {
        cout << "Inicializando menú y cargando lista de reproducción..." << endl;
    }

    // Destructor
    ~Menu() {
        cout << "Liberando recursos y cerrando el menú..." << endl;
    }
    void lectura_csv();
    void matriz_menu();
    void interfaz_menu(PlayList& playlist);
    void menu_busqueda(PlayList& playlist, int numero_opcion);
    void menu_ordenamiento(PlayList& playlistSeleccionada, int numero_opcion);
    void menu_reproduccion_aleatoria(PlayList& playlistSeleccionada, int numero_opcion);
    void menu_impresion(PlayList& playlistSeleccionada, int numero_opcion);
    void menu_actualizar_cancion(PlayList& playlistSeleccionada, int numero_opcion);
    void menu_nueva_playlist();
    void menu_seleccion_playlist();
};