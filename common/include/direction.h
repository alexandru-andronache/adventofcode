#pragma once

#include "utilities.h"

namespace direction {
    class Direction {
    public:
        Direction() = default;
        static constexpr utils::point DOWN{1, 0};
        static constexpr utils::point UP{-1, 0};
        static constexpr utils::point LEFT{0, -1};
        static constexpr utils::point RIGHT{0, 1};
        const std::vector<utils::point> directions {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        const std::vector<utils::point> fullDirections {{-1, -1}, {-1, 0}, {-1, 1},
                                                    {0, -1}, {0, 1},
                                                    {1, -1}, {1, 0}, {1, 1}};
    };
}
