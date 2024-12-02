#pragma once

#include "array"
#include "vector"
#include "iostream"
#include "algorithm"
#include "string"
#include <cmath>
#include "stdexcept"

class RecordAnalyser
{
public:
    RecordAnalyser(std::array<std::vector<int>, 1000> &records);
    size_t countSafeRecords(size_t tolerance);
    size_t getRecords()
    {
        return m_number_safe_records;
    };

private:
    std::array<std::vector<int>, 1000> p_records;
    size_t m_number_safe_records = 0;
    size_t latest_tolerance;
    RecordAnalyser() = default;
    bool checkOptions(std::vector<int> record, size_t const tolerance, size_t const index);
    bool testRecordForAlternative(std::vector<int> const &record, size_t const tolerance, size_t const index);
    bool isRecordSafe(std::vector<int> const &record, size_t const tolerance);
};
