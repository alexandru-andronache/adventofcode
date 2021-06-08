#include "file.h"
#include "utilities.h"
#include <iostream>
#include <map>
#include <stack>
#include <set>

namespace aoc2020_day08 {
    bool processSeries(const std::vector<std::string> &input, int &accumulator) {
        std::set<int> instructions;
        int index = 0;
        accumulator = 0;
        while (instructions.find(index) == instructions.end() && index < input.size()) {
            instructions.insert(index);
            std::vector<std::string> words = utils::splitString(input[index], " ");
            if (words[0] == "acc") {
                accumulator += std::stoi(words[1]);
                index++;
            } else if (words[0] == "jmp") {
                index += std::stoi(words[1]);
            } else {
                index++;
            }
        }
        return index < input.size();
    }

    int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        int accumulator = 0;
        processSeries(input, accumulator);
        return accumulator;
    }

    int part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        int accumulator = 0;
        std::map<std::string, std::string> replacements{{"jmp", "nop"},
                                                        {"nop", "jmp"},
                                                        {"acc", "acc"}};
        for (auto &line : input) {
            std::vector<std::string> words = utils::splitString(line, " ");
            line.replace(0, 3, replacements[line.substr(0, 3)]);
            if (!processSeries(input, accumulator)) {
                return accumulator;
            }
            line.replace(0, 3, replacements[line.substr(0, 3)]);
        }
        return 0;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2020_day08::part_1("../2020/day08/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2020_day08::part_2("../2020/day08/input.in") << std::endl;

    return 0;
}
#endif
