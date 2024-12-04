#include "FileParser.hpp"
#include <vector>

bool FileParser::is_good_instream(std::ifstream &stream)
{
    return stream.is_open() && stream.good() && stream.peek() >= 0;
}

std::vector<std::string> FileParser::parse_input(std::string const &inputFile)
{

    std::ifstream instream;
    instream.open(inputFile, std::ios::in);

    if (!is_good_instream(instream))
    {
        throw std::runtime_error("Could not open file.");
        exit(1);
    }

    std::string line;
    std::vector<std::string> input;
    while (getline(instream, line))
    {
        input.push_back(line);
    };

    return input;
}

