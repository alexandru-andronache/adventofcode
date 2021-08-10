#include "file.h"
#include "utilities.h"
#include <iostream>
#include <queue>
#include <set>
#include <vector>
#include <array>

namespace aoc2018_day22 {
    const int extraPadding = 30;

    void createMap(const std::pair<int, int>& target, int depth, std::vector<std::vector<int>>& finalMap) {
        std::vector<std::vector<long long>> map(target.first + extraPadding, std::vector<long long>(target.second + extraPadding, 0));

        for (int i = 0; i < target.first + extraPadding; ++i) {
            for (int j = 0; j < target.second + extraPadding; ++j) {
                if ((i == 0 && j == 0) || (i == target.first && j == target.second)) {
                    map[i][j] = depth;
                }
                else if (i == 0) {
                    map[i][j] = (j * 48271 + depth) % 20183;
                }
                else if (j == 0) {
                    map[i][j] = (i * 16807 + depth) % 20183;
                }
                else {
                    map[i][j] = (map[i - 1][j] * map[i][j - 1] + depth) % 20183;
                }
            }
        }

        for (int i = 0; i < target.first + extraPadding; ++i) {
            std::vector<int> temp;
            for (int j = 0; j < target.second + extraPadding; ++j) {
                temp.push_back(map[i][j] % 3);
            }
            finalMap.emplace_back(temp);
        }
    }

    bool canMove(const std::vector<std::vector<int>>& map, int x, int y, int tool) {
        if (map[x][y] == tool || (map[x][y] + 1) % 3 == tool) {
            return true;
        }
        return false;
    }

    int part_1(int depth, std::pair<int, int> target) {
        std::vector<std::vector<int>> map;
        createMap(target, depth, map);

        int sum = 0;
        for (int i = 0; i <= target.first; ++i) {
            for (int j = 0; j <= target.second; ++j) {
                sum += map[i][j];
            }
        }

        return sum;
    }

    int part_2(int depth, std::pair<int, int> target) {
        enum class tool {
            TORCH = 0,
            GEAR = 1,
            NOTHING = 2
        };
        constexpr int MINUTES_TO_CHANGE_GEAR = 7;

        std::vector<std::vector<int>> map;
        createMap(target, depth, map);

        std::vector<std::vector<std::array<int, 3>>> minutes(map.size(), std::vector<std::array<int, 3>>(map[0].size(), {10000, 10000, 10000}));
        minutes[0][0] = {0, 0, 0};

        std::queue<std::tuple<int, int, tool>> points;
        points.push({0, 0, tool::TORCH});

        std::vector<std::pair<int, int>> directions {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        std::set<std::tuple<int, int, tool>> elements;
        elements.insert({0, 0, tool::TORCH});
        std::vector<std::pair<tool, tool>> toolChange {{tool::TORCH, tool::GEAR}, {tool::GEAR, tool::NOTHING}, {tool::TORCH, tool::NOTHING}};

        while (!points.empty()) {
            auto [x, y, currentTool] = points.front();
            std::pair<int, int> current = {x, y};
            elements.erase(elements.find({x, y, currentTool}));
            points.pop();

            for (const auto& d : directions) {
                if (current.first + d.first >= 0 && current.first + d.first < map.size() &&
                current.second + d.second >= 0 && current.second + d.second < map[0].size()) {

                    if (canMove(map, current.first + d.first, current.second + d.second, static_cast<int>(currentTool)) &&
                    minutes[current.first + d.first][current.second + d.second][static_cast<int>(currentTool)] >
                    minutes[current.first][current.second][static_cast<int>(currentTool)] + 1) {

                        minutes[current.first + d.first][current.second + d.second][static_cast<int>(currentTool)] =
                                minutes[current.first][current.second][static_cast<int>(currentTool)] + 1;
                        auto it = elements.find({current.first + d.first, current.second + d.second, currentTool});
                        if (it == elements.end()) {
                            elements.insert({current.first + d.first, current.second + d.second, currentTool});
                            points.push({current.first + d.first, current.second + d.second, currentTool});
                        }
                    }
                    auto tools = toolChange[map[current.first][current.second]];

                    tool nextTool;
                    if (tools.first == currentTool) {
                        nextTool = tools.second;
                    }
                    else {
                        nextTool = tools.first;
                    }
                    if (canMove(map, current.first + d.first, current.second + d.second, static_cast<int>(nextTool)) &&
                    minutes[current.first + d.first][current.second + d.second][static_cast<int>(nextTool)] >
                    minutes[current.first][current.second][static_cast<int>(currentTool)] + 1 + MINUTES_TO_CHANGE_GEAR) {
                        minutes[current.first + d.first][current.second + d.second][static_cast<int>(nextTool)] =
                                minutes[current.first][current.second][static_cast<int>(currentTool)] + 1 + MINUTES_TO_CHANGE_GEAR;
                        auto it = elements.find({current.first + d.first, current.second + d.second, nextTool});
                        if (it == elements.end()) {
                            elements.insert({current.first + d.first, current.second + d.second, nextTool});
                            points.push({current.first + d.first, current.second + d.second, nextTool});
                        }
                    }
                }
            }
        }

        return std::min({minutes[target.first][target.second][0], minutes[target.first][target.second][1] + 7, minutes[target.first][target.second][2] + 7});
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2018_day22::part_1(5355, {14, 796}) << std::endl;
    std::cout << "Part 2: " << aoc2018_day22::part_2(5355, {14, 796}) << std::endl;

    return 0;
}
#endif
