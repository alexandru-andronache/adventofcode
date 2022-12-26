#include "file.h"
#include "utilities.h"
#include "verticalhexgrid.h"
#include <iostream>

namespace aoc2022_day24 {
    struct tile {
        bool isWall = false;
        bool goLeft = false;
        bool goRight = false;
        bool goUp = false;
        bool goDown = false;
        int time = 1000;
        bool isEmpty() {
            return !isWall && !goLeft && !goRight && !goUp && !goDown;
        }
    };

    struct stateTime {
        int x;
        int y;
    };

    bool operator==(const tile& rhs, const tile& lhs) {
        return rhs.isWall == lhs.isWall && rhs.goLeft == lhs.goLeft && rhs.goRight == lhs.goRight &&
               rhs.goUp == lhs.goUp && rhs.goDown == lhs.goDown && rhs.time == lhs.time;
    }

    void print(const std::vector<std::vector<tile>>& map, bool printSteps = false) {
        for (int i = 0; i < map.size(); ++i) {
            for (int j = 0; j < map[0].size(); ++j) {
                if (map[i][j].isWall) {
                    std::cout << "#";
                }
                else if ((map[i][j].goLeft + map[i][j].goRight + map[i][j].goUp + map[i][j].goDown > 1) && (!printSteps)) {
                    std::cout << map[i][j].goLeft + map[i][j].goRight + map[i][j].goUp + map[i][j].goDown;
                }
                else if (map[i][j].goDown) {
                    std::cout << "v";
                }
                else if (map[i][j].goUp) {
                    std::cout << "^";
                }
                else if (map[i][j].goRight) {
                    std::cout << ">";
                }
                else if (map[i][j].goLeft) {
                    std::cout << "<";
                }
                else {
                    if (printSteps) {
                        std::cout << map[i][j].time % 10;
                    }
                    else {
                        std::cout << ".";
                    }

                }
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    int move(int startX, int startY,
             int endX, int endY,
             int startLoop,
             const std::vector<std::vector<std::vector<tile>>>& s,
             int& index) {
        std::vector<std::vector<std::vector<tile>>> states = s;

        std::vector<stateTime> positions{{startX, startY}};
        std::vector<std::pair<int, int>> dir {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        int time = 0;
        states[0][0][1].time = 0;
        while (!positions.empty()) {
            index++;
            time++;
            if (index == states.size()) {
                index = startLoop;
            }

            std::vector<stateTime> newPositions;
            for (const auto& p : positions) {
                for (const auto& d : dir) {
                    if (p.x + d.first >= 0 && p.x + d.first < states[index].size() &&
                        p.y + d.second >= 0 && p.y + d.second < states[index][0].size() &&
                        states[index][p.x + d.first][p.y + d.second].isEmpty() &&
                        states[index][p.x + d.first][p.y + d.second].time > time) {
                        newPositions.push_back({p.x + d.first, p.y + d.second});
                        states[index][p.x + d.first][p.y + d.second].time = time;
                    }
                }
                if (states[index][p.x][p.y].time > time && states[index][p.x][p.y].isEmpty()) {
                    states[index][p.x][p.y].time = time;
                    newPositions.push_back({p. x, p.y});
                }
            }

            positions = newPositions;
            for (const auto& p : positions) {
                if (p.x == endX && p.y == endY) {
                    return time;
                }
            }
        }

        return 0;
    }

    int part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::vector<std::vector<std::vector<tile>>> states;
        std::vector<std::vector<tile>> map(lines.size(), std::vector<tile>(lines[0].size(), {false, false, false, false, false, 1000}));

        for (int i = 0; i < lines.size(); ++i) {
            for (int j = 0; j < lines[0].size(); ++j) {
                if (lines[i][j] == '#') {
                    map[i][j].isWall = true;
                }
                else if (lines[i][j] == '>') {
                    map[i][j].goRight = true;
                }
                else if (lines[i][j] == '<') {
                    map[i][j].goLeft = true;
                }
                else if (lines[i][j] == 'v') {
                    map[i][j].goDown = true;
                }
                else if (lines[i][j] == '^') {
                    map[i][j].goUp = true;
                }
            }
        }

        while (std::find(states.begin(), states.end(), map) == states.end()) {
            states.push_back(map);
            std::vector<std::vector<tile>> newMap(lines.size(), std::vector<tile>(lines[0].size(), {false, false, false, false, false, 1000}));
            for (int i = 0; i < map.size(); ++i) {
                for (int j = 0; j < map[i].size(); ++j) {
                    if (map[i][j].goUp) {
                        if (map[i - 1][j].isWall) {
                            newMap[map.size() - 2][j].goUp = true;
                        }
                        else {
                            newMap[i - 1][j].goUp = true;
                        }
                    }
                    if (map[i][j].goDown) {
                        if (map[i + 1][j].isWall) {
                            newMap[1][j].goDown = true;
                        }
                        else {
                            newMap[i + 1][j].goDown = true;
                        }
                    }
                    if (map[i][j].goRight) {
                        if (map[i][j + 1].isWall) {
                            newMap[i][1].goRight = true;
                        }
                        else {
                            newMap[i][j + 1].goRight = true;
                        }
                    }
                    if (map[i][j].goLeft) {
                        if (map[i][j - 1].isWall) {
                            newMap[i][map[0].size() - 2].goLeft = true;
                        }
                        else {
                            newMap[i][j - 1].goLeft = true;
                        }
                    }
                    if (map[i][j].isWall) {
                        newMap[i][j].isWall = true;
                    }
                }
            }

            map = newMap;
        }

        auto startLoop = std::find(states.begin(), states.end(), map) - states.begin();
        int index = 0;

        return move(0, 1, states[0].size() - 1, states[0][0].size() - 2, startLoop, states, index);
    }

    int part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::vector<std::vector<std::vector<tile>>> states;
        std::vector<std::vector<tile>> map(lines.size(), std::vector<tile>(lines[0].size(), {false, false, false, false, false, 1000}));

        for (int i = 0; i < lines.size(); ++i) {
            for (int j = 0; j < lines[0].size(); ++j) {
                if (lines[i][j] == '#') {
                    map[i][j].isWall = true;
                }
                else if (lines[i][j] == '>') {
                    map[i][j].goRight = true;
                }
                else if (lines[i][j] == '<') {
                    map[i][j].goLeft = true;
                }
                else if (lines[i][j] == 'v') {
                    map[i][j].goDown = true;
                }
                else if (lines[i][j] == '^') {
                    map[i][j].goUp = true;
                }
            }
        }

        while (std::find(states.begin(), states.end(), map) == states.end()) {
            states.push_back(map);
            std::vector<std::vector<tile>> newMap(lines.size(), std::vector<tile>(lines[0].size(), {false, false, false, false, false, 1000}));
            for (int i = 0; i < map.size(); ++i) {
                for (int j = 0; j < map[i].size(); ++j) {
                    if (map[i][j].goUp) {
                        if (map[i - 1][j].isWall) {
                            newMap[map.size() - 2][j].goUp = true;
                        }
                        else {
                            newMap[i - 1][j].goUp = true;
                        }
                    }
                    if (map[i][j].goDown) {
                        if (map[i + 1][j].isWall) {
                            newMap[1][j].goDown = true;
                        }
                        else {
                            newMap[i + 1][j].goDown = true;
                        }
                    }
                    if (map[i][j].goRight) {
                        if (map[i][j + 1].isWall) {
                            newMap[i][1].goRight = true;
                        }
                        else {
                            newMap[i][j + 1].goRight = true;
                        }
                    }
                    if (map[i][j].goLeft) {
                        if (map[i][j - 1].isWall) {
                            newMap[i][map[0].size() - 2].goLeft = true;
                        }
                        else {
                            newMap[i][j - 1].goLeft = true;
                        }
                    }
                    if (map[i][j].isWall) {
                        newMap[i][j].isWall = true;
                    }
                }
            }

            map = newMap;
        }

        auto startLoop = std::find(states.begin(), states.end(), map) - states.begin();
        int index = 0;

        int time1 = move(0, 1, states[0].size() - 1, states[0][0].size() - 2, startLoop, states, index);
        int time2 = move(states[0].size() - 1, states[0][0].size() - 2, 0, 1, startLoop, states, index);
        int time3 = move(0, 1, states[0].size() - 1, states[0][0].size() - 2, startLoop, states, index);

        return time1 + time2 + time3;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2022_day24::part_1("../2022/day24/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2022_day24::part_2("../2022/day24/input.in") << std::endl;

    return 0;
}
#endif
