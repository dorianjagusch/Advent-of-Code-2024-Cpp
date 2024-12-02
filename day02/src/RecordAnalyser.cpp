#include "RecordAnalyser.hpp"

RecordAnalyser::RecordAnalyser(std::array<std::vector<int>, 1000> &records) : p_records({records})
{
}

bool RecordAnalyser::checkOptions(std::vector<int> record, size_t const tolerance, size_t const index)
{
    record.erase(record.begin() + index);
    return isRecordSafe(record, tolerance);
}

bool RecordAnalyser::testRecordForAlternative(std::vector<int> const &record, size_t const tolerance, size_t const index)
{
    return checkOptions(record, tolerance, index) ||
           (index > 0 && checkOptions(record, tolerance, index - 1)) ||
           (index < record.size() - 1 && checkOptions(record, tolerance, index + 1));
}

bool RecordAnalyser::isRecordSafe(std::vector<int> const &record, size_t const tolerance)
{
    if (record.size() == 0)
    {
        throw std::invalid_argument("record must not be empty");
    }
    if (record.size() == 1)
    {
        return true;
    };

    int distance;
    int sign = std::signbit(record[2] - record[1]);

    for (size_t i = 1; i < record.size(); i++)
    {
        distance = (1 - 2 * sign) * (record[i] - record[i - 1]);
        if (!(1 <= distance && distance <= 3))
        {
            if (tolerance > 0 && testRecordForAlternative(record, tolerance - 1, i))
            {
                return true;
            }

            return false;
        };
    }
    return true;
}

size_t RecordAnalyser::countSafeRecords(size_t tolerance)
{
    if (latest_tolerance == tolerance)
    {
        return m_number_safe_records;
    }
    m_number_safe_records = 0;
    for (auto &record : p_records)
    {
        if (isRecordSafe(record, tolerance))
        {
            m_number_safe_records++;
        };
    };
    return m_number_safe_records;
}
