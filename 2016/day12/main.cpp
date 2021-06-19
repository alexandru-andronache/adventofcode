#include "file.h"
#include "utilities.h"
#include <iostream>
#include <set>
#include <array>

namespace aoc2016_day12 {
    int solve(const std::vector<std::vector<std::string>>& instructions, std::array<int, 4> registers = {0, 0, 0, 0}) {
        int index = 0;
        while (index < instructions.size()) {
            if (instructions[index][0] == "cpy") {
                if (instructions[index][1][0] >= '0' && instructions[index][1][0] <= '9') {
                    registers[instructions[index][2][0] - 'a'] = std::stoi(instructions[index][1]);
                }
                else {
                    registers[instructions[index][2][0] - 'a'] = registers[instructions[index][1][0] - 'a'];
                }
                index++;
            }
            else if (instructions[index][0] == "inc") {
                registers[instructions[index][1][0] - 'a']++;
                index++;
            }
            else if (instructions[index][0] == "dec") {
                registers[instructions[index][1][0] - 'a']--;
                index++;
            }
            else {
                int value = 0;
                if (instructions[index][1][0] >= '0' && instructions[index][1][0] <= '9') {
                    value = std::stoi(instructions[index][1]);
                }
                else {
                    value = registers[instructions[index][1][0] - 'a'];
                }
                if (value != 0) {
                    index += std::stoi(instructions[index][2]);
                }
                else {
                    index++;
                }
            }
        }

        return registers[0];
    }

    int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::vector<std::string>> instructions;
        for (const auto& line : input) {
            instructions.push_back(utils::splitString(line, " ="));
        }
        return solve(instructions);
    }

    int part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::vector<std::string>> instructions;
        for (const auto& line : input) {
            instructions.push_back(utils::splitString(line, " ="));
        }
        return solve(instructions, {0, 0, 1, 0});
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2016_day12::part_1("../2016/day12/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2016_day12::part_2("../2016/day12/input.in") << std::endl;

    return 0;
}
#endif
