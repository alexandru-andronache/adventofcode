#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>
#include <numeric>
#include <deque>

namespace aoc2021_day13 {
    void foldHorizontal(std::vector<std::vector<int>>& map, int fold) {
        for (int i = 0; i < map.size(); ++i) {
            std::deque<int> newLine;
            for (int j = 0; j < fold; ++j) {
                newLine.push_back(map[i][j]);
            }
            for (int j = fold + 1, k = fold - 1; j < map[i].size(); ++j, --k) {
                if (k >= 0) {
                    newLine[k] = std::min(1, newLine[k] + map[i][j]);
                }
                else {
                    newLine.push_front(map[i][j]);
                }
            }
            map[i] = std::vector<int>(newLine.begin(), newLine.end());
        }
    }

    void foldVertically(std::vector<std::vector<int>>& map, int fold) {
        int y = map[0].size();
        for (int j = 0; j <= y; ++j) {
            std::deque<int> newLine;
            for (int i = 0; i < fold; ++i) {
                newLine.push_back(map[i][j]);
            }
            for (int i = fold + 1, k = fold - 1; i < map.size(); ++i, --k) {
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
        map.erase(map.begin() + fold, map.end());
    }

    int part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        int maxX = 0;
        int maxY = 0;

        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, ",");
            if (tokens.size() > 1) {
                maxX = std::max(maxX, std::stoi(tokens[1]));
                maxY = std::max(maxY, std::stoi(tokens[0]));
            }
        }

        std::vector<std::vector<int>> map(maxX + 1, std::vector<int>(maxY + 1, 0));

        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, ",");
            std::vector<std::string> tokens2 = utils::splitString(line, "= ");
            if (tokens.size() > 1) {
                map[std::stoi(tokens[1])][std::stoi(tokens[0])] = 1;
            }
            else if (!tokens2.empty()) {
                if (tokens2[2] == "x") {
                    foldHorizontal(map, std::stoi(tokens2[3]));
                }
                else if (tokens2[2] == "y") {
                    foldVertically(map, std::stoi(tokens2[3]));
                }
                int sum = 0;
                for (const auto& l : map) {
                    sum += std::accumulate(l.begin(), l.end(), 0);
                }
                return sum;
            }
        }
        return 0;
    }

    int part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        int maxX = 0;
        int maxY = 0;

        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, ",");
            if (tokens.size() > 1) {
                maxX = std::max(maxX, std::stoi(tokens[1]));
                maxY = std::max(maxY, std::stoi(tokens[0]));
            }
        }

        std::vector<std::vector<int>> map(maxX + 1, std::vector<int>(maxY + 1, 0));
        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, ",");
            std::vector<std::string> tokens2 = utils::splitString(line, "= ");
            if (tokens.size() > 1) {
                map[std::stoi(tokens[1])][std::stoi(tokens[0])] = 1;
            }
            else if (!tokens2.empty()) {
                if (tokens2[2] == "x") {
                    foldHorizontal(map, std::stoi(tokens2[3]));
                }
                else if (tokens2[2] == "y") {
                    foldVertically(map, std::stoi(tokens2[3]));
                }
            }
        }
        for (const auto& line: map) {
            for (const auto& c : line) {
                std::cout << char('X' * (c == 1) + ' ' * (c != 1));
            }
            std::cout << std::endl;
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
    std::cout << "Part 1: " << aoc2021_day13::part_1("../2021/day13/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2021_day13::part_2("../2021/day13/input.in") << std::endl;

    return 0;
}
#endif
