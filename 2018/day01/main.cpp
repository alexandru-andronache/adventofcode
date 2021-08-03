#include "file.h"
#include <iostream>
#include <vector>
#include <numeric>
#include <set>

namespace aoc2018_day01 {
    int part_1(std::string_view path) {
        std::vector<int> input = file::readFileAsArrayInt(path);
        return std::accumulate(input.begin(), input.end(), 0);
    }

    int part_2(std::string_view path) {
        std::vector<int> input = file::readFileAsArrayInt(path);
        std::set<int> partialSums;
        int sum = 0;
        while (true) {
            for (auto x : input) {
                partialSums.insert(sum);
                sum += x;
                if (partialSums.find(sum) != partialSums.end()) {
                    return sum;
                }
            }
        }
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2018_day01::part_1("../2018/day01/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2018_day01::part_2("../2018/day01/input.in") << std::endl;

    return 0;
}
#endif
