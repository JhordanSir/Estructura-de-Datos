#ifndef BTREE_H
#define BTREE_H

#include "cancion.h"
#include <vector>
#include <string>

class BTreeNode {
public:
    std::vector<Cancion> keys;
    std::vector<BTreeNode*> children;
    bool isLeaf;
    int t;

    BTreeNode(int t, bool isLeaf);

    void insertNonFull(Cancion k);
    void splitChild(int i, BTreeNode* y);
    void traverse();
    BTreeNode* search(const std::string& key, bool searchByArtist);
    void searchAll(const std::string& key, bool searchByArtist, std::vector<Cancion>& result);

};

class BTree {
public:
    BTreeNode* root;
    int t;

    BTree(int t);

    void traverse();
    BTreeNode* search(const std::string& key, bool searchByArtist);
    void insert(Cancion k);
    void searchAll(const std::string& key, bool searchByArtist, std::vector<Cancion>& result); 
};

#endif // BTREE_H