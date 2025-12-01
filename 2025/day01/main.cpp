#include "file.h"
#include "utilities.h"
#include <vector>

#include <fmt/printf.h>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2025_day01 {
    const int START = 50;
    int part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        int result = 0;
        int rotation = START;

        for (const auto& line : lines) {
            int nr = utils::getNumber(line, 1);
            nr = nr % 100;
            if (line[0] == 'R') {
                rotation += nr;
                rotation %= 100;
            }
            else if (line[0] == 'L') {
                rotation -= nr;
                rotation = (rotation + 100) % 100;
            }
            result += (rotation == 0);
        }

        return result;
    }

    int part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        int result = 0;
        int rotation = START;

        for (const auto& line : lines) {
            int nr = utils::getNumber(line, 1);
            result += nr / 100;
            nr = nr % 100;

            if (line[0] == 'R') {
                rotation += nr;
                result += rotation / 100;
                rotation = rotation % 100;
            }
            if (line[0] == 'L') {
                if (rotation > nr) {
                    rotation -= nr;
                }
                else if (rotation == nr) {
                    rotation = 0;
                    result++;
                }
                else {
                    if (rotation > 0) {
                        result++;
                    }
                    rotation = 100 - (nr - rotation);
                }
            }
        }

        return result;
    }
}

#ifdef TESTING
    TEST(Test2025Day01, part_1_test) {
        ASSERT_EQ(aoc2025_day01::part_1("../2025/day01/input_test.in"), 3);
    }

    TEST(Test2025Day01, part_1_real_test) {
        ASSERT_EQ(aoc2025_day01::part_1("../2025/day01/input.in"), 1191);
    }

    TEST(Test2025Day01, part_2_test) {
        ASSERT_EQ(aoc2025_day01::part_2("../2025/day01/input_test.in"), 6);
    }

    TEST(Test2025Day01, part_2_real_test) {
        ASSERT_EQ(aoc2025_day01::part_2("../2025/day01/input.in"), 6858);
    }
#endif

#ifndef TESTING
int main() {
    fmt::print("Part 1: {}\n", aoc2025_day01::part_1("../2025/day01/input.in"));
    fmt::print("Part 2: {}\n", aoc2025_day01::part_2("../2025/day01/input.in"));

    return 0;
}
#endif
