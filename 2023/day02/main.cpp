#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2023_day02 {
    int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        int sol = 0;
        for (int index = 0; const auto& line : input) {
            std::vector<std::string> token = utils::splitString(line, ":;");
            bool x = true;
            for (int i = 1; i < token.size(); ++i) {
                std::vector<std::string> t = utils::splitString(token[i], ",");
                for (const auto & j : t) {
                    std::vector<std::string> t1 = utils::splitString(j, " ");
                    if ((t1[1] == "blue") && (std::stoi(t1[0]) > 14)) {
                        x = false;
                    } else if ((t1[1] == "red") && (std::stoi(t1[0]) > 12)) {
                        x = false;
                    } else if ((t1[1] == "green") && (std::stoi(t1[0]) > 13)) {
                        x = false;
                    }
                }
            }
            if (x) sol += index + 1;
            index++;
        }
        return sol;
    }

    long long part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        int sol = 0;
        for (const auto& line : input) {
            std::vector<std::string> token = utils::splitString(line, ":;");
            int minB = 0;
            int minR = 0;
            int minG = 0;
            for (int i = 1; i < token.size(); ++i) {
                std::vector<std::string> t = utils::splitString(token[i], ",");
                for (int j = 0; j < t.size(); ++j) {
                    std::vector<std::string> t1 = utils::splitString(t[j], " ");
                    if ((t1[1] == "blue")) {
                        minB = std::max(minB, std::stoi(t1[0]));
                    } else if ((t1[1] == "red")) {
                        minR = std::max(minR, std::stoi(t1[0]));
                    } else if ((t1[1] == "green")) {
                        minG = std::max(minG, std::stoi(t1[0]));
                    }
                }
            }
            sol += minB * minR * minG;
        }
        return sol;
    }
}

#ifdef TESTING
TEST(Tests2023Day02, part_1_test) {
    ASSERT_EQ(aoc2023_day02::part_1("../2023/day02/input_test.in"), 8);
}

TEST(Tests2023Day02, part_1_real_test) {
    ASSERT_EQ(aoc2023_day02::part_1("../2023/day02/input.in"), 2369);
}

TEST(Tests2023Day02, part_2_test) {
    ASSERT_EQ(aoc2023_day02::part_2("../2023/day02/input_test.in"), 2286);
}

TEST(Tests2023Day02, part_2_real_test) {
    ASSERT_EQ(aoc2023_day02::part_2("../2023/day02/input.in"), 66363);
}
#endif

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2023_day02::part_1("../2023/day02/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2023_day02::part_2("../2023/day02/input.in") << std::endl;

    return 0;
}
#endif
