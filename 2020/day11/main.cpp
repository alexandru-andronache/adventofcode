#include "file.h"
#include "utilities.h"
#include <iostream>
#include <set>

namespace aoc2020_day11 {
    int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::vector<char>> seats(input.size(), std::vector<char>(input[0].size(), ' '));
        for (int i = 0; i < input.size(); ++i) {
            for (int j = 0; j < input[0].size(); ++j) {
                seats[i][j] = input[i][j];
            }
        }

        bool shouldContinue = true;
        std::vector<std::pair<int, int>> directions{{-1, -1},
                                                    {-1, 0},
                                                    {-1, 1},
                                                    {0,  -1},
                                                    {0,  1},
                                                    {1,  -1},
                                                    {1,  0},
                                                    {1,  1}};
        std::set<std::vector<std::vector<char>>> prevState;
        while (shouldContinue) {
            shouldContinue = false;
            std::vector<std::vector<char>> newState(input.size(), std::vector<char>(input[0].size(), ' '));
            for (int i = 0; i < seats.size(); ++i) {
                for (int j = 0; j < seats[i].size(); ++j) {
                    if (seats[i][j] != '.') {
                        int nrEmpty = 0;
                        int nrOccupied = 0;
                        for (const auto &d : directions) {
                            if (i + d.first >= 0 && i + d.first < input.size() &&
                                j + d.second >= 0 && j + d.second < input[0].size() &&
                                seats[i + d.first][j + d.second] == '#') {
                                nrOccupied++;
                            }
                        }
                        if (seats[i][j] == 'L' && nrOccupied == 0) {
                            newState[i][j] = '#';
                        } else if (seats[i][j] == '#' && nrOccupied >= 4) {
                            newState[i][j] = 'L';
                        } else {
                            newState[i][j] = seats[i][j];
                        }
                    } else {
                        newState[i][j] = seats[i][j];
                    }
                }
            }

            if (prevState.find(newState) == prevState.end()) {
                prevState.insert(newState);
                seats = newState;
                shouldContinue = true;
            } else {
                int nr = 0;
                for (int i = 0; i < seats.size(); ++i) {
                    for (int j = 0; j < seats[i].size(); ++j) {
                        if (newState[i][j] == '#') {
                            nr++;
                        }
                    }
                }
                return nr;
            }

        }

        return 0;
    }

    int part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::vector<char>> seats(input.size(), std::vector<char>(input[0].size(), ' '));
        for (int i = 0; i < input.size(); ++i) {
            for (int j = 0; j < input[0].size(); ++j) {
                seats[i][j] = input[i][j];
            }
        }

        bool shouldContinue = true;
        std::vector<std::pair<int, int>> directions{{-1, -1},
                                                    {-1, 0},
                                                    {-1, 1},
                                                    {0,  -1},
                                                    {0,  1},
                                                    {1,  -1},
                                                    {1,  0},
                                                    {1,  1}};
        std::set<std::vector<std::vector<char>>> prevState;
        while (shouldContinue) {
            shouldContinue = false;
            std::vector<std::vector<char>> newState(input.size(), std::vector<char>(input[0].size(), ' '));
            for (int i = 0; i < seats.size(); ++i) {
                for (int j = 0; j < seats[i].size(); ++j) {
                    if (seats[i][j] != '.') {
                        int nrEmpty = 0;
                        int nrOccupied = 0;
                        for (const auto &d : directions) {
                            int k = 1;
                            bool found = false;
                            while (i + d.first * k >= 0 && i + d.first * k < input.size() &&
                                   j + d.second * k >= 0 && j + d.second * k < input[0].size() && !found) {
                                if (seats[i + d.first * k][j + d.second * k] == '#') {
                                    nrOccupied++;
                                    found = true;
                                } else if (seats[i + d.first * k][j + d.second * k] == 'L') {
                                    found = true;
                                }
                                k++;
                            }
                        }
                        if (seats[i][j] == 'L' && nrOccupied == 0) {
                            newState[i][j] = '#';
                        } else if (seats[i][j] == '#' && nrOccupied >= 5) {
                            newState[i][j] = 'L';
                        } else {
                            newState[i][j] = seats[i][j];
                        }
                    } else {
                        newState[i][j] = seats[i][j];
                    }
                }
            }

            if (prevState.find(newState) == prevState.end()) {
                prevState.insert(newState);
                seats = newState;
                shouldContinue = true;
            } else {
                int nr = 0;
                for (int i = 0; i < seats.size(); ++i) {
                    for (int j = 0; j < seats[i].size(); ++j) {
                        if (newState[i][j] == '#') {
                            nr++;
                        }
                    }
                }
                return nr;
            }

        }

        return 0;
    }
}
#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2020_day11::part_1("../2020/day11/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2020_day11::part_2("../2020/day11/input.in") << std::endl;

    return 0;
}
#endif
