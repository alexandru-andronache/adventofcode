#include "file.h"
#include <iostream>
#include <utilities.h>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2024_day13 {
    long long solve(std::string_view path, long long extra = 10000000000000) {
        struct button {
            long long x, y;
            int token;
        };
        std::vector<std::string> input = file::readFileAsArrayString(path);
        long long sum = 0;
        for (int k = 0; k < input.size(); k += 4) {
            std::vector<std::string> tokensA = utils::splitString(input[k], " ,+");
            std::vector<std::string> tokensB = utils::splitString(input[k + 1], " ,+");
            std::vector<std::string> tokensTotal = utils::splitString(input[k + 2], " ,=");
            button a {std::stoll(tokensA[3]), std::stoll(tokensA[5]), 3};
            button b {std::stoll(tokensB[3]), std::stoll(tokensB[5]), 1};
            long long prizeX = std::stoi(tokensTotal[2]) + extra, prizeY = std::stoi(tokensTotal[4]) + extra;

            long long d = a.x * b.y - a.y * b.x;
            long long dx = prizeX * b.y - prizeY * b.x;
            long long dy = a.x * prizeY - a.y * prizeX;

            if (d == 0) {
                continue;
            }
            if (dx % d != 0 || dy % d != 0) {
                continue;
            }
            sum += (dx / d) * a.token + (dy / d) * b.token;
        }
        return sum;
    }

    long long part_1(std::string_view path) {
        return solve(path, 0);
    }

    long long part_2(std::string_view path) {
        return solve(path);
    }
}

#ifdef TESTING
namespace aoc2024_day13 {
    TEST(Tests2024Day13, part_1_test) {
        ASSERT_EQ(part_1("../2024/day13/input_test.in"), 480);
    }

    TEST(Tests2024Day13, part_1_real_test) {
        ASSERT_EQ(part_1("../2024/day13/input.in"), 27105);
    }

    TEST(Tests2024Day13, part_2_test) {
        ASSERT_EQ(part_2("../2024/day13/input_test.in"), 875318608908);
    }

    TEST(Tests2024Day13, part_2_real_test) {
        ASSERT_EQ(part_2("../2024/day13/input.in"), 101726882250942);
    }
}
#endif

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2024_day13::part_1("../2024/day13/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2024_day13::part_2("../2024/day13/input.in") << std::endl;

    return 0;
}
#endif
