#include "file.h"
#include "utilities.h"
#include <iostream>
#include <set>

namespace aoc2023_day11 {
    unsigned long long solve(std::string_view path, int extra) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        unsigned long long sol = 0;
        std::vector<int> emptyLines;
        for (int index = 0; const auto& line : input) {
            bool emptyLine = std::all_of(line.begin(), line.end(), [](char c) {
                return c == '.';
            });
            if (emptyLine) emptyLines.push_back(index);
            index++;
        }

        std::vector<int> emptyCols;
        for (int j = 0; j < input[0].size(); ++j) {
            bool emptyCol = true;
            for (const auto& col : input) {
                if (col[j] == '#')  {
                    emptyCol = false;
                }
            }
            if (emptyCol) emptyCols.push_back(j);
        }

        std::vector<utils::point> points = utils::findAll(input, '#');

        for (int i = 0; i < points.size(); ++i) {
            for (int j = i + 1; j < points.size(); ++j) {
                sol += utils::manhattanDistance(points[i].x, points[i].y, points[j].x, points[j].y);

                for (const auto& emptyCol : emptyCols) {
                    if ((emptyCol >= points[i].y && emptyCol <= points[j].y) ||
                        (emptyCol >= points[j].y && emptyCol <= points[i].y)) {
                        sol += extra - 1;
                    }
                }

                for (const auto& emptyLine : emptyLines) {
                    if ((emptyLine >= points[i].x && emptyLine <= points[j].x) ||
                        (emptyLine >= points[j].x && emptyLine <= points[i].x)) {
                        sol += extra - 1;
                    }
                }
            }
        }

        return sol;
    }
    unsigned long long part_1(std::string_view path) {
        return solve(path, 2);
    }

    unsigned long long part_2(std::string_view path, int extra = 1000000) {
        return solve(path, extra);
    }
}
#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2023_day11::part_1("../2023/day11/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2023_day11::part_2("../2023/day11/input.in") << std::endl;

    return 0;
}
#endif
