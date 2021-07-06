#include "file.h"
#include "utilities.h"
#include <iostream>
#include <map>
#include <array>

namespace aoc2019_day18 {
    int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        struct connections {
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

        std::vector<std::vector<connections>> distance(size, std::vector<connections>(size, {std::numeric_limits<int>::max(), {}}));

        struct pp {
            int x;
            int y;
            int startGate;
            connections connection;
        };

        std::vector<std::pair<int, int>> directions {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        for (int k = 0; k < size; ++k) {
            int startX = 0, startY = 0;
            char c = '@';
            if (k > 0) {
                c = 'a' + k - 1;
            }
            for (int i = 0; i < board.size(); ++i) {
                for (int j = 0; j < board[0].size(); ++j) {
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
                        if ((distances[p.x + dir.first][p.y + dir.second] == -1 || distances[p.x + dir.first][p.y + dir.second] + 1 < p.connection.distance)
                        && board[p.x + dir.first][p.y + dir.second] != '#') {
                            distances[p.x + dir.first][p.y + dir.second] = p.connection.distance + 1;
                            if (board[p.x + dir.first][p.y + dir.second] == '.' || board[p.x + dir.first][p.y + dir.second] == '@') {
                                next.push_back({p.x + dir.first, p.y + dir.second, p.startGate, {p.connection.distance + 1, p.connection.gates}});
                            }
                            else if (board[p.x + dir.first][p.y + dir.second] >= 'A' && board[p.x + dir.first][p.y + dir.second] <= 'Z') {
                                std::bitset<32> tmp = p.connection.gates;
                                tmp.set(board[p.x + dir.first][p.y + dir.second] - 'A' + 1);
                                next.push_back({p.x + dir.first, p.y + dir.second, p.startGate, {p.connection.distance + 1, tmp}});
                            }
                            else if (board[p.x + dir.first][p.y + dir.second] >= 'a' && board[p.x + dir.first][p.y + dir.second] <= 'z') {
                                if (distance[p.startGate][board[p.x + dir.first][p.y + dir.second] - 'a' + 1].distance > p.connection.distance + 1) {
                                    distance[p.startGate][board[p.x + dir.first][p.y + dir.second] - 'a' + 1].distance = p.connection.distance + 1;
                                    distance[p.startGate][board[p.x + dir.first][p.y + dir.second] - 'a' + 1].gates = p.connection.gates;
                                }
                                next.push_back({p.x + dir.first, p.y + dir.second, p.startGate, {p.connection.distance + 1, p.connection.gates}});
                            }
                        }
                    }
                }
                positions = next;
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
        std::vector<rr> routes {startPos};

        struct Comparer {
            bool operator() (const std::pair<int, std::bitset<32>> &b1, const std::pair<int, std::bitset<32>> &b2) const {
                if (b1.first != b2.first) {
                    return b1.first < b2.first;
                }
                return b1.second.to_ulong() < b2.second.to_ulong();
            }
        };

        std::map<std::pair<int, std::bitset<32>>, int, Comparer> minimDistances;
        while (!routes.empty()) {
            std::vector<rr> newRoutes;
            for (const auto& r : routes) {
                if (r.totalDistance < minDistance) {
                    for (int i = 0; i < size; ++i) {
                        if (distance[r.currentIndex][i].distance != std::numeric_limits<int>::max() && !r.visited[i]) {
                            auto gates = distance[r.currentIndex][i].gates;
                            bool foundAllKeys = true;
                            for (int j = 1; j < size; ++j) {
                                if (gates[j] && !r.collectedKeys[j]) {
                                    foundAllKeys = false;
                                }
                            }
                            if (foundAllKeys) {
                                std::bitset<32> collectedKeys = r.collectedKeys;
                                collectedKeys[i] = true;
                                std::bitset<32> visited = r.visited;
                                visited[i] = true;
                                if (minimDistances.find({i, collectedKeys}) == minimDistances.end()) {
                                    minimDistances[{i, collectedKeys}] = r.totalDistance + distance[r.currentIndex][i].distance;
                                    newRoutes.push_back({i, r.totalDistance + distance[r.currentIndex][i].distance, collectedKeys, visited});
                                }
                                else {
                                    if (minimDistances[{i, collectedKeys}] > r.totalDistance + distance[r.currentIndex][i].distance) {
                                        minimDistances[{i, collectedKeys}] = r.totalDistance + distance[r.currentIndex][i].distance;
                                        newRoutes.push_back({i, r.totalDistance + distance[r.currentIndex][i].distance, collectedKeys, visited});
                                    }
                                }
                            }
                        }
                    }
                }
            }
            routes = newRoutes;

            for (const auto& r : routes) {
                if (r.collectedKeys.count() == size) {
                    if (minDistance > r.totalDistance) {
                        minDistance = r.totalDistance;
                    }
                }
            }
        }

        return minDistance;
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
