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
            std::bitset<32> gates;
        };
        struct position {
            int x{};
            int y{};
            std::bitset<32> gates;
        };
        struct state {
            int totalDistance{};
            int gate{};
            std::bitset<32> gates;
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
                                std::bitset<32> tmp = p.gates;
                                tmp.set(board[xx][yy] - 'a' + 1);
                                newPositions.push_back({xx, yy, tmp});
                            } else if (board[xx][yy] >= 'A' && board[xx][yy] <= 'Z' && dist[xx][yy] > dist[p.x][p.y] + 1) {
                                dist[xx][yy] = dist[p.x][p.y] + 1;
                                std::bitset<32> tmp = p.gates;
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
                bool operator() (const std::pair<std::bitset<32>, int> &b1, const std::pair<std::bitset<32>, int> &b2) const {
                    return b1.first.to_ullong() * 100 + b1.second < b2.first.to_ullong() * 100 + b2.second;
                }
            };
            std::map<std::pair<std::bitset<32>, int>, int, Comparer> minDistance;
            for (const auto& s : states) {
                for (int i = 0; i < size; ++i) {
                    if (!s.gates[i] && i != s.gate) {
                        std::bitset<32> keys = distance[s.gate][i].gates;
                        bool found = true;
                        for (int k = 0; k < keys.size(); ++k) {
                            if (keys[k]) {
                                if (!s.gates[k]) {
                                    found = false;
                                }
                            }
                        }
                        if (found) {
                            std::bitset<32> tmp = s.gates;
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
        std::vector<std::string> input = file::readFileAsArrayString(path);
        struct dist {
            int distance;
            std::bitset<32> gates;
        };
        std::vector<std::vector<char>> board(input.size(), std::vector<char>(input[0].size(), ' '));
        int size = 1;
        for (int i = 0; i < input.size(); ++i) {
            for (int j = 0; j < input[0].size(); ++j) {
                board[i][j] = input[i][j];
                if (board[i][j] >= 'a' && board[i][j] <= 'z') {
                    size++;
                }
            }
        }

        bool modified = false;
        int centerX = 0, centerY = 0;
        for (int i = 0; i < board.size() && !modified; ++i) {
            for (int j = 0; j < board[0].size() && !modified; ++j) {
                if (board[i][j] == '@') {
                    centerX = i;
                    centerY = j;
                    modified = true;
                    board[i][j] = board[i - 1][j] = board[i + 1][j] = board[i][j - 1] = board[i][j + 1] = '#';
                    board[i - 1][j - 1] = board[i - 1][j + 1] = board[i + 1][j - 1] = board[i + 1][j + 1] = '@';
                }
            }
        }

        std::array<std::vector<std::vector<dist>>, 4> distance; //(size, std::vector<dist>(size, {std::numeric_limits<int>::max(), {}}));
        std::fill(distance.begin(), distance.end(), std::vector<std::vector<dist>>(size, std::vector<dist>(size, {std::numeric_limits<int>::max(), {}})));

        struct pp {
            int x;
            int y;
            int startGate;
            dist d;
        };

        std::vector<std::pair<int, int>> directions {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        struct Rectangle{
            int startX;
            int startY;
            int endX;
            int endY;
            int index;
        };
        std::vector<Rectangle> rectangles{{0, 0, centerX, centerY, 0},
                                          {0, centerY, centerX, (int)board[0].size(), 1},
                                          {centerX, 0, (int)board.size(), centerY, 2},
                                          {centerX, centerY, (int)board.size(), (int)board[0].size(), 3}};

        for (const auto& r : rectangles) {
            for (int k = 0; k < size; ++k) {
                int startX = 0, startY = 0;
                char c = '@';
                if (k > 0) {
                    c = 'a' + k - 1;
                }
                for (int i = r.startX; i < r.endX; ++i) {
                    for (int j = r.startY; j < r.endY; ++j) {
                        if (board[i][j] == c) {
                            startX = i;
                            startY = j;
                        }
                    }
                }

                std::vector<pp> positions {{startX, startY, k, {0, {}}}};
                std::vector<std::vector<int>> distances(board.size(), std::vector<int>(board[0].size(), -1));
                distances[startX][startY] = 0;
                while (!positions.empty()) {
                    std::vector<pp> next;
                    for (const auto& p : positions) {
                        for (const auto& dir : directions) {
                            if (p.x + dir.first >= 0 && p.x + dir.first < board.size() && p.y + dir.second >= 0 && p.y + dir.second < board[0].size() &&
                            (distances[p.x + dir.first][p.y + dir.second] == -1 || distances[p.x + dir.first][p.y + dir.second] + 1 < p.d.distance)
                            && board[p.x + dir.first][p.y + dir.second] != '#') {
                                distances[p.x + dir.first][p.y + dir.second] = p.d.distance + 1;
                                if (board[p.x + dir.first][p.y + dir.second] == '.' || board[p.x + dir.first][p.y + dir.second] == '@') {
                                    next.push_back({p.x + dir.first, p.y + dir.second, p.startGate, {p.d.distance + 1, p.d.gates}});
                                }
                                else if (board[p.x + dir.first][p.y + dir.second] >= 'A' && board[p.x + dir.first][p.y + dir.second] <= 'Z') {
                                    std::bitset<32> tmp = p.d.gates;
                                    tmp.set(board[p.x + dir.first][p.y + dir.second] - 'A' + 1);
                                    next.push_back({p.x + dir.first, p.y + dir.second, p.startGate, {p.d.distance + 1, tmp}});
                                }
                                else if (board[p.x + dir.first][p.y + dir.second] >= 'a' && board[p.x + dir.first][p.y + dir.second] <= 'z') {
                                    if (distance[r.index][p.startGate][board[p.x + dir.first][p.y + dir.second] - 'a' + 1].distance > p.d.distance + 1) {
                                        distance[r.index][p.startGate][board[p.x + dir.first][p.y + dir.second] - 'a' + 1].distance = p.d.distance + 1;
                                        distance[r.index][p.startGate][board[p.x + dir.first][p.y + dir.second] - 'a' + 1].gates = p.d.gates;
                                    }
                                    next.push_back({p.x + dir.first, p.y + dir.second, p.startGate, {p.d.distance + 1, p.d.gates}});
                                }
                            }
                        }
                    }
                    positions = next;
                }
            }
        }

        struct rr {
            int currentIndex;
            int totalDistance;
            std::bitset<32> collectedKeys;
            std::bitset<32> visited;
        };
        int minDistance = std::numeric_limits<int>::max();
        rr startPos;
        startPos.currentIndex = 0;
        startPos.totalDistance = 0;
        startPos.collectedKeys.set(0);
        startPos.visited.set(0);
        std::vector<std::array<rr, 4>> routes {{startPos, startPos, startPos, startPos}};

        struct Comparer {
            bool operator() (const std::pair<std::array<int, 4>, std::bitset<32>> &b1, const std::pair<std::array<int, 4>, std::bitset<32>> &b2) const {
                for (int i = 0; i < 4; ++i) {
                    if (b1.first[i] != b2.first[i]) {
                        return b1.first[i] < b2.first[i];
                    }
                }
                return b1.second.to_ulong() < b2.second.to_ulong();
            }
        };

        std::map<std::pair<std::array<int, 4>, std::bitset<32>>, int, Comparer> minimDistances;
        while (!routes.empty()) {
            std::vector<std::array<rr, 4>> newRoutes;
            for (const auto& r : routes) {
                if (r[0].totalDistance + r[1].totalDistance + r[2].totalDistance + r[3].totalDistance < minDistance) {
                    for (int pp = 0; pp < r.size(); ++pp) {
                        for (int i = 0; i < size; ++i) {
                            if (distance[pp][r[pp].currentIndex][i].distance != std::numeric_limits<int>::max() && !r[pp].visited[i]) {
                                std::bitset<32> allGates = distance[pp][r[pp].currentIndex][i].gates;

                                std::bitset<32> allKeys(false);
                                for (int ppp = 0; ppp < r.size(); ++ppp) {
                                    auto keys = r[ppp].collectedKeys;
                                    for (int l = 0; l < keys.size(); ++l) {
                                        if (keys[l]) {
                                            allKeys[l] = true;
                                        }
                                    }
                                }

                                bool foundAllKeys = true;
                                for (int j = 1; j < size; ++j) {
                                    if (allGates[j] && !allKeys[j]) {
                                        foundAllKeys = false;
                                    }
                                }
                                if (foundAllKeys) {
                                    std::array<int, 4> positions{r[0].currentIndex, r[1].currentIndex, r[2].currentIndex, r[3].currentIndex};
                                    positions[pp] = i;

                                    std::array<rr, 4> newVector = r;
                                    newVector[pp].collectedKeys[i] = true;
                                    newVector[pp].visited[i] = true;
                                    newVector[pp].currentIndex = i;
                                    newVector[pp].totalDistance += distance[pp][r[pp].currentIndex][i].distance;

                                    std::bitset<32> allKeysCollected(false);
                                    for (int ppp = 0; ppp < r.size(); ++ppp) {
                                        auto keys = newVector[ppp].collectedKeys;
                                        for (int l = 0; l < keys.size(); ++l) {
                                            if (keys[l]) {
                                                allKeysCollected[l] = true;
                                            }
                                        }
                                    }

                                    if (minimDistances.find({positions, allKeysCollected}) == minimDistances.end()) {
                                        minimDistances[{positions, allKeysCollected}] = r[0].totalDistance + r[1].totalDistance + r[2].totalDistance + r[3].totalDistance + distance[pp][r[pp].currentIndex][i].distance;
                                        newRoutes.push_back(newVector);
                                    }
                                    else {
                                        if (minimDistances[{positions, allKeysCollected}] > r[0].totalDistance + r[1].totalDistance + r[2].totalDistance + r[3].totalDistance + distance[pp][r[pp].currentIndex][i].distance) {
                                            minimDistances[{positions, allKeysCollected}] = r[0].totalDistance + r[1].totalDistance + r[2].totalDistance + r[3].totalDistance + distance[pp][r[pp].currentIndex][i].distance;
                                            newRoutes.push_back(newVector);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            routes = newRoutes;

            for (const auto& r : routes) {
                std::bitset<32> allKeys(false);
                for (int i = 0; i < 4; ++i) {
                    auto keys = r[i].collectedKeys;
                    for (int j = 0; j < 32; ++j) {
                        if (keys[j]) {
                            allKeys[j] = true;
                        }
                    }
                }
                if (allKeys.count() == size) {
                    if (minDistance > r[0].totalDistance + r[1].totalDistance + r[2].totalDistance + r[3].totalDistance) {
                        minDistance = r[0].totalDistance + r[1].totalDistance + r[2].totalDistance + r[3].totalDistance;
                    }
                }
            }
        }

        return minDistance;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2019_day18::part_1("../2019/day18/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2019_day18::part_2("../2019/day18/input.in") << std::endl;

    return 0;
}
#endif
