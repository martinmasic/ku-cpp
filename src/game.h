#pragma once

#ifndef GAME_H
#define GAME_H

namespace Game {

    const std::vector<char> LegalValues = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };

    const char emptyValue = '.';

    struct Board {
        std::array<std::array<char,9>,9> values;
        std::array<std::array<bool,9>,9> isGiven;

        // Default Move Constructor
        Board(Board&&) noexcept = default;

        // Default Move Assignment
        Board& operator=(Board&&) noexcept = default;

        // Default Constructor
        Board() = default;

        // Copy Constructor and Copy Assignemnt
        Board(const Board&) = default;
        Board& operator=(const Board&) = default;
    };

};

#endif
