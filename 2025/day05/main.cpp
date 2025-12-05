#include "file.h"
#include "utilities.h"
#include <ranges.h>
#include <vector>

#include <fmt/printf.h>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2025_day05 {
    int part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        int result = 0;

        aoc::Ranges<unsigned long long> ranges;

        int index = 0;
        while (!lines[index].empty()) {
            std::vector<std::string> tokens = utils::splitString(lines[index], "-");
            ranges.addRange(std::stoull(tokens[0]), std::stoull(tokens[1]));
            index++;
        }
        index++;
        for (int i = index; i < lines.size(); ++i) {
            result += ranges.isInRange(std::stoull(lines[i]));
        }

        return result;
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        aoc::Ranges<unsigned long long> ranges;

        int index = 0;
        while (!lines[index].empty()) {
            std::vector<std::string> tokens = utils::splitString(lines[index], "-");
            ranges.addRange(std::stoull(tokens[0]), std::stoull(tokens[1]));
            index++;
        }

        return ranges.count();
    }
}

#ifdef TESTING
    TEST(Test2025Day05, part_1_test) {
        ASSERT_EQ(aoc2025_day05::part_1("../2025/day05/input_test.in"), 3);
    }

    TEST(Test2025Day05, part_1_real_test) {
        ASSERT_EQ(aoc2025_day05::part_1("../2025/day05/input.in"), 862);
    }

    TEST(Test2025Day05, part_2_test) {
        ASSERT_EQ(aoc2025_day05::part_2("../2025/day05/input_test.in"), 14);
    }

    TEST(Test2025Day05, part_2_real_test) {
        ASSERT_EQ(aoc2025_day05::part_2("../2025/day05/input.in"), 357907198933892);
    }
#endif

#ifndef TESTING
int main() {
    fmt::print("Part 1: {}\n", aoc2025_day05::part_1("../2025/day05/input.in"));
    fmt::print("Part 2: {}\n", aoc2025_day05::part_2("../2025/day05/input.in"));

    return 0;
}
#endif
