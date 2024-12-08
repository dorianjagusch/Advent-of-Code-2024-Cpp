#include "../inc/Solver.hpp"

void Solver::print()
{
    for (auto &line : p_map.map)
    {
        std::cout << line << std::endl;
    }
    std::cout << std::endl;
}

Solver::Solver(Map &inputMap, std::regex search) : p_map(inputMap), p_antennaSymbols(search)
{

    bool hasCaptureGroups = search.mark_count() > 0;
    if (!hasCaptureGroups)
    {
        throw std::invalid_argument("The regular expression must contain a capture group.");
    }

    for (size_t row = 0; row < p_map.nRows; row++)
    {
        for (std::sregex_iterator it(p_map.map[row].begin(), p_map.map[row].end(), p_antennaSymbols), end; it != end; ++it)
        {
            char antennaChar = (*it).str()[0];
            size_t antennaeCol = it->position();
            p_antennae[antennaChar].push_back(getIndex(row, antennaeCol));
        }
    }
}

size_t Solver::getIndex(size_t const row, size_t const col) const
{
    return row * p_map.nCols + col;
}

std::pair<size_t, size_t> Solver::indexToPair(size_t index) const
{
    return std::pair<size_t, size_t>(getRow(index), getCol(index));
}

size_t Solver::getRow(size_t const index) const
{
    return index / p_map.nCols;
}

size_t Solver::getCol(size_t const index) const
{
    return index % p_map.nCols;
}

bool Solver::isOutOfBounds(std::pair<size_t, size_t> location) const
{
    return location.first >= p_map.nRows || location.second >= p_map.nCols;
}

void Solver::addValid(std::pair<size_t, size_t> candidate, std::unordered_set<size_t> &antinodes)
{
    if (!isOutOfBounds(candidate))
    {
        antinodes.insert(getIndex(candidate.first, candidate.second));
    }
}

std::unordered_set<size_t> Solver::calculateAntinodes(std::vector<size_t> const &positions, std::pair<size_t, size_t> harmonicLimits)
{

    std::unordered_set<size_t> antinodes;
    for (size_t i = 0; i < positions.size() - 1; i++)
    {
        for (size_t j = i + 1; j < positions.size(); j++)
        {
            std::pair<size_t, size_t> antennaA = indexToPair(positions[i]);
            std::pair<size_t, size_t> antennaB = indexToPair(positions[j]);

            size_t rowDiff = antennaB.first - antennaA.first;
            size_t colDiff = antennaB.second - antennaA.second;

            for (size_t distance = harmonicLimits.first; distance < harmonicLimits.second + 1; distance++)
            {
                std::pair<size_t, size_t> candidate(antennaA.first - distance * rowDiff,
                                                    antennaA.second - distance * colDiff);

                std::pair<size_t, size_t> antiCandidate(antennaB.first + distance * rowDiff,
                                                        antennaB.second + distance * colDiff);

                addValid(candidate, antinodes);
                addValid(antiCandidate, antinodes);
            }
        }
    }
    return antinodes;
}

std::pair<size_t, size_t> Solver::solve()
{

    for (auto antennae : p_antennae)
    {
        std::unordered_set<size_t> antinodes = calculateAntinodes(antennae.second, {1, 1});
        p_antinodes.first.insert(antinodes.begin(), antinodes.end());
        std::unordered_set<size_t> antinodes2 = calculateAntinodes(antennae.second, {0, p_map.nRows});
        p_antinodes.second.insert(antinodes2.begin(), antinodes2.end());
    }
    return std::pair<size_t, size_t> {p_antinodes.first.size(), p_antinodes.second.size()};
}
