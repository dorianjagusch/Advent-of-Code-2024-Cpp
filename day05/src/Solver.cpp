#include "Solver.hpp"

Solver::graph Solver::createDAG(std::vector<std::pair<int, int>> const &edges)
{
    Solver::graph graph;

    for (auto edge : edges)
    {
        int dependency = edge.first;
        int focus = edge.second;
        graph[dependency].insert(focus);
        if (graph.find(dependency) == graph.end())
        {
            graph[dependency] = std::set<int>();
        }
    }

    return graph;
}

bool Solver::isValidUpdate(Solver::graph const &order, std::vector<int> const &update)
{
    std::unordered_map<int, int> node_position;
    for (size_t i = 0; i < update.size(); ++i)
    {
        node_position[update[i]] = static_cast<int>(i);
    }

    for (const auto &[node, neighbours] : order)
    {
        for (int neighbour : neighbours)
        {
            if (node_position.find(node) != node_position.end() &&
                node_position.find(neighbour) != node_position.end())
            {
                if (node_position[node] >= node_position[neighbour])
                {
                    return false;
                }
            }
        }
    }

    return true;
}

std::vector<int> Solver::topologicalSort(graph const &graph, std::unordered_map<int, int> &inDegree, const std::unordered_set<int> &nodes)
{
    std::queue<int> zeroIndegreeNodes;
    std::vector<int> correctedUpdate;

    for (const auto &node : nodes)
    {
        if (inDegree.at(node) == 0)
        {
            zeroIndegreeNodes.push(node);
        }
    }

    while (!zeroIndegreeNodes.empty())
    {
        int node = zeroIndegreeNodes.front();
        zeroIndegreeNodes.pop();
        correctedUpdate.push_back(node);
        if(graph.find(node) == graph.end())
        {
            continue;
        }
        for (int neighbour : graph.at(node))
        {  
            if (inDegree.find(neighbour) == inDegree.end()){
                continue;
            }
            int &degree = inDegree.at(neighbour);
            degree--;
            if (degree == 0)
            {
                zeroIndegreeNodes.push(neighbour);
            }
        }
    }
    return correctedUpdate;
}

std::vector<int> Solver::correctUpdate(graph const &order, std::vector<int> update)
{
    std::unordered_set<int> nodes(update.begin(), update.end());

    std::unordered_map<int, int> inDegree;
    for (const auto &[node, neighbours] : order)
    {
        for (int neighbour : neighbours)
        {
            if (std::find(update.begin(), update.end(), node) != update.end() && nodes.find(neighbour) != nodes.end())
            {
                inDegree[neighbour]++;
            }
        }
        if (std::find(update.begin(), update.end(), node) != update.end() && inDegree.find(node) == inDegree.end())
        {
            inDegree[node] = 0;
        }
    }

    return topologicalSort(order, inDegree, nodes);
}

std::pair<long, long> Solver::solve(Solver::graph const &order, std::vector<std::vector<int>> const &updates)
{

    std::pair<long, long> middleSum = {0, 0};
    for (auto const &update : updates)
    {

        if (isValidUpdate(order, update))
        {
            middleSum.first += update[update.size() / 2UL];
        }
        else
        {
            std::vector<int> correctedUpdate = correctUpdate(order, update);
            middleSum.second += correctedUpdate[correctedUpdate.size() / 2UL];
        }
    }
    return middleSum;
}