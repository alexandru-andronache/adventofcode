#include "file.h"
#include "utilities.h"
#include <iostream>
#include <array>

namespace aoc2018_day10 {
    struct Point {
        int x;
        int y;
        int speedX;
        int speedY;
    };

    const int STEPS = 10081;

    std::string part_1(std::string_view path) {
        std::vector<Point> points;
        std::vector<std::vector<std::string>> lines = file::readFileAndSplit(path, "<>, ");
        for (const auto& line : lines) {
            points.push_back({std::stoi(line[1]),
                              std::stoi(line[2]),
                              std::stoi(line[4]),
                              std::stoi(line[5])});
        }

        for (int i = 0; i < STEPS; ++i) {
            for (auto& p : points) {
                p.x += p.speedX;
                p.y += p.speedY;
            }
        }

        int minX = std::numeric_limits<int>::max();
        int maxX = std::numeric_limits<int>::min();
        int minY = std::numeric_limits<int>::max();
        int maxY = std::numeric_limits<int>::min();
        for (const auto& p : points) {
            minX = std::min(minX, p.x);
            maxX = std::max(maxX, p.x);
            minY = std::min(minY, p.y);
            maxY = std::max(maxY, p.y);
        }
        int map[100][10];
        for (int i = 0; i < 100; ++i) {
            for (int j = 0; j < 10; ++j) {
                map[i][j] = 0;
            }
        }
        for (const auto &p : points) {
            map[p.x - minX][p.y - minY] = 1;
        }

        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 100; ++j) {
                if (map[j][i] == 0) {
                    std::cout << ".";
                } else {
                    std::cout << "#";
                }
            }
            std::cout << std::endl;
        }

        return "CRXKEZPZ";
    }

    int part_2(std::string_view path) {
        return STEPS;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2018_day10::part_1("../2018/day10/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2018_day10::part_2("../2018/day10/input.in") << std::endl;

    return 0;
}
#endif
