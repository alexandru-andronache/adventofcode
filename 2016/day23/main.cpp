#include "file.h"
#include "utilities.h"
#include <iostream>
#include <array>

namespace aoc2016_day23 {
    int solve(std::vector<std::vector<std::string>> instructions, std::array<int, 4> registers = {0, 0, 0, 0}) {
        int index = 0;
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
                if (index == 7) {
                    registers[0] += registers[2];
                    registers[2] = 0;
                }
                else if (index == 9) {
                    registers[0] += registers[1] * registers[3];
                    registers[3] = 0;
                }
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
            else if (instructions[index][0] == "tgl") {
                int value = 0;
                if (utils::isInteger(instructions[index][1])) {
                    value = std::stoi(instructions[index][1]);
                }
                else {
                    value = registers[instructions[index][1][0] - 'a'];
                }
                value += index;
                if (value < instructions.size()) {
                    if (instructions[value].size() == 2) {
                        if (instructions[value][0] == "inc") {
                            instructions[value][0] = "dec";
                        }
                        else {
                            instructions[value][0] = "inc";
                        }
                    }
                    else {
                        if (instructions[value][0] == "jnz") {
                            instructions[value][0] = "cpy";
                        }
                        else {
                            instructions[value][0] = "jnz";
                        }
                    }
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

        return solve(input, {7, 0, 0, 0});
    }

    int part_2(std::string_view path) {
        std::vector<std::vector<std::string>> input;
        for (const auto& line : file::readFileAsArrayString(path)) {
            input.emplace_back(utils::splitString(line, " ="));
        }

        return solve(input, {12, 0, 0, 0});
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2016_day23::part_1("../2016/day23/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2016_day23::part_2("../2016/day23/input.in") << std::endl;

    return 0;
}
#endif
