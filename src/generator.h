#pragma once

#include <array>
#include <random>

#include "game.h"

namespace Generator {

    Game::Board generateFullBoard(std::default_random_engine rng);

    Game::Board generateValidBoard(std::default_random_engine rng, int cluesNum);

}
