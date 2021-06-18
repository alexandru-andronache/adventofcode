#include "file.h"
#include "utilities.h"
#include <iostream>
#include <array>
#include <vector>

namespace aoc2016_day03 {
    bool isTriangle(const std::array<int, 3> triangle) {
        int max = std::max({triangle[0], triangle[1], triangle[2]});
        int sum = triangle[0] + triangle[1] + triangle[2];
        if (sum - max > max) {
            return true;
        }
        return false;
    }

    int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::array<int, 3>> triangles;
        for (const auto& line : input) {
            std::vector<int> t = utils::splitStringToInt(line, " ");
            triangles.push_back({t[0], t[1], t[2]});
        }

        int sol = 0;
        for (const auto& triangle : triangles) {
            if (isTriangle(triangle)) {
                sol++;
            }
        }
        return sol;
    }

    int part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::array<int, 3>> triangles;
        for (const auto& line : input) {
            std::vector<int> t = utils::splitStringToInt(line, " ");
            triangles.push_back({t[0], t[1], t[2]});
        }

        int sol = 0;
        for (int i = 0; i < triangles.size(); i += 3) {
            for (int j = 0; j < 3; ++j) {
                if (isTriangle({triangles[i][j], triangles[i + 1][j], triangles[i + 2][j]})) {
                    sol++;
                }
            }
        }
        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2016_day03::part_1("../2016/day03/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2016_day03::part_2("../2016/day03/input.in") << std::endl;

    return 0;
}
#endif
