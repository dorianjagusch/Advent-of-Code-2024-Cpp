#include "FileParser.hpp"
#include <vector>

bool FileParser::is_good_instream(std::ifstream &stream)
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

inputData FileParser::parse_input(std::string const &inputFile)
{

    std::ifstream instream;
    instream.open(inputFile, std::ios::in);

    if (!is_good_instream(instream))
    {
        throw std::runtime_error("Could not open file.");
        exit(1);
    }

    std::string line;
    std::vector<std::string> rule;
    inputData data;

    while (getline(instream, line))
    {
        rule = split(line, '|');
        if (rule.size() != 2)
        {
            break;
        }
        data.ordering.push_back(std::pair(std::stoi(rule[0]), std::stoi(rule[1])));
    };

    std::vector<int> numerical_updates;
    while (getline(instream, line))
    {
        rule = split(line, ',');
        if (rule.size() == 0)
        {
            break;
        }
        numerical_updates.clear();
        for (auto &entry : rule)
        {
            numerical_updates.push_back(std::stoi(entry));
        }
        data.updates.push_back(numerical_updates);
    }

    return data;
}
