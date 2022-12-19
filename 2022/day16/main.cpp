#include "file.h"
#include "utilities.h"
#include <iostream>
#include <map>
#include <stack>
#include <array>
#include <algorithm>

namespace aoc2022_day16 {
    const int MAX_VALUE = 1000;
    std::vector<std::vector<int>> minPath(100, std::vector<int>(100, MAX_VALUE));
    std::vector<int> visited2;

    std::map<int, int> solution;

    void solve(int currentPosition, int minutesLeft, int state, int flow, const std::vector<std::pair<int, int>>& flowRate) {
        if (solution.contains(state)) {
            solution[state] = std::max(solution[state], flow);
        }
        else {
            solution.insert({state, 0});
        }

        for (int i = 0; i < flowRate.size(); ++i) {
            int newMinLeft = minutesLeft - minPath[currentPosition][flowRate[i].second] - 1;
            if ((visited2[i] & state) || (newMinLeft <= 0)) {
                continue;
            }
            solve(flowRate[i].second, newMinLeft, state | visited2[i], flow + newMinLeft * flowRate[i].first, flowRate);
        }
    }

    int insertInMap(std::map<std::string, int>& valves, int& index, std::string valve) {
        if (valves.contains(valve)) {
           return valves[valve];
        }
        valves.insert({valve, index});
        index++;
        return index - 1;
    }

    int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::map<std::string, int> valves;
        std::vector<std::vector<bool>> roads(100, std::vector<bool>(100, false));
        std::vector<std::pair<int, int>> flowRate;

        solution.clear();
        visited2.clear();

        for (int i = 0; i < 100; ++i) {
            for (int j = 0; j < 100; ++j) {
                minPath[i][j] = 1000;
            }
        }

        int index = 0;
        for (const auto& l : input) {
            std::vector<std::string> t = utils::splitString(l, ";,= ");
            int valve = insertInMap(valves, index, t[1]);
            int rate = std::stoi(t[5]);
            if (rate > 0) {
                flowRate.emplace_back(rate, valve);
            }
            for (int i = 10; i < t.size(); ++i) {
                roads[valve][insertInMap(valves, index, t[i])] = true;
            }
        }

        for (int i = 0; i < flowRate.size(); ++i) {
            visited2.push_back(1 << i);
        }

        for (int i = 0; i < 100; ++i) {
            for (int j = 0; j < 100; ++j) {
                if (roads[i][j]) {
                    minPath[i][j] = 1;
                }
            }
        }

        for (int k = 0; k < 100; ++k) {
            for (int i = 0; i < 100; ++i) {
                for (int j = 0; j < 100; ++j) {
                    minPath[i][j] = std::min(minPath[i][j], minPath[i][k] + minPath[k][j]);
                }
            }
        }

        solve(valves["AA"], 30, 0, 0, flowRate);

        int m = 0;
        for (const auto& s : solution) {
            m = std::max(m, s.second);
        }

        return m;
    }

    int part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::map<std::string, int> valves;
        std::vector<std::vector<bool>> roads(100, std::vector<bool>(100, false));
        std::vector<std::pair<int, int>> flowRate;

        solution.clear();
        visited2.clear();

        for (int i = 0; i < 100; ++i) {
            for (int j = 0; j < 100; ++j) {
                minPath[i][j] = 1000;
            }
        }

        int index = 0;
        for (const auto& l : input) {
            std::vector<std::string> t = utils::splitString(l, ";,= ");
            int valve = insertInMap(valves, index, t[1]);
            int rate = std::stoi(t[5]);
            if (rate > 0) {
                flowRate.emplace_back(rate, valve);
            }
            for (int i = 10; i < t.size(); ++i) {
                roads[valve][insertInMap(valves, index, t[i])] = true;
            }
        }

        for (int i = 0; i < flowRate.size(); ++i) {
            visited2.push_back(1 << i);
        }

        for (int i = 0; i < 100; ++i) {
            for (int j = 0; j < 100; ++j) {
                if (roads[i][j]) {
                    minPath[i][j] = 1;
                }
            }
        }

        for (int k = 0; k < 100; ++k) {
            for (int i = 0; i < 100; ++i) {
                for (int j = 0; j < 100; ++j) {
                    minPath[i][j] = std::min(minPath[i][j], minPath[i][k] + minPath[k][j]);
                }
            }
        }

        solve(valves["AA"], 30 - 4, 0, 0, flowRate);

        int m = 0;
        for (const auto& s1 : solution) {
            for (const auto& s2 : solution) {
                if (!(s1.first & s2.first)) {
                    m = std::max(m, s1.second + s2.second);
                }
            }
        }

        return m;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2022_day16::part_1("../2022/day16/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2022_day16::part_2("../2022/day16/input.in") << std::endl;

    return 0;
}
#endif
