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

    inputData data = FileParser::parse_input(av[1]);
    std::unordered_map<int, std::set<int>> rules = Solver::createDAG(data.ordering);
    std::pair<long, long> count = Solver::solve(rules, data.updates);
    std::cout << "There sum of the middle entries in the correct updates is " << count.first << std::endl;
    std::cout << "There sum of the middle entries in the fixed updates is " << count.second << std::endl;
    return 0;
}