#include "file.h"
#include "utilities.h"
#include "direction.h"
#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <numeric>
#include <limits>

namespace aoc2022_day12 {
    int solve(const std::vector<std::string>& in, int sx, int sy, int ex, int ey) {
        std::vector<std::vector<int>> p(in.size(), std::vector<int>(in[0].size(), 0));
        direction::Direction dir;

        std::vector<std::pair<int, int>> nr;
        nr.push_back({sx, sy});
        while (nr.size() > 0) {
            std::vector<std::pair<int, int>> t;
            for (const auto& n : nr) {
                for (const auto& d : dir.directions) {
                    if (n.first + d.x >= 0 && n.first + d.x < in.size() && n.second + d.y >= 0 && n.second + d.y < in[0].size()) {
                        if (in[n.first + d.x][n.second + d.y] - in[n.first][n.second] <= 1) {
                            if (p[n.first + d.x][n.second + d.y] == 0 ||
                                p[n.first + d.x][n.second + d.y] > p[n.first][n.second] + 1) {
                                p[n.first + d.x][n.second + d.y] = p[n.first][n.second] + 1;
                                t.emplace_back(n.first + d.x, n.second + d.y);
                            }
                        }
                    }
                }
            }
            nr = t;
        }

        return p[ex][ey];
    }

    int part_1(std::string_view path) {
        std::vector<std::string> in = file::readFileAsArrayString(path);

        int sX = 0, sY = 0, ex, ey = 0;
        for (int i = 0; i < in.size(); ++i) {
            for (int j = 0; j < in[0].size(); ++j) {
                if (in[i][j] == 'S') {
                    sX = i;
                    sY = j;
                }
                else if (in[i][j] == 'E') {
                    ex = i;
                    ey = j;
                }
            }
        }
        in[sX][sY] = 'a';
        in[ex][ey] = 'z';

        return solve(in, sX, sY, ex, ey);
    }

    int part_2(std::string_view path) {
        std::vector<std::string> in = file::readFileAsArrayString(path);

        int sX = 0, sY = 0, ex, ey = 0;
        for (int i = 0; i < in.size(); ++i) {
            for (int j = 0; j < in[0].size(); ++j) {
                if (in[i][j] == 'S') {
                    sX = i;
                    sY = j;
                }
                else if (in[i][j] == 'E') {
                    ex = i;
                    ey = j;
                }
            }
        }
        in[sX][sY] = 'a';
        in[ex][ey] = 'z';

        int min = 10000;
        for (int i = 0; i < in.size(); ++i) {
            for (int j = 0; j < in[0].size(); ++j) {
                if (in[i][j] == 'a') {
                    int x = solve(in, i, j, ex, ey);
                    if (x > 0)
                        min = std::min(min, x);
                }
            }
        }

        return min;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2022_day12::part_1("../2022/day12/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2022_day12::part_2("../2022/day12/input.in") << std::endl;

    return 0;
}
#endif
