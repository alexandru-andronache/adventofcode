#include "file.h"
#include <iostream>
#include <map>
#include <vector>

namespace aoc2016_day13 {
    int part_1(int favoriteNumber, int endX, int endY, int size = 50) {
        std::vector<std::vector<int>> map(size, std::vector<int>(size, std::numeric_limits<int>::max()));

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                size_t value = j * j + 3 * j + 2 * j * i + i + i * i + favoriteNumber;
                std::bitset<sizeof(size_t) * CHAR_BIT> b(value);
                if (b.count() % 2 == 1) {
                    map[i][j] = -1;
                }
            }
        }

        map[1][1] = 0;
        std::vector<std::pair<int, int>> positions {{1, 1}};
        std::vector<std::pair<int, int>> directions {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        while (!positions.empty()) {
            std::vector<std::pair<int, int>> newPositions;
            for (const auto& p : positions) {
                for (const auto& d : directions) {
                    if (p.first + d.first >= 0 && p.first + d.first < size &&
                    p.second + d.second >= 0 && p.second + d.second < size &&
                    map[p.first + d.first][p.second + d.second] != -1 &&
                    map[p.first + d.first][p.second + d.second] > map[p.first][p.second] + 1) {
                        map[p.first + d.first][p.second + d.second] = map[p.first][p.second] + 1;
                        newPositions.emplace_back(p.first + d.first, p.second + d.second);
                    }
                }
            }
            positions.clear();
            positions = newPositions;
        }

        return map[endY][endX];
    }

    int part_2(int favoriteNumber, int steps = 50, int size = 100) {
        std::vector<std::vector<int>> map(size, std::vector<int>(size, std::numeric_limits<int>::max()));

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                size_t value = j * j + 3 * j + 2 * j * i + i + i * i + favoriteNumber;
                std::bitset<sizeof(size_t) * CHAR_BIT> b(value);
                if (b.count() % 2 == 1) {
                    map[i][j] = -1;
                }
            }
        }

        map[1][1] = 0;
        std::vector<std::pair<int, int>> positions {{1, 1}};
        std::vector<std::pair<int, int>> directions {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        while (!positions.empty()) {
            std::vector<std::pair<int, int>> newPositions;
            for (const auto& p : positions) {
                for (const auto& d : directions) {
                    if (p.first + d.first >= 0 && p.first + d.first < size &&
                    p.second + d.second >= 0 && p.second + d.second < size &&
                    map[p.first + d.first][p.second + d.second] != -1 &&
                    map[p.first + d.first][p.second + d.second] > map[p.first][p.second] + 1) {
                        map[p.first + d.first][p.second + d.second] = map[p.first][p.second] + 1;
                        newPositions.emplace_back(p.first + d.first, p.second + d.second);
                    }
                }
            }
            positions.clear();
            positions = newPositions;
        }

        int sol = 0;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (map[i][j] != -1 && map[i][j] <= steps) {
                    sol++;
                }
            }
        }

        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2016_day13::part_1(1358, 31, 39) << std::endl;
    std::cout << "Part 2: " << aoc2016_day13::part_2(1358) << std::endl;

    return 0;
}
#endif
