#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "avl_tree.h"

int main(int argc, char* argv[]) {
    std::cout << "|==========================================================================|" << std::endl;
    std::cout << "|                      T E X T    C O N C O R D A N C E                    |" << std::endl;
    std::cout << "|==========================================================================|" << std::endl;

    // Ensure proper command-line arguments
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file.txt>" << std::endl;
        return 1;
    }

    // Open the input file
    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }

    // Initialize AVL Tree and Dictionary
    AVLTree concordance;
    Dictionarry d1;

    std::string line;
    int lineNum = 1;

    // Read the file line by line
    while (std::getline(inputFile, line)) {
        std::istringstream stream(line);
        std::string word;

        // Process each word
        while (stream >> word) {
            word = concordance.cleanWord(word);  // Clean the word
            if (!word.empty()) {
                concordance.insert(word, lineNum);  // Insert into AVL Tree
            }
        }
        lineNum++;
    }

    inputFile.close();  // Close the input file

    // Display the concordance (AVL Tree) content
    cout << " This is the frequency of each word given in the file" << endl;
    concordance.display();
    cout << endl;
cout << " please enter what is the minimum number of repetitions for a word to start changing it"<<endl;
    int minimum_repetitions;
    cin >> minimum_repetitions;

    // Find and replace words exceeding the threshold with synonyms
    concordance.findWordsExceedingThreshold(minimum_repetitions, argc, argv);

    // Optional: If you need to work with the dictionary, uncomment these lines
    // d1.my_library();
    // d1.display2();

    return 0;
}
