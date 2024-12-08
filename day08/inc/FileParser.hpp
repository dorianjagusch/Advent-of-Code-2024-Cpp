#pragma once
#include "Types.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

class FileParser
{
private:
    static bool isGoodInstream(std::ifstream &stream);

public:
    static Input readInput(std::string const &inputFile);
    static Map parseInput(Input const &input);
    static std::vector<std::string> split(const std::string &s, char delim);
};