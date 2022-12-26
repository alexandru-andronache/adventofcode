#include "file.h"
#include "utilities.h"
#include "verticalhexgrid.h"
#include <iostream>
#include <map>

namespace aoc2022_day24 {
    struct tile {
        int state;
        int time = 1000;
        bool isEmpty() {
            return state == 0;
        }
    };

    struct stateTime {
        int x;
        int y;
    };

    bool operator==(const tile& rhs, const tile& lhs) {
        return rhs.state == lhs.state && rhs.time == lhs.time;
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
        std::vector<std::vector<tile>> map(lines.size(), std::vector<tile>(lines[0].size(), {0, 1000}));
        std::map<char, int> input {{'#', 0}, {'>', 1}, {'<', 2}, {'v', 3}, {'^', 4}};

        for (int i = 0; i < lines.size(); ++i) {
            for (int j = 0; j < lines[0].size(); ++j) {
                if (input.contains(lines[i][j])) {
                    map[i][j].state |= (1 << input[lines[i][j]]);
                }
            }
        }

        while (std::find(states.begin(), states.end(), map) == states.end()) {
            states.push_back(map);
            std::vector<std::vector<tile>> newMap(lines.size(), std::vector<tile>(lines[0].size(), {0, 1000}));
            for (int i = 0; i < map.size(); ++i) {
                for (int j = 0; j < map[i].size(); ++j) {
                    if (map[i][j].state & (1 << 4)) {
                        if (map[i - 1][j].state & (1 << 0)) {
                            newMap[map.size() - 2][j].state |= (1 << 4);
                        }
                        else {
                            newMap[i - 1][j].state |= (1 << 4);
                        }
                    }
                    if (map[i][j].state & (1 << 3)) {
                        if (map[i + 1][j].state & (1 << 0)) {
                            newMap[1][j].state |= (1 << 3);
                        }
                        else {
                            newMap[i + 1][j].state |= (1 << 3);
                        }
                    }
                    if (map[i][j].state & (1 << 1)) {
                        if (map[i][j + 1].state & (1 << 0)) {
                            newMap[i][1].state |= (1 << 1);
                        }
                        else {
                            newMap[i][j + 1].state |= (1 << 1);
                        }
                    }
                    if (map[i][j].state & (1 << 2)) {
                        if (map[i][j - 1].state & (1 << 0)) {
                            newMap[i][map[0].size() - 2].state |= (1 << 2);
                        }
                        else {
                            newMap[i][j - 1].state |= (1 << 2);
                        }
                    }
                    if (map[i][j].state & (1 << 0)) {
                        newMap[i][j].state |= (1 << 0);
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
        std::vector<std::vector<tile>> map(lines.size(), std::vector<tile>(lines[0].size(), {0, 1000}));
        std::map<char, int> input {{'#', 0}, {'>', 1}, {'<', 2}, {'v', 3}, {'^', 4}};

        for (int i = 0; i < lines.size(); ++i) {
            for (int j = 0; j < lines[0].size(); ++j) {
                if (input.contains(lines[i][j])) {
                    map[i][j].state |= (1 << input[lines[i][j]]);
                }
            }
        }

        while (std::find(states.begin(), states.end(), map) == states.end()) {
            states.push_back(map);
            std::vector<std::vector<tile>> newMap(lines.size(), std::vector<tile>(lines[0].size(), {0, 1000}));
            for (int i = 0; i < map.size(); ++i) {
                for (int j = 0; j < map[i].size(); ++j) {
                    if (map[i][j].state & (1 << 4)) {
                        if (map[i - 1][j].state & (1 << 0)) {
                            newMap[map.size() - 2][j].state |= (1 << 4);
                        }
                        else {
                            newMap[i - 1][j].state |= (1 << 4);
                        }
                    }
                    if (map[i][j].state & (1 << 3)) {
                        if (map[i + 1][j].state & (1 << 0)) {
                            newMap[1][j].state |= (1 << 3);
                        }
                        else {
                            newMap[i + 1][j].state |= (1 << 3);
                        }
                    }
                    if (map[i][j].state & (1 << 1)) {
                        if (map[i][j + 1].state & (1 << 0)) {
                            newMap[i][1].state |= (1 << 1);
                        }
                        else {
                            newMap[i][j + 1].state |= (1 << 1);
                        }
                    }
                    if (map[i][j].state & (1 << 2)) {
                        if (map[i][j - 1].state & (1 << 0)) {
                            newMap[i][map[0].size() - 2].state |= (1 << 2);
                        }
                        else {
                            newMap[i][j - 1].state |= (1 << 2);
                        }
                    }
                    if (map[i][j].state & (1 << 0)) {
                        newMap[i][j].state |= (1 << 0);
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
