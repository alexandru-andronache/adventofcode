#include <direction.h>

#include "file.h"
#include "utilities.h"
#include "direction.h"
#include <iostream>
#include <set>

namespace aoc2024_day12 {
    int part_1(std::string_view path) {
        std::vector<std::vector<char>> map = file::readFileAsMapChar(path);
        std::set<utils::point> visited;
        int sol = 0;

        for (int i = 0; i < map.size(); ++i) {
            for (int j = 0; j < map[0].size(); ++j) {
                if (!visited.contains({i, j})) {
                    visited.insert({i, j});
                    int area = 0, perimeter = 0;
                    std::vector<utils::point> queue = {{i, j}};
                    while (!queue.empty()) {
                        std::vector<utils::point> newQueue;
                        for (const auto& point : queue) {
                            area++;
                            perimeter += 4;
                            if (point.x - 1 >= 0 && map[point.x - 1][point.y] == map[i][j]) {
                                perimeter--;
                                if (!visited.contains({point.x - 1, point.y})) {
                                    visited.insert({point.x - 1, point.y});
                                    newQueue.push_back({point.x - 1, point.y});
                                }
                            }
                            if (point.x + 1 < map.size() && map[point.x + 1][point.y] == map[i][j]) {
                                perimeter--;
                                if (!visited.contains({point.x + 1, point.y})) {
                                    visited.insert({point.x + 1, point.y});
                                    newQueue.push_back({point.x + 1, point.y});
                                }
                            }
                            if (point.y - 1 >= 0 && map[point.x][point.y - 1] == map[i][j]) {
                                perimeter--;
                                if (!visited.contains({point.x, point.y - 1})) {
                                    visited.insert({point.x, point.y - 1});
                                    newQueue.push_back({point.x, point.y - 1});
                                }
                            }
                            if (point.y + 1 < map[0].size() && map[point.x][point.y + 1] == map[i][j]) {
                                perimeter--;
                                if (!visited.contains({point.x, point.y + 1})) {
                                    visited.insert({point.x, point.y + 1});
                                    newQueue.push_back({point.x, point.y + 1});
                                }
                            }
                        }
                        queue = newQueue;
                    }
                    std::cout << map[i][j] << " " << area << " " << perimeter << std::endl;
                    sol += area * perimeter;
                }
            }
        }
        return sol;
    }

    int part_2(std::string_view path) {
        std::vector<std::vector<char>> map = file::readFileAsMapChar(path);
        std::set<utils::point> visited;
        int sol = 0;

        for (int i = 0; i < map.size(); ++i) {
            for (int j = 0; j < map[0].size(); ++j) {
                if (!visited.contains({i, j})) {
                    visited.insert({i, j});
                    int area = 0, corners = 0;
                    std::vector<utils::point> queue = {{i, j}};
                    while (!queue.empty()) {
                        std::vector<utils::point> newQueue;
                        for (const auto& point : queue) {
                            area++;
                            if (point.x - 1 >= 0 && map[point.x - 1][point.y] == map[i][j]) {
                                if (!visited.contains({point.x - 1, point.y})) {
                                    visited.insert({point.x - 1, point.y});
                                    newQueue.push_back({point.x - 1, point.y});
                                }
                            }
                            if (point.x + 1 < map.size() && map[point.x + 1][point.y] == map[i][j]) {
                                if (!visited.contains({point.x + 1, point.y})) {
                                    visited.insert({point.x + 1, point.y});
                                    newQueue.push_back({point.x + 1, point.y});
                                }
                            }
                            if (point.y - 1 >= 0 && map[point.x][point.y - 1] == map[i][j]) {
                                if (!visited.contains({point.x, point.y - 1})) {
                                    visited.insert({point.x, point.y - 1});
                                    newQueue.push_back({point.x, point.y - 1});
                                }
                            }
                            if (point.y + 1 < map[0].size() && map[point.x][point.y + 1] == map[i][j]) {
                                if (!visited.contains({point.x, point.y + 1})) {
                                    visited.insert({point.x, point.y + 1});
                                    newQueue.push_back({point.x, point.y + 1});
                                }
                            }
                            direction::Direction directions;
                            int neighbours = 0;
                            for (const auto& dir : directions.fullDirections) {
                                if (point.x + dir.x >= 0 && point.x + dir.x < map.size() &&
                                    point.y + dir.y >= 0 && point.y + dir.y < map[0].size() &&
                                    map[point.x + dir.x][point.y + dir.y] == map[i][j]) {
                                    neighbours++;
                                }
                            }
                            if (neighbours == 3 || neighbours == 4 || neighbours == 7) {
                                corners++;
                            }
                        }
                        queue = newQueue;
                    }
                    std::cout << map[i][j] << " " << area << " " << corners << std::endl;
                    sol += area * corners;
                }
            }
        }
        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2024_day12::part_1("../2024/day12/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2024_day12::part_2("../2024/day12/input.in") << std::endl;

    return 0;
}
#endif
