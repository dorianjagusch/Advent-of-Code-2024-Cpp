#pragma once
#include "Types.hpp"
#include <vector>
#include <algorithm>
#include <iostream>
#include <deque>
#include <string>
#include <unordered_map>
#include <functional>

class Solver
{
private:
    Input p_deque;

    uint64_t add(uint64_t, uint64_t);
    uint64_t multiply(uint64_t, uint64_t);
    uint64_t concatenate(uint64_t, uint64_t);

    enum class Operation
    {
        Add,
        Multiply,
        Concatenate,
    };

    struct OperationHash
    {
        std::size_t operator()(Operation op) const
        {
            return static_cast<std::size_t>(op);
        }
    };

    // Corrected unordered_map with a custom hash function
    std::unordered_map<Operation, std::function<uint64_t(uint64_t, uint64_t)>, OperationHash> operations;
    uint64_t calculate(uint64_t goal, std::deque<uint64_t> values, bool allowConcatenation);
    uint64_t doOperation(uint64_t a, uint64_t b, Operation operation);

public:
    Solver(Input &input);
    std::pair<size_t, size_t> solve();
};
