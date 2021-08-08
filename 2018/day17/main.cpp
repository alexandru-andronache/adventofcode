#include "file.h"
#include "utilities.h"
#include <iostream>

namespace aoc2018_day17 {
    enum class terrain {
        Nothing = 0,
        Wall = 1,
        Water = 2
    };

    void flow(int startX, int startY, std::vector<std::vector<terrain>> &map, int maxX, int maxY) {
        // go down
        map[startX][startY] = terrain::Water;
        while (startX + 1 <= maxX && map[startX + 1][startY] == terrain::Nothing) {
            startX++;
            map[startX][startY] = terrain::Water;
        }
        if (startX == maxX) {
            return;
        }
        if (map[startX + 1][startY] == terrain::Water) {
            int tempY_l = startY, tempY_r = startY;
            int nrWalls = 0;
            while (map[startX + 1][tempY_l] == terrain::Water && map[startX][tempY_l - 1] != terrain::Wall) {
                tempY_l--;
            }
            if (map[startX][tempY_l - 1] == terrain::Wall) {
                nrWalls++;
            }
            while (map[startX + 1][tempY_r] == terrain::Water && map[startX][tempY_r + 1] != terrain::Wall) {
                tempY_r++;
            }
            if (map[startX][tempY_r + 1] == terrain::Wall) {
                nrWalls++;
            }
            if (nrWalls == 0) {
                return;
            }
        }

        bool cont = true;
        int tmpX_left = startX, tmpY_left = startY;
        int tmpX_right = startX, tmpY_right = startY;
        while (cont) {
            //go lateral
            //go left
            tmpX_left = startX, tmpY_left = startY;
            tmpX_right = startX, tmpY_right = startY;
            map[startX][startY] = terrain::Water;
            while (map[tmpX_left][tmpY_left - 1] == terrain::Nothing && map[tmpX_left + 1][tmpY_left - 1] != terrain::Nothing) {
                tmpY_left--;
                map[tmpX_left][tmpY_left] = terrain::Water;
            }
            //go right

            while (map[tmpX_right][tmpY_right + 1] == terrain::Nothing && map[tmpX_right + 1][tmpY_right + 1] != terrain::Nothing) {
                tmpY_right++;
                map[tmpX_right][tmpY_right] = terrain::Water;
            }

            cont = false;
            //go up
            if (map[tmpX_left][tmpY_left - 1] == terrain::Wall && map[tmpX_right][tmpY_right + 1] == terrain::Wall) {
                startX--;
                cont = true;
            }
        }

        if (map[tmpX_left][tmpY_left - 1] == terrain::Nothing) {
            flow(tmpX_left, tmpY_left - 1, map, maxX, maxY);
        }
        if (map[tmpX_right][tmpY_right + 1] == terrain::Nothing) {
            flow(tmpX_right, tmpY_right + 1, map, maxX, maxY);
        }

        int tempY_l = startY, tempY_r = startY;
        int nrWalls = 0;
        while (map[startX][tempY_l] == terrain::Water) {
            tempY_l--;
        }
        if (map[startX][tempY_l] == terrain::Wall) {
            nrWalls++;
        }
        while (map[startX][tempY_r] == terrain::Water) {
            tempY_r++;
        }
        if (map[startX][tempY_r] == terrain::Wall) {
            nrWalls++;
        }
        if (nrWalls == 2) {
            flow(startX - 1, startY, map, maxX, maxY);
        }
    }

    std::vector<std::vector<terrain>> createMap(const std::vector<std::tuple<int, int, int>>& horizontalLines,
                                                const std::vector<std::tuple<int, int, int>>& verticalLines,
                                                int &minX, int &maxX, int &minY, int &maxY) {
        maxX = 0;
        maxY = 0;
        minY = std::numeric_limits<int>::max();
        minX = std::numeric_limits<int>::max();
        for (const auto& line : verticalLines) {
            auto [ y, x1, x2 ] = line;
            maxX = std::max(maxX, x2);
            minX = std::min(minX, x1);
            maxY = std::max(maxY, y);
            minY = std::min(minY, y);
        }
        for (const auto& line : horizontalLines) {
            auto [ x, y1, y2 ] = line;
            maxX = std::max(maxX, x);
            minX = std::min(minX, x);
            maxY = std::max(maxY, y2);
            minY = std::min(minY, y1);
        }

        std::vector<std::vector<terrain>> map(maxX + 2, std::vector<terrain>(maxY + 2, terrain::Nothing));

        for (const auto& line: horizontalLines) {
            auto [ x, y1, y2 ] = line;
            for (int i = y1; i <= y2; ++i) {
                map[x][i] = terrain::Wall;
            }
        }
        for (const auto& line: verticalLines) {
            auto [ y, x1, x2 ] = line;
            for (int i = x1; i <= x2; ++i) {
                map[i][y] = terrain::Wall;
            }
        }

        flow(1, 500, map, maxX, maxY);

        return map;
    }

    int part_1(std::string_view path) {
        std::vector<std::tuple<int, int, int>> horizontalLines;
        std::vector<std::tuple<int, int, int>> verticalLines;
        std::vector<std::vector<std::string>> lines = file::readFileAndSplit(path, ", =.");
        for (const auto& line : lines) {
            if (line[0] == "x") {
                verticalLines.emplace_back(std::stoi(line[1]), std::stoi(line[3]), std::stoi(line[4]));
            }
            else {
                horizontalLines.emplace_back(std::stoi(line[1]), std::stoi(line[3]), std::stoi(line[4]));
            }
        }

        int minX, maxX, minY, maxY;
        std::vector<std::vector<terrain>> map = createMap(horizontalLines, verticalLines, minX, maxX, minY, maxY);

        int water = 0;
        for (int i = minX; i < maxX + 1; ++i) {
            for (int j = 0; j < maxY + 1; ++j) {
                if (map[i][j] == terrain::Water) water++;
            }
        }

        return water;
    }

    int part_2(std::string_view path) {
        std::vector<std::tuple<int, int, int>> horizontalLines;
        std::vector<std::tuple<int, int, int>> verticalLines;
        std::vector<std::vector<std::string>> lines = file::readFileAndSplit(path, ", =.");
        for (const auto& line : lines) {
            if (line[0] == "x") {
                verticalLines.emplace_back(std::stoi(line[1]), std::stoi(line[3]), std::stoi(line[4]));
            }
            else {
                horizontalLines.emplace_back(std::stoi(line[1]), std::stoi(line[3]), std::stoi(line[4]));
            }
        }

        int minX, maxX, minY, maxY;
        auto map = createMap(horizontalLines, verticalLines, minX, maxX, minY, maxY);

        int water = 0;
        for (int i = minX; i < maxX + 1; ++i) {
            for (int j = 0; j < maxY + 1; ++j) {
                if (map[i][j] == terrain::Water) {
                    int x = i, y_left = j, y_right = j;
                    while (map[x][y_left] == terrain::Water) {
                        y_left--;
                    }
                    while (map[x][y_right] == terrain::Water) {
                        y_right++;
                    }
                    if (map[x][y_left] == terrain::Wall && map[x][y_right] == terrain::Wall) {
                        water++;
                    }
                }
            }
        }

        return water;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2018_day17::part_1("../2018/day17/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2018_day17::part_2("../2018/day17/input.in") << std::endl;

    return 0;
}
#endif
