#include "file.h"
#include "utilities.h"
#include <vector>

#include <fmt/printf.h>
#include <iostream>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2025_day04 {
    int part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);

        int result = 0;

        for (int i = 0; i < lines.size(); ++i) {
            for (int j = 0; j < lines[i].size(); ++j) {
                std::vector<utils::point> dir = utils::getListOfNeighboursAllDirections(i, j, lines.size(), lines[0].size());
                int c = 0;
                for (const auto& d : dir) {
                    if (lines[i + d.x][j + d.y] == '@') {
                        c++;
                    }
                }
                if (c < 4 && lines[i][j] == '@') {
                    result++;
                }
            }
        }

        return result;
    }

    int part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);

        int result = 0;
        bool keep = true;

        while (keep) {
            keep = false;
            for (int i = 0; i < lines.size(); ++i) {
                for (int j = 0; j < lines[i].size(); ++j) {
                    if (lines[i][j] == '@') {
                        std::vector<utils::point> dir = utils::getListOfNeighboursAllDirections(i, j, lines.size(), lines[0].size());
                        int c = 0;
                        for (const auto& d : dir) {
                            if (lines[i + d.x][j + d.y] == '@') {
                                c++;
                            }
                        }
                        if (c < 4) {
                            result++;
                            lines[i][j] = '.';
                            keep = true;
                        }
                    }
                }
            }
        }

        return result;
    }
}

#ifdef TESTING
    TEST(Test2025Day04, part_1_test) {
        ASSERT_EQ(aoc2025_day04::part_1("../2025/day04/input_test.in"), 13);
    }

    TEST(Test2025Day04, part_1_real_test) {
        ASSERT_EQ(aoc2025_day04::part_1("../2025/day04/input.in"), 1626);
    }

    TEST(Test2025Day04, part_2_test) {
        ASSERT_EQ(aoc2025_day04::part_2("../2025/day04/input_test.in"), 43);
    }

    TEST(Test2025Day04, part_2_real_test) {
        ASSERT_EQ(aoc2025_day04::part_2("../2025/day04/input.in"), 9173);
    }
#endif

#ifndef TESTING
int main() {
    fmt::print("Part 1: {}\n", aoc2025_day04::part_1("../2025/day04/input.in"));
    fmt::print("Part 2: {}\n", aoc2025_day04::part_2("../2025/day04/input_test.in"));

    return 0;
}
#endif
