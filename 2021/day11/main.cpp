#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>
#include <set>

namespace aoc2021_day11 {

    int part_1(std::string_view path, int steps = 100) {
        std::vector<std::vector<int>> map = file::readFileAsMap(path);
        std::set<std::pair<int, int>> explosions;
        int sol = 0;

        for (int step = 0; step < steps; ++step) {
            explosions.clear();
            for (int i = 0; i < map.size(); ++i) {
                for (int j = 0; j < map[i].size(); ++j) {
                    map[i][j]++;
                    if (map[i][j] > 9 && explosions.count({i, j}) == 0) {
                        explosions.insert({i, j});
                        std::vector<utils::point> flash {{i, j}};
                        while (!flash.empty()) {
                            std::vector<utils::point> newFlash;
                            for (const auto& f : flash) {
                                map[f.x][f.y] = 0;
                                sol++;
                                std::vector<utils::point> neighbours = utils::getListOfNeighboursAllDirections(f.x, f.y, map);
                                for (const auto& n : neighbours) {
                                    map[n.x][n.y]++;
                                    if (map[n.x][n.y] > 9 && explosions.count({n.x, n.y}) == 0) {
                                        explosions.insert({n.x, n.y});
                                        newFlash.push_back({n.x, n.y});
                                    }
                                }
                            }
                            flash = newFlash;
                        }
                    }
                }
            }
            for (const auto& e : explosions) {
                map[e.first][e.second] = 0;
            }
        }
        return sol;
    }

    int part_2(std::string_view path) {
        std::vector<std::vector<int>> map = file::readFileAsMap(path);
        std::set<std::pair<int, int>> explosions;
        int step = 0;

        while (true) {
            explosions.clear();
            for (int i = 0; i < map.size(); ++i) {
                for (int j = 0; j < map[i].size(); ++j) {
                    map[i][j]++;
                    if (map[i][j] > 9 && explosions.count({i, j}) == 0) {
                        explosions.insert({i, j});
                        std::vector<utils::point> flash {{i, j}};
                        while (!flash.empty()) {
                            std::vector<utils::point> newFlash;
                            for (const auto& f : flash) {
                                map[f.x][f.y] = 0;
                                std::vector<utils::point> neighbours = utils::getListOfNeighboursAllDirections(f.x, f.y, map);
                                for (const auto& n : neighbours) {
                                    map[n.x][n.y]++;
                                    if (map[n.x][n.y] > 9 && explosions.count({n.x, n.y}) == 0) {
                                        explosions.insert({n.x, n.y});
                                        newFlash.push_back({n.x, n.y});
                                    }
                                }
                            }
                            flash = newFlash;
                        }
                    }
                }
            }
            for (const auto& e : explosions) {
                map[e.first][e.second] = 0;
            }
            step++;
            if (explosions.size() == map.size() * map[0].size()) {
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
