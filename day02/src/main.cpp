#include "FileParser.hpp"
#include "RecordAnalyser.hpp"
#include <iostream>
#include <vector>
#include <stdexcept>

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        std::cout << "File name missing. Run as " << argv[0] << " <input file>" << std::endl;
        return 1;
    }

    std::array<std::vector<int>, 1000> records = FileParser::parseInput(argv[1]);

    RecordAnalyser recordAnalyser(records);
    try
    {
        recordAnalyser.countSafeRecords(0);
        std::cout << "There are " << recordAnalyser.getRecords() << " safe records" << std::endl;
        recordAnalyser.countSafeRecords(1);
        std::cout << "There are " << recordAnalyser.getRecords() << " safe records with dampening level 1" << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
};