#include "file.h"
#include "utilities.h"
#include <iostream>
#include <array>

namespace aoc2016_day25 {
    int solve(std::vector<std::vector<std::string>> instructions, std::array<int, 4> registers = {0, 0, 0, 0}) {
        int index = 0;
        std::vector<int> prev;
        while (index < instructions.size()) {
            if (instructions[index][0] == "cpy") {
                if (!utils::isInteger(instructions[index][2])) {
                    if (utils::isInteger(instructions[index][1])) {
                        registers[instructions[index][2][0] - 'a'] = std::stoi(instructions[index][1]);
                    } else {
                        registers[instructions[index][2][0] - 'a'] = registers[instructions[index][1][0] - 'a'];
                    }
                }
                index++;
            }
            else if (instructions[index][0] == "inc") {
                if (!utils::isInteger(instructions[index][1])) {
                    registers[instructions[index][1][0] - 'a']++;
                }
                index++;
            }
            else if (instructions[index][0] == "dec") {
                if (!utils::isInteger(instructions[index][1])) {
                    registers[instructions[index][1][0] - 'a']--;
                }
                index++;
            }
            else if (instructions[index][0] == "jnz") {
                int value = 0;
                if (utils::isInteger(instructions[index][1])) {
                    value = std::stoi(instructions[index][1]);
                }
                else {
                    value = registers[instructions[index][1][0] - 'a'];
                }
                if (value != 0) {
                    if (utils::isInteger(instructions[index][2])) {
                        index += std::stoi(instructions[index][2]);
                    }
                    else {
                        index += registers[instructions[index][2][0] - 'a'];
                    }
                }
                else {
                    index++;
                }
            }
            else if (instructions[index][0] == "out") {
                prev.push_back(registers[instructions[index][1][0] - 'a']);
                if (prev.size() >= 10) {
                    for (int i = 1; i < prev.size(); ++i) {
                        if (prev[i - 1] == prev[i]) {
                            return false;
                        }
                    }
                    return true;
                }
                index++;
            }
        }

        return registers[0];
    }

    int part_1(std::string_view path) {
        std::vector<std::vector<std::string>> input;
        for (const auto& line : file::readFileAsArrayString(path)) {
            input.emplace_back(utils::splitString(line, " ="));
        }

        int i = 1;
        while (!solve( input, {i, 0, 0, 0})) {
            i++;
        }
        return i;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2016_day25::part_1("../2016/day25/input.in") << std::endl;
    return 0;
}
#endif
