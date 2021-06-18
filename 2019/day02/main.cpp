#include "file.h"
#include "intcode.h"
#include <iostream>
#include <vector>

namespace aoc2019_day02 {
    long long solveWithReplace(const std::vector<long long>& input, long long first, long long second) {
        std::vector<long long> v(input);
        v[1] = first;
        v[2] = second;
        intcode::IntCode<long long> calc{v, {}};
        calc.advance();
        return calc.values[0];
    }

    long long part_1(std::string_view path) {
        std::vector<long long> input = file::readFileAsArrayLongLong(path, ",");
        return solveWithReplace(input, 12, 2);
    }

    long long part_2(std::string_view path) {
        std::vector<long long> input = file::readFileAsArrayLongLong(path, ",");
        for (int i = 0; i < 100; ++i) {
            for (int j = 0; j < 100; ++j) {
                if (solveWithReplace(input, i, j) == 19690720) {
                    return i * 100 + j;
                }
            }
        }
        return 0;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2019_day02::part_1("../2019/day02/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2019_day02::part_2("../2019/day02/input.in") << std::endl;

    return 0;
}
#endif
