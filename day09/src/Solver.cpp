#include "../inc/Solver.hpp"

Solver::Solver(Data &data)
{
    Data result;
    uint64_t j = 0;
    for (uint64_t i = 1; i <= data.size(); i += 1)
    {
        for (j = data[i - 1] - 1; j < data[i - 1]; j--)
        {
            result.push_back(i % 2 ? i / 2 : FREE_SPACE);
        }
    }
    p_data = std::make_shared<Data>(result);
}

void Solver::print(Data &data) const
{
    for (auto value : data)
    {
        std::string c = (value == FREE_SPACE) ? "." : std::to_string(value);
    }
}

template <typename T>
void debugRange(std::string const &label, const T &range)
{

    std::cout << label << "<";
    for (auto &item : range)
    {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

std::unique_ptr<Data> Solver::compressData() const
{
    std::unique_ptr<Data> data = std::make_unique<Data>(*p_data);

    auto j = data->rbegin();
    auto i = data->begin();
    while (i < j.base())
    {
        while (*i != FREE_SPACE)
        {
            i++;
        }
        while (*j == FREE_SPACE)
        {
            j++;
        }
        if (i < j.base())
        {
            std::iter_swap(i++, j++);
        }
    }
    return data;
}

std::unique_ptr<Data> Solver::compressBlockData() const
{
    std::unique_ptr<Data> data = std::make_unique<Data>(*p_data);

    auto fileBlocks = *data | std::views::reverse | std::views::filter([](uint64_t a)
                                                                       { return a != FREE_SPACE; }) |
                      std::views::chunk_by([](uint64_t a, uint64_t b)
                                           { return a == b; });

    for (auto fileBlock : fileBlocks)
    {
        debugRange("File: ", fileBlock);
        auto spaceBlocks = *data | std::views::chunk_by([](uint64_t a, uint64_t b)
                                                        { return a == FREE_SPACE && a == b; }) |
                           std::views::filter([](auto chunk)
                                              { return *chunk.begin() == FREE_SPACE; });

        for (auto spaceBlock : spaceBlocks)
        {
            debugRange("Space: ", spaceBlock);
            auto fileIterator = std::ranges::begin(fileBlock).base().base();
            auto spaceIterator = std::ranges::begin(spaceBlock);

            auto fileIndex = std::distance(data->begin(), fileIterator);
            auto spaceIndex = std::distance((*data).begin(), spaceIterator);
            if (spaceIndex >= fileIndex)
            {
                break;
            }
            std::vector<uint64_t> fileBlockCopy(fileBlock.begin(), fileBlock.end());
            auto fileStart = std::ranges::find(*data, fileBlockCopy.front());
            if (RANGE::distance(fileBlock) <= RANGE::distance(spaceBlock))
            {
                uint64_t writePos = 0;
                for (auto file : fileBlockCopy)
                {
                    spaceBlock[writePos++] = file;
                }
                std::fill(fileStart, fileStart + fileBlockCopy.size(), FREE_SPACE);
                break;
            }
        }
    }
    return data;
}

uint64_t Solver::calculateCheckSum(Data const &data)
{
    uint64_t checkSum = 0;
    uint64_t previous = 0;

    for (uint64_t i = 0; i < data.size(); ++i)
    {
        if (data[i] != FREE_SPACE)
        {
            if (previous > checkSum)
            {
                throw std::runtime_error("OVERFLOW");
            }
            previous = checkSum;
            checkSum += (i * data[i]);
        }
    }
    return checkSum;
}

std::pair<uint64_t, uint64_t> Solver::solve()
{
    std::pair<uint64_t, uint64_t> result;
    auto compressedData = compressData();
    auto compressedBlockData = compressBlockData();
    result.first = calculateCheckSum(*compressedData);
    result.second = calculateCheckSum(*compressedBlockData);

    return result;
}
