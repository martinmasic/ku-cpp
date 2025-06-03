#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <vector>
// #include <ranges> // only from C++20

#include "generator.h"
#include "test.h"
#include "game.h"

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

    void fillBoxRandomly(
        Game::Board& board,
        int boxNumber,
        std::default_random_engine rng)
    {
        auto nums = Game::LegalValues;
        std::shuffle(std::begin(nums), std::end(nums), rng);
        // std::ranges::shuffle(nums, rng);

        auto num_i = 0;
        auto l = ((boxNumber - 1) % 3) * 3;
        auto u = (boxNumber - 1) / 3 * 3;

        for (auto i = u; i < u + 3; ++i)
            for (auto j = l; j < l + 3; ++j)
                board.values[i][j] = nums[num_i++];
    }

    Game::Board zeroBoard() {
        auto board = Game::Board {};
        // TODO: a prettier way to do this? (initialization)
        for (auto i = 0; i < 9; ++i)
            for (auto j = 0; j < 9; ++j) {
                board.values[i][j] = Game::emptyValue;
                board.isGiven[i][j] = true;
            }
        return board;
    }

    bool candidateIsValid(Game::Board board, char candidate, int r, int c) {
        for (auto i = 0; i < r; ++i)
            if (board.values[i][c] == candidate)
                return false;

        for (auto j = 0; j < c; ++j)
            if (board.values[r][j] == candidate)
                return false;

        auto l = c - c % 3;
        auto u = r - r % 3;
        for (auto i = u; i < u + 3; ++i)
            for (auto j = l; j < l + 3; ++j)
                if (board.values[i][j] == candidate)
                    return false;

        return true;
    }

    std::array<std::array<std::vector<char>,9>,9> fillCandidates(std::default_random_engine& rng) {
        std::array<std::array<std::vector<char>,9>,9> candidates;
        for (auto i = 0; i < 9; ++i)
            for (auto j = 0; j < 9; ++j) {
                candidates[i][j] = Game::LegalValues;
                std::shuffle(std::begin(candidates[i][j]), std::end(candidates[i][j]), rng);
                // std::ranges::shuffle(candidates[i][j], rng);
            }
        return candidates;
    }

    std::array<std::array<std::vector<char>,9>,9> fillCandidates(const Game::Board& board) {
        std::array<std::array<std::vector<char>,9>,9> candidates;
        for (auto i = 0; i < 9; ++i)
            for (auto j = 0; j < 9; ++j) {
                if (board.isGiven[i][j]) continue;
                candidates[i][j] = Game::LegalValues;
            }
        return candidates;
    }

    /*
    ** Generates a full sudoku board
     */
    Game::Board generateFullBoard(std::default_random_engine rng)
    {
        auto board = zeroBoard();
        auto candidates = fillCandidates(rng);

        auto pos = 0;
        while (pos < 81) {
            auto r = pos / 9;
            auto c = pos % 9;

            if (candidates[r][c].empty()) {
                if (pos == 0) {
                    std::cout << "Something is wrong!\n" << std::endl;
                    std::exit(-1);
                } // TODO: better panic system (maybe assert)

                candidates[r][c] = Game::LegalValues;
                std::shuffle(std::begin(candidates[r][c]), std::end(candidates[r][c]), rng);
                // std::ranges::shuffle(candidates[r][c], rng);

                board.values[r][c] = Game::emptyValue;
                pos--;
                continue;
            }

            auto cand = candidates[r][c].back();
            candidates[r][c].pop_back();

            if (!candidateIsValid(board, cand, r, c))
                continue;

            board.values[r][c] = cand;

            pos++;
        }

        return board;
    }

    // TODO: what if no previous non-given?
    int findPreviousNonGiven(const Game::Board& board, int pos) {
        pos--;
        auto r = pos / 9; auto c = pos % 9;
        while (board.isGiven[r][c] && pos >= 0) {
            pos--;
            r = pos / 9; c = pos % 9;
        }

        return pos;
    }

    // TODO: implement
    int numberOfSolutions(Game::Board board) {
        Test::printBoard(board); // TODO: remove

        int solutionsCount = 0;
        // TODO: algorithm
        // 1. for each non-given cell
        for (auto pos = 0; pos < 81;) {
            auto r = pos / 9;
            auto c = pos % 9;

            if (board.isGiven[r][c]) continue;

            // 2. for each valid value
            std::vector<char> candidates = Game::LegalValues;
            board.isGiven[r][c] = true;
            for (auto cand : candidates) {
                if (!candidateIsValid(board, cand, r, c)) continue;
                // 3. recursively eval number of solutions
                board.values[r][c] = cand;
                solutionsCount += numberOfSolutions(board);
                board.isGiven[r][c] = false;
                board.values[r][c] = Game::emptyValue;
            }

        }

        // TODO: base case?!
        // one base case is when whole board is complete and valid!
        // second base case is when there are no valid candidates for a cell

        return solutionsCount;
    }

    // TODO: implement
    bool isUniquelySolvable(Game::Board board) {

        // TODO: inefficient but mayber easier to implement
        return numberOfSolutions(board) == 1;
    }

    // BUG: always returns false
    bool isUniquelySolvable2(Game::Board board) {
        Test::printBoard(board); // TODO: remove

        auto candidates = fillCandidates(board);

        auto solutionsCount = 0;
        for (auto pos = 0; pos < 81;) {
            auto r = pos / 9;
            auto c = pos % 9;

            std::cout << "pos: " << pos << "; r: " << r << "; c: " << c;
            std::cout << std::endl;

            if (board.isGiven[r][c] && pos == 80) {
                if (solutionsCount > 0) {
                    // BUG: why?!
                    std::cout << "ping" << std::endl;
                    return false;
                } else {
                    solutionsCount++;
                    pos = findPreviousNonGiven(board, pos); // TODO
                    continue;
                }
            }

            if (board.isGiven[r][c]) {
                pos++;
                continue;
            }

            if (candidates[r][c].empty()) {
                candidates[r][c] = Game::LegalValues;
                board.values[r][c] = Game::emptyValue;
                std::cout << "reset at: " << pos;
                pos = findPreviousNonGiven(board, pos); // TODO
                std::cout << "; new pos: " << pos << std::endl;
                continue;
            }

            if (board.values[r][c] != Game::emptyValue) {
                board.values[r][c] = Game::emptyValue;
            }

            auto cand = candidates[r][c].back();
            candidates[r][c].pop_back();

            if (!candidateIsValid(board, cand, r, c)) continue;

            board.values[r][c] = cand;
            pos++;
        }

        std::cout << "solutionsCount: " << solutionsCount << std::endl;
        return solutionsCount == 1;
    }

    Game::Board generateValidBoard(std::default_random_engine rng, int cluesNum) {
        auto board = generateFullBoard(rng);
        Test::printBoard(board);

        auto positions = std::array<int,81> {};
        for (auto i = 0; i < 81; ++i) positions[i] = i;
        std::shuffle(std::begin(positions), std::end(positions), rng);
        // std::ranges::shuffle(positions, rng);

        std::cout << "positions: ";
        for (auto i = 0; i < 81; ++i) std::cout << positions[i] << " ";
        std::cout << std::endl;

        for (int i = 0; i < 81 && i < (81-cluesNum) && i < (81-17); i++) {
            auto r = positions[i] / 9;
            auto c = positions[i] % 9;

            // std::cout << "i: " << i;
            // std::cout << " position: " << positions[i] << "; r: " << r << "; c: " << c << std::endl;
            // std::cout << std::endl;

            auto val = board.values[r][c];
            board.values[r][c] = Game::emptyValue;
            board.isGiven[r][c] = false;

            // std::cout << "Before solving: " << std::endl;
            // Test::printBoard(board);
            if (!isUniquelySolvable(board)) {

                // std::cout << "After solving: " << std::endl;
                // Test::printBoard(board);

                board.values[r][c] = val;
                board.isGiven[r][c] = true;

                std::cout << "Is not uniqely solvable." << std::endl;
                continue;
            }

            std::cout << "After solving: " << std::endl;
            Test::printBoard(board);

        }

        return board;
    }

};
