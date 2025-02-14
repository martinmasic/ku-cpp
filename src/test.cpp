#include <iostream>
#include <random>
#include <string>

#include "generator.h"


int main(void) {

    // TODO: enable this to randomize every time
    // auto rd = std::random_device {};
    // auto static rng = std::default_random_engine { rd };
    auto static rng = std::default_random_engine {};

    auto board = Generator::generateFullBoard(rng);

    Generator::printBoard(board);


}
