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
        std::vector<utils::point> neighbours = utils::getListOfNeighboursAllDirections(x, y, map);
        for (const auto& n : neighbours) {
            map[n.x][n.y]++;
            if (map[n.x][n.y] > 9 && explosions.count({n.x, n.y}) == 0) {
                explosions.insert({n.x, n.y});
                map[n.x][n.y] = 0;
                sol1++;
                calculate(n.x, n.y);
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
