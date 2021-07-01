#include "file.h"
#include "intcode.h"
#include <iostream>
#include <vector>

namespace aoc2019_day05 {
    int part_1(std::string_view path, long long inputId = 1) {
        std::vector<long long> input = file::readFileAsArrayLongLong(path, ",");

        intcode::IntCode<long long> calc(input, {inputId}, 0);
        intcode::IntCode<long long>::exitState exit {0, 0, false};
        while (exit.returnValue == 0 && !exit.halt) {
            exit = calc.advance();
        }
        return exit.returnValue;
    }

    int part_2(std::string_view path, long long inputId = 5) {
        std::vector<long long> input = file::readFileAsArrayLongLong(path, ",");

        intcode::IntCode<long long> calc(input, {inputId}, 0);
        intcode::IntCode<long long>::exitState exit {0, 0, false};
        while (exit.returnValue == 0 && !exit.halt) {
            exit = calc.advance();
        }
        return exit.returnValue;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2019_day05::part_1("../2019/day05/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2019_day05::part_2("../2019/day05/input.in") << std::endl;

    return 0;
}
#endif
