#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>
#include <numeric>

namespace aoc2021_day06 {
    unsigned long long solve(std::string_view path, int days) {
        std::string input = file::readFileAsString(path);
        std::vector<int> fishes = utils::splitStringToInt(input, " ,");

        std::vector<unsigned long long> fishCount(9, 0);

        for (const auto& f : fishes) {
            fishCount[f]++;
        }

        while (days--) {
            unsigned long long t = fishCount[0];
            std::rotate(fishCount.begin(), fishCount.begin() + 1, fishCount.end());
            fishCount[6] += t;
        }

        return std::accumulate(fishCount.begin(), fishCount.end(), 0ULL);
    }

    unsigned long long part_1(std::string_view path, int days) {
        return solve(path, days);
    }

    unsigned long long part_2(std::string_view path, int days) {
        return solve(path, days);
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2021_day06::part_1("../2021/day06/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2021_day06::part_2("../2021/day06/input.in") << std::endl;

    return 0;
}
#endif
