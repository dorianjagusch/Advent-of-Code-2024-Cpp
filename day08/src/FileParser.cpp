#include "../inc/FileParser.hpp"

bool FileParser::isGoodInstream(std::ifstream &stream)
{
    return stream.is_open() && stream.good() && stream.peek() >= 0;
}

std::vector<std::string> FileParser::split(const std::string &s, char delim)
{
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string token;
    while (getline(ss, token, delim))
    {
        result.push_back(token);
    }
    return result;
}

Input FileParser::readInput(std::string const &inputFile)
{

    std::ifstream instream;
    instream.open(inputFile, std::ios::in);

    if (!isGoodInstream(instream))
    {
        throw std::runtime_error("Could not open file.");
        exit(1);
    }

    std::string line;
    std::vector<std::string> input;

    while (getline(instream, line))
    {
        input.push_back(line);
    }

    return input;
}

Map FileParser::parseInput(Input const &input)
{

    Map map;
    map.nRows = input.size();
    map.nCols = input[0].size();
    map.map = input;
    return map;
}