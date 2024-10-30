#include "b_tree.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Función para redondear a n decimales
float roundToDecimals(float value, int decimals) {
    float factor = pow(10, decimals);
    return roundf(value * factor) / factor;
}

struct BTreeNode *createNode() {
    struct BTreeNode *newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
    if (newNode == NULL) {
        printf("La asignación de memoria falló.\n");
        exit(1);
    }
    newNode->num_keys = 0;
    for (int i = 0; i < MAX_KEYS + 1; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

void splitChild(struct BTreeNode *parent, int index) {
    struct BTreeNode *child = parent->children[index];
    struct BTreeNode *newChild = createNode();
    
    // El punto medio
    int mid = child->num_keys / 2;

    // Copiar la mitad de las claves a newChild
    for (int i = 0; i < mid; i++) {
        newChild->keys[i] = child->keys[i + mid + 1];
    }

    // Copiar los hijos, si existen
    if (child->children[0] != NULL) {
        for (int i = 0; i <= mid; i++) {
            newChild->children[i] = child->children[i + mid + 1];
        }
    }

    // Ajustar el número de claves en los nodos
    newChild->num_keys = mid;
    child->num_keys = mid;

    // Mover los hijos en parent
    for (int i = parent->num_keys; i >= index + 1; i--) {
        parent->children[i + 1] = parent->children[i];
    }
    parent->children[index + 1] = newChild;

    // Mover las claves en parent
    for (int i = parent->num_keys - 1; i >= index; i--) {
        parent->keys[i + 1] = parent->keys[i];
    }
    parent->keys[index] = child->keys[mid]; // Usar la clave central
    parent->num_keys++;
}

void insertKey(struct BTreeNode *node, float key) {
    int i = node->num_keys - 1;
    while (i >= 0 && node->keys[i] > key) {
        node->keys[i + 1] = node->keys[i];
        i--;
    }
    node->keys[i + 1] = key;
    node->num_keys++;
}

void insertNonFull(struct BTreeNode *node, float key) {
    int i = node->num_keys - 1;

    if (node->children[0] == NULL) { // Es un nodo hoja
        insertKey(node, key);
        return;
    }

    // Encontrar el hijo correspondiente
    while (i >= 0 && node->keys[i] > key) {
        i--;
    }
    i++;

    // Verificar si el hijo está lleno
    if (node->children[i]->num_keys == MAX_KEYS) {
        splitChild(node, i);
        if (node->keys[i] < key) {
            i++;
        }
    }
    insertNonFull(node->children[i], key);
}

void insert(struct BTreeNode **root, float key) {
    if (*root == NULL) {
        *root = createNode();
        (*root)->keys[0] = key;
        (*root)->num_keys = 1;
    } else {
        if ((*root)->num_keys == MAX_KEYS) {
            struct BTreeNode *newRoot = createNode();
            newRoot->children[0] = *root;
            splitChild(newRoot, 0);
            *root = newRoot;
        }
        insertNonFull(*root, key);
    }
}

void loadCSVIntoBTree(struct BTreeNode **root, const char *filename, int decimals) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("No se pudo abrir el archivo %s.\n", filename);
        return;
    }

    char line[1024];
    // Saltar la primera fila del archivo (encabezado)
    fgets(line, sizeof(line), file);

    // Leer las siguientes filas que contienen las llaves
    while (fgets(line, sizeof(line), file)) {
        printf("Leyendo línea: %s", line);
        
        char *token = strtok(line, ",");
        // Ignorar la primera columna (índice)
        token = strtok(NULL, ",");

        while (token != NULL) {
            while (isspace((unsigned char)*token)) token++; // Eliminar espacios en blanco
            float key = atof(token);
            key = roundToDecimals(key, decimals);
            printf("Insertando clave: %f\n", key);
            insert(root, key);
            token = strtok(NULL, ",");
        }
    }

    fclose(file);
    printf("Datos cargados desde %s al árbol B.\n", filename);
}

void printBTree(struct BTreeNode *node, int level) {
    if (node == NULL) {
        return;
    }

    // Imprimir el nivel actual
    for (int i = 0; i < level; i++) {
        printf("  ");
    }

    // Imprimir las claves del nodo actual
    for (int i = 0; i < node->num_keys; i++) {
        printf("%f ", node->keys[i]);
    }
    printf("\n");

    // Recorrer recursivamente los hijos
    for (int i = 0; i <= node->num_keys; i++) {
        printBTree(node->children[i], level + 1);
    }
}
