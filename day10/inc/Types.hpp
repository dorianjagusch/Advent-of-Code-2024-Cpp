#pragma once
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <vector>
#include <string>
#include <cstdint>

struct Map
{
    std::vector<std::string> map;
    size_t nRows;
    size_t nCols;
};

using Input = std::vector<std::string>;