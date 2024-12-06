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
    static std::vector<std::string> parseInput(std::string const &inputFile);
    static std::vector<std::string> split(const std::string &s, char delim);

};