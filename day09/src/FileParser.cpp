#include "../inc/FileParser.hpp"

bool FileParser::isGoodInstream(std::ifstream &stream)
{
    return stream.is_open() && stream.good() && stream.peek() >= 0;
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

    getline(instream, line);

    return line;
}

Data FileParser::parseInput(Input const &input)
{
    Data values;
    values.resize(input.size());
    for (uint64_t i = 0; i < input.size(); ++i)
    {
        values[i] = static_cast<uint64_t>(input[i] - '0');
    };
    return values;
}
