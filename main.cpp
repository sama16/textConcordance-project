#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "avl_tree.h"

int main(int argc, char* argv[]) {
    std::cout << "|==========================================================================|" << std::endl;
    std::cout << "|                      T E X T    C O N C O R D A N C E                    |" << std::endl;
    std::cout << "|==========================================================================|" << std::endl;

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file.txt>" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }

    AVLTree concordance;
    std::string line;
    int lineNum = 1;

    while (std::getline(inputFile, line)) {
        std::istringstream stream(line);
        std::string word;

        while (stream >> word) {
            word = AVLTree::cleanWord(word);
            if (!word.empty()) {
                concordance.insert(word, lineNum);
            }
        }
        lineNum++;
    }

    inputFile.close();
    concordance.display();
    return 0;
}
