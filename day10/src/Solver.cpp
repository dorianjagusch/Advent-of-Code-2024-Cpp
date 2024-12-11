#include "../inc/Solver.hpp"

void Solver::print()
{
    for (auto &line : p_map.map)
    {
        std::cout << line << std::endl;
    }
    std::cout << std::endl;
}

Solver::Solver(Map &inputMap) : p_map(inputMap)
{
    for (size_t i = 0; i < p_map.nRows; ++i)
    {
        for (size_t j = 0; j < p_map.nCols; ++j)
        {
            if (p_map.map[i][j] == '0')
            {
                p_trailHeads[getIndex(Cell(i, j))];
            }
        }
    }
}

size_t Solver::getIndex(Cell const cell) const
{
    return cell.first * p_map.nCols + cell.second;
}

size_t Solver::getRow(size_t const index) const
{
    return index / p_map.nCols;
}

size_t Solver::getCol(size_t const index) const
{
    return index % p_map.nCols;
}

bool Solver::isOutOfBounds(Cell location) const
{
    return location.first >= p_map.nRows || location.second >= p_map.nCols;
}

Solver::Cell Solver::checkAhead(size_t const current, std::pair<int, int> direction)
{
    size_t curRow = current / p_map.nCols;
    size_t curCol = current % p_map.nCols;

    size_t newRow = curRow + direction.first;
    size_t newCol = curCol + direction.second;

    return Cell(newRow, newCol);
}

size_t Solver::checkNeighbours(size_t index, size_t head)
{
    size_t nPaths = 0;
    for (auto direction : p_directions)
    {
        Cell neighbourCell(checkAhead(index, direction));
        if (!isOutOfBounds(neighbourCell))
        {
            char currentValue = p_map.map[getRow(index)][getCol(index)];
            char neighbourValue = p_map.map[neighbourCell.first][neighbourCell.second];
            if (currentValue == '8' && neighbourValue == '9')
            {
                p_trailHeads[head].insert(getIndex(neighbourCell));
                nPaths++;
            }
            else if (neighbourValue == currentValue + 1)
            {
                nPaths += checkNeighbours(getIndex(neighbourCell), head);
            }
        }
    }
    return nPaths;
}

size_t Solver::calculatePaths()
{
    size_t nPaths = 0;
    for (auto &[head, value] : p_trailHeads)
    {
        nPaths += checkNeighbours(head, head);
    }
    return nPaths;
}

size_t Solver::sumHeads()
{
    size_t nTailsReached = 0;
    for (auto &[head, tails] : p_trailHeads)
    {
        nTailsReached += tails.size();
    }
    return nTailsReached;
}

std::pair<size_t, size_t> Solver::solve()
{
    std::pair<size_t, size_t> result;

    result.second = calculatePaths();
    result.first = sumHeads();
    return result;
}
