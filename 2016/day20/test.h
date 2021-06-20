#pragma once

#include <string>

namespace aoc2016_day20 {
    long long part_1(std::string_view path);
    long long part_2(std::string_view path, long long start = 0, long long finish = 4294967295);
}
