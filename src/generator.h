#pragma once

#include <array>
#include <random>

namespace Generator {

    typedef std::array<std::array<char,9>,9> board;;

    void printBoard(board& board);

    board generateFullBoard(std::default_random_engine rng);

}
