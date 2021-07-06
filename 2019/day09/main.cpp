#include "file.h"
#include "intcode.h"
#include <iostream>
#include <vector>

namespace aoc2019_day09 {
    unsigned long long part_1(std::string_view path, int id = 1) {
        std::vector<long long> input = file::readFileAsArrayLongLong(path, ",");

        intcode::IntCode calc{input, {id, 0}};
        return calc.advance().returnValue;
    }

    unsigned long long part_2(std::string_view path, int id = 2) {
        std::vector<long long> input = file::readFileAsArrayLongLong(path, ",");

        intcode::IntCode calc{input, {id, 0}};
        return calc.advance().returnValue;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2019_day09::part_1("../2019/day09/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2019_day09::part_2("../2019/day09/input.in") << std::endl;

    return 0;
}
#endif
