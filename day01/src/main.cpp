#include <iostream>
#include <fstream>
#include "FileParser.hpp"

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input file>" << std::endl;
        return 1;
    }

    std::ifstream inputFile;
    inputFile.open(argv[1], std::ios::in);

    FileParser fileParser(inputFile);
    fileParser.checkInstream();
    fileParser.parseFile();
    fileParser.sortLocationIDs();
    std::cout << "The sum of differences is: " << fileParser.calculateDifferences() << std::endl;
    std::cout << "The similarity score is: " << fileParser.calculateSimilarity() << std::endl;
}