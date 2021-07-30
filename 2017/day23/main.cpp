#include "file.h"
#include "utilities.h"
#include <iostream>
#include <map>

namespace aoc2017_day23 {
    long long findValueInMap(const std::map<std::string, long long>& registers, const std::string& x) {
        auto it = registers.find(x);
        if (it != registers.end()) {
            return registers.at(x);
        }
        return 0;
    }

    int part_1(std::string_view path) {
        std::vector<std::tuple<std::string, std::string, std::string>> input;
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, " ");
            input.emplace_back(tokens[0], tokens[1], tokens.size() > 2 ? tokens[2] : "");
        }

        int index = 0;
        std::map<std::string, long long> registers;
        int sol = 0;
        while (index < lines.size()) {
            bool indexIncreased = false;
            auto [op, x, y] = input[index];
            if (op == "set") {
                if (utils::isInteger(y)) {
                    registers[x] = std::stoi(y);
                }
                else {
                    registers[x] = findValueInMap(registers, y);
                }
            }
            else if (op == "sub") {
                if (utils::isInteger(y)) {
                    registers[x] -= std::stoi(y);
                }
                else {
                    registers[x] -= findValueInMap(registers, y);
                }
            }
            else if (op == "mul") {
                if (utils::isInteger(y)) {
                    registers[x] *= std::stoi(y);
                }
                else {
                    registers[x] *= findValueInMap(registers, y);
                }
                sol++;
            }
            else if (op == "jnz") {
                long long value = 0;
                if (utils::isInteger(x)) {
                    value = std::stoi(x);
                }
                else {
                    value = findValueInMap(registers, x);
                }
                if (value != 0) {
                    indexIncreased = true;
                    if (utils::isInteger(y)) {
                        index += std::stoi(y);
                    }
                    else {
                        index += findValueInMap(registers, y);
                    }
                }
            }

            if (!indexIncreased) {
                index++;
            }
        }
        return sol;
    }

    int part_2(std::string_view path) {
        std::vector<std::tuple<std::string, std::string, std::string>> input;
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, " ");
            input.emplace_back(tokens[0], tokens[1], tokens.size() > 2 ? tokens[2] : "");
        }

        int index = 0;
        std::map<std::string, long long> registers;
        registers["a"] = 1;
        registers["f"] = 0;
        while (registers["f"] == 0) {
            auto [op, x, y] = input[index];
            bool indexIncreased = false;
            if (op == "set") {
                if (utils::isInteger(y)) {
                    registers[x] = std::stoi(y);
                }
                else {
                    registers[x] = findValueInMap(registers, y);
                }
            }
            else if (op == "sub") {
                if (utils::isInteger(y)) {
                    registers[x] -= std::stoi(y);
                }
                else {
                    registers[x] -= findValueInMap(registers, y);
                }
            }
            else if (op == "mul") {
                if (utils::isInteger(y)) {
                    registers[x] *= std::stoi(y);
                }
                else {
                    registers[x] *= findValueInMap(registers, y);
                }
            }
            else if (op == "jnz") {
                long long value = 0;
                if (utils::isInteger(x)) {
                    value = std::stoi(x);
                }
                else {
                    value = findValueInMap(registers, x);
                }
                if (value != 0) {
                    indexIncreased = true;
                    if (utils::isInteger(y)) {
                        index += std::stoi(y);
                    }
                    else {
                        index += findValueInMap(registers, y);
                    }
                }
            }

            if (!indexIncreased) {
                index++;
            }
        }

        // analysing the instructions, if "a" is set to 1 it will create two numbers in register["b"] and register["c"]
        // and then it will increase them by 17(instruction 30) and it will verify if they are composite numbers or not
        // if they are composite it will set the register["f"] to zero(instruction 15) and then it will increase
        // register["h"] with one

        int sol = 0;
        for (int i = registers["b"]; i <= registers["c"]; i = i + 17) {
            bool prime = true;
            for (int j = 2; j <= i / 2; ++j) {
                if (i % j == 0) {
                    prime = false;
                }
            }
            if (!prime) {
                sol++;
            }
        }

        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2017_day23::part_1("../2017/day23/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2017_day23::part_2("../2017/day23/input.in") << std::endl;

    return 0;
}
#endif
