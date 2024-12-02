#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <array>
#include <vector>
#include <string>
#include <algorithm>

class FileParser
{
private:
    static std::vector<int> split(std::string const line, char delim);
    static bool isGoodInstream(std::ifstream &stream);

public:
    static std::array<std::vector<int>, 1000> parseInput(std::string const &inputFile);
};