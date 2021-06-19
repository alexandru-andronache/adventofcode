#include "file.h"
#include "utilities.h"
#include <iostream>
#include <array>
#include <map>

namespace aoc2016_day10 {
    int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::pair<int, int>> initial;
        std::vector<std::tuple<int, bool, int, bool, int>> assignments; // true for output
        const int value1 = 61;
        const int value2 = 17;
        for (const auto& line : input) {
            std::vector<std::string> s = utils::splitString(line, " =");

            if (s[0] == "value") {
                initial.emplace_back(std::stoi(s[1]), std::stoi(s[5]));
            }
            else {
                assignments.emplace_back(std::stoi(s[1]), (s[5] == "output"), std::stoi(s[6]), (s[10] == "output"), std::stoi(s[11]));
            }
        }

        std::map<int, std::vector<int>> values;
        for (const auto& state: initial) {
            values[state.second].push_back(state.first);
        }

        while (true) {
            std::pair<int, std::vector<int>> it({-1, {}});
            for (const auto& v : values) {
                if (v.second.size() == 2) {
                    it = v;
                }
            }
            if (std::min(it.second[0], it.second[1]) == std::min(value1, value2) &&
            std::max(it.second[0], it.second[1]) == std::max(value1, value2)) {
                return it.first;
            }
            for (const auto& assignment : assignments) {
                auto [bot, isOutput1, valueLow, isOutput2 , valueHigh] = assignment;
                if (bot == it.first) {
                    if (!isOutput1)
                        values[valueLow].push_back(std::min(it.second[0], it.second[1]));
                    if (!isOutput2)
                        values[valueHigh].push_back(std::max(it.second[0], it.second[1]));
                }
            }
            values[it.first].clear();
        }
    }

    int part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::pair<int, int>> initial;
        std::vector<std::tuple<int, bool, int, bool, int>> assignments; // true for output
        int output1 = 0, output2 = 1, output3 = 2;
        for (const auto& line : input) {
            std::vector<std::string> s = utils::splitString(line, " =");

            if (s[0] == "value") {
                initial.emplace_back(std::stoi(s[1]), std::stoi(s[5]));
            }
            else {
                assignments.emplace_back(std::stoi(s[1]), (s[5] == "output"), std::stoi(s[6]), (s[10] == "output"), std::stoi(s[11]));
            }
        }

        std::map<int, std::vector<int>> values;
        std::vector<int> outputs(300, -1);
        for (const auto& state: initial) {
            values[state.second].push_back(state.first);
        }

        while (true) {
            std::pair<int, std::vector<int>> it({-1, {}});
            for (const auto& v : values) {
                if (v.second.size() == 2) {
                    it = v;
                }
            }
            if (it.first == -1) {
                break;
            }
            for (const auto& assignment : assignments) {
                auto [bot, isOutput1, valueLow, isOutput2 , valueHigh] = assignment;
                if (bot == it.first) {
                    if (!isOutput1)
                        values[valueLow].push_back(std::min(it.second[0], it.second[1]));
                    else {
                        outputs[valueLow] = std::min(it.second[0], it.second[1]);
                    }
                    if (!isOutput2) {
                        values[valueHigh].push_back(std::max(it.second[0], it.second[1]));
                    }
                    else {
                        outputs[valueHigh] = std::max(it.second[0], it.second[1]);
                    }
                }
            }
            values[it.first].clear();
        }

        return outputs[output1] * outputs[output2] * outputs[output3];
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2016_day10::part_1("../2016/day10/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2016_day10::part_2("../2016/day10/input.in") << std::endl;

    return 0;
}
#endif
