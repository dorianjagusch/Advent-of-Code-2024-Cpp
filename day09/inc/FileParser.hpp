#pragma once
#include "Types.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

class FileParser
{
private:
    static bool isGoodInstream(std::ifstream &stream);

public:
    static Input readInput(std::string const &inputFile);
    static Data parseInput(Input const &input);
};