#include <iostream>
#include <random>
#include <string>

#include "generator.h"
#include "test.h"

namespace Test {
    void printBoard(Game::Board board) {
        for (auto i = 0; i < 3; ++i) {
            std::cout << board.values[i][0] << " " << board.values[i][1] << " " << board.values[i][2];
            std::cout << " | ";
            std::cout << board.values[i][3] << " " << board.values[i][4] << " " << board.values[i][5];
            std::cout << " | ";
            std::cout << board.values[i][6] << " " << board.values[i][7] << " " << board.values[i][8];
            std::cout << std::endl;
        }
        for (auto i = 0; i < 21; ++i) std::cout << "-";
        std::cout << std::endl;

        for (auto i = 3; i < 6; ++i) {
            std::cout << board.values[i][0] << " " << board.values[i][1] << " " << board.values[i][2];
            std::cout << " | ";
            std::cout << board.values[i][3] << " " << board.values[i][4] << " " << board.values[i][5];
            std::cout << " | ";
            std::cout << board.values[i][6] << " " << board.values[i][7] << " " << board.values[i][8];
            std::cout << std::endl;
        }
        for (auto i = 0; i < 21; ++i) std::cout << "-";
        std::cout << std::endl;

        for (auto i = 6; i < 9; ++i) {
            std::cout << board.values[i][0] << " " << board.values[i][1] << " " << board.values[i][2];
            std::cout << " | ";
            std::cout << board.values[i][3] << " " << board.values[i][4] << " " << board.values[i][5];
            std::cout << " | ";
            std::cout << board.values[i][6] << " " << board.values[i][7] << " " << board.values[i][8];
            std::cout << std::endl;
        }
    }

}


int main(void) {

    // TODO: enable this to randomize every time
    // auto rd = std::random_device {};
    // auto static rng = std::default_random_engine { rd };
    auto static rng = std::default_random_engine {};

    // auto board = Generator::generateFullBoard(rng);

    auto board = Generator::generateValidBoard(rng, 40);

    std::cout << std::endl;

    Test::printBoard(board);

}
