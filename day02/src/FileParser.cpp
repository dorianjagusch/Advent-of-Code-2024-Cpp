#include "FileParser.hpp"

std::vector<int> FileParser::split(std::string const line, char delim)
{
    std::stringstream ss(line);
    std::vector<int> result;
    std::string token;

    while (getline(ss, token, delim))
    {
        result.push_back(std::stoi(token));
    }
    return result;
}

bool FileParser::isGoodInstream(std::ifstream &stream){
    return stream.is_open() && stream.good() && stream.peek() >= 0;
    }


std::array<std::vector<int>, 1000> FileParser::parseInput(std::string const &input){

    std::ifstream instream;
    instream.open(input, std::ios::in);

    if (!isGoodInstream(instream)){
        std::cout << "Could not open " << input << "." << std::endl;
        exit(1);
    }

    std::string line;
    std::array<std::vector<int>, 1000> records;

    for (size_t i = 0; i < records.size(); i++)
    {
        getline(instream, line);
        records[i] = FileParser::split(line, ' ');
    }
    return records;
}