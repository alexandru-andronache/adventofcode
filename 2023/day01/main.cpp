#include "file.h"
#include <iostream>
#include <vector>
#include <map>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2023_day01 {
    int solve(std::string_view path, std::vector<std::string> numbers) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        int sum = 0;
        for (const auto& line : input) {
            std::vector<int> start(numbers.size(), (int)line.size());
            std::vector<int> end(numbers.size(), -1);
            for (int i = 0; i < numbers.size(); ++i) {
                auto t = line.find(numbers[i], 0);
                while (t != std::string::npos)
                {
                    if (start[i] == (int)line.size()) {
                        start[i] = t;
                    }
                    end[i] = t;
                    t = line.find(numbers[i], t + 1);
                }
            }
            int first = std::distance(start.begin(), std::min_element(start.begin(), start.end())) % 10;
            int second = std::distance(end.begin(), std::max_element(end.begin(), end.end())) % 10;
            sum += first * 10 + second;
        }
        return sum;
    }

    int part_1(std::string_view path) {
        return solve(path, {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"});
    }

    int part_2(std::string_view path) {
        return solve(path, {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "zero", "one","two", "three", "four", "five", "six", "seven", "eight", "nine"});
    }
}

#ifdef TESTING
TEST(Tests2023Day01, part_1_test) {
    ASSERT_EQ(aoc2023_day01::part_1("../2023/day01/input_test.in"), 142);
}

TEST(Tests2023Day01, part_1_real_test) {
    ASSERT_EQ(aoc2023_day01::part_1("../2023/day01/input.in"), 55834);
}

TEST(Tests2023Day01, part_2_test) {
    ASSERT_EQ(aoc2023_day01::part_2("../2023/day01/input_test2.in"), 281);
}

TEST(Tests2023Day01, part_2_real_test) {
    ASSERT_EQ(aoc2023_day01::part_2("../2023/day01/input.in"), 53221);
}
#endif

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2023_day01::part_1("../2023/day01/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2023_day01::part_2("../2023/day01/input.in") << std::endl;

    return 0;
}
#endif
