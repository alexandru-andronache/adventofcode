#include "file.h"
#include "utilities.h"
#include <iostream>
#include <array>

namespace aoc2020_day10 {
    int part_1(std::string_view path) {
        std::vector<int> input = file::readFileAsArrayInt(path);
        input.push_back(0);
        std::sort(input.begin(), input.end());
        input.push_back(input.back() + 3);
        std::array<int, 3> diff{0, 0, 0};
        for (int i = 1; i < input.size(); ++i) {
            diff[input[i] - input[i - 1] - 1]++;
        }
        return diff[0] * diff[2];
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<int> input = file::readFileAsArrayInt(path);
        std::sort(input.begin(), input.end());
        input.push_back(input.back() + 3);
        std::vector<unsigned long long> results(input.back() + 1, 0);

        results[0] = 1;
        int k = 0;

        for (int j = 1; j <= input.back(); ++j) {
            if (input[k] == j) {
                results[j] = 0;
                for (int i = 1; i <= 3; ++i) {
                    if (j - i >= 0) {
                        results[j] += results[j - i];
                    }
                }
                k++;
            } else {
                results[j] = 0;
            }
        }
        return results.back();
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2020_day10::part_1("../2020/day10/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2020_day10::part_2("../2020/day10/input.in") << std::endl;

    return 0;
}
#endif
