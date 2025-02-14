#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <vector>

#include "generator.h"

// 0 1 2 | 3 4 5 | 6 7 8
// 1 1   |   2   |   3
// 2     |       |
// - - - x - - - x - - -
// 3     |       |
// 4 4   |   5   |   6
// 5     |       |
// - - - x - - - x - - -
// 6     |       |
// 7 7   |   8   |   9
// 8     |       |

// 0 1 2 | 3 4 5 | 6 7 8
// 91011 |121314 |151617
//181920 |212223 |242526
//----------------------
//272829 |303132 |333435
//363738 |394041 |424344
//...

namespace Generator {


    const std::vector<char> LegalValues = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };

    /*
    ** Print board content to standard output
     */
    void printBoard(board& board) {
        for (auto i = 0; i < 3; ++i) {
            std::cout << board[i][0] << " " << board[i][1] << " " << board[i][2];
            std::cout << " | ";
            std::cout << board[i][3] << " " << board[i][4] << " " << board[i][5];
            std::cout << " | ";
            std::cout << board[i][6] << " " << board[i][7] << " " << board[i][8];
            std::cout << std::endl;
        }
        for (auto i = 0; i < 21; ++i) std::cout << "-";
        std::cout << std::endl;

        for (auto i = 3; i < 6; ++i) {
            std::cout << board[i][0] << " " << board[i][1] << " " << board[i][2];
            std::cout << " | ";
            std::cout << board[i][3] << " " << board[i][4] << " " << board[i][5];
            std::cout << " | ";
            std::cout << board[i][6] << " " << board[i][7] << " " << board[i][8];
            std::cout << std::endl;
        }
        for (auto i = 0; i < 21; ++i) std::cout << "-";
        std::cout << std::endl;

        for (auto i = 6; i < 9; ++i) {
            std::cout << board[i][0] << " " << board[i][1] << " " << board[i][2];
            std::cout << " | ";
            std::cout << board[i][3] << " " << board[i][4] << " " << board[i][5];
            std::cout << " | ";
            std::cout << board[i][6] << " " << board[i][7] << " " << board[i][8];
            std::cout << std::endl;
        }
    }

    void fillSquareRandomly(board& board, int squareNumber, std::default_random_engine rng) {
        auto nums = LegalValues;
        std::ranges::shuffle(nums, rng);

        auto num_i = 0;
        auto l = ((squareNumber - 1) % 3) * 3;
        auto u = (squareNumber - 1) / 3 * 3;

        for (auto i = u; i < u + 3; ++i)
            for (auto j = l; j < l + 3; ++j)
                board[i][j] = nums[num_i++];
    }

    board zeroBoard() {
        board board;
        // TODO: a prettier way to do this? (initialization)
        for (int i = 0; i < 9; ++i)
            for (int j = 0; j < 9; ++j)
                board[i][j] = '0'; // alternative: '_'
        return board;
    }

    /*
    ** Generates a full sudoku board
     */
    board generateFullBoard(std::default_random_engine rng) {
        board board = zeroBoard();

        // candidate lists per cell
        std::array<std::array<std::vector<char>,9>,9> candidates;
        for (auto i = 0; i < 9; ++i)
            for (auto j = 0; j < 9; ++j) {
                candidates[i][j] = LegalValues;
                std::ranges::shuffle(candidates[i][j], rng);
            }

        auto pos = 0;
        while (pos < 81) {
            auto r = pos / 9;
            auto c = pos % 9;

            // backtracking 1 cell if no possible candidates
            if (candidates[r][c].empty()) {
                if (pos == 0) {
                    std::cout << "Something is wrong!\n" << std::endl;
                    std::exit(-1);
                } // TODO: better panic system

                candidates[r][c] = LegalValues;
                std::ranges::shuffle(candidates[r][c], rng);

                board[r][c] = '0';
                pos--;
                continue;
            }

            auto cand = candidates[r][c].back();

            // checking rules
            auto invalid = false;
            for (auto i = 0; i < r; ++i)
                if (board[i][c] == cand) {
                    invalid = true;
                    break;
                }
            if (!invalid)
                for (auto j = 0; j < c; ++j)
                    if (board[r][j] == cand) {
                        invalid = true;
                        break;
                    }
            if (!invalid) {
                auto squareNumber = (pos / 3 % 3 + 1) + (pos / 27 * 3);
                auto l = ((squareNumber - 1) % 3) * 3;
                auto u = (squareNumber - 1) / 3 * 3;

                for (auto i = u; i < u + 3; ++i)
                    for (auto j = l; j < l + 3; ++j)
                        if (board[i][j] == cand) {
                            invalid = true;
                            break;
                        }
            }

            candidates[r][c].pop_back();

            if (invalid) continue;

            board[r][c] = cand;

            pos++;
        }

        return board;
    }

}
