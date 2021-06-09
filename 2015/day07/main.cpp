#include "file.h"
#include "utilities.h"
#include <iostream>
#include <map>
#include <stack>

namespace aoc2015_day07 {
    bool isValid(const std::map<std::string, unsigned int>& wires, const std::string& symbol) {
        if (utils::isInteger(symbol)) {
            return true;
        }
        return (wires.find(symbol) != wires.end());
    }

    int getValue(const std::map<std::string, unsigned int>& wires, const std::string& symbol) {
        if (utils::isInteger(symbol)) {
            return std::stoi(symbol);
        }
        if (wires.find(symbol) != wires.end()) {
            return wires.at(symbol);
        }
        return 0;
    }

    unsigned long long part_1(std::string_view path, std::string_view key = "a", const std::map<std::string, unsigned int>& startValues = {}) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::map<std::string, unsigned int> wires = startValues;
        while (!input.empty()) {
            std::vector<std::string> tmp;
            for (const auto &line : input) {
                std::vector<std::string> symbols = utils::splitString(line, " ");
                if (symbols[1] == "->" && isValid(wires, symbols[0])) {
                    if (!isValid(wires, symbols[2])) {
                        wires[symbols[2]] = getValue(wires, symbols[0]);
                    }
                } else if (symbols[1] == "AND" && isValid(wires, symbols[0]) && isValid(wires, symbols[2])) {
                    wires[symbols[4]] = getValue(wires, symbols[0]) & getValue(wires, symbols[2]);
                } else if (symbols[1] == "OR" && isValid(wires, symbols[0]) && isValid(wires, symbols[2])) {
                    wires[symbols[4]] = getValue(wires, symbols[0]) | getValue(wires, symbols[2]);
                } else if (symbols[1] == "LSHIFT" && isValid(wires, symbols[0]) && isValid(wires, symbols[2])) {
                    wires[symbols[4]] = getValue(wires, symbols[0]) << getValue(wires, symbols[2]);
                } else if (symbols[1] == "RSHIFT" && isValid(wires, symbols[0]) && isValid(wires, symbols[2])) {
                    wires[symbols[4]] = getValue(wires, symbols[0]) >> getValue(wires, symbols[2]);
                } else if (symbols[0] == "NOT" && isValid(wires, symbols[1])) {
                    wires[symbols[3]] = getValue(wires, symbols[1]) ^ (0b1111111111111111);
                }
                else {
                    tmp.emplace_back(line);
                }
            }
            input = tmp;
        }

        return wires.at(key.data());
    }

    unsigned long long part_2(std::string_view path, unsigned int val) {
        return part_1(path, "a", {{"b", val}});
    }
}

#ifndef TESTING
int main() {
    unsigned long long sol = aoc2015_day07::part_1("../2015/day07/input.in");
    std::cout << "Part 1: " << sol << std::endl;
    std::cout << "Part 2: " << aoc2015_day07::part_2("../2015/day07/input.in", sol) << std::endl;

    return 0;
}
#endif
