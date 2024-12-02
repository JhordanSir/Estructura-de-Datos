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
    void insert(const string& word);
    void deleteTrie(TrieNode* node);
    vector<string> findWordsWithPrefix(const string& prefix);

private:
    TrieNode* root;
    void findAllWords(TrieNode* node, string currentPrefix, vector<string>& words);
};

#endif
