#include "file.h"
#include "utilities.h"
#include <iostream>
#include <cmath>
#include <optional>

namespace aoc2015_day20 {
    int part_1(int total) {
        int N = total / 10 + 1;
        std::vector<int> numbers(N, 0);
        for (int i = 1; i <= total / 10; ++i) {
            for (int j = i; j < N; j += i) {
                numbers[j] += i;
            }
        }
        for (int j = 1; j < N; ++j) {
            if (numbers[j] >= total / 10) {
                return j;
            }
        }
        return 0;
    }

    int part_2(int total) {
        int N = (total * 50) / 11 + 1;
        std::vector<int> numbers(N, 0);
        for (int i = 1; i <= total / 11; ++i) {
            for (int j = i; j <= i * 50; j += i) {
                numbers[j] += i;
            }
        }
        for (int j = 1; j < N; ++j) {
            if (numbers[j] >= total / 11) {
                return j;
            }
        }
        return 0;
    }

}


#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2015_day20::part_1(36000000) << std::endl;
    std::cout << "Part 2: " << aoc2015_day20::part_2(36000000) << std::endl;

    return 0;
}
#endif
