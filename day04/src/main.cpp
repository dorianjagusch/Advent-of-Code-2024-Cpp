#include "FileParser.hpp"
#include "Grid.hpp"
#include <iostream>
#include <vector>
#include <string>

int main(int ac, char *av[]){

    if (ac != 2){
        std::cout << "Execute with: ./a.out <filename>" << std::endl;
    }

    std::vector<std::string> input = FileParser::parse_input(av[1]);

    Grid grid = Grid(input);
    std::cout << "There are " << grid.count_words("XMAS") << " counts of \"XMAS\" in the input"<< std::endl;

    std::cout << "There are " << grid.find_x_word("MAS") << " counts of \"X-MAS\" in the input"<< std::endl;

    return 0;


}