#include "file.h"
#include "utilities.h"
#include <iostream>
#include <set>

namespace aoc2023_day11 {
    unsigned long long solve(std::string_view path, int extra) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        unsigned long long sol = 0;
        std::vector<int> index_2;
        for (int index = 0; const auto& line : input) {
            std::vector<std::string> t = utils::splitString(line, "");
            bool s = true;
            for (int i = 0; i < line.size(); ++i) {
                if (line[i] == '#') {
                    s = false;
                }
            }
            if (s) index_2.push_back(index);
            index++;
        }

        std::vector<int> index;
        for (int j = 0; j < input[0].size(); ++j) {
            int s = true;
            for (int i = 0; i < input.size(); ++i) {
                if (input[i][j] == '#')  {
                    s = false;
                }
            }
            if (s) index.push_back(j);
        }

        std::vector<std::pair<int, int>> points;
        for (int i = 0; i < input.size(); ++i) {
            for (int j = 0; j < input[0].size(); ++j) {
                if (input[i][j] == '#') {
                    points.emplace_back(i, j);
                }
            }
        }

        for (int i = 0; i < points.size(); ++i) {
            for (int j = i + 1; j < points.size(); ++j) {
                sol += utils::manhattanDistance(points[i].first, points[i].second, points[j].first, points[j].second);

                for (int k = 0; k < index.size(); ++k) {
                    if ((index[k] >= points[i].second && index[k] <= points[j].second) ||
                        (index[k] >= points[j].second && index[k] <= points[i].second)){
                        sol += extra - 1;
                    }
                }

                for (int k = 0; k < index_2.size(); ++k) {
                    if ((index_2[k] >= points[i].first && index_2[k] <= points[j].first) ||
                        (index_2[k] >= points[j].first && index_2[k] <= points[i].first)){
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
