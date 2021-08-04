#include "file.h"
#include "utilities.h"
#include <iostream>
#include <set>

namespace aoc2018_day11 {
    int getPowerLevel(int x, int y, int serialNumber) {
        int rackId = x + 10;
        int powerLevel = (rackId * y + serialNumber) * rackId;
        powerLevel = (powerLevel % 1000) / 100;
        return powerLevel - 5;
    }

    std::pair<int, int> part_1(int input, int size) {
        std::vector<std::vector<int>> map(size, std::vector<int>(size, 0));
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                map[j][i] = getPowerLevel(j + 1, i + 1, input);
            }
        }

        int max = 0;
        std::pair<int, int> sol;
        for (int i = 0; i < size - 2; ++i) {
            for (int j = 0; j < size - 2; ++j) {
                int sum = map[j][i] + map[j][i + 1] + map[j][i + 2] +
                        map[j + 1][i] + map[j + 1][i + 1] + map[j + 1][i + 2] +
                        map[j + 2][i] + map[j + 2][i + 1] + map[j + 2][i + 2];
                if (max < sum) {
                    max = sum;
                    sol.first = j + 1;
                    sol.second = i + 1;
                }
            }
        }

        return sol;
    }

    std::tuple<int, int, int> part_2(int input, int size) {
        std::vector<std::vector<int>> map(size, std::vector<int>(size, 0));

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                map[j][i] = getPowerLevel(j + 1, i + 1, input);
            }
        }

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (j > 0) {
                    map[j][i] += map[j - 1][i];
                }
                if (i > 0) {
                    map[j][i] += map[j][i - 1];
                }
                if (i > 0 && j > 0) {
                    map[j][i] -= map[j - 1][i - 1];
                }
            }
        }

        std::tuple<int, int, int> sol;
        int max = 0;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                for (int s = 0; j + s < size && i + s < size; ++s) {
                    int sum = map[j + s][i + s];
                    if (i > 0 && j > 0) {
                        sum += map[j - 1][i - 1];
                    }
                    if (i > 0) {
                        sum -= map[j + s][i - 1];
                    }
                    if (j > 0) {
                        sum -= map[j - 1][i + s];
                    }
                    if (max < sum) {
                        max = sum;
                        sol = std::make_tuple(j + 1, i + 1, s + 1);
                    }
                }
            }
        }

        return sol;
    }
}
#ifndef TESTING
int main() {
    auto sol1 = aoc2018_day11::part_1(1788, 300);
    std::cout << "Part 1: " << sol1.first << "," << sol1.second << std::endl;
    auto [x, y, s] = aoc2018_day11::part_2(1788, 300);
    std::cout << "Part 1: " << x << "," << y << "," << s << std::endl;

    return 0;
}
#endif
