#include "file.h"
#include "utilities.h"
#include <iostream>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2023_day15 {
    int hash(std::string_view str) {
        int sum = 0;
        for (const auto& c : str) {
            sum = (sum + c) * 17 % 256;
        }
        return sum;
    }
    unsigned long long part_1(std::string_view path) {
        std::string input = file::readFileAsString(path);
        std::vector<std::string> tokens = utils::splitString(input, ",");
        unsigned long long sol = 0;
        for (const auto& token : tokens) {
            sol += hash(token);
        }
        return sol;
    }

    unsigned long long part_2(std::string_view path) {
        struct bb{
            bb() = default;
            bb(std::string n, int x): name(std::move(n)), nr(x) {}
            std::string name;
            int nr;
        };
        std::string input = file::readFileAsString(path);
        std::vector<std::string> t = utils::splitString(input, ",");
        std::vector<std::vector<bb>> boxes(256, std::vector<bb>());
        unsigned long long sol = 0;

        for (const auto& s : t) {
            if (s.back() == '-') {
                int b = hash(s.substr(0, s.size() - 1));
                boxes[b].erase(std::remove_if(boxes[b].begin(),
                                              boxes[b].end(),
                                              [s](auto str) { return str.name == s.substr(0, s.size() - 1); }),
                               boxes[b].end());
            }
            else {
                int b = hash(s.substr(0, s.size() - 2));
                bool found = false;
                int x = s[s.size() - 1] - '0';
                for (int i = 0; i < boxes[b].size() && !found; ++i) {
                    if (boxes[b][i].name == s.substr(0, s.size() - 2)) {
                        boxes[b][i].nr = x;
                        found = true;
                    }
                }
                if (!found) {
                    boxes[b].emplace_back(s.substr(0, s.size() - 2), x);
                }
            }
        }
        for (int i = 0; i < boxes.size(); ++i) {
            for (int j = 0; j < boxes[i].size(); ++j) {
                sol += (i + 1) * (j + 1) * boxes[i][j].nr;
            }
        }


        return sol;
    }
}

#ifdef TESTING
TEST(Tests2023Day15, part_1_test) {
    ASSERT_EQ(aoc2023_day15::part_1("../2023/day15/input_test.in"), 1320);
}

TEST(Tests2023Day15, part_1_real_test) {
    ASSERT_EQ(aoc2023_day15::part_1("../2023/day15/input.in"), 517965);
}

TEST(Tests2023Day15, part_2_test) {
    ASSERT_EQ(aoc2023_day15::part_2("../2023/day15/input_test.in"), 145);
}

TEST(Tests2023Day15, part_2_real_test) {
    ASSERT_EQ(aoc2023_day15::part_2("../2023/day15/input.in"), 267372);
}
#endif

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2023_day15::part_1("../2023/day15/input.in") << std::endl;
    std::cout << "Part 1: " << aoc2023_day15::part_2("../2023/day15/input.in") << std::endl;

    return 0;
}
#endif
