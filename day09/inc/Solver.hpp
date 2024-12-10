#pragma once
#include "Types.hpp"
#include <algorithm>
#include <iostream>
#include <limits>
#include <memory>
#include <ranges>

class Solver
{

public:
    Solver(Data &);

    std::pair<uint64_t, uint64_t> solve();

private:
    std::shared_ptr<Data> p_data;

    std::unique_ptr<Data> compressData() const;
    std::unique_ptr<Data> compressBlockData() const;
    uint64_t calculateCheckSum(Data const &);
    void print(Data &) const;
};
