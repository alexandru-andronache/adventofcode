#include "file.h"
#include "utilities.h"
#include <iostream>
#include <map>
#include <array>
#include <queue>

namespace aoc2017_day18 {
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
        long long lastSound = -1;
        std::map<std::string, long long> registers;
        while (true) {
            bool indexIncreased = false;
            auto [op, x, y] = input[index];
            if (op == "snd") {
                if (utils::isInteger(x)) {
                    lastSound = std::stoi(x);
                }
                else {
                    lastSound = findValueInMap(registers, x);
                }
            }
            else if (op == "set") {
                if (utils::isInteger(y)) {
                    registers[x] = std::stoi(y);
                }
                else {
                    registers[x] = findValueInMap(registers, y);
                }
            }
            else if (op == "add") {
                if (utils::isInteger(y)) {
                    registers[x] += std::stoi(y);
                }
                else {
                    registers[x] += findValueInMap(registers, y);
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
            else if (op == "mod") {
                if (utils::isInteger(y)) {
                    registers[x] = registers[x] % std::stoi(y);
                }
                else {
                    registers[x] = registers[x] % findValueInMap(registers, y);
                }
            }
            else if (op == "rcv") {
                if (findValueInMap(registers, x) != 0)
                    return lastSound;
            }
            else if (op == "jgz") {
                long long value = 0;
                if (utils::isInteger(x)) {
                    value = std::stoi(x);
                }
                else {
                    value = findValueInMap(registers, x);
                }
                if (value > 0) {
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
    }

    int part_2(std::string_view path) {
        std::vector<std::tuple<std::string, std::string, std::string>> input;
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, " ");
            input.emplace_back(tokens[0], tokens[1], tokens.size() > 2 ? tokens[2] : "");
        }

        int sol = 0;
        std::array<int, 2> index {0, 0};
        long long lastSound = -1;
        std::array<std::map<std::string, long long>, 2> registers;
        std::array<std::queue<int>, 2> send;
        registers[0]["p"] = 0;
        registers[1]["p"] = 1;
        int currentIndex = 0;
        while (true) {
            bool indexIncreased = false;
            auto [op, x, y] = input[index[currentIndex]];
            if (op == "snd") {
                if (currentIndex == 1) {
                    sol++;
                }
                if (utils::isInteger(x)) {
                    send[(currentIndex + 1) % 2].push(std::stoi(x));
                }
                else {
                    send[(currentIndex + 1) % 2].push(findValueInMap(registers[currentIndex], x));
                }
            }
            else if (op == "set") {
                if (utils::isInteger(y)) {
                    registers[currentIndex][x] = std::stoi(y);
                }
                else {
                    registers[currentIndex][x] = findValueInMap(registers[currentIndex], y);
                }
            }
            else if (op == "add") {
                if (utils::isInteger(y)) {
                    registers[currentIndex][x] += std::stoi(y);
                }
                else {
                    registers[currentIndex][x] += findValueInMap(registers[currentIndex], y);
                }
            }
            else if (op == "mul") {
                if (utils::isInteger(y)) {
                    registers[currentIndex][x] *= std::stoi(y);
                }
                else {
                    registers[currentIndex][x] *= findValueInMap(registers[currentIndex], y);
                }
            }
            else if (op == "mod") {
                if (utils::isInteger(y)) {
                    registers[currentIndex][x] = registers[currentIndex][x] % std::stoi(y);
                }
                else {
                    registers[currentIndex][x] = registers[currentIndex][x] % findValueInMap(registers[currentIndex], y);
                }
            }
            else if (op == "rcv") {
                if (!send[currentIndex].empty()) {
                    registers[currentIndex][x] = send[currentIndex].front();
                    send[currentIndex].pop();
                }
                else {
                    currentIndex = (currentIndex + 1) % 2;
                    indexIncreased = true;
                    bool shouldReturn = false;
                    if (index[currentIndex] >= lines.size()) {
                        shouldReturn = true;
                    }
                    else {
                        auto [op, x, y] = input[index[currentIndex]];
                        if (op == "rcv" && send[currentIndex].empty()) {
                            shouldReturn = true;
                        }
                    }
                    if (shouldReturn) {
                        return sol;
                    }
                }
            }
            else if (op == "jgz") {
                long long value = 0;
                if (utils::isInteger(x)) {
                    value = std::stoi(x);
                }
                else {
                    value = findValueInMap(registers[currentIndex], x);
                }
                if (value > 0) {
                    indexIncreased = true;
                    if (utils::isInteger(y)) {
                        index[currentIndex] += std::stoi(y);
                    }
                    else {
                        index[currentIndex] += findValueInMap(registers[currentIndex], y);
                    }
                }
            }

            if (!indexIncreased) {
                index[currentIndex]++;
            }
        }
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2017_day18::part_1("../2017/day18/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2017_day18::part_2("../2017/day18/input.in") << std::endl;

    return 0;
}
#endif
