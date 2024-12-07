#include "../inc/Solver.hpp"

Solver::Solver(Input &input) : p_deque(input)
{
    operations = {
        {Operation::Add, [this](uint64_t a, uint64_t b)
        { return a + b; }},
        {Operation::Multiply, [this](uint64_t a, uint64_t b)
        { return a * b; }},
        {Operation::Concatenate, [this](uint64_t a, uint64_t b)
        { return std::stol(std::to_string(a) + std::to_string(b)); }},
    };
}

uint64_t Solver::calculate(uint64_t goal, std::deque<uint64_t> values, bool allowConcatenation)
{
    if (values.size() == 1)
    {
        return goal == values.front();
    }
    uint64_t lastValue = values.front();
    values.pop_front();
    uint64_t nextValue = values.front();
    values.pop_front();

    uint64_t result;
    for (auto &operation : operations)
    {
        if (!allowConcatenation && operation.first == Operation::Concatenate)
        {
            continue;
        }
        std::deque<uint64_t> valuesCpy = values;

        result = operations[operation.first](lastValue, nextValue);
        if (result > goal)
        {
            continue;
        }
        valuesCpy.push_front(result);
        if (calculate(goal, valuesCpy, allowConcatenation))
        {
            return goal;
        };
    }
    return 0;
}

std::pair<size_t, size_t> Solver::solve()
{
    std::pair<size_t, size_t> result;
    for (auto &equation : p_deque)
    {
        result.first += calculate(equation.first, equation.second, false);
        result.second += calculate(equation.first, equation.second, true);
    }
    return result;
}
