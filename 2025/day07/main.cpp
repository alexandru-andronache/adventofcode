#include "file.h"
#include "utilities.h"
#include <vector>

#include <fmt/printf.h>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2025_day07 {
    int part_1(std::string_view path) {
        // std::string input = file::readFileAsString(path);
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        int result = 0;

        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, "");
        }

        return result;
    }

    int part_2(std::string_view path) {
        return 0;
    }
}

#ifdef TESTING
    TEST(Test2025Day07, part_1_test) {
        ASSERT_EQ(aoc2025_day07::part_1("../2025/day07/input_test.in"), 0);
    }

    TEST(Test2025Day07, part_1_real_test) {
        ASSERT_EQ(aoc2025_day07::part_1("../2025/day07/input.in"), 0);
    }

    TEST(Test2025Day07, part_2_test) {
        ASSERT_EQ(aoc2025_day07::part_2("../2025/day07/input_test.in"), 0);
    }

    TEST(Test2025Day07, part_2_real_test) {
        ASSERT_EQ(aoc2025_day07::part_2("../2025/day07/input.in"), 0);
    }
#endif

#ifndef TESTING
int main() {
    fmt::print("Part 1: {}\n", aoc2025_day07::part_1("../2025/day07/input.in"));
    fmt::print("Part 2: {}\n", aoc2025_day07::part_1("../2025/day07/input.in"));

    return 0;
}
#endif
