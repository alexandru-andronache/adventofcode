#include "file.h"
#include <iostream>
#include <vector>

namespace aoc2021_day02 {
    int part_1(std::string_view path) {
        std::vector<std::vector<std::string>> input = file::readFileAndSplit(path, " ");

        int position = 0;
        int depth = 0;
        for (const auto& line : input) {
            if (line[0] == "forward") {
                position += std::stoi(line[1]);
            }
            else if (line[0] == "down") {
                depth += std::stoi(line[1]);
            }
            else if (line[0] == "up") {
                depth -= std::stoi(line[1]);
            }
        }

        return position * depth;
    }

    long long part_2(std::string_view path) {
        std::vector<std::vector<std::string>> input = file::readFileAndSplit(path, " ");

        long long position = 0;
        long long depth = 0;
        long long aim = 0;
        for (const auto& line : input) {
            if (line[0] == "forward") {
                position += std::stoi(line[1]);
                depth += aim * std::stoi(line[1]);
            }
            else if (line[0] == "down") {
                aim += std::stoi(line[1]);
            }
            else if (line[0] == "up") {
                aim -= std::stoi(line[1]);
            }
        }

        return position * depth;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2021_day02::part_1("../2021/day02/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2021_day02::part_2("../2021/day02/input.in") << std::endl;

    return 0;
}
#endif
