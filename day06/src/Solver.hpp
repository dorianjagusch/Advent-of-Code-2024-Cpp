#pragma once
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <map>
#include <string>

struct Map
{
    std::vector<std::string> map;
    std::unordered_set<size_t> obstacles;
    size_t nRows;
    size_t nCols;
    size_t guardPosition;
};

class Solver
{

public:
    Solver(std::vector<std::string>);

    std::pair<size_t, size_t> solve();

private:
    Map map;

    enum class CardinalDir
    {
        North,
        East,
        South,
        West
    };

    using Direction = std::map<CardinalDir, std::pair<int, int>>;

    Direction directions = {
        {CardinalDir::North, {-1, 0}},
        {CardinalDir::East, {0, 1}},
        {CardinalDir::South, {1, 0}},
        {CardinalDir::West, {0, -1}}};

    using PathCells = std::unordered_map<Solver::CardinalDir, std::unordered_set<size_t>>;

    PathCells calculatePath(size_t, CardinalDir);
    CardinalDir changeDir(CardinalDir);
    std::pair<size_t, size_t> checkAhead(size_t const, CardinalDir);
    size_t getIndex(size_t const, size_t const) const;
    std::unordered_set<size_t> collapsePath(PathCells);
    bool isOutOfBounds(std::pair<size_t, size_t>) const;
    size_t countInfiniteLoops(size_t, std::unordered_set<size_t>);
};
