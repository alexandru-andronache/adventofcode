#include "file.h"
#include <iostream>
#include <direction.h>
#include <vector>

namespace aoc2021_day09 {
    int part_1(std::string_view path) {
        std::vector<std::vector<int>> map = file::readFileAsMap(path);

        int risk = 0;

        direction::Direction dir;
        for (int i = 0; i < map.size(); ++i) {
            for (int j = 0; j < map[0].size(); ++j) {
                bool found = true;
                for (const auto& d : dir.directions) {
                    if (i + d.x >= 0 && i + d.x < map.size() && j + d.y >= 0 && j + d.y < map[0].size() &&
                        map[i][j] >= map[i + d.x][j + d.y]) {
                        found = false;
                    }
                }
                if (found) {
                    risk += 1 + map[i][j];
                }
            }
        }

        return risk;
    }

    int part_2(std::string_view path) {
        std::vector<std::vector<int>> map = file::readFileAsMap(path);

        direction::Direction dir;
        std::vector<int> basins;
        for (int i = 0; i < map.size(); ++i) {
            for (int j = 0; j < map[0].size(); ++j) {
                bool found = true;
                for (const auto& d : dir.directions) {
                    if (i + d.x >= 0 && i + d.x < map.size() && j + d.y >= 0 && j + d.y < map[0].size() &&
                        map[i][j] >= map[i + d.x][j + d.y]) {
                        found = false;
                    }
                }
                if (found) {
                    std::vector<std::vector<bool>> visited(map.size(), std::vector<bool>(map[0].size(), false));
                    std::vector<std::pair<int, int>> points {{i, j}};
                    map[i][j] = true;
                    while (!points.empty()) {
                        std::vector<std::pair<int, int>> newPoints;
                        for (const auto& p : points) {
                            for (const auto& d : dir.directions) {
                                if (p.first + d.x >= 0 && p.first + d.x < map.size() && p.second + d.y >= 0 && p.second + d.y < map[0].size() &&
                                    !visited[p.first + d.x][p.second + d.y] && map[p.first + d.x][p.second + d.y] != 9) {
                                    newPoints.emplace_back(p.first + d.x, p.second + d.y);
                                    visited[p.first + d.x][p.second + d.y] = true;
                                }
                            }
                        }
                        points = newPoints;
                    }
                    int nr = 0;
                    for (const auto& line : visited) {
                        nr += std::count(line.begin(), line.end(), true);
                    }
                    basins.push_back(nr);
                }
            }
        }

        std::sort(basins.begin(), basins.end(), std::greater<int>());

        return basins[0] * basins[1] * basins[2];
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2021_day09::part_1("../2021/day09/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2021_day09::part_2("../2021/day09/input.in") << std::endl;

    return 0;
}
#endif
