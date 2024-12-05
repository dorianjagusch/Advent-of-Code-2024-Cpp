#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <regex>

struct inputData {
    std::vector<std::pair<int, int>> ordering;
    std::vector<std::vector<int>> updates;
};

class FileParser
{
private:
    static bool is_good_instream(std::ifstream &stream);

public:
    static inputData parse_input(std::string const &inputFile);
    static std::vector<std::string> split(const std::string &s, char delim);

};