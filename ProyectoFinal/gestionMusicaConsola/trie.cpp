#include "Trie.h"

Trie::Trie() {
    root = new TrieNode();  // Crear la raíz del Trie
}

Trie::~Trie() {
    deleteTrie(root);  // Liberar memoria de los nodos del Trie
}

void Trie::deleteTrie(TrieNode* node) {
    for (auto& pair : node->children) {
        deleteTrie(pair.second); 
    }
    delete node;  
}

void Trie::insert(const string& word) {
    TrieNode* node = root;
    for (char c : word) {
        if (node->children.find(c) == node->children.end()) {
            node->children[c] = new TrieNode();
        }
        node = node->children[c];
    }
    node->isleaf = true;
}

vector<string> Trie::findWordsWithPrefix(const string& prefix) {
    TrieNode* node = root;
    vector<string> words;

    for (char c : prefix) {
        if (node->children.find(c) == node->children.end()) {
            return words;  // Prefijo no encontrado
        }
        node = node->children[c];
    }

    findAllWords(node, prefix, words);
    return words;
}

void Trie::findAllWords(TrieNode* node, string currentPrefix, vector<string>& words) {
    if (node->isleaf) {
        words.push_back(currentPrefix);
    }

    for (auto& pair : node->children) {
        findAllWords(pair.second, currentPrefix + pair.first, words);
    }
}

