#include "FileParser.hpp"

int main(int argc, char *argv[]){
    if (argc != 2)
    {
        std::cout << "Please provide one argument." << std::endl;
        return 1;
    }

    std::regex pattern("mul\\((\\d{1,3}),(\\d{1,3}\\))");
    std::string input = FileParser::parseInput(argv[1]);
    long product = FileParser::multiply(input, pattern);
    std::cout << "The sum of the uncorrupted products is " << product << "." << std::endl;

    std::regex pattern2("(do\\(\\)|don't\\(\\)|mul\\((\\d{1,3}),(\\d{1,3})\\))");
    product = FileParser::cond_multiply(input, pattern2);
    std::cout << "The sum of the conditional products is " << product << "." << std::endl;
    return 0;
}
