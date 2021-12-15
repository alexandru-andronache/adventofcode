#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>

namespace aoc2021_day15 {
    int solve(int startX, int startY, int endX, int endY, const std::vector<std::vector<int>>& map, int extra) {
        std::vector<std::vector<int>> risk(map.size(), std::vector<int>(map[0].size(), std::numeric_limits<int>::max()));
        risk[startX][startY] = 0;

        std::vector<utils::point> positions {{startX, startY}};
        while (!positions.empty()) {
            std::vector<utils::point> newPositions;
            for (const auto& position : positions) {
                std::vector<utils::point> neighbours = utils::getListOfNeighbours4Directions(position.x, position.y, map);
                for (const auto& n : neighbours) {
                    if (risk[position.x][position.y] + map[n.x][n.y] + extra < risk[n.x][n.y]) {
                        risk[n.x][n.y] = risk[position.x][position.y] + map[n.x][n.y] + extra;
                        newPositions.push_back({n.x, n.y});
                    }
                }
            }
            positions = newPositions;
        }

        return risk[endX][endY];
    }

    int part_1(std::string_view path) {
        std::vector<std::vector<int>> map = file::readFileAsMap(path);
        return solve(0, 0, map.size() - 1, map[0].size() - 1, map, 0);
    }

    int part_2(std::string_view path) {
        std::vector<std::vector<int>> map = file::readFileAsMap(path);
        std::vector<std::vector<int>> newMap;
        int x = map.size();
        int y = map[0].size();
        for (int i = 0; i < x * 5; ++i) {
            std::vector<int> line;
            for (int j = 0; j < y * 5; ++j) {
                int val = (map[i % x][j % y] + i / x + j / y);
                if (val > 9) {
                    val = val % 9;
                }
                line.push_back(val);
            }
            newMap.push_back(line);
        }
        map = newMap;
        std::vector<std::vector<int>> risk(map.size(), std::vector<int>(map[0].size(), std::numeric_limits<int>::max()));
        risk[0][0] = 0;

        std::vector<utils::point> positions {{0, 0}};
        while (!positions.empty()) {
            std::vector<utils::point> newPositions;
            for (const auto& position : positions) {
                std::vector<utils::point> neighbours = utils::getListOfNeighbours4Directions(position.x, position.y, map);
                for (const auto& n : neighbours) {
                    if (risk[position.x][position.y] + map[n.x][n.y] < risk[n.x][n.y]) {
                        risk[n.x][n.y] = risk[position.x][position.y] + map[n.x][n.y];
                        newPositions.push_back({n.x, n.y});
                    }
                }
            }
            positions = newPositions;
        }

        return risk.back().back();
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2021_day15::part_1("../2021/day15/input.in") << std::endl;
    std::cout << "Part 1: " << aoc2021_day15::part_2("../2021/day15/input.in") << std::endl;

    return 0;
}
#endif
