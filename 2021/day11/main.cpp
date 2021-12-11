#include "file.h"
#include "direction.h"
#include "utilities.h"
#include <iostream>
#include <vector>
#include <set>

namespace aoc2021_day11 {
    std::vector<std::vector<int>> map;
    std::set<std::pair<int, int>> explosions;
    int sol1 = 0;
    void calculate(int x, int y) {
        direction::Direction dir;
        for (const auto &d: dir.fullDirections) {
            if (x + d.x >= 0 && x + d.x < map.size() && y + d.y >= 0 && y + d.y < map[0].size()) {
                map[x + d.x][y + d.y]++;
                if (map[x + d.x][y + d.y] > 9 && explosions.count({x + d.x, y + d.y}) == 0) {
                    explosions.insert({x + d.x, y + d.y});
                    map[x + d.x][y + d.y] = 0;
                    sol1++;
                    calculate(x + d.x, y + d.y);
                }
            }
        }
    }
    int part_1(std::string_view path) {
        map = file::readFileAsMap(path);
        sol1 = 0;

        for (int step = 0; step < 100; ++step) {
            explosions.clear();
            for (int i = 0; i < map.size(); ++i) {
                for (int j = 0; j < map[i].size(); ++j) {
                    map[i][j]++;
                    if (map[i][j] > 9 && explosions.count({i, j}) == 0) {
                        explosions.insert({i, j});
                        map[i][j] = 0;
                        sol1++;
                        calculate(i, j);
                    }
                }
            }
            for (const auto& e : explosions) {
                map[e.first][e.second] = 0;
            }
        }
        return sol1;
    }

    int part_2(std::string_view path) {
        map = file::readFileAsMap(path);

        int step = 0;
        while (true) {
            step++;
            explosions.clear();
            for (int i = 0; i < map.size(); ++i) {
                for (int j = 0; j < map[i].size(); ++j) {
                    map[i][j]++;
                    if (map[i][j] > 9 && explosions.count({i, j}) == 0) {
                        explosions.insert({i, j});
                        map[i][j] = 0;
                        calculate(i, j);
                    }
                }
            }
            for (const auto& e : explosions) {
                map[e.first][e.second] = 0;
            }
            if (explosions.size() == 100) {
                return step;
            }
        }
    }
}
#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2021_day11::part_1("../2021/day11/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2021_day11::part_2("../2021/day11/input.in") << std::endl;

    return 0;
}
#endif
