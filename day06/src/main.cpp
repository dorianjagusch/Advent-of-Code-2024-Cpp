#include "FileParser.hpp"
#include "Solver.hpp"
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

    std::vector<std::string> map = FileParser::parseInput(av[1]);
    Solver solver(map);
    std::pair<size_t, size_t> result = solver.solve();
    std::cout << "The path length is " << result.first << " units long."<< std::endl;
    std::cout << "There are " << result.second << " places to create infinite loops." << std::endl;
    return 0;
}