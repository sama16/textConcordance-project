#include "avl_tree.h"
#include <cctype>
#include <sstream>

AVLTree::AVLTree() : root(nullptr) {}

int AVLTree::getHeight(Node* node) {
    return node ? node->height : 0;
}

int AVLTree::getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

Node* AVLTree::rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

Node* AVLTree::leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

Node* AVLTree::insert(Node* node, const std::string& word, int lineNumber) {
    if (!node)
        return new Node(word, lineNumber);

    if (word < node->word)
        node->left = insert(node->left, word, lineNumber);
    else if (word > node->word)
        node->right = insert(node->right, word, lineNumber);
    else {
        node->frequency++;
        node->lineNumbers.push_back(lineNumber);
        node->lastLine = lineNumber;
        return node;
    }

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    if (balance > 1 && word < node->left->word)
        return rightRotate(node);

    if (balance < -1 && word > node->right->word)
        return leftRotate(node);

    if (balance > 1 && word > node->left->word) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && word < node->right->word) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void AVLTree::insert(const std::string& word, int lineNumber) {
    root = insert(root, word, lineNumber);
}

void AVLTree::inOrder(Node* node) const {
    if (node) {
        inOrder(node->left);
        std::cout << node->word << ": " << node->frequency << " (";
        for (int line : node->lineNumbers) {
            std::cout << line << " ";
        }
        std::cout << ")\n";
        inOrder(node->right);
    }
}

void AVLTree::display() const {
    inOrder(root);
}

// Static method for cleaning the word (making it lowercase and removing non-alphabetic characters)
std::string AVLTree::cleanWord(const std::string& word) {
    std::string cleaned;
    for (char ch : word) {
        if (std::isalpha(ch)) {
            cleaned += std::tolower(ch);
        }
    }
    return cleaned;
}
