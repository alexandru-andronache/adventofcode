#include "file.h"
#include <iostream>
#include <vector>

namespace aoc2017_day05 {
    int part_1(std::string_view path) {
        std::vector<int> input = file::readFileAsArrayInt(path);

        int start = 0;
        int steps = 0;
        while (start < input.size()) {
            int newStart = start + input[start];
            input[start]++;
            start = newStart;
            steps++;
        }
        return steps;
    }

    int part_2(std::string_view path) {
        std::vector<int> input = file::readFileAsArrayInt(path);

        int start = 0;
        int steps = 0;
        while (start < input.size()) {
            int newStart = start + input[start];
            if (input[start] >= 3) {
                input[start]--;
            }
            else {
                input[start]++;
            }
            start = newStart;
            steps++;
        }
        return steps;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2017_day05::part_1("../2017/day05/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2017_day05::part_2("../2017/day05/input.in") << std::endl;

    return 0;
}
#endif
