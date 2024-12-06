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

    std::unordered_set<size_t> calculatePath(size_t, CardinalDir);
    CardinalDir changeDir(CardinalDir);
    size_t moveGuard(size_t const, CardinalDir);
    std::pair<size_t, size_t> checkAhead(size_t const, CardinalDir);
    size_t getIndex(size_t const, size_t const) const;
    size_t getCurrentCol(size_t const) const;
    size_t getCurrentRow(size_t const) const;
    bool isOutOfBounds(size_t const) const;
    bool isOutOfBounds(std::pair<size_t, size_t>) const;
    size_t countInfiniteLoops(size_t, std::unordered_set<size_t>);
    bool isPathInfinite(size_t , CardinalDir directon);
};

void operator<<(std::ostream &os, std::vector<std::string> const &map);