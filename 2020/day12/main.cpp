#include "file.h"
#include "utilities.h"
#include <iostream>
#include <set>

namespace aoc2020_day12 {
    int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        int startX = 0, startY = 0;
        std::vector<char> directions{'N', 'E', 'S', 'W'};
        int dir = 1;
        for (const auto &line : input) {
            int nr = std::stoi(line.substr(1));
            if (line[0] == 'R') {
                dir = (dir + nr / 90) % 4;
            } else if (line[0] == 'L') {
                dir = (dir - nr / 90 + 4) % 4;
            } else if (line[0] == 'N') {
                startX += nr;
            } else if (line[0] == 'S') {
                startX -= nr;
            } else if (line[0] == 'E') {
                startY += nr;
            } else if (line[0] == 'W') {
                startY -= nr;
            } else if (line[0] == 'F') {
                if (dir == 0) {
                    startX += nr;
                } else if (dir == 2) {
                    startX -= nr;
                } else if (dir == 1) {
                    startY += nr;
                } else if (dir == 3) {
                    startY -= nr;
                }
            }
        }
        return std::abs(startX) + std::abs(startY);
    }

    int part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        int startX = 0, startY = 0;
        int waypointX = 1, waypointY = 10;
        for (const auto &line : input) {
            int nr = std::stoi(line.substr(1));
            if (line[0] == 'F') {
                startX += nr * waypointX;
                startY += nr * waypointY;
            } else if (line[0] == 'N') {
                waypointX += nr;
            } else if (line[0] == 'S') {
                waypointX -= nr;
            } else if (line[0] == 'E') {
                waypointY += nr;
            } else if (line[0] == 'W') {
                waypointY -= nr;
            } else if (line[0] == 'R') {
                for (int i = 0; i < nr / 90; ++i) {
                    int t = waypointX;
                    waypointX = -waypointY;
                    waypointY = t;
                }
            } else if (line[0] == 'L') {
                for (int i = 0; i < nr / 90; ++i) {
                    int t = waypointX;
                    waypointX = waypointY;
                    waypointY = -t;
                }
            }
        }

        return std::abs(startX) + std::abs(startY);
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2020_day12::part_1("../2020/day12/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2020_day12::part_2("../2020/day12/input.in") << std::endl;

    return 0;
}
#endif
