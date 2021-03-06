#pragma once

#include <string>

namespace aoc2019_day06 {
    int part_1(std::string_view path);
    int part_2(std::string_view path, const std::string& begin = "YOU", const std::string& end = "SAN");
}

