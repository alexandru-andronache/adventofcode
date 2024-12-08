#include "file.h"
#include <iostream>
#include <utilities.h>
#include <map>
#include <numeric>

namespace aoc2024_day08 {
    unsigned long long part_1(std::string_view path) {
        unsigned long long sol = 0;
        std::vector<std::vector<char>> grid = file::readFileAsMapChar(path);
        std::vector<std::vector<bool>> final(grid.size(), std::vector<bool>(grid[0].size(), false));

        std::map<char, std::vector<utils::point>> portals;

        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                if (grid[i][j] != '.') {
                    portals[grid[i][j]].emplace_back(i, j);
                }
            }
        }

        for (const auto& [_, value] : portals) {
            for (int i = 0; i < value.size() - 1; ++i) {
                for (int j = i + 1; j < value.size(); ++j) {
                    int dx = abs(value[i].x - value[j].x);
                    int dy = abs(value[i].y - value[j].y);

                    if (value[i].y < value[j].y) {
                        if (value[i].x - dx >= 0 && value[i].y - dy >= 0) {
                            final[value[i].x - dx][value[i].y - dy] = true;
                        }
                        if (value[j].x + dx < grid.size() && value[j].y + dy < final[0].size()) {
                            final[value[j].x + dx][value[j].y + dy] = true;
                        }
                    }
                    else {
                        if (value[i].x - dx >= 0 && value[i].y + dy < final[0].size()) {
                            final[value[i].x - dx][value[i].y + dy] = true;
                        }
                        if (value[j].x + dx < grid.size() && value[j].y - dy >= 0) {
                            final[value[j].x + dx][value[j].y - dy] = true;
                        }
                    }
                }
            }
        }

        sol = std::accumulate(final.begin(), final.end(), 0, [](const int acc, const std::vector<bool>& vec) {
            return acc + std::ranges::count(vec, true);
        });

        return sol;
    }

    unsigned long long part_2(std::string_view path) {
        unsigned long long sol = 0;
        std::vector<std::vector<char>> grid = file::readFileAsMapChar(path);
        std::vector<std::vector<bool>> final(grid.size(), std::vector<bool>(grid[0].size(), false));

        std::map<char, std::vector<utils::point>> portals;

        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                if (grid[i][j] != '.') {
                    portals[grid[i][j]].emplace_back(i, j);
                }
            }
        }

        for (const auto& [_, value] : portals) {
            for (int i = 0; i < value.size() - 1; ++i) {
                for (int j = i + 1; j < value.size(); ++j) {
                    for (int k = 1; k < grid.size(); ++k) {
                        int dx = abs(value[i].x - value[j].x) * k;
                        int dy = abs(value[i].y - value[j].y) * k;
                        if (value[i].y < value[j].y) {
                            if (value[i].x - dx >= 0 && value[i].y - dy >= 0) {
                                final[value[i].x - dx][value[i].y - dy] = true;
                            }
                            if (value[j].x + dx < grid.size() && value[j].y + dy < final[0].size()) {
                                final[value[j].x + dx][value[j].y + dy] = true;
                            }
                        }
                        else {
                            if (value[i].x - dx >= 0 && value[i].y + dy < final[0].size()) {
                                final[value[i].x - dx][value[i].y + dy] = true;
                            }
                            if (value[j].x + dx < grid.size() && value[j].y - dy >= 0) {
                                final[value[j].x + dx][value[j].y - dy] = true;
                            }
                        }
                    }
                }
            }
        }

        for (const auto& [_, value] : portals) {
            if (value.size() > 1) {
                for (const auto& point : value) {
                    final[point.x][point.y] = true;
                }
            }
        }

        sol = std::accumulate(final.begin(), final.end(), 0, [](const int acc, const std::vector<bool>& vec) {
            return acc + std::ranges::count(vec, true);
        });

        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2024_day08::part_1("../2024/day08/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2024_day08::part_2("../2024/day08/input.in") << std::endl;

    return 0;
}
#endif
