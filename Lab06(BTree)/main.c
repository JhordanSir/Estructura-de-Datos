#include "b_tree.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	struct BTreeNode *root = NULL;
	loadCSVIntoBTree(&root, "random_numbers_1000000.csv", 10);
}
