#include "btree.h"
#include <iostream>

BTree::BTree(int t) : t(t), root(nullptr) {}

BTreeNode::BTreeNode(int t, bool isLeaf) : t(t), isLeaf(isLeaf) {
    keys.reserve(2 * t - 1);
    children.reserve(2 * t);
}

void BTreeNode::traverse() {
    int i;
    for (i = 0; i < keys.size(); i++) {
        if (!isLeaf) {
            children[i]->traverse();
        }
        keys[i].imprimirDatos();
    }
    if (!isLeaf) {
        children[i]->traverse();
    }
}

BTreeNode* BTreeNode::search(const std::string& key, bool searchByArtist) {
    int i = 0;
    while (i < keys.size() && (searchByArtist ? keys[i].artist_name : keys[i].track_name) < key) {
        i++;
    }

    if (i < keys.size() && (searchByArtist ? keys[i].artist_name : keys[i].track_name) == key) {
        return this;
    }

    if (isLeaf) {
        return nullptr;
    }

    return children[i]->search(key, searchByArtist);
}

void BTreeNode::searchAll(const std::string& key, bool searchByArtist, std::vector<Cancion>& result) {
    int i = 0;
    while (i < keys.size() && (searchByArtist ? keys[i].artist_name : keys[i].track_name) < key) {
        i++;
    }

    if (i < keys.size() && (searchByArtist ? keys[i].artist_name : keys[i].track_name) == key) {
        result.push_back(keys[i]);
    }

    if (isLeaf) {
        return;
    }

    for (int j = 0; j <= keys.size(); j++) {
        children[j]->searchAll(key, searchByArtist, result);
    }
}

void BTree::traverse() {
    if (root != nullptr) {
        root->traverse();
    }
}

BTreeNode* BTree::search(const std::string& key, bool searchByArtist) {
    return (root == nullptr) ? nullptr : root->search(key, searchByArtist);
}

void BTree::searchAll(const std::string& key, bool searchByArtist, std::vector<Cancion>& result) {
    if (root != nullptr) {
        root->searchAll(key, searchByArtist, result);
    }
}

void BTree::insert(Cancion k) {
    if (root == nullptr) {
        root = new BTreeNode(t, true);
        root->keys.push_back(k);
    } else {
        if (root->keys.size() == 2 * t - 1) {
            BTreeNode* s = new BTreeNode(t, false);
            s->children.push_back(root);
            s->splitChild(0, root);

            int i = 0;
            if ((s->keys[0].artist_name < k.artist_name) || (s->keys[0].track_name < k.track_name)) {
                i++;
            }
            s->children[i]->insertNonFull(k);

            root = s;
        } else {
            root->insertNonFull(k);
        }
    }
}

void BTreeNode::insertNonFull(Cancion k) {
    int i = keys.size() - 1;

    if (isLeaf) {
        keys.push_back(k);
        while (i >= 0 && (keys[i].artist_name > k.artist_name || keys[i].track_name > k.track_name)) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
    } else {
        while (i >= 0 && (keys[i].artist_name > k.artist_name || keys[i].track_name > k.track_name)) {
            i--;
        }
        if (children[i + 1]->keys.size() == 2 * t - 1) {
            splitChild(i + 1, children[i + 1]);
            if ((keys[i + 1].artist_name < k.artist_name) || (keys[i + 1].track_name < k.track_name)) {
                i++;
            }
        }
        children[i + 1]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->t, y->isLeaf);
    z->keys.assign(y->keys.begin() + t, y->keys.end());
    y->keys.resize(t - 1);

    if (!y->isLeaf) {
        z->children.assign(y->children.begin() + t, y->children.end());
        y->children.resize(t);
    }

    children.insert(children.begin() + i + 1, z);
    keys.insert(keys.begin() + i, y->keys[t - 1]);
}