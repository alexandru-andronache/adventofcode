#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>

namespace aoc2017_day24 {
    void dfs(const std::vector<std::vector<int>>& connections, std::vector<std::pair<int, int>>& nodes, int& maxStrength) {
        for (int i = 0; i < connections[nodes.back().first].size(); ++i) {
            int value = connections[nodes.back().first][i];
            auto it = std::find_if(nodes.begin(), nodes.end(), [value](auto p) {
                return p.second == value;
            });
            if (value != -1 && it == nodes.end()) {
                nodes.emplace_back(i, value);
                int sum = 0;
                for (int j = 1; j < nodes.size(); ++j) {
                    sum += nodes[j].first + nodes[j - 1].first;
                }
                maxStrength = std::max(maxStrength, sum);
                dfs(connections, nodes, maxStrength);
                nodes.pop_back();
            }
        }
    }

    void dfs(const std::vector<std::vector<int>>& connections, std::vector<std::pair<int, int>>& nodes, int& maxStrength, int& maxLength) {
        for (int i = 0; i < connections[nodes.back().first].size(); ++i) {
            int value = connections[nodes.back().first][i];
            auto it = std::find_if(nodes.begin(), nodes.end(), [value](auto p) {
                return p.second == value;
            });
            if (value != -1 && it == nodes.end()) {
                nodes.emplace_back(i, value);
                int sum = 0;
                for (int j = 1; j < nodes.size(); ++j) {
                    sum += nodes[j].first + nodes[j - 1].first;
                }
                if (nodes.size() > maxLength) {
                    maxLength = nodes.size();
                    maxStrength = sum;
                }
                else if (nodes.size() == maxLength) {
                    maxStrength = std::max(sum, maxStrength);
                }

                dfs(connections, nodes, maxStrength, maxLength);
                nodes.pop_back();
            }
        }
    }

    int part_1(std::string_view path) {
        std::vector<std::pair<int, int>> connections;
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        for (const auto& line : lines) {
            std::vector<int> tokens = utils::splitStringToInt(line, "/");
            connections.emplace_back(tokens[0], tokens[1]);
        }

        int max = std::numeric_limits<int>::min();
        for (const auto& c : connections) {
            max = std::max({max, c.first, c.second});
        }

        std::vector<std::vector<int>> map(max + 1, std::vector<int>(max + 1, -1));
        for (int i = 0; i < connections.size(); ++i) {
            map[connections[i].first][connections[i].second] = i;
            map[connections[i].second][connections[i].first] = i;
        }

        std::vector<std::pair<int, int>> nodes;
        nodes.emplace_back(0, -1);
        int maxStrength = 0;
        dfs(map, nodes, maxStrength);

        return maxStrength;
    }

    int part_2(std::string_view path) {
        std::vector<std::pair<int, int>> connections;
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        for (const auto& line : lines) {
            std::vector<int> tokens = utils::splitStringToInt(line, "/");
            connections.emplace_back(tokens[0], tokens[1]);
        }

        int max = std::numeric_limits<int>::min();
        for (const auto& c : connections) {
            max = std::max({max, c.first, c.second});
        }

        std::vector<std::vector<int>> map(max + 1, std::vector<int>(max + 1, -1));
        for (int i = 0; i < connections.size(); ++i) {
            map[connections[i].first][connections[i].second] = i;
            map[connections[i].second][connections[i].first] = i;
        }

        std::vector<std::pair<int, int>> nodes;
        nodes.emplace_back(0, -1);
        int maxStrength = 0;
        int maxLength = 0;
        dfs(map, nodes, maxStrength, maxLength);

        return maxStrength;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2017_day24::part_1("../2017/day24/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2017_day24::part_2("../2017/day24/input.in") << std::endl;

    return 0;
}
#endif
