#include "../inc/FileParser.hpp"
#include "../inc/Solver.hpp"
#include <iostream>
#include <vector>
#include <string>

int main(int ac, char *av[])
{

    if (ac != 2)
    {
        std::cout << "Execute with: ./a.out <filename>" << std::endl;
        return 1;
    }

    std::vector<std::string> rawInput = FileParser::readInput(av[1]);
    Input parsedInput = FileParser::parseInput(rawInput);
    Solver solver(parsedInput);
    std::pair<size_t, size_t> result = solver.solve();
    std::cout << "The calibration value (with +, *) is " << result.first << "." << std::endl;
    std::cout << "The corrected calibration value (with +, *, ||) is " << result.second << "." << std::endl;
    return 0;
}