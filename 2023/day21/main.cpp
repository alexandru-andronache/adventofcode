#include "file.h"
#include "utilities.h"
#include "direction.h"
#include <iostream>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2023_day21 {
    unsigned long long part_1(std::string_view path, int steps) {
        unsigned long long sol = 0;
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::vector<int>> visited(input.size(), std::vector<int>(input[0].size(), 0));
        std::vector<std::vector<int>> newvisited(input.size(), std::vector<int>(input[0].size(), 0));
        std::pair<int, int> start = utils::findValue(input, 'S');
        std::vector<std::pair<int, int>> points{start};
        direction::Direction d;
        input[start.first][start.second] = '.';
        visited[start.first][start.second] = 1;
        for (int step = 0; step < steps; ++step) {
            std::vector<std::pair<int, int>> newPoints;
            std::vector<std::vector<int>> newvisited(input.size(), std::vector<int>(input[0].size(), 0));
            for (const auto& p : points) {
                std::vector<utils::point> po = utils::getListOfNeighbours4Directions2(p.first, p.second, input.size(), (int) input[0].size());
                for (const auto &x: po) {
                    if (input[x.x][x.y] == '.') {
                        if (newvisited[x.x][x.y] == 0) {
                            newPoints.push_back({x.x, x.y});
                        }
                        newvisited[x.x][x.y] = 1;
                    }
                }
            }
            points = newPoints;
            visited = newvisited;
        }

        for (int i = 0; i < visited.size(); ++i) {
            for (int j = 0; j < visited[0].size(); ++j) {
                if (visited[i][j] > 0) sol++;
            }
        }

        return sol;
    }

    int normalize(int x, int size) {
        x = x % size;
        if (x < 0) {
            x += size;
        }
        return x;
    }

    bool isPath(int x, int y, const std::vector<std::string>& input) {
        if (x < 0 || y < 0) {
            std::cout << "";
        }
        x = x % (int)input.size();
        if (x < 0) {
            x += input.size();
        }
        y = y % (int)input[0].size();
        if (y < 0) {
            y += input[0].size();
        }
        return input[x][y] == '.';
    }

    unsigned long long part_2(std::string_view path, int steps) {
        unsigned long long sol = 0;
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::pair<int, int> start = utils::findValue(input, 'S');
        std::vector<std::pair<int, int>> points{start};
        std::vector<std::vector<int>> visited(input.size(), std::vector<int>(input[0].size(), 0));
        direction::Direction d;
        input[start.first][start.second] = '.';
        std::vector<unsigned long long> prev;
        for (int step = 0; step < 65 + 131 * 2; ++step) {
            std::vector<std::pair<int, int>> newPoints;
            std::set<std::pair<int, int>> newV;
            std::vector<std::vector<int>> newvisited(input.size(), std::vector<int>(input[0].size(), 0));
            for (const auto &p: points) {
                std::vector<utils::point> po = d.directions;
                for (const auto &x: po) {
                    if (isPath(x.x + p.first, x.y + p.second, input)) {
                        if (!newV.contains({x.x + p.first, x.y + p.second})) {
                            newPoints.push_back({x.x + p.first, x.y + p.second});
                        }
                        newV.insert({x.x + p.first, x.y + p.second});
                    }
                }
            }
            points = newPoints;
            prev.push_back(newV.size());
        }

        // solve quadratic equation
        long long c = (long long)prev[64];
        long long y = (long long)prev[64 + 131] - c;
        long long x = (long long)prev[64 + 131 + 131]- c;
        long long z = x - (2 * y);
        long long a = z / 2;
        long long b = y - a;
        long long rep = steps / 131;

        return a * (rep * rep) + b * rep + c;
    }
}

#ifdef TESTING
TEST(Tests2023Day21, part_1_test) {
    ASSERT_EQ(aoc2023_day21::part_1("../2023/day21/input_test.in", 6), 16);
}

TEST(Tests2023Day21, part_1_real_test) {
    ASSERT_EQ(aoc2023_day21::part_1("../2023/day21/input.in", 64), 3591);
}

//TEST(Tests2023Day21, part_2_test) {
//    ASSERT_EQ(aoc2023_day21::part_2("../2023/day21/input_test.in", 6), 16);
//}
//
//TEST(Tests2023Day21, part_2_test_2) {
//    ASSERT_EQ(aoc2023_day21::part_2("../2023/day21/input_test.in", 10), 50);
//}

//TEST(Tests2023Day21, part_2_test_3) {
//    ASSERT_EQ(aoc2023_day21::part_2("../2023/day21/input_test.in", 50), 1594);
//}

//TEST(Tests2023Day21, part_2_test_4) {
//    ASSERT_EQ(aoc2023_day21::part_2("../2023/day21/input.in", 65), 3726);
//}
//
//TEST(Tests2023Day21, part_2_test_5) {
//    ASSERT_EQ(aoc2023_day21::part_2("../2023/day21/input.in", 65 + 131), 33086);
//}
//
//TEST(Tests2023Day21, part_2_test_6) {
//    ASSERT_EQ(aoc2023_day21::part_2("../2023/day21/input.in", 65 + 131 + 131), 91672);
//}

//TEST(Tests2023Day21, part_2_test_4) {
//    ASSERT_EQ(aoc2023_day21::part_2("../2023/day21/input_test.in", 5000), 16733044);
//}

TEST(Tests2023Day21, part_2_real_test) {
    ASSERT_EQ(aoc2023_day21::part_2("../2023/day21/input.in", 26501365), 598044246091826);
}
#endif

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2023_day21::part_1("../2023/day21/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2023_day21::part_2("../2023/day21/input.in") << std::endl;

    return 0;
}
#endif
