#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>
#include <numeric>
#include <deque>

namespace aoc2021_day13 {
    int part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::deque<std::deque<int>> map(2000, std::deque<int>(2000, 0));
        int maxX = 0;
        int maxY = 0;

        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, ",");
            if (tokens.size() > 1) {
                map[std::stoi(tokens[1])][std::stoi(tokens[0])] = 1;
                maxX = std::max(maxX, std::stoi(tokens[1]));
                maxY = std::max(maxY, std::stoi(tokens[0]));
            }
            else {
                std::vector<std::string> tokens2 = utils::splitString(line, "= ");
                if (!tokens2.empty() && tokens2[2] == "x") {
                    int fold = std::stoi(tokens2[3]);
                    int sum = 0;
                    for (int i = 0; i <= maxX; ++i) {
                        std::deque<int> newLine;
                        for (int j = 0; j < fold; ++j) {
                            newLine.push_back(map[i][j]);
                        }
                        for (int j = fold + 1, k = fold - 1; j <= maxY; ++j, --k) {
                            if (k >= 0) {
                                newLine[k] = std::min(1, newLine[k] + map[i][j]);
                            }
                            else {
                                newLine.push_front(map[i][j]);
                            }
                        }
                        map[i] = newLine;
                    }
                    maxY = fold - 1;

                    for (int i = 0; i <= maxX; ++i) {
                        for (int j = 0; j <= maxY; ++j) {
                            sum += map[i][j];
                        }
                    }

                    return sum;
                }
            }
        }
        return 0;
    }

    int part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::deque<std::deque<int>> map(2000, std::deque<int>(2000, 0));
        int maxX = 0;
        int maxY = 0;

        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, ",");
            if (tokens.size() > 1) {
                map[std::stoi(tokens[1])][std::stoi(tokens[0])] = 1;
                maxX = std::max(maxX, std::stoi(tokens[1]));
                maxY = std::max(maxY, std::stoi(tokens[0]));
            }
            else {
                std::vector<std::string> tokens2 = utils::splitString(line, "= ");
                if (!tokens2.empty() && tokens2[2] == "x") {
                    int fold = std::stoi(tokens2[3]);
                    for (int i = 0; i <= maxX; ++i) {
                        std::deque<int> newLine;
                        for (int j = 0; j < fold; ++j) {
                            newLine.push_back(map[i][j]);
                        }
                        for (int j = fold + 1, k = fold - 1; j <= maxY; ++j, --k) {
                            if (k >= 0) {
                                newLine[k] = std::min(1, newLine[k] + map[i][j]);
                            }
                            else {
                                newLine.push_front(map[i][j]);
                            }
                        }
                        map[i] = newLine;
                    }
                    maxY = fold - 1;
                }
                else if (!tokens2.empty() && tokens2[2] == "y") {
                    int fold = std::stoi(tokens2[3]);
                    for (int j = 0; j <= maxY; ++j) {
                        std::deque<int> newLine;
                        for (int i = 0; i < fold; ++i) {
                            newLine.push_back(map[i][j]);
                        }
                        for (int i = fold + 1, k = fold - 1; i <= maxX; ++i, --k) {
                            if (k >= 0) {
                                newLine[k] = std::min(1, newLine[k] + map[i][j]);
                            }
                            else {
                                newLine.push_front(map[i][j]);
                            }
                        }
                        for (int i = 0; i < fold; ++i) {
                            map[i][j] = newLine[i];
                        }
                    }
                    maxX = fold - 1;
                }
            }
        }
        for (int i = 0; i <= maxX; ++i) {
            for (int j = 0; j <= maxY; ++j) {
                if (map[i][j] == 1) {
                    std::cout << "X";
                }
                else {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
        }
        return 0;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2021_day13::part_1("../2021/day13/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2021_day13::part_2("../2021/day13/input.in") << std::endl;

    return 0;
}
#endif
