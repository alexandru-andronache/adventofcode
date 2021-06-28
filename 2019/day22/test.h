#pragma once

#include <string>

namespace aoc2019_day22 {
    unsigned int part_1(std::string_view path, int size = 10007, int card = 2019);
    long long part_2(std::string_view path, long long position = 2020, long long size = 119315717514047, long long rounds = 101741582076661);
}