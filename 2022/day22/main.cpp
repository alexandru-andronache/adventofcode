#include "file.h"
#include "utilities.h"
#include <iostream>
#include <complex>
#include <map>

namespace aoc2022_day22 {
    enum type {
        nothing = 0,
        free = 1,
        wall = 2
    };

    std::pair<int, int> getNext_Part1(int x, int y, int maxX, int maxY, std::complex<int> dir) {
        x = x + dir.real();
        y = y + dir.imag();
        if (x < 0) {
            x = maxX - 1;
        }
        if (x >= maxX) {
            x = 0;
        }
        if (y < 0) {
            y = maxY - 1;
        }
        if (y >= maxY) {
            y = 0;
        }

        return {x, y};
    }

    int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::map<char, type> terrain {{'#', type::wall}, {'.', type::free}, {' ', type::nothing}};
        auto max = 0UL;
        for (const auto& l : input) {
            if (l == "") break;
            max = std::max(max, l.size());
        }
        std::vector<std::vector<type>> map(input.size() - 2, std::vector<type>(max, type::nothing));
        std::string instructions = input.back();
        int row = 0;

        for (const auto& l : input) {
            if (l == "") {
                break;
            }
            for (int i = 0; i < l.size(); ++i) {
                map[row][i] = terrain[l[i]];
            }
            row++;
        }

        int index = 0;
        int currentX = 0, currentY = 0;
        while (map[currentX][currentY] == type::nothing) {
            currentY++;
        }

        std::complex direction{0, 1};
        while (index < instructions.size()) {
            int steps = utils::getNumber(instructions, index);
            for (int i = 0; i < steps; ++i) {
                std::pair<int, int> next = getNext_Part1(currentX, currentY, map.size(), max, direction);
//                if (map[next.first][next.second] == type::free) {
//                    currentX += direction.real();
//                    currentY += direction.imag();
//                }
//                else if (map[next.first][next.second] == type::nothing) {
//                    while (map[next.first][next.second] == type::nothing) {
//                        currentX += direction.real();
//                        currentY += direction.imag();
//                        next = getNext_Part1(currentX, currentY, map.size(), max, direction);
//                    }
//                }

                if (map[next.first][next.second] == type::nothing) {
                    currentX += direction.real();
                    currentY += direction.imag();
                    if (currentX < 0) {
                        currentX = map.size() - 1;
                    }
                    else if (currentX == map.size()) {
                        currentX = 0;
                    }
                    else if (currentY < 0) {
                        currentY = max - 1;
                    }
                    else if (currentY == max) {
                        currentY = 0;
                    }
                    while (map[currentX][currentY] == type::nothing) {
                        currentX += direction.real();
                        currentY += direction.imag();
                        if (currentX < 0) {
                            currentX = map.size() - 1;
                        }
                        else if (currentX == map.size()) {
                            currentX = 0;
                        }
                        else if (currentY < 0) {
                            currentY = max - 1;
                        }
                        else if (currentY == max) {
                            currentY = 0;
                        }
                    }
                }
                else if (map[next.first][next.second] == type::free) {
                    currentX += direction.real();
                    currentY += direction.imag();
                }
            }
            if (index < instructions.size()) {
                if (instructions[index] == 'L') {
                    direction = direction * std::complex{0, 1};
                } else {
                    direction = direction * std::complex{0, -1};
                }
                index++;
            }
        }

        int sol = (currentX + 1) * 1000 + (currentY + 1) * 4;
        if (direction == std::complex{0, 1}) {
            return sol;
        }
        else if (direction == std::complex{1, 0}) {
            return sol + 1;
        }
        else if (direction == std::complex{0, -1}) {
            return sol + 2;
        }
        else {
            return sol + 3;
        }
    }

    struct newPos {
        int x;
        int y;
        std::complex<int> newDir;
    };

    struct Class1Compare
    {
        bool operator() (const newPos& lhs, const newPos& rhs) const
        {
            if (lhs.x != rhs.x) {
                return lhs.x < rhs.x;
            }
            if (lhs.y != rhs.y) {
                return lhs.y < rhs.y;
            }
            if (lhs.newDir.real() != rhs.newDir.real()) {
                return lhs.newDir.real() < rhs.newDir.real();
            }
            if (lhs.newDir.imag() != rhs.newDir.imag()) {
                return lhs.newDir.imag() < rhs.newDir.imag();
            }
            return false;
        }
    };

    int part_2(std::string_view path, int size) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::map<char, type> terrain {{'#', type::wall}, {'.', type::free}, {' ', type::nothing}};
        auto max = 0UL;
        for (const auto& l : input) {
            if (l == "") break;
            max = std::max(max, l.size());
        }
        std::vector<std::vector<type>> map(input.size() - 2, std::vector<type>(max, type::nothing));
        std::string instructions = input.back();
        int row = 0;

        for (const auto& l : input) {
            if (l == "") {
                break;
            }
            for (int i = 0; i < l.size(); ++i) {
                map[row][i] = terrain[l[i]];
            }
            row++;
        }

        int index = 0;
        std::complex direction{0, 1};

        int currentX = 0, currentY = 0;
        while (map[currentX][currentY] == type::nothing) {
            currentY++;
        }

        std::map<newPos, newPos, Class1Compare> portals;

        // box 1
        for (int i = 50; i < 100; ++i) {
            portals.insert({{-1, i, {-1, 0}}, {150 + i - 50, 0, {0, 1}}});
            portals.insert({{150 + i - 50, -1, {0, -1}}, {0, i, {1, 0}}});
        }

        for (int i = 0; i < 50; ++i) {
            portals.insert({{i, 49, {0, -1}}, {149 - i, 0, {0, 1}}});
            portals.insert({{149 - i, -1, {0, -1}}, {i, 50, {0, 1}}});
        }

        // box 2
        for (int i = 100; i < 150; ++i) {
            portals.insert({{-1, i, {-1, 0}}, {199, i - 100, {-1, 0}}});
            portals.insert({{200, i - 100, {1, 0}}, {0, i, {1, 0}}});
        }

        for (int i = 0; i < 50; ++i) {
            portals.insert({{i, 150, {0, 1}}, {149 - i, 99, {0, -1}}});
            portals.insert({{149 - i, 100, {0, 1}}, {i, 149, {0, -1}}});
        }

        for (int i = 100; i < 150; ++i) {
            portals.insert({{50, i, {1, 0}}, {50 + i - 100, 99, {0, -1}}});
            portals.insert({{50 + i - 100, 100, {0, 1}}, {49, i, {-1, 0}}});
        }

        // box 3
        for (int i = 50; i < 100; ++i) {
            portals.insert({{i, 49, {0, -1}}, {100, i - 50, {1, 0}}});
            portals.insert({{99, i - 50, {-1, 0}}, {i, 50, {0, 1}}});
        }

        // box 4
        for (int i = 50; i < 100; ++i) {
            portals.insert({{150, i, {1, 0}},  {150 + i - 50, 49, {0, -1}}});
            portals.insert({{150 + i - 50, 50, {0, 1}}, {149, i, {-1, 0}}});
        }

        while (index < instructions.size()) {
            int steps = utils::getNumber(instructions, index);
            for (int step = 0; step < steps; ++step) {
                int nextX = currentX + direction.real();
                int nextY = currentY + direction.imag();

                bool found = false;
                std::complex<int> d;

                if (portals.find({nextX, nextY, direction}) != portals.end()) {
                    newPos t = portals[{nextX, nextY, direction}];
                    nextX = t.x;
                    nextY = t.y;
                    d = t.newDir;
                    found = true;
                }
                if (map[nextX][nextY] == type::free) {
                    if (found) {
                        direction = d;
                    }
                    currentX = nextX;
                    currentY = nextY;
                }
            }
            if (index < instructions.size()) {
                if (instructions[index] == 'L') {
                    direction = direction * std::complex{0, 1};
                } else {
                    direction = direction * std::complex{0, -1};
                }
                index++;
            }
        }

        int sol = (currentX + 1) * 1000 + (currentY + 1) * 4;
        if (direction == std::complex{0, 1}) {
            return sol;
        }
        else if (direction == std::complex{1, 0}) {
            return sol + 1;
        }
        else if (direction == std::complex{0, -1}) {
            return sol + 2;
        }
        else {
            return sol + 3;
        }
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2022_day22::part_1("../2022/day22/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2022_day22::part_2("../2022/day22/input.in") << std::endl;

    return 0;
}
#endif
