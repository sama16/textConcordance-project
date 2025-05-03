#include "avl_tree.h"
#include <cctype>
#include <algorithm>

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

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

Node* AVLTree::leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

Node* AVLTree::insert(Node* node, const std::string& word, int lineNumber) {
    if (!node) {
        return new Node(word, lineNumber);
    }

    if (word < node->word) {
        node->left = insert(node->left, word, lineNumber);
    }
    else if (word > node->word) {
        node->right = insert(node->right, word, lineNumber);
    }
    else {
        // Word already exists
        node->frequency++;
        if (lineNumber != node->lastLine) {
            node->lineNumbers.push_back(lineNumber);
            node->lastLine = lineNumber;
        }
        return node;
    }

    // Update height
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    // Rebalance tree
    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && word < node->left->word) {
        return rightRotate(node);
    }

    // Right Right Case
    if (balance < -1 && word > node->right->word) {
        return leftRotate(node);
    }

    // Left Right Case
    if (balance > 1 && word > node->left->word) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
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
        std::cout << node->word << ": " << node->frequency << " (lines: ";
        for (auto it = node->lineNumbers.begin(); it != node->lineNumbers.end(); ++it) {
            if (it != node->lineNumbers.begin()) {
                std::cout << ", ";
            }
            std::cout << *it;
        }
        std::cout << ")\n";
        inOrder(node->right);
    }
}

void AVLTree::display() const {
    inOrder(root);
}

std::string AVLTree::cleanWord(const std::string& word) {
    std::string cleaned;
    for (char ch : word) {
        if (std::isalpha(ch)) {
            cleaned += std::tolower(ch);
        }
    }
    return cleaned;
}
Dictionarry::Node::Node(const string word[]) {
    count = 0;
    for (int i = 0; i < maxValue && !word[i].empty(); ++i) {
        arr[i] = word[i];
        count++;
    }
    left = nullptr;
    right = nullptr;
}
// Traverse the AVL tree and call the search function for words that appear more than 2 times
void AVLTree::findWordsExceedingThreshold(Node* node, int threshold) {
    if (!node) return;

    // Check the frequency of the current word
    if (node->frequency >= threshold) {
        // Call the search function to get synonyms of this word
        Dictionarry dictionary;
        dictionary.my_library();// Assuming Dictionarry is available in your code
        dictionary.search(node->word);  // Retrieve and display synonyms
    }

    // Recursively check the left and right subtrees
    findWordsExceedingThreshold(node->left, threshold);
    findWordsExceedingThreshold(node->right, threshold);
}

// Wrapper function for convenience
void AVLTree::findWordsExceedingThreshold(int threshold) {
    findWordsExceedingThreshold(root, threshold);
}

// Constructor for Dictionarry
Dictionarry::Dictionarry() {
    root = nullptr;
}

// Destructor
Dictionarry::~Dictionarry() {
    clear(root);
}

// Helper to deallocate tree
void Dictionarry::clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

// Insert wrapper
void Dictionarry::insert(const string word[]) {
    if (!root) {
        root = new Node(word);
        return;
    }

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        if (!current->left) {
            current->left = new Node(word);
            return;
        } else {
            q.push(current->left);
        }

        if (!current->right) {
            current->right = new Node(word);
            return;
        } else {
            q.push(current->right);
        }
    }
}

// Load predefined synonyms
void Dictionarry::my_library() {
    string word1[] = {"happy", "joyful", "content", "cheerful", "pleased", "elated", "blissful", "", "", ""};
string word2[] = {"sad", "unhappy", "sorrowful", "melancholy", "downcast", "dismal", "blue", "", "", ""};
string word3[] = {"fast", "quick", "rapid", "speedy", "swift", "hasty", "brisk", "", "", ""};
string word4[] = {"strong", "powerful", "robust", "sturdy", "resilient", "tough", "vigorous", "", "", ""};
string word5[] = {"smart", "intelligent", "clever", "bright", "brilliant", "sharp", "wise", "", "", ""};
string word6[] = {"beautiful", "attractive", "pretty", "lovely", "gorgeous", "stunning", "handsome", "", "", ""};
string word7[] = {"big", "large", "huge", "massive", "gigantic", "immense", "enormous", "", "", ""};
string word8[] = {"small", "tiny", "miniature", "petite", "diminutive", "compact", "little", "", "", ""};
string word9[] = {"funny", "amusing", "humorous", "entertaining", "hilarious", "witty", "comical", "", "", ""};
string word10[] = {"quick", "fast", "swift", "rapid", "speedy", "hasty", "brisk", "", "", ""};
string word11[] = {"quiet", "silent", "calm", "peaceful", "still", "hushed", "mute"};




    insert(word1);
    insert(word2);
    insert(word3);
    insert(word4);
    insert(word5);
    insert(word6);
    insert(word7);
    insert(word8);
    insert(word9);
    insert(word10);
    insert(word11);


}

// Display helper
void Dictionarry::display(Node* node) {
    if (!node) return;

    for (int i = 0; i < node->count; ++i) {
        cout << node->arr[i];
        if (i < node->count - 1)
            cout << ", ";
    }
    cout << endl;

    display(node->left);
    display(node->right);
}

// Display wrapper
void Dictionarry::display2() {
    display(root);
}
// Search helper (recursive) - Returns a vector of strings excluding the searched word
bool Dictionarry::search(Node* node, const string& word, string wordy[], int& wordyCount) {
    if (!node) return false;

    // Step 1: Check if the word exists in this node
    for (int i = 0; i < node->count; ++i) {
        if (node->arr[i] == word) {
            // Word found in this node
            std::cout << " the word "<< word <<" is repeated many times, use one of these synonyms to make the text better"<<endl;
            std::cout << "Synonyms for \"" << word << "\": ";
            for (int j = 0; j < node->count; ++j) {
                if (node->arr[j] != word) {
                    std::cout << node->arr[j];
                    if (j < node->count - 1) std::cout << ", ";
                }
            }
            std::cout << std::endl;
            return true;
        }
    }

    // Step 2: Recursively search left and right
    return search(node->left, word, wordy, wordyCount) || search(node->right, word, wordy, wordyCount);
}


// Search wrapper - Returns an array of synonyms excluding the searched word
bool Dictionarry::search(const string& word) {
    string* wordy = new string[100];  // Dynamically allocate the array
    int wordyCount = 0; // This keeps track of the number of synonyms found
    bool result = search(root, word, wordy, wordyCount);

    // Optional: Delete the dynamically allocated array to prevent memory leak
    delete[] wordy;

    return result;
}
