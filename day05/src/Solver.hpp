#pragma once
#include <vector>
#include <unordered_map>
#include <queue>
#include <set>
#include <algorithm>
#include <unordered_set>
#include <functional>
#include <iostream>

class Solver
{

    using graph = std::unordered_map<int, std::set<int>>;

public:
    static graph createDAG(std::vector<std::pair<int, int>> const &edges);
    static std::pair<long,long> solve(graph const &, std::vector<std::vector<int>> const &);

private:
    static std::vector<int> correctUpdate(graph const &order, std::vector<int> update);
    static bool isValidUpdate(graph const &order, std::vector<int> const &update);
    static std::vector<int> topologicalSort(graph const &graph, std::unordered_map<int, int> &inDegree, const std::unordered_set<int> &nodes);
};