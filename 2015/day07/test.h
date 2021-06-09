#pragma once

#include <string>

namespace aoc2015_day07 {
    unsigned long long part_1(std::string_view path, std::string_view key = "a", const std::map<std::string, unsigned int>& startValues = {});
    unsigned long long part_2(std::string_view path, unsigned int val);
}