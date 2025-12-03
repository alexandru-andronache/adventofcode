#include "file.h"
#include "utilities.h"
#include <vector>
#include <iostream>

#include <fmt/printf.h>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2025_day03 {
    int part_1(std::string_view path) {
        // std::string input = file::readFileAsString(path);
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        int result = 0;

        for (const auto& line : lines) {
            int max = 0;
            for (int i = 0; i < line.size(); ++i) {
                for (int j = i + 1; j < line.size(); ++j) {
                    int nr = (line[i] - '0') * 10 + (line[j] - '0');
                    if (nr > max) {
                        max = nr;
                    }
                }
            }
            result += max;
        }

        return result;
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        unsigned long long result = 0;

        for (const auto& line : lines) {
            unsigned long long max = 0;
            int index = 0;
            for (int k = 12; k > 0; --k) {
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
        ASSERT_EQ(aoc2025_day03::part_2("../2025/day03/input.in"), 0);
    }
#endif

#ifndef TESTING
int main() {
    fmt::print("Part 1: {}\n", aoc2025_day03::part_1("../2025/day03/input.in"));
    fmt::print("Part 2: {}\n", aoc2025_day03::part_2("../2025/day03/input.in"));

    return 0;
}
#endif
