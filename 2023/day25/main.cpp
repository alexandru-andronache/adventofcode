#include "file.h"
#include "utilities.h"
#include <iostream>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2023_day25 {
    int part_1(std::string_view path) {
        return 0;
    }
}

#ifdef TESTING
TEST(Tests2023Day25, part_1_test) {
    ASSERT_EQ(aoc2023_day25::part_1("../2023/day15/input_test.in"), 0);
}

TEST(Tests2023Day25, part_1_real_test) {
    ASSERT_EQ(aoc2023_day25::part_1("../2023/day15/input.in"), 0);
}
#endif

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2023_day25::part_1("../2023/day25/input.in") << std::endl;
    return 0;
}
#endif
