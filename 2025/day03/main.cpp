#include "file.h"
#include "utilities.h"
#include <vector>
#include <iostream>

#include <fmt/printf.h>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2025_day03 {
    unsigned long long solve(std::string_view path, int length) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        unsigned long long result = 0;

        for (const auto& line : lines) {
            unsigned long long max = 0;
            int index = 0;
            for (int k = length; k > 0; --k) {
                int maxN = 0;
                for (int i = index; i <= line.size() - k; ++i) {
                    if (line[i] - '0' > maxN) {
                        maxN = line[i] - '0';
                        index = i;
                    }
                }
                index++;
                max = max * 10 + maxN;
            }
            result += max;
        }

        return result;
    }
    int part_1(std::string_view path) {
        return solve(path, 2);
    }

    unsigned long long part_2(std::string_view path) {
        return solve(path, 12);
    }
}

#ifdef TESTING
    TEST(Test2025Day03, part_1_test) {
        ASSERT_EQ(aoc2025_day03::part_1("../2025/day03/input_test.in"), 357);
    }

    TEST(Test2025Day03, part_1_real_test) {
        ASSERT_EQ(aoc2025_day03::part_1("../2025/day03/input.in"), 17321);
    }

    TEST(Test2025Day03, part_2_test) {
        ASSERT_EQ(aoc2025_day03::part_2("../2025/day03/input_test.in"), 3121910778619);
    }

    TEST(Test2025Day03, part_2_real_test) {
        ASSERT_EQ(aoc2025_day03::part_2("../2025/day03/input.in"), 171989894144198);
    }
#endif

#ifndef TESTING
int main() {
    fmt::print("Part 1: {}\n", aoc2025_day03::part_1("../2025/day03/input.in"));
    fmt::print("Part 2: {}\n", aoc2025_day03::part_2("../2025/day03/input.in"));

    return 0;
}
#endif
