#include "file.h"
#include "utilities.h"
#include "grid.h"
#include <iostream>
#include <algorithm>

namespace aoc2015_day18 {
    int part_1(std::string_view path, int steps) {
        std::vector<std::string> input = file::readFileAsArrayString(path);

        std::vector<std::vector<bool>> map(input.size(), std::vector<bool>(input[0].size(), false));
        for (int i = 0; i < input.size(); ++i) {
            for (int j = 0; j < input[0].size(); ++j) {
                map[i][j] = (input[i][j] == '#');
            }
        }

        for (int step = 0; step < steps; ++step) {
            std::vector<std::vector<bool>> t(input.size(), std::vector<bool>(input[0].size(), false));
            for (int i = 0; i < input.size(); ++i) {
                for (int j = 0; j < input[0].size(); ++j) {
                    t[i][j] = map[i][j];
                    if ((map[i][j] && (grid::numberOfNeighbors(map, i, j, true) != 2 && grid::numberOfNeighbors(map, i, j, true) != 3)) ||
                    (!map[i][j] && grid::numberOfNeighbors(map, i, j, true) == 3)) {
                        t[i][j] = !map[i][j];
                    }
                }
            }
            map = t;
        }
        int sol = 0;
        for (const auto& line : map) {
            sol += std::count(line.begin(), line.end(), true);
        }
        return sol;
    }

    int part_2(std::string_view path, int steps) {
        std::vector<std::string> input = file::readFileAsArrayString(path);

        std::vector<std::vector<bool>> map(input.size(), std::vector<bool>(input[0].size(), false));
        for (int i = 0; i < input.size(); ++i) {
            for (int j = 0; j < input[0].size(); ++j) {
                map[i][j] = (input[i][j] == '#');
            }
        }
        map[0][0] = map[0].back() = map.back()[0] = map.back().back() = true;

        for (int step = 0; step < steps; ++step) {
            std::vector<std::vector<bool>> t(input.size(), std::vector<bool>(input[0].size(), false));
            for (int i = 0; i < input.size(); ++i) {
                for (int j = 0; j < input[0].size(); ++j) {
                    t[i][j] = map[i][j];
                    if ((map[i][j] && (grid::numberOfNeighbors(map, i, j, true) != 2 && grid::numberOfNeighbors(map, i, j, true) != 3)) ||
                    (!map[i][j] && grid::numberOfNeighbors(map, i, j, true) == 3)) {
                        t[i][j] = !map[i][j];
                    }
                }
            }
            map = t;
            map[0][0] = map[0].back() = map.back()[0] = map.back().back() = true;
        }
        int sol = 0;
        for (const auto& line : map) {
            sol += std::count(line.begin(), line.end(), true);
        }
        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2015_day18::part_1("../2015/day18/input.in", 100) << std::endl;
    std::cout << "Part 2: " << aoc2015_day18::part_2("../2015/day18/input.in", 100) << std::endl;

    return 0;
}
#endif
