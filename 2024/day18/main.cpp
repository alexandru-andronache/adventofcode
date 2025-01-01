#include "file.h"
#include "utilities.h"
#include <iostream>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2024_day18 {
    int solve(std::string_view path, int bytes = 1024, int size = 70) {
        std::vector<std::vector<bool>> grid(size + 1, std::vector<bool>(size + 1, false));
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        for (int i = 0; i < bytes; ++i) {
            std::vector<int> tokens = utils::splitStringToInt(lines[i], ",");
            grid[tokens[0]][tokens[1]] = true;
        }
        int steps = 0;
        std::vector<utils::point> points{{0, 0}};
        std::vector<utils::point> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        grid[0][0] = true;
        while (!points.empty()) {
            std::vector<utils::point> new_points;
            for (auto& point : points) {
                for (auto& direction : directions) {
                    if (point.x + direction.x < 0 || point.x + direction.x > size || point.y + direction.y < 0 || point.y + direction.y > size) {
                        continue;
                    }
                    if (grid[point.x + direction.x][point.y + direction.y]) {
                        continue;
                    }
                    grid[point.x + direction.x][point.y + direction.y] = true;
                    if (point.x + direction.x == size && point.y + direction.y == size) {
                        return steps + 1;
                    }
                    new_points.emplace_back(point.x + direction.x, point.y + direction.y);
                }
            }
            points = new_points;
            ++steps;
        }

        return 0;
    }

    int part_1(std::string_view path, int bytes = 1024, int size = 70) {
        return solve(path, bytes, size);
    }

    std::string part_2(std::string_view path, int bytes = 1024, int size = 70) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        int li = bytes + 1;
        int ls = lines.size() - 1;
        while (li <= ls) {
            int m = (li + ls) / 2;
            int result = solve(path, m, size);
            if (result != 0) {
                li = m + 1;
            } else {
                ls = m - 1;
            }
        }
        return lines[li - 1];
    }
}

#ifdef TESTING
namespace aoc2024_day18 {
    TEST(Tests2024Day18, part_1_test) {
        ASSERT_EQ(part_1("../2024/day18/input_test.in", 12, 6), 22);
    }

    TEST(Tests2024Day18, part_1_real_test) {
        ASSERT_EQ(part_1("../2024/day18/input.in"), 252);
    }

    TEST(Tests2024Day18, part_2_test) {
        ASSERT_EQ(part_2("../2024/day18/input_test.in", 12, 6), "6,1");
    }

    TEST(Tests2024Day18, part_2_real_test) {
        ASSERT_EQ(part_2("../2024/day18/input.in"), "5,60");
    }
}
#endif

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2024_day18::part_1("../2024/day18/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2024_day18::part_2("../2024/day18/input_test.in", 12, 6) << std::endl;

    return 0;
}
#endif
