#include "playlist.h"
#include <iostream>
#include <chrono>

using namespace std;

class Menu {
public:
    //Constructor
    Menu() {
        cout << "Inicializando menú y cargando lista de reproducción..." << endl;
        playlist = PlayList();
    }

    // Destructor
    ~Menu() {
        cout << "Liberando recursos y cerrando el menú..." << endl;
    }
    PlayList playlist;
    void lectura_csv(PlayList& playlist);
    void interfaz_menu(PlayList& playlist);
    void menu_busqueda(PlayList& playlist, int numero_opcion);
    void menu_ordenamiento(PlayList& playlist, int numero_opcion);
    void menu_reproduccion_aleatoria(PlayList& playlist, int numero_opcion);
    void menu_impresion(PlayList& playlist, int numero_opcion);
    void menu_actualizar_cancion (PlayList& playlist, int numero_opcion);
};