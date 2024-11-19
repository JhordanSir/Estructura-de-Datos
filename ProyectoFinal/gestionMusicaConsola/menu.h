#include "playlist.h"
#include <iostream>
#include <chrono>

using namespace std;

class Menu {
public:
    PlayList playlist;
    Menu() {
        cout << "Inicializando menú y cargando lista de reproducción..." << endl;
    }

    // Destructor
    ~Menu() {
        cout << "Liberando recursos y cerrando el menú..." << endl;
    }
    void lectura_csv();
    void interfaz_menu();
    void menu_busqueda(int numero_opcion);
    void menu_ordenamiento(int numero_opcion);
    void menu_reproduccion_aleatoria(int numero_opcion);
    void menu_impresion(int numero_opcion);
    void menu_actualizar_cancion (int numero_opcion);
};