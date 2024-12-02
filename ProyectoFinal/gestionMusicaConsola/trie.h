#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isleaf; 

    TrieNode() : isleaf(false) {}
};

class Trie {
public:
    Trie();
    ~Trie();                    
    bool startsWith(const string& prefix); 

private:
    TrieNode* root;
    void deleteTrie(TrieNode* node);
    bool findWordsWithPrefix(const string& prefix);

};

#endif
