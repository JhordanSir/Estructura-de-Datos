#ifndef MY_B_TREE_H
#define MY_B_TREE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MAX_KEYS 4

struct BTreeNode {
  int num_keys;
  float keys[MAX_KEYS];
  struct BTreeNode *children[MAX_KEYS + 1];
};

// Funciones para manejo del árbol B
struct BTreeNode *createNode();
void splitChild(struct BTreeNode *parent, int index);
void insertKey(struct BTreeNode *node, float key);
void insertNonFull(struct BTreeNode *node, float key);
void insert(struct BTreeNode **root, float key);
void loadCSVIntoBTree(struct BTreeNode **root, const char *filename, int decimals);
void printBTree(struct BTreeNode *node, int level);
float roundToDecimals(float value, int decimals);

#endif

