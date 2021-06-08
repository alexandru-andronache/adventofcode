#include "file.h"
#include "utilities.h"
#include "verticalhexgrid.h"
#include <iostream>
#include <chrono>

namespace aoc2020_day24 {
    int part_1(std::string_view path) {
        std::vector<std::string> paths = file::readFileAsArrayString(path);
        const int SIZE = 1000;
        verticalhexgrid::VerticalHexGrid<bool> hexGrid(SIZE, true);

        for (const auto &path : paths) {
            int X = SIZE / 2;
            int Y = SIZE / 2;
            int i = 0;
            while (i < path.size()) {
                int size = 2;
                if (path[i] == 'e' || path[i] == 'w') {
                    size = 1;
                }
                auto result = hexGrid.moveInHexGridVertical(X, Y, path.substr(i, size));
                X += result.first;
                Y += result.second;
                i += size;
            }
            hexGrid.grid[X][Y] = !hexGrid.grid[X][Y];
        }

        int sol = 0;
        for (const auto &line : hexGrid.grid) {
            sol += std::count(line.begin(), line.end(), false);
        }
        return sol;
    }

    int part_2(std::string_view path, int days = 100) {
        std::vector<std::string> paths = file::readFileAsArrayString(path);
        const int SIZE = 1000;
        verticalhexgrid::VerticalHexGrid<bool> hexGrid(SIZE, true);

        for (const auto &path : paths) {
            int X = SIZE / 2;
            int Y = SIZE / 2;
            int i = 0;
            while (i < path.size()) {
                int size = 0;
                if (path[i] == 'e' || path[i] == 'w') {
                    size = 1;
                } else {
                    size = 2;
                }
                auto result = hexGrid.moveInHexGridVertical(X, Y, path.substr(i, size));
                X += result.first;
                Y += result.second;
                i += size;
            }
            hexGrid.grid[X][Y] = !hexGrid.grid[X][Y];
        }

        for (int day = 0; day < days; ++day) {
            std::vector<std::vector<bool>> newGrid = hexGrid.grid;
            hexGrid.calculateNeighbors(false);
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    if (!hexGrid.grid[i][j]) {
                        if (hexGrid.neighbors[i][j] == 0 || hexGrid.neighbors[i][j] > 2) {
                            newGrid[i][j] = true;
                        } else {
                            newGrid[i][j] = hexGrid.grid[i][j];
                        }
                    } else {
                        if (hexGrid.neighbors[i][j] == 2) {
                            newGrid[i][j] = false;
                        } else {
                            newGrid[i][j] = hexGrid.grid[i][j];
                        }
                    }
                }
            }
            hexGrid.grid = newGrid;
        }

        int sol = 0;
        for (const auto &line : hexGrid.grid) {
            sol += std::count(line.begin(), line.end(), false);
        }
        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2020_day24::part_1("../2020/day24/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2020_day24::part_2("../2020/day24/input.in") << std::endl;

    return 0;
}
#endif
