#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <string>
#include <list>
#include <algorithm>

// AVL Tree Node
struct Node {
    std::string word;
    int frequency;
    std::list<int> lineNumbers;
    int lastLine;
    Node* left;
    Node* right;
    int height;

    Node(const std::string& w, int lineNum)
        : word(w), frequency(1), lastLine(lineNum), left(nullptr), right(nullptr), height(1) {
        lineNumbers.push_back(lineNum);
    }
};

// AVL Tree Class
class AVLTree {
public:
    AVLTree();
    void insert(const std::string& word, int lineNumber);
    void display() const;

    static std::string cleanWord(const std::string& word);  // Static method for cleaning words

private:
    Node* root;
    Node* insert(Node* node, const std::string& word, int lineNumber);
    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);
    int getHeight(Node* node);
    int getBalance(Node* node);
    void inOrder(Node* node) const;
};

#endif
