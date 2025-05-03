#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <string>
#include <list>
#include <queue>
#include <cstdlib>  // for rand() and srand()
#include <ctime>    // for time()
using namespace std;


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
class AVLTree  {

public:

    AVLTree();
    void insert(const std::string& word, int lineNumber);
    void display() const;

    static std::string cleanWord(const std::string& word);  // Static method for cleaning words
    void findWordsExceedingThreshold(int threshold);



private:
    Node* root;
    Node* insert(Node* node, const std::string& word, int lineNumber);
    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);
    int getHeight(Node* node);
    int getBalance(Node* node);
    void inOrder(Node* node) const;
    void findWordsExceedingThreshold(Node* node, int threshold);
};
class Dictionarry {
private:
    static const int maxValue = 10;

    struct Node {
        std::string arr[maxValue];
        int count;
        Node* left;
        Node* right;

        Node(const std::string word[]);
    };

    Node* root;

    void insert(Node*& root, const std::string word[]);
    void display(Node* node);
private:
    bool search(Node* node, const std::string& word, std::string wordy[], int& wordyCount);

public:
    Dictionarry();
    ~Dictionarry();

    void insert(const std::string word[]);
    void my_library();
    void display2();
    void clear(Node* node); // helper for destructor
    bool search(const std::string& word);

};

#endif
