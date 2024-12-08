#include "../inc/FileParser.hpp"
#include "../inc/Solver.hpp"

int main(int ac, char *av[])
{

    if (ac != 2)
    {
        std::cout << "Execute with: ./a.out <filename>" << std::endl;
        return 1;
    }

    Input rawInput = FileParser::readInput(av[1]);
    Map parsedInput = FileParser::parseInput(rawInput);
    Solver solver(parsedInput, std::regex("([A-Za-z0-9])"));
    std::pair<size_t, size_t> result = solver.solve();
    std::cout << "There are " << result.first << " antinodes." << std::endl;
    std::cout << "There are " << result.second << " harmonic antinodes." << std::endl;
    return 0;
}