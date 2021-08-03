#include "file.h"
#include <iostream>
#include <vector>

namespace aoc2018_day03 {
    struct Rectangle {
        int id;
        int startX;
        int startY;
        int sizeX;
        int sizeY;
    };

    bool doOverlap(Rectangle r1, Rectangle r2) {
        if (r1.startX + r1.sizeX - 1 < r2.startX)
            return false;
        if (r2.startX + r2.sizeX - 1 < r1.startX)
            return false;
        if (r1.startY + r1.sizeY - 1 < r2.startY)
            return false;
        if (r2.startY + r2.sizeY - 1 < r1.startY)
            return false;

        return true;
    }

    int part_1(std::string_view path) {
        std::vector<std::vector<std::string>> lines = file::readFileAndSplit(path, " ';#@,:x");
        std::vector<Rectangle> input;
        for (const auto& line : lines) {
            input.push_back({std::stoi(line[0]), std::stoi(line[1]), std::stoi(line[2]), std::stoi(line[3]), std::stoi(line[4])});
        }

        constexpr int N = 1000;
        std::vector<std::vector<int>> map(N, std::vector<int>(N, 0));

        for (const auto& r : input) {
            for (int i = r.startX; i < r.startX + r.sizeX; ++i) {
                for (int j = r.startY; j < r.startY + r.sizeY; ++j) {
                    map[i][j]++;
                }
            }
        }

        int sol = 0;
        for (const auto& l : map) {
            sol += std::count_if(l.begin(), l.end(), [](const auto& x) {
                return x >= 2;
            });
        }

        return sol;
    }

    int part_2(std::string_view path) {
        std::vector<std::vector<std::string>> lines = file::readFileAndSplit(path, " ';#@,:x");
        std::vector<Rectangle> input;
        for (const auto& line : lines) {
            input.push_back({std::stoi(line[0]), std::stoi(line[1]), std::stoi(line[2]), std::stoi(line[3]), std::stoi(line[4])});
        }

        for (const auto& rectangle1 : input) {
            bool intersect = false;
            for (const auto& rectangle2 : input) {
                if (rectangle1.id != rectangle2.id)
                    intersect = intersect || doOverlap(rectangle1, rectangle2);
            }
            if (!intersect)
                return rectangle1.id;
        }
        return 0;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2018_day03::part_1("../2018/day03/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2018_day03::part_2("../2018/day03/input.in") << std::endl;

    return 0;
}
#endif
