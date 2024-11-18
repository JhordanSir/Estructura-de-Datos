#include "menu.h"
#include "playlist.h"
#include <iostream>

//menú principal
void Menu::lectura_csv(PlayList& playlist){
    // =============================== LECTURA DEL CSV ===============================
    cout << "Leyendo datos desde archivo CSV..." << endl;
    auto inicioLectura = chrono::high_resolution_clock::now();
    
    playlist.cargarCSV("Pruebas.csv"); // Cambia el nombre del archivo según sea necesario

    auto finLectura = chrono::high_resolution_clock::now();
    auto duracionLectura = chrono::duration_cast<chrono::seconds>(finLectura - inicioLectura).count();
    cout << "Archivo cargado en " << duracionLectura << " segundos." << endl; 
}

void Menu::interfaz_menu(PlayList& playlist) {
    int numero_opcion;
    Menu::lectura_csv(playlist);
    // Bucle infinito para mantener el menú en ejecución hasta que el usuario elija salir
    while (numero_opcion != 5) {
        cout << "\nSeleccione una opción: " << endl;
        cout << "[1] Búsqueda" << endl;
        cout << "[2] Ordenamiento" << endl;
        cout << "[3] Reproducción Aleatoria" << endl;
        cout << "[4] Impresión" << endl;
        cout << "[5] Salir \n>> ";  // Opción para salir
        cin >> numero_opcion;
        cout << "\n";
        // Ejecuta la acción según la opción seleccionada
        if (numero_opcion == 1) {
            menu_busqueda(playlist, numero_opcion);
        }
        else if (numero_opcion == 2) {
            menu_ordenamiento(playlist, numero_opcion);
        }
        else if (numero_opcion == 3) {
            menu_reproduccion_aleatoria(playlist, numero_opcion);
        }
        else if (numero_opcion == 4) {
            menu_impresion(playlist, numero_opcion);
        }
        else if (numero_opcion == 5) {
            cout << "Saliendo del menú..." << endl;
            break;  // Sale del bucle y termina el programa
        }
        else {
            cout << "Opción no válida." << endl;
        }
    }
}


void Menu::menu_busqueda(PlayList& playlist, int numero_opcion) {
    int anioBusqueda;
    vector<Node*> cancionesAnio;
    Node* cancionID;
    int idBusqueda;
    cout << "Seleccione un tipo de Búsqueda: " << endl;
    cout << "[1] Por ID" << endl;
    cout << "[2] Por Año" << endl;
    cin >> numero_opcion;
    switch (numero_opcion) {
        case 1:
            // Búsqueda por ID
            // =============================== BÚSQUEDA POR ID ===============================
            idBusqueda = playlist.size - 1; // Buscar última canción por ID
            cout << "\nBuscando canción por ID: " << idBusqueda << "..." << endl;
            cancionID = playlist.buscarPorID(idBusqueda);

            if (cancionID) {
                cout << "Canción encontrada:\n";
                cancionID->cancion.imprimirDatos();
            } else {
                cout << "No se encontró una canción con el ID " << idBusqueda << ".\n";
            }
            break;
        case 2:
            // =============================== BÚSQUEDA POR AÑO ===============================
            cout << "\nIngrese un año" << endl;
            cin >> anioBusqueda;
            cout << "Buscando canciones del año " << anioBusqueda << "..." << endl;
            cancionesAnio = playlist.ordenarporDeterminadoAnio(anioBusqueda);

            if (!cancionesAnio.empty()) {
                cout << "Canciones encontradas del año " << anioBusqueda << ":\n";
                for (Node* nodo : cancionesAnio) {
                    nodo->cancion.imprimirDatos();
                }
            } else {
                cout << "No se encontraron canciones del año " << anioBusqueda << ".\n";
            }
            break;

        default:
            cout << "Opción no válida." << endl;
            break;
    }
}


void Menu::menu_ordenamiento(PlayList& playlist, int numero_opcion) {
    // Declarar variables fuera del switch para evitar errores de alcance
    chrono::time_point<chrono::high_resolution_clock> inicioOrdenamiento, finOrdenamiento;
    long long duracionOrdenamiento;

    cout << "Seleccione un tipo de Ordenamiento" << endl;
    cout << "[1] Por Popularidad" << endl;
    cout << "[2] Por Duración" << endl;
    cout << "[3] Por Año" << endl; // Corregido el número de opción duplicado
    cin >> numero_opcion;

    switch (numero_opcion) {
        case 1:
            playlist.ordenarPorPopularidad();
            break;

        case 2:
            playlist.ordenarPorDuracion();
            break;

        case 3:
            // =============================== ORDENAMIENTO POR AÑO ===============================
            cout << "Ordenando canciones por año..." << endl;

            // Capturar tiempo inicial antes de ordenar
            inicioOrdenamiento = chrono::high_resolution_clock::now();

            playlist.ordenarPorAnio();

            // Capturar tiempo final después de ordenar
            finOrdenamiento = chrono::high_resolution_clock::now();

            // Calcular la duración del ordenamiento en segundos
            duracionOrdenamiento = chrono::duration_cast<chrono::seconds>(finOrdenamiento - inicioOrdenamiento).count();
            cout << "Ordenamiento completado en " << duracionOrdenamiento << " segundos." << endl;
            break;

        default:
            cout << "Opción no válida." << endl;
            break;
    }
}

void Menu::menu_impresion (PlayList& playlist, int numero_opcion){
    cout<<"Seleccione un tipo de Impresion"<<endl;
    cout<< "[1] De forma ascendente" << endl;
    cout<< "[2] De forma descendente" << endl;
    cin>> numero_opcion;
    switch(numero_opcion){
        case 1:
        // =============================== IMPRESIÓN ASCENDENTE Y DESCENDENTE ===============================
        cout << "\nImpresión de canciones en orden ascendente:" << endl;
        playlist.imprimirCanciones(false); // False para imprimir desde `head` (orden ascendente)
        break;

        case 2:
        cout << "\nImpresión de canciones en orden descendente:" << endl;
        playlist.imprimirCanciones(true); // True para imprimir desde `tail` (orden descendente)
        break;

        default:
            cout << "Opción no válida." << endl;
            break;
    }

}

void Menu::menu_reproduccion_aleatoria (PlayList& playlist, int numero_opcion){
    // =============================== REPRODUCCIÓN ALEATORIA ===============================
    cout << "\nReproduciendo canción aleatoria..." << endl;
    playlist.reproduccionAleatoria();

} 

void Menu::menu_actualizar_cancion (PlayList& playlist, int numero_opcion){
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
}