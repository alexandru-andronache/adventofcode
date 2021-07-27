#pragma once

#include <string>

namespace aoc2017_day10 {
    int part_1(std::string_view path, int size = 256);
    std::string part_2(std::string_view path, int size = 256, int rounds = 64);
}