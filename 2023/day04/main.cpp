#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2023_day04 {
    unsigned long long part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        unsigned long long sol = 0;
        for (const auto& line : input) {
            std::vector<std::string> t = utils::splitString(line, ":|");
            std::vector<int> nr1 = utils::splitStringToInt(t[1], " ");
            std::vector<int> nr2 = utils::splitStringToInt(t[2], " ");
            int matches = 0;
            for (const auto& n : nr1) {
                if (std::find(nr2.begin(), nr2.end(), n) != nr2.end()) {
                    matches++;
                }
            }
            sol += std::pow(2, matches - 1);
        }
        return sol;
    }

    int part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<int> cards(input.size(), 1);
        unsigned long long sol = 0;
        for (int index = 0; const auto& line : input) {
            std::vector<std::string> t = utils::splitString(line, ":|");
            std::vector<int> nr1 = utils::splitStringToInt(t[1], " ");
            std::vector<int> nr2 = utils::splitStringToInt(t[2], " ");
            int matches = 0;
            for (int i = 0; i < nr1.size(); ++i) {
                if (std::find(nr2.begin(), nr2.end(), nr1[i]) != nr2.end()) {
                    matches++;
                }
            }
            for (int i = 0; i < matches; ++i) {
                if (i + index + 1 < input.size()) {
                    cards[i + index + 1] += cards[index];
                }
            }
            index++;
        }
        for (const auto& c: cards) {
            sol += c;
        }
        return sol;
    }
}

#ifdef TESTING
TEST(Tests2023Day04, part_1_test) {
    ASSERT_EQ(aoc2023_day04::part_1("../2023/day04/input_test.in"), 13);
}

TEST(Tests2023Day04, part_1_real_test) {
    ASSERT_EQ(aoc2023_day04::part_1("../2023/day04/input.in"), 23441);
}

TEST(Tests2023Day04, part_2_test) {
    ASSERT_EQ(aoc2023_day04::part_2("../2023/day04/input_test.in"), 30);
}

TEST(Tests2023Day04, part_2_real_test) {
    ASSERT_EQ(aoc2023_day04::part_2("../2023/day04/input.in"), 5923918);
}
#endif

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2023_day04::part_1("../2023/day04/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2023_day04::part_2("../2023/day04/input.in") << std::endl;

    return 0;
}
#endif
