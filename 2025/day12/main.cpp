#include "file.h"
#include "utilities.h"
#include <vector>

#include <fmt/printf.h>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2025_day12 {
    struct shape {
        std::array<std::array<bool, 3>, 3> matrix;
        int total = 0;
    };

    int part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        int result = 0;

        std::vector<shape> shapes;
        for (int k = 0; k < lines.size(); ++k) {
            if (lines[k][1] == ':') {
                shape s;
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        s.matrix[i][j] = (lines[k + 1 + i][j] == '#');
                        s.total += s.matrix[i][j];
                    }
                }
                shapes.push_back(s);
                k += 4;
            }
            else {
                std::vector<int> tokens = utils::splitStringToInt(lines[k], " :x,");

                int w = tokens[0];
                int h = tokens[1];
                int s = 0;
                for (int i = 2; i < tokens.size(); ++i) {
                    s += shapes[i - 2].total * tokens[i];
                }
                if (s < w * h) {
                    result++;
                }
            }
        }

        return result;
    }

    int part_2(std::string_view path) {
        return 0;
    }
}

#ifdef TESTING

    TEST(Test2025Day12, part_1_real_test) {
        ASSERT_EQ(aoc2025_day12::part_1("../2025/day12/input.in"), 510);
    }
#endif

#ifndef TESTING
int main() {
    fmt::print("Part 1: {}\n", aoc2025_day12::part_1("../2025/day12/input.in"));
    fmt::print("Part 2: {}\n", aoc2025_day12::part_1("../2025/day12/input.in"));

    return 0;
}
#endif
