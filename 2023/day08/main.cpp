#include "file.h"
#include "utilities.h"
#include <iostream>
#include <map>
#include <string>
#include <numeric>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2023_day08 {
    struct s {
        s() = default;
        s(std::string l, std::string r) {
            left = l;
            right = r;
        }
        std::string left;
        std::string right;
    };
    int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::string instructions = input[0];
        std::map<std::string, s> paths;
        int sol = 0;
        for (int index = 2; index < input.size(); ++index) {
            std::vector<std::string> t = utils::splitString(input[index], " =,()");
            paths.insert({t[0], {t[1], t[2]}});
        }

        std::string current = "AAA";
        int i = 0;
        while (current != "ZZZ") {
            if (instructions[i] == 'L') {
                current = paths[current].left;
            }
            else {
                current = paths[current].right;
            }
            i++;
            if (i >= instructions.size()) {
                i = 0;
            }
            sol++;
        }
        return sol;
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::string instructions = input[0];
        std::map<std::string, s> paths;
        std::vector<std::string> current;
        std::vector<int> sol;

        for (int index = 2; index < input.size(); ++index) {
            std::vector<std::string> t = utils::splitString(input[index], " =,()");
            paths.insert({t[0], {t[1], t[2]}});
            if (t[0][2] == 'A') {
                current.push_back(t[0]);
                sol.push_back(0);
            }
        }

        for (int k = 0; k < current.size(); ++k) {
            int i = 0;
            while (current[k][2] != 'Z') {
                if (instructions[i] == 'L') {
                    current[k] = paths[current[k]].left;
                } else {
                    current[k] = paths[current[k]].right;
                }
                i++;
                if (i >= instructions.size()) {
                    i = 0;
                }
                sol[k]++;
            }
        }

        unsigned long long solution = sol[0];
        for (int i = 1; i < sol.size(); ++i) {
            solution = std::lcm(solution, sol[i]);
        }


        return solution;
    }
}

#ifdef TESTING
TEST(Tests2023Day08, part_1_test) {
    ASSERT_EQ(aoc2023_day08::part_1("../2023/day08/input_test.in"), 6);
}

TEST(Tests2023Day08, part_1_real_test) {
    ASSERT_EQ(aoc2023_day08::part_1("../2023/day08/input.in"), 22357);
}

TEST(Tests2023Day08, part_2_test) {
    ASSERT_EQ(aoc2023_day08::part_2("../2023/day08/input_test2.in"), 6);
}

TEST(Tests2023Day08, part_2_real_test) {
    ASSERT_EQ(aoc2023_day08::part_2("../2023/day08/input.in"), 10371555451871);
}
#endif

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2023_day08::part_1("../2023/day08/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2023_day08::part_2("../2023/day08/input.in") << std::endl;

    return 0;
}
#endif
