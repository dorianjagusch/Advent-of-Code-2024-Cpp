#include "Grid.hpp"

Grid::Grid(std::vector<std::string> &input)
{
    if (!input.size())
    {
        throw std::invalid_argument("Input cannot be empty.");
    }
    for (auto line : input)
    {
        m_data.append(line);
    }
    n_rows = input.size();
    n_cols = input[0].size();
}

size_t Grid::get_index(size_t current, Direction direction)
{

    size_t row = current / n_cols;
    size_t col = current % n_cols;

    int new_row = static_cast<int>(row) + direction_offsets.at(direction).first;
    int new_col = static_cast<int>(col) + direction_offsets.at(direction).second;

    if (new_row < 0 || new_row >= static_cast<int>(n_rows) || new_col < 0 || new_col >= static_cast<int>(n_cols))
    {
        return INVALID_INDEX;
    }
    return static_cast<size_t>(new_col + new_row * n_cols);
}

// bool Grid::check_neighbours(std::string word, size_t current){
//     for (size_t offset_row = -1; offset_row <= 1; offset_row++)
//     {
//         for (size_t offset_col = -1; offset_col <= 1; offset_col++)
//         {
//             if (offset_row == 0 && offset_col == 0)
//             {
//                 continue;
//             }
//             size_t index = get_index(current + offset_row, current + offset_col);
//         }
//     }
// }

size_t Grid::check_neighbours(std::string word, size_t current, Direction direction)
{
    if (word.empty())
    {
        return 1;
    }
    size_t index_to_check = get_index(current, direction);
    if (index_to_check == INVALID_INDEX)
    {
        return 0;
    }
    if (m_data[index_to_check] != word[0])
    {
        return 0;
    }
    return check_neighbours(word.substr(1), index_to_check, direction);
}

size_t Grid::count_words(std::string word)
{

    if (word.empty())
    {
        return 1;
    }
    char first_letter = word[0];

    size_t occurence = m_data.find(first_letter);
    size_t count = 0;

    while (occurence != std::string::npos)
    {
        for (const auto &[direction, offsets] : direction_offsets)
        {
            count += check_neighbours(word.substr(1), occurence, direction);
        }
        occurence = m_data.find(first_letter, occurence + 1);
    }
    return count;
}

size_t Grid::find_x_pattern(std::string word, size_t occurence){

    size_t top_left = get_index(occurence, Direction::top_left);
    size_t top_right = get_index(occurence, Direction::top_right);
    size_t bottom_left = get_index(occurence, Direction::bottom_left);
    size_t bottom_right = get_index(occurence, Direction::bottom_right);

    if (top_left == INVALID_INDEX || top_right == INVALID_INDEX ||
        bottom_left == INVALID_INDEX || bottom_right == INVALID_INDEX )
        {
            return 0;
        }

    if ((m_data[top_left] == word[0] || m_data[top_left] == word[2]) &&
        (m_data[bottom_right] == word[0] || m_data[bottom_right] == word[2]) &&
        (m_data[bottom_left] == word[0] || m_data[bottom_left] == word[2]) &&
        (m_data[top_right] == word[0] || m_data[top_right] == word[2]) &&
        m_data[top_left] != m_data[bottom_right] && m_data[top_right] != m_data[bottom_left]
        ){
        return 1;
    }
    return 0;
}

size_t Grid::find_x_word(std::string word){
    char middle_letter = word[1];
    size_t occurence = m_data.find(middle_letter);
    size_t count = 0;

    while (occurence != std::string::npos)
    {
        count += find_x_pattern(word, occurence);
        occurence = m_data.find(middle_letter, occurence + 1);
    }
    return count;
}