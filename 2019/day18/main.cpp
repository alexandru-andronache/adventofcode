#include "file.h"
#include "utilities.h"
#include "direction.h"
#include <iostream>
#include <map>
#include <array>

namespace aoc2019_day18 {

    int part_1(std::string_view path) {
        struct connections {
            int distance{};
            std::bitset<27> gates;
        };
        struct position {
            int x{};
            int y{};
            std::bitset<27> gates;
        };
        struct state {
            int totalDistance{};
            int gate{};
            std::bitset<27> gates;
        };

        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::vector<char>> board(input.size(), std::vector<char>(input[0].size(), ' '));
        std::vector<std::pair<int, int>> startPoints;

        int size = 1;
        for (const auto& line : input) {
            size += std::count_if(line.begin(), line.end(), [](const auto& l) {
                return l >= 'a' && l <= 'z';
            });
        }

        std::vector<std::vector<connections>> distance(size, std::vector<connections>(size, {std::numeric_limits<int>::max(), {}}));

        for (int i = 0; i < input.size(); ++i) {
            std::copy(input[i].begin(), input[i].end(), board[i].begin());
        }

        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[i].size(); ++j) {
                if (board[i][j] == '@') {
                    startPoints.emplace_back(i, j);
                    board[i][j] = '.';
                }
            }
        }

        for (int k = 'a'; k <= 'z'; ++k) {
            for (int i = 0; i < board.size(); ++i) {
                for (int j = 0; j < board[i].size(); ++j) {
                    if (board[i][j] == k) {
                        startPoints.emplace_back(i, j);
                    }
                }
            }
        }

        for (int k = 0; k < startPoints.size(); ++k) {
            std::vector<std::vector<int>> dist(input.size(),
                                               std::vector<int>(input[0].size(), std::numeric_limits<int>::max() - 10));
            std::vector<position> positions;
            direction::Direction dir;

            positions.push_back({startPoints[k].first, startPoints[k].second, {}});
            dist[startPoints[k].first][startPoints[k].second] = 0;

            while (!positions.empty()) {
                std::vector<position> newPositions;
                for (const auto &p: positions) {
                    for (const auto &d: dir.directions) {
                        int xx = p.x + d.x;
                        int yy = p.y + d.y;

                        if (xx >= 0 && xx < board.size() && yy >= 0 && yy < board[0].size()) {
                            if (board[xx][yy] == '.' && dist[xx][yy] > dist[p.x][p.y] + 1) {
                                dist[xx][yy] = dist[p.x][p.y] + 1;
                                newPositions.push_back({xx, yy, p.gates});
                            } else if (board[xx][yy] >= 'a' && board[xx][yy] <= 'z' && dist[xx][yy] > dist[p.x][p.y] + 1) {
                                dist[xx][yy] = dist[p.x][p.y] + 1;
                                distance[k][board[xx][yy] - 'a' + 1].distance = dist[p.x][p.y] + 1;
                                distance[k][board[xx][yy] - 'a' + 1].gates = p.gates;
                                std::bitset<27> tmp = p.gates;
                                tmp.set(board[xx][yy] - 'a' + 1);
                                newPositions.push_back({xx, yy, tmp});
                            } else if (board[xx][yy] >= 'A' && board[xx][yy] <= 'Z' && dist[xx][yy] > dist[p.x][p.y] + 1) {
                                dist[xx][yy] = dist[p.x][p.y] + 1;
                                std::bitset<27> tmp = p.gates;
                                tmp.set(board[xx][yy] - 'A' + 1);
                                newPositions.push_back({xx, yy, tmp});
                            }
                        }
                    }
                }
                positions = newPositions;
            }
        }



        std::vector<state> states;
        states.push_back({0, 0, {}});
        states[0].gates[0] = true;
        int sol = std::numeric_limits<int>::max();

        while (!states.empty()) {
            std::vector<state> newStates;
            struct Comparer {
                bool operator() (const std::pair<std::bitset<27>, int> &b1, const std::pair<std::bitset<27>, int> &b2) const {
                    return b1.first.to_ullong() * 100 + b1.second < b2.first.to_ullong() * 100 + b2.second;
                }
            };
            std::map<std::pair<std::bitset<27>, int>, int, Comparer> minDistance;
            for (const auto& s : states) {
                for (int i = 0; i < size; ++i) {
                    if (!s.gates[i] && i != s.gate) {
                        std::bitset<27> keys = distance[s.gate][i].gates;
                        bool found = true;
                        for (int k = 0; k < keys.size(); ++k) {
                            if (keys[k]) {
                                if (!s.gates[k]) {
                                    found = false;
                                }
                            }
                        }
                        if (found) {
                            std::bitset<27> tmp = s.gates;
                            tmp.set(i);
                            if (minDistance.count({tmp, i}) == 0 || (minDistance.count({tmp, i}) > 0 && minDistance[{tmp, i}] > s.totalDistance + distance[s.gate][i].distance)) {
                                newStates.push_back({s.totalDistance + distance[s.gate][i].distance, i, tmp});
                                minDistance[{tmp, i}] = s.totalDistance + distance[s.gate][i].distance;
                            }
                        }
                    }
                }
            }
            states = newStates;
            for (const auto& s : states) {
                bool valid = true;
                for (int i = 0; i < size; ++i) {
                    if (!s.gates[i]) {
                        valid = false;
                    }
                }
                if (valid) {
                    sol = std::min(sol, s.totalDistance);
                }
            }
        }

        return sol;
    }

    int part_2(std::string_view path) {
        struct connections {
            int distance{};
            std::bitset<30> gates;
        };
        struct position {
            int x{};
            int y{};
            std::bitset<30> gates;
        };
        struct state {
            int totalDistance{};
            std::array<int, 4> gate{};
            std::bitset<30> gates;
        };

        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::vector<char>> board(input.size(), std::vector<char>(input[0].size(), ' '));
        std::vector<std::pair<int, int>> startPoints;

        int size = 4;
        for (const auto& line : input) {
            size += std::count_if(line.begin(), line.end(), [](const auto& l) {
                return l >= 'a' && l <= 'z';
            });
        }

        std::vector<std::vector<connections>> distance(size, std::vector<connections>(size, {std::numeric_limits<int>::max(), {}}));

        for (int i = 0; i < input.size(); ++i) {
            std::copy(input[i].begin(), input[i].end(), board[i].begin());
        }

        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[i].size(); ++j) {
                if (board[i][j] == '@') {
                    startPoints.emplace_back(i - 1, j - 1);
                    startPoints.emplace_back(i - 1, j + 1);
                    startPoints.emplace_back(i + 1, j - 1);
                    startPoints.emplace_back(i + 1, j + 1);
                    board[i][j] = '#';
                    board[i - 1][j] = '#';
                    board[i][j - 1] = '#';
                    board[i][j + 1] = '#';
                    board[i + 1][j] = '#';
                }
            }
        }

        for (int k = 'a'; k <= 'z'; ++k) {
            for (int i = 0; i < board.size(); ++i) {
                for (int j = 0; j < board[i].size(); ++j) {
                    if (board[i][j] == k) {
                        startPoints.emplace_back(i, j);
                    }
                }
            }
        }

        for (int k = 0; k < startPoints.size(); ++k) {
            std::vector<std::vector<int>> dist(input.size(),
                                               std::vector<int>(input[0].size(), std::numeric_limits<int>::max() - 10));
            std::vector<position> positions;
            direction::Direction dir;

            positions.push_back({startPoints[k].first, startPoints[k].second, {}});
            dist[startPoints[k].first][startPoints[k].second] = 0;

            while (!positions.empty()) {
                std::vector<position> newPositions;
                for (const auto &p: positions) {
                    for (const auto &d: dir.directions) {
                        int xx = p.x + d.x;
                        int yy = p.y + d.y;

                        if (xx >= 0 && xx < board.size() && yy >= 0 && yy < board[0].size()) {
                            if (board[xx][yy] == '.' && dist[xx][yy] > dist[p.x][p.y] + 1) {
                                dist[xx][yy] = dist[p.x][p.y] + 1;
                                newPositions.push_back({xx, yy, p.gates});
                            } else if (board[xx][yy] >= 'a' && board[xx][yy] <= 'z' && dist[xx][yy] > dist[p.x][p.y] + 1) {
                                dist[xx][yy] = dist[p.x][p.y] + 1;
                                distance[k][board[xx][yy] - 'a' + 4].distance = dist[p.x][p.y] + 1;
                                distance[k][board[xx][yy] - 'a' + 4].gates = p.gates;
                                std::bitset<30> tmp = p.gates;
                                tmp.set(board[xx][yy] - 'a' + 4);
                                newPositions.push_back({xx, yy, tmp});
                            } else if (board[xx][yy] >= 'A' && board[xx][yy] <= 'Z' && dist[xx][yy] > dist[p.x][p.y] + 1) {
                                dist[xx][yy] = dist[p.x][p.y] + 1;
                                std::bitset<30> tmp = p.gates;
                                tmp.set(board[xx][yy] - 'A' + 4);
                                newPositions.push_back({xx, yy, tmp});
                            }
                        }
                    }
                }
                positions = newPositions;
            }
        }



        std::vector<state> states;
        states.push_back({0, {0, 1, 2, 3}, {}});
        states[0].gates[0] = true;
        states[0].gates[1] = true;
        states[0].gates[2] = true;
        states[0].gates[3] = true;
        int sol = std::numeric_limits<int>::max();

        while (!states.empty()) {
            std::vector<state> newStates;
            struct Comparer {
                bool operator() (const std::pair<std::bitset<30>, std::array<int, 4>> &b1, const std::pair<std::bitset<30>, std::array<int, 4>> &b2) const {
                    unsigned long long a = b1.first.to_ullong();
                    for (int i = 0; i < b1.second.size(); ++i) {
                        a = a * 100 + b1.second[i];
                    }

                    unsigned long long b = b2.first.to_ullong();
                    for (int i = 0; i < b2.second.size(); ++i) {
                        b = b * 100 + b2.second[i];
                    }

                    return a < b;
                }
            };
            std::map<std::pair<std::bitset<30>, std::array<int, 4>>, int, Comparer> minDistance;
            for (const auto& s : states) {
                for (int i = 0; i < size; ++i) {
                    for (int j = 0; j < s.gate.size(); ++j) {
                        if (!s.gates[i] && i != s.gate[j]) {
                            std::bitset<30> keys = distance[s.gate[j]][i].gates;
                            bool found = distance[s.gate[j]][i].distance != std::numeric_limits<int>::max();
                            for (int k = 0; k < keys.size(); ++k) {
                                if (keys[k]) {
                                    if (!s.gates[k]) {
                                        found = false;
                                    }
                                }
                            }
                            if (found) {
                                std::bitset<30> tmp = s.gates;
                                tmp.set(i);
                                std::array<int, 4> tmpGates = s.gate;
                                tmpGates[j] = i;
                                if (minDistance.count({tmp, tmpGates}) == 0 || (minDistance.count({tmp, tmpGates}) > 0 &&
                                                                         minDistance[{tmp, tmpGates}] > s.totalDistance +
                                                                                                 distance[s.gate[j]][i].distance)) {
                                    newStates.push_back({s.totalDistance + distance[s.gate[j]][i].distance, tmpGates, tmp});
                                    minDistance[{tmp, tmpGates}] = s.totalDistance + distance[s.gate[j]][i].distance;
                                }
                            }
                        }
                    }
                }
            }
            states = newStates;
            for (const auto& s : states) {
                bool valid = true;
                for (int i = 0; i < size; ++i) {
                    if (!s.gates[i]) {
                        valid = false;
                    }
                }
                if (valid) {
                    sol = std::min(sol, s.totalDistance);
                }
            }
        }

        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2019_day18::part_1("../2019/day18/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2019_day18::part_2("../2019/day18/input.in") << std::endl;

    return 0;
}
#endif
