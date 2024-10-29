#include "b_tree.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Función para redondear a n decimales
float roundToDecimals(float value, int decimals) {
  float factor = pow(10, decimals);
  return roundf(value * factor) / factor;
}

struct BTreeNode *createNode() {
  struct BTreeNode *newNode =
  	(struct BTreeNode *)malloc(sizeof(struct BTreeNode));
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
  newChild->num_keys = MAX_KEYS / 2;
  for (int i = 0; i < MAX_KEYS / 2; i++) {
	newChild->keys[i] = child->keys[i + MAX_KEYS / 2 + 1];
  }
  if (child->children[0] != NULL) {
	for (int i = 0; i < MAX_KEYS / 2 + 1; i++) {
  	newChild->children[i] = child->children[i + MAX_KEYS / 2 + 1];
	}
  }
  child->num_keys = MAX_KEYS / 2;
  for (int i = parent->num_keys; i >= index + 1; i--) {
	parent->children[i + 1] = parent->children[i];
  }
  parent->children[index + 1] = newChild;
  for (int i = parent->num_keys - 1; i >= index; i--) {
	parent->keys[i + 1] = parent->keys[i];
  }
  parent->keys[index] = child->keys[MAX_KEYS / 2];
  parent->num_keys++;
}

void insertKey(struct BTreeNode *node, float key) {  // Cambiado a float
  int i = node->num_keys - 1;
  while (i >= 0 && node->keys[i] > key) {
	node->keys[i + 1] = node->keys[i];
	i--;
  }
  node->keys[i + 1] = key;
  node->num_keys++;
}

void insertNonFull(struct BTreeNode *node, float key) {  // Cambiado a float
  int i = node->num_keys - 1;
  if (node->children[0] == NULL) {
	insertKey(node, key);
	return;
  }
  while (i >= 0 && node->keys[i] > key) {
	i--;
  }
  i++;
  if (node->children[i]->num_keys == MAX_KEYS) {
	splitChild(node, i);
	if (node->keys[i] < key) {
  	i++;
	}
  }
  insertNonFull(node->children[i], key);
}

void insert(struct BTreeNode **root, float key) {  // Cambiado a float
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

  // Leer la segunda fila, que contiene las llaves
  if (fgets(line, sizeof(line), file)) {
	char *token = strtok(line, ",");
	// Ignorar la primera columna vacía
	token = strtok(NULL, ",");
    
	while (token != NULL) {
  	float key = atof(token);               	// Convertimos cada número a flotante
  	key = roundToDecimals(key, decimals);  	// Redondeamos al número de decimales especificado
  	insert(root, key);                     	// Insertamos el número en el árbol B
  	token = strtok(NULL, ",");
	}
  }

  fclose(file);
  printf("Datos cargados desde %s al árbol B.\n", filename);
}
