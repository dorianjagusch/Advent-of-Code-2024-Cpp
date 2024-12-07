#pragma once
#include "Types.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <deque>

class FileParser
{
private:
    static bool isGoodInstream(std::ifstream &stream);

public:
    static std::vector<std::string> readInput(std::string const &inputFile);
    static Input parseInput(std::vector<std::string> const &input);
    static std::vector<std::string> split(const std::string &s, char delim);
};