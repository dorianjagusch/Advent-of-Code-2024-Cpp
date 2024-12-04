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
    static bool is_good_instream(std::ifstream &stream);

public:
    static std::vector<std::string> parse_input(std::string const &inputFile);
};