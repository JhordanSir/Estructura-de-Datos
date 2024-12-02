#include "menu.h"
#include <iostream>

//menú principal

void Menu::lectura_csv(){
    // =============================== LECTURA DEL CSV ===============================
    cout << "Leyendo datos desde archivo CSV..." << endl;
    auto inicioLectura = chrono::high_resolution_clock::now();
    
    playlist.cargarCSV("Pruebas.csv");

    auto finLectura = chrono::high_resolution_clock::now();
    auto duracionLectura = chrono::duration_cast<chrono::seconds>(finLectura - inicioLectura).count();
    cout << "Archivo cargado en " << duracionLectura << " segundos." << endl; 
}

void Menu::interfaz_menu() {
    int numero_opcion = 0;
    Menu::lectura_csv();
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
            menu_busqueda(numero_opcion);
        }
        else if (numero_opcion == 2) {
            menu_ordenamiento(numero_opcion);
        }
        else if (numero_opcion == 3) {
            menu_reproduccion_aleatoria(numero_opcion);
        }
        else if (numero_opcion == 4) {
            playlist.imprimirCanciones();
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

void Menu::menu_busqueda(int numero_opcion) {
    cout << "Seleccione un tipo de Búsqueda: " << endl;
    cout << "[1] Por Nombre de Canción" << endl;
    cout << "[2] Por Nombre de Artista" << endl;
    cout << "[3] Salir" << endl;
    cin >> numero_opcion;

    string nombreBusqueda;
    vector<Cancion> resultados;

    switch (numero_opcion) {
        case 1:
            cout << "Ingrese el prefijo del nombre de la canción: ";
            cin.ignore();
            getline(cin, nombreBusqueda);
            {
                vector<string> canciones = playlist.cancionesTrie.findWordsWithPrefix(nombreBusqueda);
                if (!canciones.empty()) {
                    cout << "Canciones encontradas con el prefijo '" << nombreBusqueda << "':\n";
                    for (size_t i = 0; i < canciones.size(); ++i) {
                        cout << "[" << i + 1 << "] " << canciones[i] << endl;
                    }
                    cout << "Seleccione el número de la canción que desea buscar: ";
                    int seleccion;
                    cin >> seleccion;
                    if (seleccion > 0 && seleccion <= canciones.size()) {
                        nombreBusqueda = canciones[seleccion - 1];
                        resultados = playlist.buscarPorNombre(nombreBusqueda, false);
                        if (!resultados.empty()) {
                            for (auto& cancion : resultados) {
                                cancion.imprimirDatos();
                            }
                        } else {
                            cout << "No se encontró ninguna canción con el nombre " << nombreBusqueda << ".\n";
                        }
                    } else {
                        cout << "Selección no válida.\n";
                    }
                } else {
                    cout << "No se encontró ninguna canción con el prefijo " << nombreBusqueda << ".\n";
                }
            }
            break;
        case 2:
            cout << "Ingrese el prefijo del nombre del artista: ";
            cin.ignore();
            getline(cin, nombreBusqueda);
            {
                vector<string> artistas = playlist.artistasTrie.findWordsWithPrefix(nombreBusqueda);
                if (!artistas.empty()) {
                    cout << "Artistas encontrados con el prefijo '" << nombreBusqueda << "':\n";
                    for (size_t i = 0; i < artistas.size(); ++i) {
                        cout << "[" << i + 1 << "] " << artistas[i] << endl;
                    }
                    cout << "Seleccione el número del artista que desea buscar: ";
                    int seleccion;
                    cin >> seleccion;
                    if (seleccion > 0 && seleccion <= artistas.size()) {
                        nombreBusqueda = artistas[seleccion - 1];
                        resultados = playlist.buscarPorNombre(nombreBusqueda, true);
                        if (!resultados.empty()) {
                            for (auto& cancion : resultados) {
                                cancion.imprimirDatos();
                            }
                        } else {
                            cout << "No se encontró ningún artista con el nombre " << nombreBusqueda << ".\n";
                        }
                    } else {
                        cout << "Selección no válida.\n";
                    }
                } else {
                    cout << "No se encontró ningún artista con el prefijo " << nombreBusqueda << ".\n";
                }
            }
            break;
        case 3:
            break;
        default:
            cout << "Opción no válida." << endl;
            break;
    }
}

void Menu::menu_ordenamiento(int numero_opcion) {
    cout << "Seleccione un tipo de Ordenamiento: " << endl;
    cout << "[1] Por Popularidad" << endl;
    cout << "[2] Por Año" << endl;
    cout << "[3] Por Nombre del Artista" << endl;
    cout << "[4] Por Nombre de la Canción" << endl;
    cout << "[5] Por Género" << endl;
    cout << "[6] Por Duración" << endl;
    cout << "[7] Por Tempo" << endl;
    cout << "[8] Salir" << endl;
    cin >> numero_opcion;

    switch (numero_opcion) {
        case 1:
            playlist.ordenarPorAtributo("popularidad");
            break;
        case 2:
            playlist.ordenarPorAtributo("anio");
            break;
        case 3:
            playlist.ordenarPorAtributo("artista");
            break;
        case 4:
            playlist.ordenarPorAtributo("cancion");
            break;
        case 5:
            playlist.ordenarPorAtributo("genero");
            break;
        case 6:
            playlist.ordenarPorAtributo("duracion");
            break;
        case 7:
            playlist.ordenarPorAtributo("tempo");
            break;
        case 8:
            break;
        default:
            cout << "Opción no válida." << endl;
            break;
    }
}

void Menu::menu_reproduccion_aleatoria(int numero_opcion){
    // =============================== REPRODUCCIÓN ALEATORIA ===============================
    cout << "\nReproduciendo canción aleatoria..." << endl;
    playlist.reproduccionAleatoria();
} 

void Menu::menu_actualizar_cancion(int numero_opcion) {
    int idActualizacion;
    cout << "Ingrese el ID de la canción a actualizar: ";
    cin >> idActualizacion;

    BTreeNode* nodo = playlist.btree->search(to_string(idActualizacion), false);
    Cancion* cancion = nullptr;

    if (nodo) {
        for (auto& c : nodo->keys) {
            if (c.id == idActualizacion) {
                cancion = &c;
                break;
            }
        }
    }

    if (!cancion) {
        cout << "No se encontró una canción con el ID " << idActualizacion << " para actualizar.\n";
        return;
    }

    int opcion;
    do {
        cout << "\nSeleccione el atributo a modificar: " << endl;
        cout << "[1] Nombre del Artista" << endl;
        cout << "[2] Nombre de la Canción" << endl;
        cout << "[3] ID del Track" << endl;
        cout << "[4] Popularidad" << endl;
        cout << "[5] Año" << endl;
        cout << "[6] Género" << endl;
        cout << "[7] Danceability" << endl;
        cout << "[8] Energy" << endl;
        cout << "[9] Key" << endl;
        cout << "[10] Loudness" << endl;
        cout << "[11] Mode" << endl;
        cout << "[12] Speechiness" << endl;
        cout << "[13] Acousticness" << endl;
        cout << "[14] Instrumentalness" << endl;
        cout << "[15] Liveness" << endl;
        cout << "[16] Valence" << endl;
        cout << "[17] Tempo" << endl;
        cout << "[18] Duración en ms" << endl;
        cout << "[19] Time Signature" << endl;
        cout << "[20] Salir" << endl;
        cout << ">> ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese el nuevo nombre del artista: ";
                cin.ignore();
                getline(cin, cancion->artist_name);
                break;
            case 2:
                cout << "Ingrese el nuevo nombre de la canción: ";
                cin.ignore();
                getline(cin, cancion->track_name);
                break;
            case 3:
                cout << "Ingrese el nuevo ID del track: ";
                cin.ignore();
                getline(cin, cancion->track_id);
                break;
            case 4:
                cout << "Ingrese la nueva popularidad: ";
                cin >> cancion->popularity;
                break;
            case 5:
                cout << "Ingrese el nuevo año: ";
                cin >> cancion->year;
                break;
            case 6:
                cout << "Ingrese el nuevo género: ";
                cin.ignore();
                getline(cin, cancion->genre);
                break;
            case 7:
                cout << "Ingrese la nueva danceability: ";
                cin >> cancion->danceability;
                break;
            case 8:
                cout << "Ingrese la nueva energy: ";
                cin >> cancion->energy;
                break;
            case 9:
                cout << "Ingrese el nuevo key: ";
                cin >> cancion->key;
                break;
            case 10:
                cout << "Ingrese el nuevo loudness: ";
                cin >> cancion->loudness;
                break;
            case 11:
                cout << "Ingrese el nuevo mode: ";
                cin >> cancion->mode;
                break;
            case 12:
                cout << "Ingrese la nueva speechiness: ";
                cin >> cancion->speechiness;
                break;
            case 13:
                cout << "Ingrese la nueva acousticness: ";
                cin >> cancion->acousticness;
                break;
            case 14:
                cout << "Ingrese la nueva instrumentalness: ";
                cin >> cancion->instrumentalness;
                break;
            case 15:
                cout << "Ingrese la nueva liveness: ";
                cin >> cancion->liveness;
                break;
            case 16:
                cout << "Ingrese la nueva valence: ";
                cin >> cancion->valence;
                break;
            case 17:
                cout << "Ingrese el nuevo tempo: ";
                cin >> cancion->tempo;
                break;
            case 18:
                cout << "Ingrese la nueva duración en ms: ";
                cin >> cancion->duration_ms;
                break;
            case 19:
                cout << "Ingrese el nuevo time signature: ";
                cin >> cancion->time_signature;
                break;
            case 20:
                cout << "Saliendo de la actualización de canción..." << endl;
                break;
            default:
                cout << "Opción no válida." << endl;
                break;
        }
    } while (opcion != 20);

    cout << "Canción actualizada:\n";
    cancion->imprimirDatos();
}