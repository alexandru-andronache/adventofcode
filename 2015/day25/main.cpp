#include "file.h"
#include "utilities.h"
#include <iostream>

namespace aoc2015_day25 {
    long long getNextValue(long long value) {
        const long long multiplier = 252533;
        const long long divider = 33554393;
        return (value * multiplier) % divider;
    }

    long long part_1(int row, int column) {
        long long value = 20151125;

        for (int i = 2; i <= row + column - 2; ++i) {
            for (int j = 1; j <= i; ++j) {
                value = getNextValue(value);
            }
        }
        for (int j = 1; j <= column; ++j) {
            value = getNextValue(value);
        }
        return value;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2015_day25::part_1(2978, 3083) << std::endl;
    return 0;
}
#endif
