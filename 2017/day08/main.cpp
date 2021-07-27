#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>
#include <map>

namespace aoc2017_day08 {
    int part_1(std::string_view path) {
        std::vector<std::tuple<std::string, std::string, int, std::string, std::string, int>> input;
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, " ");
            input.push_back({tokens[0], tokens[1], std::stoi(tokens[2]), tokens[4], tokens[5], std::stoi(tokens[6])});
        }

        std::map<std::string, int> registers;
        for (const auto& line : input) {
            const auto& [value1, op, nr1, value2, comp, nr2] = line;
            int value = 0;
            if (registers.find(value2) != registers.end()) {
                value = registers[value2];
            }
            bool conditionTrue = false;
            if (comp.compare("<") == 0 && value < nr2) {
                conditionTrue = true;
            }
            else if (comp.compare("<=") == 0 && value <= nr2) {
                conditionTrue = true;
            }
            else if (comp.compare(">") == 0 && value > nr2) {
                conditionTrue = true;
            }
            else if (comp.compare(">=") == 0 && value >= nr2) {
                conditionTrue = true;
            }
            else if (comp.compare("==") == 0 && value == nr2) {
                conditionTrue = true;
            }
            else if (comp.compare("!=") == 0 && value != nr2) {
                conditionTrue = true;
            }
            if (conditionTrue) {
                if (registers.find(value1) == registers.end()) {
                    registers.insert({value1, 0});
                }
                if (op.compare("inc") == 0) {
                    registers[value1] += nr1;
                }
                else {
                    registers[value1] -= nr1;
                }
            }
        }

        return std::max_element(registers.begin(), registers.end(), [](const auto& a, const auto& b) {
            return a.second < b.second;
        })->second;
    }

    int part_2(std::string_view path) {
        std::vector<std::tuple<std::string, std::string, int, std::string, std::string, int>> input;
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, " ");
            input.push_back({tokens[0], tokens[1], std::stoi(tokens[2]), tokens[4], tokens[5], std::stoi(tokens[6])});
        }

        std::map<std::string, int> registers;
        int max = std::numeric_limits<int>::min();
        for (const auto& line : input) {
            const auto& [value1, op, nr1, value2, comp, nr2] = line;
            int value = 0;
            if (registers.find(value2) != registers.end()) {
                value = registers[value2];
            }
            bool conditionTrue = false;
            if (comp.compare("<") == 0 && value < nr2) {
                conditionTrue = true;
            }
            else if (comp.compare("<=") == 0 && value <= nr2) {
                conditionTrue = true;
            }
            else if (comp.compare(">") == 0 && value > nr2) {
                conditionTrue = true;
            }
            else if (comp.compare(">=") == 0 && value >= nr2) {
                conditionTrue = true;
            }
            else if (comp.compare("==") == 0 && value == nr2) {
                conditionTrue = true;
            }
            else if (comp.compare("!=") == 0 && value != nr2) {
                conditionTrue = true;
            }
            if (conditionTrue) {
                if (registers.find(value1) == registers.end()) {
                    registers.insert({value1, 0});
                }
                if (op.compare("inc") == 0) {
                    registers[value1] += nr1;
                }
                else {
                    registers[value1] -= nr1;
                }
                max = std::max(max, registers[value1]);
            }
        }

        return max;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2017_day08::part_1("../2017/day08/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2017_day08::part_2("../2017/day08/input.in") << std::endl;

    return 0;
}
#endif
