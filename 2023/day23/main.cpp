#include "file.h"
#include "utilities.h"
#include "direction.h"
#include <iostream>
#include <set>
#include <queue>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2023_day23 {

    struct edge {
        int x, y;
        int d;
    };

    int dfs(int x, int y, int px, int py, const std::vector<std::string>& input, int steps) {
        int sol = steps;
        direction::Direction d;
        std::map<char, utils::point> mapping {{'^', {-1, 0}},
                                              {'v', {1, 0}},
                                              {'<', {0, -1}},
                                              {'>', {0, 1}}};

        for (const auto& p : d.directions) {
            int nx = x + p.x, ny = y + p.y;
            if (nx < 0 || ny < 0 || nx >= input.size() || ny >= input[0].size()) continue;
            if (input[nx][ny] == '#') continue;
            if (mapping.contains(input[x][y]) &&
                (mapping[input[x][y]].x != p.x || mapping[input[x][y]].y != p.y))
                continue;
            if (nx == px && ny == py) continue;
            steps++;
            sol = std::max(dfs(nx, ny, x, y, input, steps), sol);
            steps--;
        }

        return sol;
    }

    void dfs_part_2(int x, int y, int px, int py,
                    int sx, int sy, int d,
                    const std::vector<std::string>& input,
                    const std::set<std::pair<int, int>>& candidates,
                    std::vector<std::vector<std::vector<edge>>>& adj) {
        direction::Direction d1;
        if (candidates.count({x, y}) && (x != sx || y != sy)) {
            adj[sx][sy].push_back({x, y, d});
            return;
        }
        for (const auto& p : d1.directions) {
            int nx = x + p.x, ny = y + p.y;
            if (nx < 0 || ny < 0 || nx >= input.size() || ny >= input[0].size()) continue;
            if (input[nx][ny] == '#') continue;
            if (nx == px && ny == py) continue;
            dfs_part_2(nx, ny, x, y, sx, sy, d + 1, input, candidates, adj);
        }
    }

    int solve_part_2(int x, int y, int sizeX, int sizeY,
                      std::vector<std::vector<int>>& visited, int steps,
                      const std::vector<std::vector<std::vector<edge>>>& adj) {
        int sol = 0;
        if (x == sizeX - 1 && y == sizeY - 2) {
            return steps;
        }
        visited[x][y] = 1;
        for (const auto& a : adj[x][y]) {
            if (visited[a.x][a.y]) continue;
            steps += a.d;
            sol = std::max(sol, solve_part_2(a.x, a.y, sizeX, sizeY, visited, steps, adj));
            steps -= a.d;
        }
        visited[x][y] = 0;
        return sol;
    }

    int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);

        return dfs(0, 1, 0, 0, input, 0);
    }

    int part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        direction::Direction d;

        std::set<std::pair<int, int>> candidates {{0, 1}, {input.size() - 1, input[0].size() - 2}};
        for (int x = 0; x < input.size(); ++x) {
            for (int y = 0; y < input[0].size(); ++y) {
                if (input[x][y] == '#') continue;
                int free_neighbours = 0;
                for (int dir = 0; dir < 4; ++dir) {
                    int nx = x + d.directions[dir].x, ny = y + d.directions[dir].y;
                    if (nx < 0 || ny < 0 || nx >= input.size() || ny >= input[0].size()) continue;
                    if (input[nx][ny] == '#') continue;
                    free_neighbours++;
                }
                if (free_neighbours >= 3) {
                    candidates.insert({x, y});
                }
            }
        }

        std::vector<std::vector<std::vector<edge>>> adj(input.size(), std::vector<std::vector<edge>>(input[0].size()));
        for (auto [x, y] : candidates) {
            dfs_part_2(x, y, x, y, x, y, 0, input, candidates, adj);
        }

        std::vector<std::vector<int>> visited(input.size(), std::vector<int>(input.size(), 0));
        return solve_part_2(0, 1, input.size(), input[0].size(), visited, 0, adj);
    }
}

#ifdef TESTING
TEST(Tests2023Day23, part_1_test) {
    ASSERT_EQ(aoc2023_day23::part_1("../2023/day23/input_test.in"), 94);
}

TEST(Tests2023Day23, part_1_real_test) {
    ASSERT_EQ(aoc2023_day23::part_1("../2023/day23/input.in"), 2050);
}

TEST(Tests2023Day23, part_2_test) {
    ASSERT_EQ(aoc2023_day23::part_2("../2023/day23/input_test.in"), 154);
}

TEST(Tests2023Day23, part_2_real_test) {
    ASSERT_EQ(aoc2023_day23::part_2("../2023/day23/input.in"), 6262);
}
#endif

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2023_day23::part_1("../2023/day23/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2023_day23::part_2("../2023/day23/input.in") << std::endl;

    return 0;
}
#endif
