#pragma once

#include <string>

namespace aoc2018_day07 {
    std::string part_1(std::string_view path);
    int part_2(std::string_view path, int nrWorkers = 2, int extraSeconds = 0);
}