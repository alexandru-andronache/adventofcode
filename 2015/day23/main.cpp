#include "file.h"
#include "utilities.h"
#include <iostream>
#include <array>

namespace aoc2015_day23 {
    long long solve(const std::vector<std::string>& input, std::array<long long, 2> registers, int exitRegister) {
        int index = 0;
        while (index < input.size()) {
            std::vector<std::string> tokens = utils::splitString(input[index], " ,");
            if (tokens[0] == "hlf") {
                registers[tokens[1][0] - 'a'] >>= 1;
                index++;
            }
            else if (tokens[0] == "tpl") {
                registers[tokens[1][0] - 'a'] *= 3;
                index++;
            }
            else if (tokens[0] == "inc") {
                registers[tokens[1][0] - 'a']++;
                index++;
            }
            else if (tokens[0] == "jmp") {
                index += std::stoi(tokens[1]);
            }
            else if (tokens[0] == "jie") {
                if (registers[tokens[1][0] - 'a'] % 2 == 0) {
                    index += std::stoi(tokens[2]);
                }
                else {
                    index++;
                }
            }
            else if (tokens[0] == "jio") {
                if (registers[tokens[1][0] - 'a'] == 1) {
                    index += std::stoi(tokens[2]);
                }
                else {
                    index++;
                }
            }
        }
        return registers[exitRegister];
    }

    int part_1(std::string_view path, int exitRegister) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        return solve(input, {0, 0}, exitRegister);
    }

    int part_2(std::string_view path, int exitRegister) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        return solve(input, {1, 0}, exitRegister);
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2015_day23::part_1("../2015/day23/input.in", 1) << std::endl;
    std::cout << "Part 2: " << aoc2015_day23::part_2("../2015/day23/input.in", 1) << std::endl;

    return 0;
}
#endif
