#include "file.h"
#include "utilities.h"
#include "verticalhexgrid.h"
#include <iostream>
#include <chrono>

namespace aoc2016_day24 {
    int sumMax = std::numeric_limits<int>::max();
    int sumMax2 = std::numeric_limits<int>::max();

    void dfs(const std::vector<std::vector<int>>& distances, int node, std::vector<bool> visited, int sum) {
        bool found = true;
        for (const auto& x : visited) {
            found &= x;
        }
        if (found) {
            sumMax = std::min(sumMax, sum);
        }
        else {
            for (int i = 0; i < distances.size(); ++i) {
                if (distances[i][node] > 0 && distances[i][node] != std::numeric_limits<int>::max() && !visited[i]) {
                    visited[i] = true;
                    sum += distances[i][node];
                    dfs(distances, i, visited, sum);
                    sum -= distances[i][node];
                    visited[i] = false;
                }
            }
        }
    }

    void dfs2(const std::vector<std::vector<int>>& distances, int node, std::vector<bool> visited, int sum) {
        bool found = true;
        for (const auto& x : visited) {
            found &= x;
        }
        if (found) {
            if (node == 0)
                sumMax2 = std::min(sumMax2, sum);
        }
        else {
            for (int i = 0; i < distances.size(); ++i) {
                if (distances[i][node] > 0 && distances[i][node] != std::numeric_limits<int>::max() && !visited[i]) {
                    visited[i] = true;
                    sum += distances[i][node];
                    dfs2(distances, i, visited, sum);
                    sum -= distances[i][node];
                    visited[i] = false;
                }
            }
        }
    }

    int part_1(std::string_view path) {
        sumMax = std::numeric_limits<int>::max();
        std::vector<std::string> input = file::readFileAsArrayString(path);

        std::vector<std::vector<std::pair<int, std::vector<int>>>> map(input.size(), std::vector<std::pair<int, std::vector<int>>>(input[0].size(), {-2, {}}));
        int max = std::numeric_limits<int>::min();

        for (int i = 0; i < input.size(); ++i) {
            for (int j = 0; j < input[0].size(); ++j) {
                if (input[i][j] == '#') {
                    map[i][j].first = -2;
                }
                else if (input[i][j] == '.') {
                    map[i][j].first = -1;
                }
                else {
                    map[i][j].first = input[i][j] - '0';
                    max = std::max(max, map[i][j].first);
                }
            }
        }
        std::vector<std::vector<int>> distances(max + 1, std::vector<int>(max + 1, std::numeric_limits<int>::max()));

        std::vector<std::tuple<int, int, int, int>> positions;
        for (int i = 0; i < map.size(); ++i) {
            for (int j = 0; j < map[0].size(); ++j) {
                if (map[i][j].first >= 0) {
                    positions.emplace_back(i, j, map[i][j].first, 0);
                }
            }
        }
        std::vector<std::pair<int, int>> directions{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        while (!positions.empty()) {
            std::vector<std::tuple<int, int, int, int>> newPositions;
            for (const auto& p : positions) {
                auto [x, y, id, steps] = p;
                for (const auto& d : directions) {
                    if (x + d.first >= 0 && x + d.first < map.size() &&
                    y + d.second >= 0 && y + d.second < map[0].size() &&
                    map[x + d.first][y + d.second].first != -2 &&
                    std::find(map[x + d.first][y + d.second].second.begin(), map[x + d.first][y + d.second].second.end(), id) == map[x + d.first][y + d.second].second.end()) {
                        if (map[x + d.first][y + d.second].first >= 0 && map[x + d.first][y + d.second].first != id) {
                            distances[id][map[x + d.first][y + d.second].first] = std::min(distances[id][map[x + d.first][y + d.second].first], steps + 1);
                            distances[map[x + d.first][y + d.second].first][id] = std::min(distances[map[x + d.first][y + d.second].first][id], steps + 1);
                        }
                        map[x + d.first][y + d.second].second.push_back(id);
                        newPositions.emplace_back(x + d.first, y + d.second, id, steps + 1);
                    }
                }
            }
            positions.clear();
            positions = newPositions;
        }

        std::vector<bool> visited(max + 1, false);
        visited[0] = true;
        dfs(distances, 0, visited, 0);

        return sumMax;
    }

    int part_2(std::string_view path) {
        sumMax2 = std::numeric_limits<int>::max();
        std::vector<std::string> input = file::readFileAsArrayString(path);

        std::vector<std::vector<std::pair<int, std::vector<int>>>> map(input.size(), std::vector<std::pair<int, std::vector<int>>>(input[0].size(), {-2, {}}));
        int max = std::numeric_limits<int>::min();

        for (int i = 0; i < input.size(); ++i) {
            for (int j = 0; j < input[0].size(); ++j) {
                if (input[i][j] == '#') {
                    map[i][j].first = -2;
                }
                else if (input[i][j] == '.') {
                    map[i][j].first = -1;
                }
                else {
                    map[i][j].first = input[i][j] - '0';
                    max = std::max(max, map[i][j].first);
                }
            }
        }
        std::vector<std::vector<int>> distances(max + 1, std::vector<int>(max + 1, std::numeric_limits<int>::max()));

        std::vector<std::tuple<int, int, int, int>> positions;
        for (int i = 0; i < map.size(); ++i) {
            for (int j = 0; j < map[0].size(); ++j) {
                if (map[i][j].first >= 0) {
                    positions.emplace_back(i, j, map[i][j].first, 0);
                }
            }
        }
        std::vector<std::pair<int, int>> directions{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        while (!positions.empty()) {
            std::vector<std::tuple<int, int, int, int>> newPositions;
            for (const auto& p : positions) {
                auto [x, y, id, steps] = p;
                for (const auto& d : directions) {
                    if (x + d.first >= 0 && x + d.first < map.size() &&
                    y + d.second >= 0 && y + d.second < map[0].size() &&
                    map[x + d.first][y + d.second].first != -2 &&
                    std::find(map[x + d.first][y + d.second].second.begin(), map[x + d.first][y + d.second].second.end(), id) == map[x + d.first][y + d.second].second.end()) {
                        if (map[x + d.first][y + d.second].first >= 0 && map[x + d.first][y + d.second].first != id) {
                            distances[id][map[x + d.first][y + d.second].first] = std::min(distances[id][map[x + d.first][y + d.second].first], steps + 1);
                            distances[map[x + d.first][y + d.second].first][id] = std::min(distances[map[x + d.first][y + d.second].first][id], steps + 1);
                        }
                        map[x + d.first][y + d.second].second.push_back(id);
                        newPositions.emplace_back(x + d.first, y + d.second, id, steps + 1);
                    }
                }
            }
            positions.clear();
            positions = newPositions;
        }

        std::vector<bool> visited(max + 1, false);
        dfs2(distances, 0, visited, 0);

        return sumMax2;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2016_day24::part_1("../2016/day24/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2016_day24::part_2("../2016/day24/input.in") << std::endl;

    return 0;
}
#endif
