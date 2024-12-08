#pragma once
#include "Types.hpp"
#include <algorithm>
#include <iostream>
#include <regex>

class Solver
{

public:
    Solver(Map &, std::regex);

    std::pair<size_t, size_t> solve();

private:
    Map p_map;
    std::pair<std::unordered_set<size_t>, std::unordered_set<size_t>> p_antinodes;
    std::unordered_map<char, std::vector<size_t>> p_antennae;
    std::regex p_antennaSymbols;

    std::unordered_set<size_t> calculateAntinodes(std::vector<size_t> const &positions, std::pair<size_t, size_t>);
    size_t getIndex(size_t const, size_t const) const;
    std::pair<size_t, size_t> indexToPair(size_t const index) const;
    size_t getRow(size_t const index) const;
    size_t getCol(size_t const index) const;
    bool isOutOfBounds(std::pair<size_t, size_t>) const;
    void addValid(std::pair<size_t, size_t> candidate, std::unordered_set<size_t> &antinodes);
    void print();
};
