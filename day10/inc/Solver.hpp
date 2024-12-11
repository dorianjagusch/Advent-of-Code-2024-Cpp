#pragma once
#include "Types.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <array>
#include <unordered_set>

class Solver
{

public:
    Solver(Map &);

    std::pair<size_t, size_t> solve();

private:
    using Cell = std::pair<size_t, size_t>;
    using TrailHead = std::map<size_t, std::unordered_set<size_t>>;

    Map p_map;
    TrailHead p_trailHeads;

    using Direction = std::vector<std::pair<int, int>>;

    Direction p_directions = {
        {-1, 0},
        {0, 1},
        {1, 0},
        {0, -1}};

    size_t getIndex(Cell const cell) const;
    size_t getRow(size_t const index) const;
    size_t getCol(size_t const index) const;
    Cell checkAhead(size_t const current, std::pair<int, int> direction);
    size_t checkNeighbours(size_t index, size_t head);
    bool isOutOfBounds(std::pair<size_t, size_t>) const;
    size_t calculatePaths();
    void print();
    size_t sumHeads();
};
