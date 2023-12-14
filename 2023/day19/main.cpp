#include "file.h"
#include "utilities.h"
#include <iostream>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2023_day19 {
    int part_1(std::string_view path) {
        return 0;
    }

    unsigned long long part_2(std::string_view path) {
        return 0;
    }
}

#ifdef TESTING
TEST(Tests2023Day19, part_1_test) {
    ASSERT_EQ(aoc2023_day19::part_1("../2023/day15/input_test.in"), 0);
}

TEST(Tests2023Day19, part_1_real_test) {
    ASSERT_EQ(aoc2023_day19::part_1("../2023/day15/input.in"), 0);
}

TEST(Tests2023Day19, part_2_test) {
    ASSERT_EQ(aoc2023_day19::part_2("../2023/day15/input_test.in"), 0);
}

TEST(Tests2023Day19, part_2_real_test) {
    ASSERT_EQ(aoc2023_day19::part_2("../2023/day15/input.in"), 0);
}
#endif

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2023_day19::part_1("../2023/day19/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2023_day19::part_2("../2023/day19/input.in") << std::endl;

    return 0;
}
#endif
