#include <string>
#include <stdexcept>
#include <vector>
#include <map>
#include <limits>

#define INVALID_INDEX std::numeric_limits<size_t>::max()

class Grid
{
public:
    Grid(std::vector<std::string> &input);
    size_t count_words(std::string word);
    size_t find_x_word(std::string word);

private:
    enum class Direction
    {
        top_left = 0,
        top,
        top_right,
        left,
        right,
        bottom_left,
        bottom,
        bottom_right
    };

    std::string m_data;
    size_t n_rows;
    size_t n_cols;

    std::map<Direction, std::pair<int, int>> direction_offsets = {
        {Direction::top_left, {-1, -1}},
        {Direction::top, {-1, 0}},
        {Direction::top_right, {-1, 1}},
        {Direction::left, {0, -1}},
        {Direction::right, {0, 1}},
        {Direction::bottom_left, {1, -1}},
        {Direction::bottom, {1, 0}},
        {Direction::bottom_right, {1, 1}}};

    size_t get_index(size_t current, Direction direction);
    size_t check_neighbours(std::string, size_t, Direction);
    size_t find_x_pattern(std::string word, size_t occurence);
};