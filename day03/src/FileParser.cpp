#include "FileParser.hpp"

bool FileParser::isGoodInstream(std::ifstream &stream)
{
    return stream.is_open() && stream.good() && stream.peek() >= 0;
}

std::string FileParser::parseInput(std::string const &inputFile)
{

    std::ifstream instream;
    instream.open(inputFile, std::ios::in);

    if (!isGoodInstream(instream))
    {
        throw std::runtime_error("Could not open file.");
        exit(1);
    }

    std::string line;
    std::string input;
    while (getline(instream, line))
    {
        input += line;
    };

    return input;
}

long FileParser::multiply(std::string const &input, std::regex const pattern)
{
    std::sregex_iterator first(input.begin(), input.end(), pattern);
    std::sregex_iterator last;

    long result = 0;

    for (auto it = first; it != last; ++it)
    {
        result += std::stoi((*it)[1].str()) * std::stoi((*it)[2].str());
    }
    return result;
};

long FileParser::cond_multiply(std::string const &input, std::regex const pattern)
{
    std::sregex_iterator first(input.begin(), input.end(), pattern);
    std::sregex_iterator last;

    long result = 0;
    bool isEnabled = true;

    for (auto it = first; it != last; ++it)
    {
        if ((*it)[1].str() == "do()")
        {
            isEnabled = true;
        }
        if ((*it)[1].str() == "don't()"){
            isEnabled = false;
        }
        if (isEnabled && (*it)[1].str().find("mul") != std::string::npos)
        {
            result += std::stoi((*it)[2].str()) * std::stoi((*it)[3].str());
        }
    }
    return result;
};