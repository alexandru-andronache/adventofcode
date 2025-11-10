#include "file.h"
#include <iostream>
#include <numeric>
#include <utilities.h>

namespace orientation {
    class Orientation {
    public:
        Orientation(utils::point p, int index) : p(p), index(index) {}
        [[nodiscard]] int getIndex() const {
            return index;
        }
        [[nodiscard]] utils::point getPoint() const {
            return p;
        }
        [[nodiscard]] bool operator==(const Orientation& o) const {
            return p == o.p;
        }
    private:
        utils::point p;
        int index;
    };

    static const Orientation EAST = {{0, 1}, 0};
    static const Orientation SOUTH = {{1, 0}, 1};
    static const Orientation WEST = {{0, -1}, 2};
    static const Orientation NORTH = {{-1, 0}, 3};
    static std::vector<orientation::Orientation> orientations = {EAST, SOUTH, WEST, NORTH};

    orientation::Orientation getOrientationIndex(orientation::Orientation o) {
        for (const auto& orientation : orientations) {
            if (orientation.getPoint() == o.getPoint()) {
                return orientation;
            }
        }
    }
}

namespace aoc2024_day16 {
    struct orientation {
        orientation(utils::point p) : p(p) {}
        utils::point p;
        [[nodiscard]] int getIndex() const {
            if (p == utils::point(0, 1)) {
                return 0;
            }
            if (p == utils::point(1, 0)) {
                return 1;
            }
            if (p == utils::point(0, -1)) {
                return 2;
            }
            if (p == utils::point(-1, 0)) {
                return 3;
            }
            return -1;
        }
    };

    const orientation EAST = {{0, 1}};
    const orientation SOUTH = {{1, 0}};
    const orientation WEST = {{0, -1}};
    const orientation NORTH = {{-1, 0}};

    orientation rotateLeft(orientation o) {
        return {{o.p.y * -1, o.p.x * -1}};
    }

    orientation rotateRight(orientation o) {
        return {{o.p.y * 1, o.p.x * 1}};
    }

    orientation reverseOrientation(orientation o) {
        return {{o.p.x * -1, o.p.y * -1}};
    }

    orientation getOrientationFromIndex(int index) {
        if (index == 0) {
            return EAST;
        }
        if (index == 1) {
            return SOUTH;
        }
        if (index == 2) {
            return WEST;
        }
        if (index == 3) {
            return NORTH;
        }
        return EAST;
    }

    bool isOrientationPerpendecular(int index1, int index2) {
        orientation o1 = getOrientationFromIndex(index1);
        orientation o2 = getOrientationFromIndex(index2);
        return o1.p.x * o2.p.x + o1.p.y * o2.p.y == 0;
    }

    int part_1(std::string_view path) {
        std::vector<std::vector<char>> map = file::readFileAsMapChar(path);
        std::vector<std::vector<std::vector<int>>> visited(map.size(), std::vector<std::vector<int>>(map[0].size(), std::vector<int>(4, std::numeric_limits<int>::max())));
        utils::point start = utils::findValue(map, 'S');
        utils::point end = utils::findValue(map, 'E');
        std::vector<std::pair<utils::point, orientation>> current{{start, EAST}};
        visited[start.x][start.y][EAST.getIndex()] = 0;
        while (!current.empty()) {
            std::vector<std::pair<utils::point, orientation>> next;
            for (const auto& c : current) {
                if (c.first.x + c.second.p.x >= 0 && c.first.x + c.second.p.x < map.size() && c.first.y + c.second.p.y >= 0 &&
                    c.first.y + c.second.p.y < map[0].size() && map[c.first.x + c.second.p.x][c.first.y + c.second.p.y] != '#') {
                    if (visited[c.first.x + c.second.p.x][c.first.y + c.second.p.y][c.second.getIndex()] > visited[c.first.x][c.first.y][c.second.getIndex()] + 1) {
                        visited[c.first.x + c.second.p.x][c.first.y + c.second.p.y][c.second.getIndex()] = visited[c.first.x][c.first.y][c.second.getIndex()] + 1;
                        next.push_back({{c.first.x + c.second.p.x, c.first.y + c.second.p.y}, c.second});
                    }
                }
                orientation left = rotateLeft(c.second);
                if (visited[c.first.x][c.first.y][left.getIndex()] > visited[c.first.x][c.first.y][c.second.getIndex()] + 1000) {
                    visited[c.first.x][c.first.y][left.getIndex()] = visited[c.first.x][c.first.y][c.second.getIndex()] + 1000;
                    next.emplace_back(c.first, left);
                }
                orientation right = rotateRight(c.second);
                if (visited[c.first.x][c.first.y][right.getIndex()] > visited[c.first.x][c.first.y][c.second.getIndex()] + 1000) {
                    visited[c.first.x][c.first.y][right.getIndex()] = visited[c.first.x][c.first.y][c.second.getIndex()] + 1000;
                    next.emplace_back(c.first, right);
                }
            }
            current = next;
        }
        return *std::min_element(visited[end.x][end.y].begin(), visited[end.x][end.y].end());
    }

    int part_2(std::string_view path) {
        std::vector<std::vector<char>> map = file::readFileAsMapChar(path);
        std::vector<std::vector<std::vector<int>>> visited(map.size(), std::vector<std::vector<int>>(map[0].size(), std::vector<int>(4, std::numeric_limits<int>::max())));
        std::vector<std::vector<bool>> reversedVisited(map.size(), std::vector<bool>(map[0].size(), false));
        utils::point start = utils::findValue(map, 'S');
        utils::point end = utils::findValue(map, 'E');
        std::vector<std::pair<utils::point, orientation>> current{{start, EAST}};
        visited[start.x][start.y][EAST.getIndex()] = 0;
        while (!current.empty()) {
            std::vector<std::pair<utils::point, orientation>> next;
            for (const auto& c : current) {
                if (c.first.x + c.second.p.x >= 0 && c.first.x + c.second.p.x < map.size() && c.first.y + c.second.p.y >= 0 &&
                    c.first.y + c.second.p.y < map[0].size() && map[c.first.x + c.second.p.x][c.first.y + c.second.p.y] != '#') {
                    if (visited[c.first.x + c.second.p.x][c.first.y + c.second.p.y][c.second.getIndex()] > visited[c.first.x][c.first.y][c.second.getIndex()] + 1) {
                        visited[c.first.x + c.second.p.x][c.first.y + c.second.p.y][c.second.getIndex()] = visited[c.first.x][c.first.y][c.second.getIndex()] + 1;
                        next.push_back({{c.first.x + c.second.p.x, c.first.y + c.second.p.y}, c.second});
                    }
                }
                orientation left = rotateLeft(c.second);
                if (visited[c.first.x][c.first.y][left.getIndex()] > visited[c.first.x][c.first.y][c.second.getIndex()] + 1000) {
                    visited[c.first.x][c.first.y][left.getIndex()] = visited[c.first.x][c.first.y][c.second.getIndex()] + 1000;
                    next.emplace_back(c.first, left);
                }
                orientation right = rotateRight(c.second);
                if (visited[c.first.x][c.first.y][right.getIndex()] > visited[c.first.x][c.first.y][c.second.getIndex()] + 1000) {
                    visited[c.first.x][c.first.y][right.getIndex()] = visited[c.first.x][c.first.y][c.second.getIndex()] + 1000;
                    next.emplace_back(c.first, right);
                }
            }
            current = next;
        }
        struct step {
            utils::point p;
            int points;
            int orientation;
        };

        int min = *std::min_element(visited[end.x][end.y].begin(), visited[end.x][end.y].end());
        int o = std::min_element(visited[end.x][end.y].begin(), visited[end.x][end.y].end()) - visited[end.x][end.y].begin();
        // o = reverseOrientation(getOrientationFromIndex(o)).getIndex();
        std::vector<utils::point> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        reversedVisited[end.x][end.y] = true;
        // std::vector<std::pair<utils::point, int>> currentRevered{{end, min}};
        std::vector<step> currentSteps{{end, min, o}};
        while (!currentSteps.empty()) {
            std::vector<step> next;
            for (const auto& c : currentSteps) {
                orientation o = reverseOrientation(getOrientationFromIndex(c.orientation));
                int newX = c.p.x + o.p.x;
                int newY = c.p.y + o.p.y;
                if (visited[newX][newY][c.orientation] == c.points - 1) {
                    reversedVisited[newX][newY] = true;
                    next.emplace_back(utils::point(newX, newY), c.points - 1, c.orientation);
                }
                orientation left = rotateLeft(o);
                orientation reverse = reverseOrientation(left);
                newX = c.p.x + left.p.x;
                newY = c.p.y + left.p.y;
                if (visited[newX][newY][reverse.getIndex()] == c.points - 1001) {
                    reversedVisited[newX][newY] = true;
                    next.emplace_back(utils::point(newX, newY), c.points - 1001, reverse.getIndex());
                }
                orientation right = rotateRight(o);
                reverse = reverseOrientation(right);
                newX = c.p.x + right.p.x;
                newY = c.p.y + right.p.y;
                if (visited[newX][newY][reverse.getIndex()] == c.points - 1001) {
                    reversedVisited[newX][newY] = true;
                    next.emplace_back(utils::point(newX, newY), c.points - 1001, reverse.getIndex());
                }
            }
            currentSteps = next;
        }

        return std::accumulate(reversedVisited.begin(), reversedVisited.end(), 0, [](int acc, const std::vector<bool>& v) {
            return acc + std::count(v.begin(), v.end(), true);
        });;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2024_day16::part_1("../2024/day16/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2024_day16::part_2("../2024/day16/input.in") << std::endl;

    return 0;
}
#endif
