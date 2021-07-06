#pragma once

#include <string>

namespace aoc2019_day16 {
    std::string part_1(std::string_view path, int phases = 100);
    std::string part_2(std::string_view path, int phases = 100, int repeat = 10000);
}