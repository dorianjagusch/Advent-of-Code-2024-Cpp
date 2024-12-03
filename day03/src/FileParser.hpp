#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <regex>

class FileParser
{
private:
    static bool isGoodInstream(std::ifstream &stream);

public:
    static std::string parseInput(std::string const &inputFile);

    static long multiply(std::string const &input, std::regex const pattern);
    static long cond_multiply(std::string const &input, std::regex const pattern);
};