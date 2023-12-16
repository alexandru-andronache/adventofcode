#include "file.h"
#include <iostream>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2023_day16 {
    int solve(std::string_view path, int originalX, int originalY, int dir) {
        struct state{
            state() = default;
            state(int _x, int _y, int _d) : x(_x), y(_y), direction(_d) {}
            int x;
            int y;
            int direction; // left = 0, right = 1, up = 2, down = 3
        };
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::vector<bool>> visited(input.size(), std::vector<bool>(input[0].size(), false));
        std::vector<std::vector<std::array<int, 4>>> past(input.size(), std::vector<std::array<int, 4>>(input[0].size(), {0, 0, 0, 0}));
        std::vector<state> points;
        points.emplace_back(originalX, originalY, dir);
        while (!points.empty()) {
            std::vector<state> newPoints;

            for (const auto& p : points) {
                if ((p.direction == 0) && (p.y - 1 >= 0) && !past[p.x][p.y - 1][p.direction]) {
                    visited[p.x][p.y - 1] = true;
                    past[p.x][p.y - 1][p.direction] = true;
                    if (input[p.x][p.y - 1] == '.') {
                        newPoints.emplace_back(p.x, p.y - 1, p.direction);
                    }
                    else if (input[p.x][p.y - 1] == '-') {
                        newPoints.emplace_back(p.x, p.y - 1, p.direction);
                    }
                    else if (input[p.x][p.y - 1] == '/') {
                        newPoints.emplace_back(p.x, p.y - 1, 3);
                    }
                    else if (input[p.x][p.y - 1] == '\\') {
                        newPoints.emplace_back(p.x, p.y - 1, 2);
                    }
                    else if (input[p.x][p.y - 1] == '|') {
                        newPoints.emplace_back(p.x, p.y - 1, 3);
                        newPoints.emplace_back(p.x, p.y - 1, 2);
                    }
                }
                else if ((p.direction == 1) && (p.y + 1 < input[0].size()) && !past[p.x][p.y + 1][p.direction]) {
                    visited[p.x][p.y + 1] = true;
                    past[p.x][p.y + 1][p.direction] = true;
                    if (input[p.x][p.y + 1] == '.') {
                        newPoints.emplace_back(p.x, p.y + 1, p.direction);
                    }
                    else if (input[p.x][p.y + 1] == '-') {
                        newPoints.emplace_back(p.x, p.y + 1, p.direction);
                    }
                    else if (input[p.x][p.y + 1] == '/') {
                        newPoints.emplace_back(p.x, p.y + 1, 2);
                    }
                    else if (input[p.x][p.y + 1] == '\\') {
                        newPoints.emplace_back(p.x, p.y + 1, 3);
                    }
                    else if (input[p.x][p.y + 1] == '|') {
                        newPoints.emplace_back(p.x, p.y + 1, 3);
                        newPoints.emplace_back(p.x, p.y + 1, 2);
                    }
                }
                else if ((p.direction == 2) && (p.x - 1 >= 0) && !past[p.x - 1][p.y][p.direction]) {
                    visited[p.x - 1][p.y] = true;
                    past[p.x - 1][p.y][p.direction] = true;
                    if (input[p.x - 1][p.y] == '.') {
                        newPoints.emplace_back(p.x - 1, p.y, p.direction);
                    }
                    else if (input[p.x - 1][p.y] == '|') {
                        newPoints.emplace_back(p.x - 1, p.y, p.direction);
                    }
                    else if (input[p.x - 1][p.y] == '/') {
                        newPoints.emplace_back(p.x - 1, p.y, 1);
                    }
                    else if (input[p.x - 1][p.y] == '\\') {
                        newPoints.emplace_back(p.x - 1, p.y, 0);
                    }
                    else if (input[p.x - 1][p.y] == '-') {
                        newPoints.emplace_back(p.x - 1, p.y, 1);
                        newPoints.emplace_back(p.x - 1, p.y, 0);
                    }
                }
                else if ((p.direction == 3) && (p.x + 1 < input.size()) && !past[p.x + 1][p.y][p.direction]) {
                    visited[p.x + 1][p.y] = true;
                    past[p.x + 1][p.y][p.direction] = true;
                    if (input[p.x + 1][p.y] == '.') {
                        newPoints.emplace_back(p.x + 1, p.y, p.direction);
                    }
                    else if (input[p.x + 1][p.y] == '|') {
                        newPoints.emplace_back(p.x + 1, p.y, p.direction);
                    }
                    else if (input[p.x + 1][p.y] == '/') {
                        newPoints.emplace_back(p.x + 1, p.y, 0);
                    }
                    else if (input[p.x + 1][p.y] == '\\') {
                        newPoints.emplace_back(p.x + 1, p.y, 1);
                    }
                    else if (input[p.x + 1][p.y] == '-') {
                        newPoints.emplace_back(p.x + 1, p.y, 1);
                        newPoints.emplace_back(p.x + 1, p.y, 0);
                    }
                }
            }
            points = newPoints;
        }

        int sol = 0;
        for (int i = 0; i < visited.size(); ++i) {
            for (int j = 0; j < visited[0].size(); ++j) {
                sol += visited[i][j];
            }
        }

        return sol;
    }

    int part_1(std::string_view path) {
        return solve(path, 0, -1, 1);
    }

    int part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        int sol = 0;
        // UP
        for (int i = 0; i < input[0].size(); ++i) {
            int v = solve(path, -1, i, 3);
            sol = std::max(sol, v);
        }
        //LEFT
        for (int i = 0; i < input.size(); ++i) {
            int v = solve(path, i, -1, 0);
            sol = std::max(sol, v);
        }
        // DOWN
        for (int i = 0; i < input[0].size(); ++i) {
            int v = solve(path, input.size(), i, 2);
            sol = std::max(sol, v);
        }
        //RIGHT
        for (int i = 0; i < input.size(); ++i) {
            int v = solve(path, i, input[0].size(), 1);
            sol = std::max(sol, v);
        }

        return sol;
    }
}

#ifdef TESTING
TEST(Tests2023Day16, part_1_test) {
    ASSERT_EQ(aoc2023_day16::part_1("../2023/day16/input_test.in"), 46);
}

TEST(Tests2023Day16, part_1_real_test) {
    ASSERT_EQ(aoc2023_day16::part_1("../2023/day16/input.in"), 7074);
}

TEST(Tests2023Day16, part_2_test) {
    ASSERT_EQ(aoc2023_day16::part_2("../2023/day16/input_test.in"), 51);
}

TEST(Tests2023Day16, part_2_real_test) {
    ASSERT_EQ(aoc2023_day16::part_2("../2023/day16/input.in"), 7530);
}
#endif

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2023_day16::part_1("../2023/day16/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2023_day16::part_2("../2023/day16/input.in") << std::endl;

    return 0;
}
#endif
