#include "file.h"
#include "utilities.h"
#include <iostream>
#include <array>
#include <numeric>

namespace aoc2024_day10 {
    void solvePart1(const std::vector<std::vector<int>>& grid, int x, int y, std::vector<std::vector<bool>>& visited) {
        if (grid[x][y] == 9) {
            visited[x][y] = true;
        }
        if (x - 1 >= 0 && grid[x - 1][y] == grid[x][y] + 1) {
            solvePart1(grid, x - 1, y, visited);
        }
        if (x + 1 < grid.size() && grid[x + 1][y] == grid[x][y] + 1) {
            solvePart1(grid, x + 1, y, visited);
        }
        if (y - 1 >= 0 && grid[x][y - 1] == grid[x][y] + 1) {
            solvePart1(grid, x, y - 1, visited);
        }
        if (y + 1 < grid[0].size() && grid[x][y + 1] == grid[x][y] + 1) {
            solvePart1(grid, x, y + 1, visited);
        }
    }

    int solvePart2(const std::vector<std::vector<int>>& grid, int x, int y, int& count) {
        if (grid[x][y] == 9) {
            count++;
        }
        if (x - 1 >= 0 && grid[x - 1][y] == grid[x][y] + 1) {
            solvePart2(grid, x - 1, y, count);
        }
        if (x + 1 < grid.size() && grid[x + 1][y] == grid[x][y] + 1) {
            solvePart2(grid, x + 1, y, count);
        }
        if (y - 1 >= 0 && grid[x][y - 1] == grid[x][y] + 1) {
            solvePart2(grid, x, y - 1, count);
        }
        if (y + 1 < grid[0].size() && grid[x][y + 1] == grid[x][y] + 1) {
            solvePart2(grid, x, y + 1, count);
        }
    }
    int part_1(std::string_view path) {
        std::vector<std::vector<int>> input = file::readFileAsMap(path);
        int sol = 0;

        for (int i = 0; i < input.size(); ++i) {
            for (int j = 0; j < input[0].size(); ++j) {
                if (input[i][j] == 0) {
                    std::vector<std::vector<bool>> visited(input.size(), std::vector<bool>(input[0].size(), false));
                    solvePart1(input, i, j, visited);
                    sol += std::accumulate(visited.begin(), visited.end(), 0, [](int acc, const std::vector<bool>& v) {
                        return acc + std::count(v.begin(), v.end(), true);
                    });
                }
            }
        }

        return sol;
    }

    int part_2(std::string_view path) {
        std::vector<std::vector<int>> input = file::readFileAsMap(path);
        int sol = 0;

        for (int i = 0; i < input.size(); ++i) {
            for (int j = 0; j < input[0].size(); ++j) {
                if (input[i][j] == 0) {
                    solvePart2(input, i, j, sol);
                }
            }
        }

        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2024_day10::part_1("../2024/day10/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2024_day10::part_2("../2024/day10/input.in") << std::endl;

    return 0;
}
#endif
