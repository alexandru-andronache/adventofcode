#include "file.h"
#include "utilities.h"
#include <iostream>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2023_day17 {

    int solve(std::string_view path, int minDist, int maxDist) {
        struct state {
            state(int _x, int _y, int _d, int _v) : x(_x), y(_y), direction(_d), value(_v) {}
            int x;
            int y;
            int direction;
            int value;
        };
        std::vector<std::vector<int>> input = file::readFileAsMap(path);
        unsigned long long sol = 0;
        std::vector<state> points;
        points.emplace_back(0, 0, -1, 0);
        std::vector<std::pair<int, int>> dir {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        std::vector<std::vector<std::array<bool, 4>>> visited(input.size(), std::vector<std::array<bool, 4>>(input[0].size(), {false, false, false, false}));
        std::vector<std::vector<std::array<int, 4>>> costs(input.size(), std::vector<std::array<int, 4>>(input[0].size(), {1000000, 1000000, 1000000, 1000000}));

        while (points.size() > 0) {
            std::pop_heap(points.begin(), points.end(),[](const auto& p1, const auto& p2) {
                return p1.value > p2.value;
            });
            state p = points.back();
            points.pop_back();
            if (p.x == input.size() - 1 && p.y == input[0].size() - 1) {
                return p.value;
            }

            if (p.direction >= 0 && visited[p.x][p.y][p.direction]) {
                continue;
            }
            if (p.direction >= 0) {
                visited[p.x][p.y][p.direction] = true;
            }
            for (int direction = 0; direction < dir.size(); ++direction) {
                if (direction == p.direction || (std::abs(dir[direction].first) == std::abs(dir[p.direction].first) &&
                        std::abs(dir[direction].second) == std::abs(dir[p.direction].second))) {
                    // we are going back
                    continue;
                }

                int extraCost = 0;
                for (int j = 0; j < maxDist; ++j) {
                    int x = p.x + dir[direction].first * (j + 1);
                    int y = p.y + dir[direction].second * (j + 1);
                    if (x >= 0 && x < input.size() && y >= 0 && y < input[0].size()) {
                        extraCost += input[x][y];
                        if (j < minDist - 1) continue;
                        if (costs[x][y][direction] == 1000000 || costs[x][y][direction] > p.value + extraCost) {
                            costs[x][y][direction] = p.value + extraCost;
                            points.emplace_back(x, y, direction, p.value + extraCost);
                            std::push_heap(points.begin(), points.end(),[](const auto& p1, const auto& p2) {
                                return p1.value > p2.value;
                            });
                        }
                    }
                }
            }
        }
    }

    unsigned long long part_1(std::string_view path) {
        return solve(path, 1, 3);
    }

    unsigned long long part_2(std::string_view path) {
        return solve(path, 4, 10);
    }
}

#ifdef TESTING
TEST(Tests2023Day17, part_1_test) {
    ASSERT_EQ(aoc2023_day17::part_1("../2023/day17/input_test.in"), 102);
}

TEST(Tests2023Day17, part_1_real_test) {
    ASSERT_EQ(aoc2023_day17::part_1("../2023/day17/input.in"), 758);
}

TEST(Tests2023Day17, part_2_test) {
    ASSERT_EQ(aoc2023_day17::part_2("../2023/day17/input_test.in"), 94);
}

TEST(Tests2023Day17, part_2_real_test) {
    ASSERT_EQ(aoc2023_day17::part_2("../2023/day17/input.in"), 892);
}
#endif

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2023_day17::part_1("../2023/day17/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2023_day17::part_2("../2023/day17/input.in") << std::endl;

    return 0;
}
#endif
