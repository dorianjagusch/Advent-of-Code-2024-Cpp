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
    Solver solver(parsedInput);
    std::pair<size_t, size_t> result = solver.solve();
    std::cout << "The sum of trail head scores is " << result.first << "."<< std::endl;
    std::cout << "The sum of trail head ratings is" << result.second << "." << std::endl;
    return 0;
}