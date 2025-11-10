#include "file.h"
#include "utilities.h"
#include <iostream>
#include <fmt/printf.h>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2024_day25 {
    int part_1(std::string_view path) {
        const auto lines = file::readFileAsArrayString(path);
        std::vector<std::array<int, 5>> locks;
        std::vector<std::array<int, 5>> keys;
        for (int k = 0; k < lines.size(); k += 8) {
            std::array<int, 5> l{0, 0, 0, 0,0};
            for (int i = 0; i < 7; ++i) {
                for (int j = 0; j < 5; ++j) {
                    if (lines[k + i][j] == '#') {
                        l[j]++;
                    }
                }
            }
            if (lines[k] == "#####") {
                locks.emplace_back(l);
            }
            else {
                keys.emplace_back(l);
            }
        }

        int count = 0;
        for (const auto& lock : locks) {
            for (const auto& key : keys) {
                bool valid = true;
                for (int i = 0; i < 5 && valid; ++i) {
                    if (lock[i] + key[i] > 7) {
                        valid = false;
                    }
                }
                count += valid;
            }
        }

        return count;
    }
}

#ifdef TESTING
namespace aoc2024_day25 {
    TEST(Tests2024Day25, part_1_test) {
        ASSERT_EQ(part_1("../2024/day25/input_test.in"), 3);
    }

    TEST(Tests2024Day25, part_1_real_test) {
        ASSERT_EQ(part_1("../2024/day25/input.in"), 3264);
    }
}
#endif

#ifndef TESTING
int main() {
    fmt::print("Part 1: {}\n", aoc2024_day25::part_1("../2024/day25/input.in"));
    return 0;
}
#endif
