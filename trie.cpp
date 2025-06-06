/*
 * trie.cpp
 *
 * Method definitions for the trie class.
 *
 * Author: Peter Gregory
 */

#include "trie.h"
#include <iostream>

trie::trie() {
    root = new node();
}

trie::~trie() {
    delete root;
}

void trie::insert(const std::string &s) {
    node* current = root;
    for(char letter : s) {
        current = current->children[(int)letter - 'a'];
        if(current == nullptr || current->children == nullptr) {
            current = new node();
        }
    }
    current->stop = true;
}

bool trie::contains(const std::string &s) {
    node* current = root;
    for(char letter : s) {
        current = current->children[(int)letter - 'a'];
        if(current->children == nullptr) {
            return false;
        }
    }
    return current->stop;
}

bool trie::is_prefix(const std::string &s) {
    node* current = root;
    for(char letter : s) {
        current = current->children[(int)letter - 'a'];
        if(current->children == nullptr) {
            return false;
        }
    }
    return true;
}

void trie::extend(const std::string &prefix, std::vector<std::string> &result) {
    node* current = root;
    for(char letter : prefix) {
        current = current->children[(int)letter - 'a'];
        if(current == nullptr) return;
    }
    current->extend(prefix, result);
}

trie::node* trie::get_root() {
    return root;
}

trie::node::node() {
    stop = false;
    children = new node*[26];
}

trie::node::~node() {
    delete[] children;
}

void trie::node::extend(const std::string &prefix, std::vector<std::string> &result) {
    if(stop) result.push_back(prefix);
    
    for(int i = 0; i < 26; i++) {
        if(children[i] != nullptr) children[i]->extend(prefix + (char)(i + 'a'), result);
    }
}