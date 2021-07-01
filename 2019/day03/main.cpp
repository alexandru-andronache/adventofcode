#include "file.h"
#include "utilities.h"
#include <iostream>

namespace aoc2019_day03 {
    struct point {
        point (int _x, int _y, int _steps) : x(_x), y(_y), steps(_steps) {}
        int x, y, steps;
    };

    bool operator==(const point& p1, const point& p2) {
        return p1.x == p2.x && p1.y == p2.y;
    }

    bool operator!=(const point& p1, const point& p2) {
        return !(p1 == p2);
    }

    bool operator< (const point& p1, const point& p2) {
        if (p1.x < p2.x) return true;
        if (p1.x == p2.x && p1.y < p2.y) return true;
        return false;
    }

    bool operator> (const point& p1, const point& p2) {
        return p2 < p1;
    }

    bool operator<=(const point& p1, const point& p2) {
        return !(p1 > p2);
    }

    bool operator>=(const point& p1, const point& p2) {
        return !(p1 < p2);
    }

    void processInput(const char* str,  std::vector<point>& path) {
        int k = 0;
        int nr = 0;
        point current = point(0, 0, 0);
        while (k < strlen(str)) {
            if (str[k] == 'L') {
                nr = utils::getNumber(str, ++k);
                for (int i = 1; i <= nr; ++i) {
                    current.y--;
                    current.steps++;
                    path.push_back(current);
                }
            } else if (str[k] == 'R') {
                nr = utils::getNumber(str, ++k);
                for (int i = 1; i <= nr; ++i) {
                    current.y++;
                    current.steps++;
                    path.push_back(current);
                }
            } else if (str[k] == 'U') {
                nr = utils::getNumber(str, ++k);
                for (int i = 1; i <= nr; ++i) {
                    current.x--;
                    current.steps++;
                    path.push_back(current);
                }
            } else if (str[k] == 'D') {
                nr = utils::getNumber(str, ++k);
                for (int i = 1; i <= nr; ++i) {
                    current.x++;
                    current.steps++;
                    path.push_back(current);
                }
            }
            k++;
        }
    }

    int part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::vector<point> path1;
        std::vector<point> path2;

        processInput(lines[0].c_str(), path1);
        processInput(lines[1].c_str(), path2);

        int distMin = std::numeric_limits<int>::max();

        std::sort(path1.begin(), path1.end());
        std::sort(path2.begin(), path2.end());

        int i = 0, j = 0;
        while (i < path1.size() && j < path2.size()) {
            if (path1[i] == path2[j]) {
                distMin = std::min(distMin, utils::manhattanDistance(path1[i].x, path1[i].y, 0, 0));
                i++;
                j++;
            }
            if (path1[i] < path2[j]) {
                i++;
            }
            if (path1[i] > path2[j]) {
                j++;
            }
        }

        return distMin;
    }

    int part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);

        std::vector<point> path1;
        std::vector<point> path2;

        processInput(lines[0].c_str(), path1);
        processInput(lines[1].c_str(), path2);

        int stepsMin = std::numeric_limits<int>::max();

        std::sort(path1.begin(), path1.end());
        std::sort(path2.begin(), path2.end());

        int i = 0, j = 0;
        while (i < path1.size() && j < path2.size()) {
            if (path1[i] == path2[j]) {
                stepsMin = std::min(stepsMin, path1[i].steps + path2[j].steps);
                i++;
                j++;
            }
            if (path1[i] < path2[j]) {
                i++;
            }
            if (path1[i] > path2[j]) {
                j++;
            }
        }

        return stepsMin;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2019_day03::part_1("../2019/day03/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2019_day03::part_2("../2019/day03/input.in") << std::endl;

    return 0;
}
#endif
