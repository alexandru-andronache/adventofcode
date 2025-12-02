#include "file.h"
#include "utilities.h"
#include <vector>

#include <fmt/printf.h>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2025_day02 {
    unsigned long long solve(const std::string& start, const std::string& end, int min, int max) {
        std::set<unsigned long long> values;
        unsigned long long sum = 0;
        const unsigned long long from = std::stoull(start);
        const unsigned long long to = std::stoull(end);

        for (int p = min; p <= max; ++p) {
            for (int j = static_cast<int>(std::ceil((float)start.size() / p)); j <= end.size() / p; ++j) {
                unsigned long long s = std::pow(10, j - 1);
                for (int k = s; k < s * 10; ++k) {
                    unsigned long long nr = 0;
                    for (int a = 0; a < p; ++a) {
                        nr = nr * pow(10, j) + k;
                    }
                    if (nr >= from && nr <= to && !values.contains(nr)) {
                        sum += nr;
                        values.insert(nr);
                    }
                }
            }
        }

        return sum;
    }

    unsigned long long part_1(std::string_view path) {
        std::string input = file::readFileAsString(path);
        unsigned long long result = 0;

        auto ranges = utils::splitString(input, ",");

        for (const auto& range : ranges) {
            std::vector<std::string> numbers = utils::splitString(range, "-");
            result += solve(numbers[0], numbers[1], 2, 2);
        }

        return result;
    }

    unsigned long long part_2(std::string_view path) {
        std::string input = file::readFileAsString(path);
        unsigned long long result = 0;

        std::vector<std::string> ranges = utils::splitString(input, ",");

        for (const auto& range : ranges) {
            std::vector<std::string> numbers = utils::splitString(range, "-");
            result += solve(numbers[0], numbers[1], 2, numbers[1].size());
        }

        return result;
    }
}

#ifdef TESTING
    TEST(Test2025Day02, part_1_test) {
        ASSERT_EQ(aoc2025_day02::part_1("../2025/day02/input_test.in"), 1227775554);
    }

    TEST(Test2025Day02, part_1_real_test) {
        ASSERT_EQ(aoc2025_day02::part_1("../2025/day02/input.in"), 13108371860);
    }

    TEST(Test2025Day02, part_2_test) {
        ASSERT_EQ(aoc2025_day02::part_2("../2025/day02/input_test.in"), 4174379265);
    }

    TEST(Test2025Day02, part_2_real_test) {
        ASSERT_EQ(aoc2025_day02::part_2("../2025/day02/input.in"), 22471660255);
    }
#endif

#ifndef TESTING
int main() {
    fmt::print("Part 1: {}\n", aoc2025_day02::part_1("../2025/day02/input.in"));
    fmt::print("Part 2: {}\n", aoc2025_day02::part_2("../2025/day02/input.in"));

    return 0;
}
#endif
