#include "file.h"
#include "utilities.h"
#include <iostream>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2024_day20 {
    int solve(std::string_view path, int nr_min_cheats, int max_cheat) {
        constexpr int WALL = -1;
        utils::point start{0, 0}, end{0, 0};
        std::vector<std::vector<char>> input = file::readFileAsMapChar(path);
        std::vector<std::vector<int>> map(input.size(), std::vector<int>(input[0].size(), 0));
        std::vector<utils::point> points;
        int sol = 0;

        for (int i = 0; i < input.size(); i++) {
            for (int j = 0; j < input[i].size(); j++) {
                if (input[i][j] == '#') {
                    map[i][j] = WALL;
                }
                else if (input[i][j] == 'S') {
                    start = {i, j};
                }
                else if (input[i][j] == 'E') {
                    end = {i, j};
                }
            }
        }

        utils::point current = start;
        int steps = 0;
        map[start.x][start.y] = ++steps;
        points.emplace_back(start.x, start.y);
        std::vector<utils::point> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        while (current != end) {
            for (const auto& dir : directions) {
                if (current.x + dir.x >= 0 && current.x + dir.x < map.size() &&
                    current.y + dir.y >= 0 && current.y + dir.y < map[0].size() &&
                    map[current.x + dir.x][current.y + dir.y] == 0) {
                    current.x += dir.x;
                    current.y += dir.y;
                    map[current.x][current.y] = ++steps;
                    points.emplace_back(current.x, current.y);
                    break;
                    }
            }
        }

        for (int i = 0; i < points.size(); ++i) {
            for (int j = i + nr_min_cheats - max_cheat; j < points.size(); ++j) {
                int dist = utils::manhattanDistance(points[i].x, points[i].y, points[j].x, points[j].y);
                if (dist <= max_cheat && j - i - dist >= nr_min_cheats) {
                    sol++;
                }
            }
        }
        return sol;
    }

    int savedSteps(const std::vector<std::vector<int>>& map, int x, int y) {
        int max = 0;
        if (x + 1 < map.size() && x - 1 >= 0) {
            if (map[x + 1][y] != -1 && map[x - 1][y] != -1) {
                max = std::max(max, std::abs(map[x + 1][y] - map[x - 1][y]));
            }
        }
        if (y + 1 < map[0].size() && y - 1 >= 0) {
            if (map[x][y + 1] != -1 && map[x][y - 1] != -1) {
                max = std::max(max, std::abs(map[x][y + 1] - map[x][y - 1]));
            }
        }
        return max;
    }
    int part_1(std::string_view path, int nr_min_cheats = 100) {
        // return solve(path, nr_min_cheats, 2);
        constexpr int WALL = -1;
        utils::point start{0, 0}, end{0, 0};
        std::vector<std::vector<char>> input = file::readFileAsMapChar(path);
        std::vector<std::vector<int>> map(input.size(), std::vector<int>(input[0].size(), 0));
        int sol = 0;

        for (int i = 0; i < input.size(); i++) {
            for (int j = 0; j < input[i].size(); j++) {
                if (input[i][j] == '#') {
                    map[i][j] = WALL;
                }
                else if (input[i][j] == 'S') {
                    start = {i, j};
                }
                else if (input[i][j] == 'E') {
                    end = {i, j};
                }
            }
        }

        utils::point current = start;
        int steps = 0;
        map[start.x][start.y] = ++steps;
        std::vector<utils::point> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        while (current != end) {
            for (const auto& dir : directions) {
                if (current.x + dir.x >= 0 && current.x + dir.x < map.size() &&
                    current.y + dir.y >= 0 && current.y + dir.y < map[0].size() &&
                    map[current.x + dir.x][current.y + dir.y] == 0) {
                    current.x += dir.x;
                    current.y += dir.y;
                    map[current.x][current.y] = ++steps;
                    break;
                }
            }
        }

        for (int i = 0; i < map.size(); ++i) {
            for (int j = 0; j < map[0].size(); ++j) {
                if (map[i][j] == WALL) {
                    int saved = savedSteps(map, i, j) - 2;
                    if (saved >= nr_min_cheats) {
                        sol++;
                    }
                }
            }
        }

        return sol;
    }

    int part_2(std::string_view path, int nr_min_cheats = 100) {
        return solve(path, nr_min_cheats, 20);
    }

}

#ifdef TESTING
namespace aoc2024_day20 {
    TEST(Tests2024Day20, part_1_test) {
        ASSERT_EQ(part_1("../2024/day20/input_test.in", 40), 1 + 1);
    }

    TEST(Tests2024Day20, part_1_real_test) {
        ASSERT_EQ(part_1("../2024/day20/input.in"), 1454);
    }

    TEST(Tests2024Day20, part_2_test) {
        ASSERT_EQ(part_2("../2024/day20/input_test.in", 74), 4 + 3);
    }

    TEST(Tests2024Day20, part_2_test_2) {
        ASSERT_EQ(part_2("../2024/day20/input_test.in", 72), 4 + 3 + 22);
    }

    TEST(Tests2024Day20, part_2_real_test) {
        ASSERT_EQ(part_2("../2024/day20/input.in"), 997879);
    }
}
#endif

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2024_day20::part_1("../2024/day20/input_test.in", 40) << std::endl;
    std::cout << "Part 2: " << aoc2024_day20::part_2("../2024/day20/input.in") << std::endl;

    return 0;
}
#endif
