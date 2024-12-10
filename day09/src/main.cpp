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
    Data parsedInput = FileParser::parseInput(rawInput);
    Solver solver(parsedInput);
    std::pair<uint64_t, uint64_t> result = solver.solve();
    std::cout << "The checksum is " << result.second << "." << std::endl;
    // std::cout << "The checksum of the unfragmented data is " << result.second << "." << std::endl;
    return 0;
}