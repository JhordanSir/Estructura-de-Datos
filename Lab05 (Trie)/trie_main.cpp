#include "my_trie.cpp"  // Asegúrate de incluir el encabezado correcto
using namespace std;

void menu(){
    cout<<"\n---------------------------------------"<<endl;
    cout << "\tMenú principal:" << endl;
    cout << "1. Buscar por prefijo" << endl;
    cout << "2. Eliminar palabra" << endl;
    cout << "3. Insertar palabra" << endl;
    cout << "4. Imprimir trie" << endl;
    cout << "5. Buscar palabra" << endl;
    cout << "6. Salir" << endl;
    cout<<"---------------------------------------"<<endl;
    cout << "Ingrese una opción: ";
}
int main() {
    int opcion;

    NodoTrie* trie = crear_nodo_trie('\0');  // Crear el Trie con un nodo raíz vacío
    cout<<"Leyendo archivo txt..."<<endl;
    leerTXT(trie, "words.txt");  // Leer palabras desde el archivo y construir el Trie
    cout<<"Se terminó de leer el archivo";
    
    do {
        menu();
        cin >> opcion;
        string palabrita;
        vector<string> resultados;
        switch (opcion) {
            case 1:
                cout << "Ingrese el prefijo a buscar: ";
                cin>>palabrita;
                resultados = buscar_por_prefijo(trie, palabrita);
                for (string palabra : resultados) {
                    cout << palabra << endl;
                }
                break;
            case 2:
                cout << "Ingrese la palabra a eliminar: ";
                cin>>palabrita;
                cout<<palabrita<<(eliminar_palabra(trie,palabrita) ? " No se elimina correctamente\n" : " Se elimina correctamente\n");
                break;
            case 3:
                cout << "Ingrese la palabra a insertar: ";
                cin>>palabrita;
                trie = insertar_trie(trie, palabrita);
                cout<<"Se inserto correctamente ;D\n";
                break;
            case 4:
                cout << "Imprimiendo trie..." << endl;
                imprimir_trie(trie);
                break;
            case 5:
                cout << "Ingrese la palabra a buscar: ";
                cin>>palabrita;
                resultados = buscar_por_prefijo(trie, palabrita);
                if (!resultados.empty() && resultados[0]==palabrita) cout<<resultados[0]<<" si existe"<<endl;
                else cout<<"Tu palabrita no existe"<<endl;
            break; 
            case 6:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción inválida. Intente nuevamente." << endl;
        }
    } while (opcion != 6);
    cout<<"Eliminando noditos..."<<endl;
    liberar_trie(trie);
    return 0;
}
