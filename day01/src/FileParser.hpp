#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

class FileParser
{
public:
    FileParser(std::ifstream &instream);
    ~FileParser();
    void checkInstream();
    void parseFile();
    size_t calculateDifferences();
    size_t calculateSimilarity();
    void sortLocationIDs();

private:
    std::ifstream p_instream;
    std::vector<int> p_locationIDs1;
    std::vector<int> p_locationIDs2;

    std::vector<std::string> split(const std::string &s, char delim);
    std::map< int, int > vectorToMap(const std::vector<int> &vec);
};