#include <iostream>
#include <fstream>
#include "LocationChecker.hpp"

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input file>" << std::endl;
        return 1;
    }

    std::ifstream inputFile;
    inputFile.open(argv[1], std::ios::in);

    LocationChecker LocationChecker(inputFile);
    LocationChecker.checkInstream();
    LocationChecker.parseFile();
    LocationChecker.sortLocationIDs();
    std::cout << "The sum of differences is: " << LocationChecker.calculateDifferences() << std::endl;
    std::cout << "The similarity score is: " << LocationChecker.calculateSimilarity() << std::endl;
}