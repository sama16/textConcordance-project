#include "avl_tree.h"
#include <cctype>
#include <algorithm>
#include <fstream>
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


string AVLTree::cleanWord(const string& word) {
    string cleanedWord = word;
    // Remove punctuation
    while (!cleanedWord.empty() && ispunct(cleanedWord.back())) {
        cleanedWord.pop_back();
    }
    return cleanedWord;
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
void AVLTree::findWordsExceedingThreshold(Node* node, int threshold, int argc, char* argv[]) {
    if (!node) return;

    // Check the frequency of the current word
    if (node->frequency >= threshold) {
        // Call the search function to get synonyms of this word
        Dictionarry dictionary;
        dictionary.my_library();
        dictionary.search(node->word);  // Retrieve and display synonyms
        change_the_text(argc, argv, node->word); // Replace word in the text file
    }

    // Recursively check the left and right subtrees
    findWordsExceedingThreshold(node->left, threshold, argc, argv);
    findWordsExceedingThreshold(node->right, threshold, argc, argv);
}


// Wrapper function for convenience
void AVLTree::findWordsExceedingThreshold(int threshold, int argc, char* argv[]) {
    findWordsExceedingThreshold(root, threshold, argc, argv);
}



void AVLTree::change_the_text(int argc, char* argv[], const string& word) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file.txt>" << endl;
        exit(1);
    }

    // Open input file
    ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        cerr << "Error opening file: " << argv[1] << endl;
        exit(1);
    }

    // Load entire content into a string
    stringstream buffer;
    buffer << inputFile.rdbuf();
    string content = buffer.str();
    inputFile.close();

    // Load synonyms
    Dictionarry dictionary;
    dictionary.my_library();
    string* synonyms = dictionary.getSynonyms(word);
    int synonymCount = dictionary.wordyCount;

    if (synonymCount > 0) {
        cout << "Found " << synonymCount << " synonyms for '" << word << "': ";
        for (int i = 0; i < synonymCount; ++i) {
            cout << synonyms[i] << " ";
        }
        cout << endl;
    } else {
        cout << "No synonyms found for '" << word << "'." << endl;
    }

    // Prepare to process words
    stringstream wordStream(content);
    ofstream outFile(argv[1]);
    if (!outFile.is_open()) {
        cerr << "Error creating output file." << endl;
        exit(1);
    }

    srand(time(nullptr)); // Seed for randomness
    string token;
    int occurrence = 0;

    while (wordStream >> token) {
        string original = token;
        string trailingPunct = "";

        // Remove trailing punctuation
        while (!original.empty() && ispunct(original.back())) {
            trailingPunct = original.back() + trailingPunct;
            original.pop_back();
        }

        string modifiedWord = original;

        if (original == word) {
            occurrence++;
            if (occurrence > 1 && synonymCount > 0) {
                modifiedWord = synonyms[rand() % synonymCount];
            }
        }

        // Write modified word and reattach punctuation
        outFile << modifiedWord + trailingPunct << " ";
    }

    outFile.close();
    cout << "Text modified and saved to text" << endl;
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
    std::ifstream infile("synonyms");
    std::string line;

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::vector<std::string> words;
        std::string word;

        // Extract each word from the line
        while (iss >> word) {
            words.push_back(word);
        }

        // Fill an array of fixed size with synonyms (pad with empty strings if less than 10)
        std::string wordArray[10] = {""};
        for (size_t i = 0; i < words.size() && i < 10; ++i) {
            wordArray[i] = words[i];
        }

        insert(wordArray); // Pass the array to your existing insert function
    }
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
                    wordy[wordyCount++] = node->arr[j];  // store synonym
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
string* Dictionarry::getSynonyms(const string& word) {
    static string wordy[100];
    wordyCount = 0;
    getSynonyms(root, word, wordy, wordyCount);
    return wordy;
}

string* Dictionarry::getSynonyms(Node* node, const string& word, string wordy[], int& wordyCount) {
    if (!node) return nullptr;

    // Step 1: Check if the word exists in this node
    for (int i = 0; i < node->count; ++i) {
        if (node->arr[i] == word) {
            // Word found in this node
            std::cout << "The word '" << word << "' is repeated many times. Use one of these synonyms to make the text better:" << std::endl;
            std::cout << "Synonyms for \"" << word << "\": ";
            for (int j = 0; j < node->count; ++j) {
                if (node->arr[j] != word) {
                    wordy[wordyCount++] = node->arr[j];  // store synonym
                    std::cout << node->arr[j];
                    if (j < node->count - 1) std::cout << ", ";
                }
            }
            std::cout << std::endl;
            return wordy;
        }
    }

    // Step 2: Recursively search left and right
    string* result = getSynonyms(node->left, word, wordy, wordyCount);
    if (result != nullptr) return result;

    return getSynonyms(node->right, word, wordy, wordyCount);
}







