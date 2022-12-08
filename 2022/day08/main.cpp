#include "file.h"
#include "utilities.h"
#include "direction.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

namespace aoc2022_day08 {

    bool isSolPart1(const std::vector<std::vector<int>>& map, int i, int j) {
        direction::Direction dir;
        for (const auto& d : dir.directions) {
            int x = i, y = j;
            bool sol = true;
            while (x + d.x >= 0 && x + d.x < map.size() && y + d.y >= 0 && y + d.y < map[0].size()) {
                if (map[x + d.x][y + d.y] >= map[i][j]) {
                    sol = false;
                }
                x += d.x;
                y += d.y;
            }
            if (sol) {
                return true;
            }
        }
        return false;
    }

    long long calculatePart2(const std::vector<std::vector<int>>& map, int i, int j) {
        long long s = 1;
        direction::Direction dir;
        for (const auto& d : dir.directions) {
            int x = i, y = j;
            int nr = 0;
            while (x + d.x >= 0 && x + d.x < map.size() &&
                   y + d.y >= 0 && y + d.y < map[0].size() &&
                   map[i][j] > map[x + d.x][y + d.y]) {
                nr++;
                x += d.x;
                y += d.y;
            }
            if (x + d.x >= 0 && x + d.x < map.size() &&
                y + d.y >= 0 && y + d.y < map[0].size()) {
                nr++;
            }
            s = s * nr;
        }
        return s;
    }

    int part_1(std::string_view path) {
        std::vector<std::vector<int>> input = file::readFileAsMap(path);
        int s = 0;
        for (int i = 0; i < input.size(); ++i) {
            for (int j = 0; j < input[i].size(); ++j) {
                s += isSolPart1(input, i, j);
            }
        }
        return s;
    }

    long long part_2(std::string_view path) {
        std::vector<std::vector<int>> input = file::readFileAsMap(path);
        long long s = 0;
        for (int i = 0; i < input.size(); ++i) {
            for (int j = 0; j < input[0].size(); ++j) {
                s = std::max(s, calculatePart2(input, i, j));
            }
        }
        return s;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2022_day08::part_1("../2022/day08/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2022_day08::part_2("../2022/day08/input.in") << std::endl;

    return 0;
}
#endif
