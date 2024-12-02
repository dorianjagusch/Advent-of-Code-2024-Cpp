#include "LocationChecker.hpp"

LocationChecker::LocationChecker(std::ifstream &instream) : p_instream(std::move(instream))
{
    if (!p_instream.is_open())
    {
        std::cerr << "Unable to open file";
        exit(1);
    }
}

LocationChecker::~LocationChecker()
{
    if (p_instream.is_open())
    {
        p_instream.close();
    }
}

void LocationChecker::checkInstream()
{
    if (!p_instream.is_open() || !p_instream.good() || p_instream.peek() < 0)
    {
        std::cerr << "Unable to open file";
        exit(1);
    }
}

std::vector<std::string> LocationChecker::split(const std::string &s, char delim)
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

void LocationChecker::parseFile()
{
    std::string line;
    do
    {
        getline(p_instream, line);
        p_locationIDs1.push_back(std::stoi(line));
        size_t pos = line.find_first_of(' ');
        if (pos == std::string::npos)
        {
            std::cerr << "Invalid input file";
            exit(1);
        }
        p_locationIDs2.push_back(std::stoi(line.substr(pos)));
    } while (!p_instream.eof());
    p_instream.close();
}

void LocationChecker::sortLocationIDs()
{
    std::sort(p_locationIDs1.begin(), p_locationIDs1.end());
    std::sort(p_locationIDs2.begin(), p_locationIDs2.end());
}

size_t LocationChecker::calculateDifferences()
{
    size_t sum = 0;
    for (size_t i = 0; i < p_locationIDs1.size(); i++)
    {
        sum += std::abs(p_locationIDs1[i] - p_locationIDs2[i]);
    }
    return sum;
}

std::map<int, int> LocationChecker::vectorToMap(const std::vector<int> &vec)
{
    std::map<int, int> occurrences;
    for (const int &num : vec)
    {
        occurrences[num]++;
    }
    return occurrences;
}

size_t LocationChecker::calculateSimilarity()
{
    size_t score = 0;
    std::map<int, int> occurrences = vectorToMap(p_locationIDs2);
    for (const int locationID : p_locationIDs1)
    {
        score += locationID * occurrences[locationID];
    }

    return score;
}