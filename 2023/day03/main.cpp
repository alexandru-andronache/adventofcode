#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>
#include <string>
#include <numeric>

namespace aoc2023_day03 {
    bool isCharacter(char c) {
        if (c >= '0' && c <= '9') {
            return false;
        }
        if (c == '.') {
            return false;
        }
        return true;
    }
    int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        int sol = 0;

        for (int i = 0; i < input.size(); ++i) {
            int j = 0;
            while (j < input[0].size()) {
                int nr = 0;
                bool x = true;
                while (j < input[0].size() && input[i][j] >= '0' && input[i][j] <= '9') {
                    nr = nr * 10 + input[i][j] - '0';
                    std::vector<utils::point> dir = utils::getListOfNeighboursAllDirections(i, j, input.size(), input[0].size());
                    for (const auto& d : dir) {
                        if (isCharacter(input[i + d.x][j + d.y])) x = false;
                    }
                    j++;
                }
                j++;
                if (!x) sol += nr;
            }
        }
        return sol;
    }

    int part_2(std::string_view path) {
        struct state{
            int neighbours;
            int score;
        };
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::vector<state>> neighbours(input.size(), std::vector<state>(input[0].size(), {0, 1}));
        for (int i = 0; i < input.size(); ++i) {
            int j = 0;
            while (j < input[0].size()) {
                int nr = 0;
                int start = j;
                while (j < input[0].size() && input[i][j] >= '0' && input[i][j] <= '9') {
                    nr = nr * 10 + input[i][j] - '0';
                    j++;
                }
                std::vector<std::vector<bool>> updated(input.size(), std::vector<bool>(input[0].size(), false));
                for (int k = start; k < j; ++k) {
                    std::vector<utils::point> dir = utils::getListOfNeighboursAllDirections(i, k, input.size(), input[0].size());
                    for (const auto& d : dir) {
                        if (isCharacter(input[i + d.x][k + d.y]) && !updated[i + d.x][k + d.y]) {
                            neighbours[i + d.x][k + d.y].neighbours++;
                            neighbours[i + d.x][k + d.y].score *= nr;
                            updated[i + d.x][k + d.y] = true;
                        }
                    }
                }

                j++;
            }
        }

        return std::accumulate(neighbours.begin(), neighbours.end(), 0, [](const auto& s, const auto& l) {
            return std::accumulate(l.begin(), l.end(), s, [](const auto& s, const auto& n) {
                if (n.neighbours == 2) {
                    return s + n.score;
                }
                return s;
            });
        });
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2023_day03::part_1("../2023/day03/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2023_day03::part_2("../2023/day03/input.in") << std::endl;

    return 0;
}
#endif
