#include "file.h"
#include "utilities.h"
#include <iostream>

namespace aoc2016_day22 {
    int part_1(std::string_view path) {
        std::vector<std::tuple<int, int, int, int>> input;
        for (const auto& line : file::readFileAsArrayString(path)) {
            std::vector<std::string> s = utils::splitString(line, " -T%xy");
            input.emplace_back(std::stoi(s[1]), std::stoi(s[2]), std::stoi(s[3]), std::stoi(s[4]));
        }

        int sol = 0;
        for (int i = 0; i < input.size(); ++i) {
            for (int j = 0; j < input.size(); ++j) {
                auto [x1, y1, size1, used1] = input[i];
                auto [x2, y2, size2, used2] = input[j];
                if (i != j && used1 != 0 && used1 <= size2 - used2) {
                    sol++;
                }
            }
        }

        return sol;
    }

    int part_2(std::string_view path) {
        std::vector<std::tuple<int, int, int, int>> input;
        for (const auto& line : file::readFileAsArrayString(path)) {
            std::vector<std::string> s = utils::splitString(line, " -T%xy");
            input.emplace_back(std::stoi(s[1]), std::stoi(s[2]), std::stoi(s[3]), std::stoi(s[4]));
        }

        const int sizeX = 26;
        const int sizeY = 38;
        std::vector<std::vector<std::pair<int, int>>> map(sizeX, std::vector<std::pair<int, int>>(sizeY, {0, 0}));
        for (const auto& line : input) {
            auto [x, y, size, used] = line;
            map[y][x] = {used, size};
        }

        // find the empty data
        int x0, y0, size;
        for (int i = 0; i < sizeX; ++i) {
            for (int j = 0; j < sizeY; ++j) {
                if (map[i][j].first == 0) {
                    x0 = i;
                    y0 = j;
                    size = map[i][j].second;
                }
            }
        }

        // find the line of positions which data can't be moved
        // assume the line is horizontal
        // this should be fixed also for vertical case

        int lineX = 0, lineY1 = 0, lineY2 = 0;
        for (int i = 0; i < sizeX; ++i) {
            for (int j = 0; j < sizeY; ++j) {
                if (map[i][j].first > size) {
                    lineX = i;
                    if (lineY1 == 0) {
                        lineY1 = j;
                    }
                    else {
                        lineY2 = j;
                    }
                }
            }
        }

        int sol = utils::manhattanDistance(x0, y0, lineX, lineY1 - 1) +
                utils::manhattanDistance(lineX, lineY1 - 1, 0, sizeY - 1);

        return sol + 5 * (sizeY - 2);
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2016_day22::part_1("../2016/day22/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2016_day22::part_2("../2016/day22/input.in") << std::endl;

    return 0;
}
#endif
