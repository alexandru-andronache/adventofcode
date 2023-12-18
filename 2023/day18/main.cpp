#include "file.h"
#include "utilities.h"
#include <iostream>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2023_day18 {

    int hex(std::string str) {
        int val = 0;
        int base = 1;
        for (int i = str.size() - 1; i >= 0; --i) {
            if (str[i] >= '0' && str[i] <= '9') {
                val += (str[i] - '0') * base;
                base = base * 16;
            }
            else {
                val += (str[i] - 'a' + 10) * base;
                base = base * 16;
            }
        }
        return val;
    }

    unsigned long long solve(std::string_view path, bool useHex) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        int posX = 0, posY = 0;
        std::vector<std::pair<unsigned long long, unsigned long long>> vertex{{0, 0}};
        std::vector<std::pair<int, int>> directions{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        std::map<char, int> dir {{'R', 0}, {'D', 1}, {'L', 2}, {'U', 3}};
        unsigned long long perimeter = 0;
        for (const auto& line : input) {
            std::vector<std::string> t = utils::splitString(line," ()");
            std::pair<int, int> d;
            int distance;
            if (useHex) {
                d = directions[t[2].back() - '0'];
                distance = hex(t[2].substr(1, 5));
            }
            else {
                d = directions[dir[t[0][0]]];
                distance = std::stoi(t[1]);
            }
            perimeter += distance;
            posX = posX + d.first * distance;
            posY = posY + d.second * distance;
            vertex.emplace_back(posX, posY);
        }

        vertex.emplace_back(0, 0);
        std::reverse(vertex.begin(), vertex.end());
        unsigned long long sol = 0;
        for (int i = 0; i < vertex.size() - 1; ++i) {
            sol += (vertex[i].second + vertex[i + 1].second) * (vertex[i].first - vertex[i + 1].first);
        }
        return perimeter / 2 + sol / 2 + 1;
    }
    unsigned long long part_1(std::string_view path) {
        return solve(path, false);
    }

    unsigned long long part_2(std::string_view path) {
        return solve(path, true);
    }
}

#ifdef TESTING
TEST(Tests2023Day18, part_1_test) {
    ASSERT_EQ(aoc2023_day18::part_1("../2023/day18/input_test.in"), 62);
}

TEST(Tests2023Day18, part_1_real_test) {
    ASSERT_EQ(aoc2023_day18::part_1("../2023/day18/input.in"), 52035);
}

TEST(Tests2023Day18, part_2_test) {
    ASSERT_EQ(aoc2023_day18::part_2("../2023/day18/input_test.in"), 952408144115);
}

TEST(Tests2023Day18, part_2_real_test) {
    ASSERT_EQ(aoc2023_day18::part_2("../2023/day18/input.in"), 60612092439765);
}
#endif

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2023_day18::part_1("../2023/day18/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2023_day18::part_2("../2023/day18/input.in") << std::endl;

    return 0;
}
#endif
