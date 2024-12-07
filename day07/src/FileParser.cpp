#include "../inc/FileParser.hpp"
#include <vector>

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

std::vector<std::string> FileParser::readInput(std::string const &inputFile)
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

Input FileParser::parseInput(std::vector<std::string> const &input)
{
    Input result;
    std::vector<std::string> splitString;
    std::vector<std::string> stringsValues;

    for (auto const &line : input)
    {
        std::deque<uint64_t> values;
        splitString = split(line, ':');
        stringsValues = split(splitString[1], ' ');
        for (auto &curString : stringsValues)
        {
            if (!curString.empty())
            {
                values.push_back(std::stol(curString));
            }
        }
        result.push_back({std::stol(splitString[0]), values});
    }
    return result;
}