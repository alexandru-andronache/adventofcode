#include "file.h"
#include "utilities.h"
#include <iostream>
#include <algorithm>

namespace aoc2022_day19 {
    int maxGeode = 0;

    void dfs(int oreRobots, int clayRobots, int obsidianRobots, int ore, int clay, int obsidian, int geodes, int timeLeft) {
        if (timeLeft < 1) {
            return;
        }

        maxGeode = std::max(maxGeode, geodes);
        if (oreRobots < 4) {

        }
    }

    int solveV2(int costRobotOre, int costRobotClay, int costRobotObsidian_ore, int costRobotObsidian_clay, int costRobotGeode_ore, int costRobotGeode_obsidian) {
        int maxOre = std::max({costRobotOre, costRobotObsidian_ore, costRobotGeode_ore});
        dfs(1, 0, 0, 0, 0, 0, 0, 30);
    }



    int solve (int costRobotOre, int costRobotClay, int costRobotObsidian_ore, int costRobotObsidian_clay, int costRobotGeode_ore, int costRobotGeode_obsidian, int total) {
        struct state {
            std::vector<int> robots;
            std::vector<int> gems;
        };

        std::vector<state> states;
        states.push_back({{1, 0, 0, 0}, {0, 0, 0, 0}});
        for (int minutes = 0; minutes < total; ++minutes) {
            std::vector<state> newStates;
            for (const auto& s : states) {
                if (s.gems[0] >= costRobotGeode_ore && s.gems[2] >= costRobotGeode_obsidian) {
                    state ns = s;
                    ns.gems[0] -= costRobotGeode_ore;
                    ns.gems[2] -= costRobotGeode_obsidian;
                    for (int i = 0; i < 4; ++i) {
                        ns.gems[i] = s.robots[i] + ns.gems[i];
                    }
                    ns.robots[3]++;
                    newStates.push_back(ns);
                } else {
                    if (s.gems[0] >= costRobotObsidian_ore && s.gems[1] >= costRobotObsidian_clay) {
                        state ns = s;
                        ns.gems[0] -= costRobotObsidian_ore;
                        ns.gems[1] -= costRobotObsidian_clay;
                        for (int i = 0; i < 4; ++i) {
                            ns.gems[i] = s.robots[i] + ns.gems[i];
                        }
                        ns.robots[2]++;
                        newStates.push_back(ns);
                    }
                    if (s.gems[0] >= costRobotClay && s.robots[1] < costRobotObsidian_clay) {
                        state ns = s;
                        ns.gems[0] -= costRobotClay;
                        for (int i = 0; i < 4; ++i) {
                            ns.gems[i] = s.robots[i] + ns.gems[i];
                        }
                        ns.robots[1]++;
                        newStates.push_back(ns);
                    }
                    if (s.gems[0] >= costRobotOre && s.robots[0] < 4) {
                        state ns = s;
                        ns.gems[0] -= costRobotOre;
                        for (int i = 0; i < 4; ++i) {
                            ns.gems[i] = s.robots[i] + ns.gems[i];
                        }
                        ns.robots[0]++;
                        newStates.push_back(ns);
                    }
                    state newState = s;
                    for (int i = 0; i < 4; ++i) {
                        newState.gems[i] = s.robots[i] + s.gems[i];
                    }
                    newStates.push_back(newState);
                }
            }
            states = newStates;
            std::sort(states.begin(), states.end(), [](const auto& s1, const auto& s2) {
//                return (s1.robots[3]) * 10000 + (s1.robots[2]) * 1000 + (s1.robots[1]) * 10 + s1.robots[0] > (s2.robots[3]) * 10000 + (s2.robots[2]) * 1000 + (s2.robots[1]) * 10 + s2.robots[0];
                return (s1.robots[3] + s1.gems[3]) * 1000 + (s1.robots[2]) * 100 + (s1.robots[1]) * 10 + s1.robots[0] > (s2.robots[3] + s2.gems[3]) * 1000 + (s2.robots[2]) * 100 + (s2.robots[1]) * 10 + s2.robots[0];
            });
            if (states.size() > 7000) {
                states.resize(7000);
            }
        }

        int max = 0;
        for (const auto& s : states) {
            max = std::max(max, s.gems[3]);
        }
        return max;
    }
    int part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        int sol = 0;
        for (const auto& l : lines) {
            std::vector<std::string> t = utils::splitString(l, ": ,");
            int costRobotOre = std::stoi(t[6]);
            int costRobotClay = std::stoi(t[12]);
            int costRobotObsidian_ore = std::stoi(t[18]);
            int costRobotObsidian_clay = std::stoi(t[21]);
            int costRobotGeode_ore = std::stoi(t[27]);
            int costRobotGeode_obsidian = std::stoi(t[30]);

            int x = solve(costRobotOre, costRobotClay, costRobotObsidian_ore, costRobotObsidian_clay, costRobotGeode_ore, costRobotGeode_obsidian, 24);
            sol += std::stoi(t[1]) * x;
//            std::cout << x << "\n";
        }
        return sol;
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        int sol = 1;
        for (int i = 0; i < std::min(3UL, lines.size()); ++i) {
            std::vector<std::string> t = utils::splitString(lines[i], ": ,");
            int costRobotOre = std::stoi(t[6]);
            int costRobotClay = std::stoi(t[12]);
            int costRobotObsidian_ore = std::stoi(t[18]);
            int costRobotObsidian_clay = std::stoi(t[21]);
            int costRobotGeode_ore = std::stoi(t[27]);
            int costRobotGeode_obsidian = std::stoi(t[30]);

            sol = sol * solve(costRobotOre, costRobotClay, costRobotObsidian_ore, costRobotObsidian_clay, costRobotGeode_ore, costRobotGeode_obsidian, 32);
        }
        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2022_day19::part_1("../2022/day19/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2022_day19::part_2("../2022/day19/input.in") << std::endl;

    return 0;
}
#endif
