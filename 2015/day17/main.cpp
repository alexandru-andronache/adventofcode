#include "file.h"
#include "utilities.h"
#include <iostream>

namespace aoc2015_day17 {
    int part_1(std::string_view path, int total) {
        std::vector<int> containers = file::readFileAsArrayInt(path);

        std::vector<int> sums(total + 1, 0);
        sums[0] = 1;

        for (const auto& c : containers) {
            for (int i = total; i >= c; --i) {
                sums[i] += sums[i - c];
            }
        }
        return sums[total];
    }

    int part_2(std::string_view path, int total) {
        std::vector<int> containers = file::readFileAsArrayInt(path);

        std::vector<int> sums(total + 1, 0);
        std::vector<int> best(total + 1, 1000000);
        sums[0] = 1;
        best[0] = 0;

        for (const auto& c : containers) {
            for (int i = total; i >= c; --i) {
                if (best[i - c] + 1 < best[i]) {
                    best[i] = best[i - c] + 1;
                    sums[i] = sums[i - c];
                }
                else if (best[i - c] + 1 == best[i]) {
                    sums[i] += sums[i - c];
                }
            }
        }
        return sums[total];
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2015_day17::part_1("../2015/day17/input.in", 150) << std::endl;
    std::cout << "Part 2: " << aoc2015_day17::part_2("../2015/day17/input.in", 150) << std::endl;

    return 0;
}
#endif
