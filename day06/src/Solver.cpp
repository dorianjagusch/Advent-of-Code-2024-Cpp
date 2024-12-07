#include "Solver.hpp"

Solver::Solver(std::vector<std::string> inputMap)
{
    map.nRows = inputMap.size();
    map.nCols = inputMap[0].size();
    map.map = inputMap;

    for (size_t row = 0; row < map.nRows; row++)
    {
        size_t obstacleCol = 0;
        obstacleCol = map.map[row].find("#");
        while (obstacleCol != std::string::npos)
        {
            map.obstacles.insert(getIndex(row, obstacleCol));
            obstacleCol = map.map[row].find("#", obstacleCol + 1);
        }
        size_t guardCol = map.map[row].find("^");
        if (guardCol != std::string::npos)
        {
            map.guardPosition = getIndex(row, guardCol);
        }
    }
    return;
}

size_t Solver::getIndex(size_t const row, size_t const col) const
{
    return row * map.nCols + col;
}

bool Solver::isOutOfBounds(std::pair<size_t, size_t> location) const
{
    return location.first >= map.nRows || location.second >= map.nCols;
}

Solver::CardinalDir Solver::changeDir(CardinalDir current)
{
    CardinalDir direction = static_cast<CardinalDir>((static_cast<int>(current) + 1) % 4);
    return direction;
}

std::pair<size_t, size_t> Solver::checkAhead(size_t const current, CardinalDir direction)
{
    size_t curRow = current / map.nCols;
    size_t curCol = current % map.nCols;

    size_t newRow = curRow + directions[direction].first;
    size_t newCol = curCol + directions[direction].second;

    return std::pair<size_t, size_t>(newRow, newCol);
}

Solver::PathCells Solver::calculatePath(size_t currentPos, CardinalDir direction)
{
    std::unordered_map<CardinalDir, std::unordered_set<size_t>> visited;
    std::pair<size_t, size_t> lookAhead = checkAhead(currentPos, direction);
    while (!isOutOfBounds(lookAhead))
    {
        while (!isOutOfBounds(lookAhead) && map.obstacles.find(getIndex(lookAhead.first, lookAhead.second)) == map.obstacles.end())
        {
            if (visited[direction].find(getIndex(lookAhead.first, lookAhead.second)) != visited[direction].end())
            {
                return {};
            }
            currentPos = getIndex(lookAhead.first, lookAhead.second);
            visited[direction].insert(currentPos);
            lookAhead = checkAhead(currentPos, direction);
        }
        if (!isOutOfBounds(lookAhead))
        {
            direction = changeDir(direction);
            lookAhead = checkAhead(currentPos, direction);
        }
    }
    return visited;
}

std::unordered_set<size_t> Solver::collapsePath(PathCells path)
{
    std::unordered_set<size_t> uniqueCells;
    for (auto &[direction, cells] : path)
    {
        uniqueCells.insert(cells.begin(), cells.end());
    }
    return uniqueCells;
}

size_t Solver::countInfiniteLoops(size_t currentPos, std::unordered_set<size_t> path)
{

    path.erase(currentPos);
    size_t infiniteLoops = 0;

    for (size_t position : path)
    {
        map.obstacles.insert(position);
        infiniteLoops += calculatePath(currentPos, CardinalDir::North).empty();
        map.obstacles.erase(position);
    }
    return infiniteLoops;
}

std::pair<size_t, size_t> Solver::solve()
{
    PathCells path;
    size_t infiniteLoops = 0;

    path = calculatePath(map.guardPosition, CardinalDir::North);
    std::unordered_set<size_t> uniqueCells = collapsePath(path);
    infiniteLoops = countInfiniteLoops(map.guardPosition, uniqueCells);

    return std::pair<size_t, size_t>(uniqueCells.size(), infiniteLoops);
}
