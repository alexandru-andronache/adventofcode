#include "file.h"
#include "utilities.h"
#include <iostream>

namespace aoc2018_day06 {
    struct Point {
        int x;
        int y;
        bool hasInfiniteArea;
        int closestAreaSize;
    };

    int part_1(std::string_view path) {
        std::vector<std::vector<std::string>> lines = file::readFileAndSplit(path, " ,");
        std::vector<Point> points;
        for (const auto& line : lines) {
            points.push_back({std::stoi(line[0]), std::stoi(line[1]), false, 0});
        }
        Point upLeft({std::numeric_limits<int>::max(), std::numeric_limits<int>::max()});
        Point downRight({0, 0});
        for (const auto& p : points) {
            upLeft.x = std::min(upLeft.x, p.x);
            upLeft.y = std::min(upLeft.y, p.y);
            downRight.x = std::max(downRight.x, p.x);
            downRight.y = std::max(downRight.y, p.y);
        }

        struct Area {
            Area() {
                id = -1;
                distance = std::numeric_limits<int>::max();
            }
            int id;
            int distance;
        };

        std::vector<std::vector<Area>> area(downRight.x - upLeft.x + 3, std::vector<Area>(downRight.y - upLeft.y + 3, Area()));

        for (int i = upLeft.x - 1; i <= downRight.x + 1; ++i) {
            for (int j = upLeft.y - 1; j <= downRight.y + 1; ++j) {
                for (int k = 0; k < points.size(); ++k) {
                    int dist = utils::manhattanDistance(points[k].x, points[k].y, i, j);
                    if (dist == area[i - upLeft.x + 1][j - upLeft.y + 1].distance) {
                        area[i - upLeft.x + 1][j - upLeft.y + 1].id = -1;
                    }
                    if (dist < area[i - upLeft.x + 1][j - upLeft.y + 1].distance) {
                        area[i - upLeft.x + 1][j - upLeft.y + 1].distance = dist;
                        area[i - upLeft.x + 1][j - upLeft.y + 1].id = k;
                    }
                }
            }
        }

        for (int i = upLeft.y - 1; i <= downRight.y + 1; ++i) {
            points[area[0][i - upLeft.y + 1].id].hasInfiniteArea = true;
        }
        for (int i = upLeft.x - 1; i <= downRight.x + 1; ++i) {
            points[area[i - upLeft.x + 1][downRight.y + 1 - upLeft.y + 1].id].hasInfiniteArea = true;
        }
        for (int i = upLeft.y - 1; i <= downRight.y + 1; ++i) {
            points[area[downRight.x + 1 - upLeft.x + 1][i - upLeft.y + 1].id].hasInfiniteArea = true;
        }
        for (int i = upLeft.x - 1; i <= downRight.x + 1; ++i) {
            points[area[i - upLeft.x + 1][0].id].hasInfiniteArea = true;
        }

        for (int i = upLeft.x; i <= downRight.x; ++i) {
            for (int j = upLeft.y; j <= downRight.y; ++j) {
                if (area[i - upLeft.x + 1][j - upLeft.y + 1].id != -1) {
                    points[area[i - upLeft.x + 1][j - upLeft.y + 1].id].closestAreaSize++;
                }
            }
        }

        int max = 0;
        for (const auto& p : points) {
            if (!p.hasInfiniteArea) {
                max = std::max(max, p.closestAreaSize);
            }
        }

        return max;
    }

    int part_2(std::string_view path, int maxDistance = 10000) {
        std::vector<std::vector<std::string>> lines = file::readFileAndSplit(path, " ,");
        std::vector<Point> points;
        for (const auto& line : lines) {
            points.push_back({std::stoi(line[0]), std::stoi(line[1]), false, 0});
        }

        Point upLeft({std::numeric_limits<int>::max(), std::numeric_limits<int>::max()});
        Point downRight({0, 0});
        for (const auto& p : points) {
            upLeft.x = std::min(upLeft.x, p.x);
            upLeft.y = std::min(upLeft.y, p.y);
            downRight.x = std::max(downRight.x, p.x);
            downRight.y = std::max(downRight.y, p.y);
        }

        struct Area {
            Area() {
                id = -1;
                distanceToAllPoints = 0;
            }
            int id;
            int distanceToAllPoints;
        };

        std::vector<std::vector<Area>> area(downRight.x - upLeft.x + 3, std::vector<Area>(downRight.y - upLeft.y + 3, Area()));

        for (int i = upLeft.x; i <= downRight.x; ++i) {
            for (int j = upLeft.y; j <= downRight.y; ++j) {
                for (const auto& p : points) {
                    area[i - upLeft.x + 1][j - upLeft.y + 1].distanceToAllPoints += utils::manhattanDistance(p.x, p.y, i, j);
                }
            }
        }

        int sol = 0;
        for (int i = upLeft.x; i <= downRight.x; ++i) {
            for (int j = upLeft.y; j <= downRight.y; ++j) {
                if (area[i - upLeft.x + 1][j - upLeft.y + 1].distanceToAllPoints < maxDistance) {
                    sol++;
                }
            }
        }
        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2018_day06::part_1("../2018/day06/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2018_day06::part_2("../2018/day06/input.in") << std::endl;

    return 0;
}
#endif
