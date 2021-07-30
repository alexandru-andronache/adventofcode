#pragma once

#include "utilities.h"

namespace direction {
    utils::point DOWN{1, 0};
    utils::point UP{-1, 0};
    utils::point LEFT{0, -1};
    utils::point RIGHT{0, 1};
    std::vector<utils::point> directions {UP, DOWN, LEFT, RIGHT};
}
