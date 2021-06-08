#pragma once

#include <vector>

/*
 * A hex grid where you can move with directions: "e", "s", "se", "sw", "ne", "nw"
 */

namespace verticalhexgrid {
    template <class T>
    class VerticalHexGrid {
    public:
        VerticalHexGrid(int size, T default_value)
        : mSize(size) {
            grid = std::vector<std::vector<T>>(size, std::vector<T>(size, default_value));
            neighbors = std::vector<std::vector<int>>(size, std::vector<int>(size, 0));
        }

        std::pair<int, int> moveInHexGridVertical(int x, int y, std::string_view dir) {
            if (dir.size() == 1) {
                return {0, dir == "e" ? 1 : -1};
            }
            int X = dir[0] == 's' ? 1 : -1;
            int Y = 0;
            if (dir[1] == 'e') {
                if (x % 2 == 0) {
                    Y = 1;
                }
            }
            else {
                if (x % 2 == 1) {
                    Y = -1;
                }
            }
            return {X, Y};
        }

        void calculateNeighbors(T value) {
            for (int i = 0; i < mSize; ++i) {
                for (int j = 0; j < mSize; ++j) {
                    neighbors[i][j] = 0;
                    if (i % 2 == 0) {
                        for (const auto& d : direction_even) {
                            if (i + d.first >= 0 && i + d.first < mSize &&
                                j + d.second >= 0 && j + d.second < mSize &&
                                grid[i + d.first][j + d.second] == value) {
                                neighbors[i][j]++;
                            }
                        }
                    }
                    else {
                        for (const auto& d : direction_odd) {
                            if (i + d.first >= 0 && i + d.first < mSize &&
                                j + d.second >= 0 && j + d.second < mSize &&
                                grid[i + d.first][j + d.second] == value) {
                                neighbors[i][j]++;
                            }
                        }
                    }
                }
            }
        }

        std::vector<std::vector<T>> grid;
        std::vector<std::vector<int>> neighbors;
    private:
        int mSize;
        const std::vector<std::pair<int, int>> direction_even {{-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, 0}, {1, 1}};
        const std::vector<std::pair<int, int>> direction_odd {{-1, -1}, {-1, 0}, {0, -1}, {0, 1}, {1, -1}, {1, 0}};
    };
}
