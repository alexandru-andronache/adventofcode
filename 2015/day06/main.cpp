#include "file.h"
#include "utilities.h"
#include <iostream>
#include <numeric>
#include <algorithm>

namespace aoc2015_day06 {
    int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::vector<int>> map(1000, std::vector<int>(1000, 0));

        for (const auto& line : input) {
            std::vector<std::string> split = utils::splitString(line, " ,");
            if (split[0] == "toggle") {
                for (int i = std::stoi(split[2]); i <= std::stoi(split[5]); ++i) {
                    for (int j = std::stoi(split[1]); j <= std::stoi(split[4]); ++j) {
                        map[i][j] = (1 + map[i][j]) % 2;
                    }
                }
            }
            else if (split[1] == "on") {
                for (int i = std::stoi(split[3]); i <= std::stoi(split[6]); ++i) {
                    for (int j = std::stoi(split[2]); j <= std::stoi(split[5]); ++j) {
                        map[i][j] = 1;
                    }
                }
            }
            else {
                for (int i = std::stoi(split[3]); i <= std::stoi(split[6]); ++i) {
                    for (int j = std::stoi(split[2]); j <= std::stoi(split[5]); ++j) {
                        map[i][j] = 0;
                    }
                }
            }
        }

        int sum = 0;
        for (const auto& l : map) {
            sum += std::count(l.begin(), l.end(), 1);
        }
        return sum;
    }

    int part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::vector<int>> map(1000, std::vector<int>(1000, 0));

        for (const auto& line : input) {
            std::vector<std::string> split = utils::splitString(line, " ,");
            if (split[0] == "toggle") {
                for (int i = std::stoi(split[2]); i <= std::stoi(split[5]); ++i) {
                    for (int j = std::stoi(split[1]); j <= std::stoi(split[4]); ++j) {
                        map[i][j] += 2;
                    }
                }
            }
            else if (split[1] == "on") {
                for (int i = std::stoi(split[3]); i <= std::stoi(split[6]); ++i) {
                    for (int j = std::stoi(split[2]); j <= std::stoi(split[5]); ++j) {
                        map[i][j] += 1;
                    }
                }
            }
            else {
                for (int i = std::stoi(split[3]); i <= std::stoi(split[6]); ++i) {
                    for (int j = std::stoi(split[2]); j <= std::stoi(split[5]); ++j) {
                        map[i][j] = std::max(0, map[i][j] - 1);
                    }
                }
            }
        }

        int sum = 0;
        for (const auto& l : map) {
            sum += std::accumulate(l.begin(), l.end(), 0);
        }
        return sum;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2015_day06::part_1("../2015/day06/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2015_day06::part_2("../2015/day06/input.in") << std::endl;

    return 0;
}
#endif
