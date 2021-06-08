#include "file.h"
#include "utilities.h"
#include <iostream>

namespace aoc2020_day15 {
    unsigned long long solve(const std::vector<int> &input, int nr) {
        std::vector<std::pair<int, int>> a(40000000, {-1, -1});

        for (int i = 0; i < input.size(); ++i) {
            a[input[i]] = {i + 1, -1};
        }

        int lastNumber = input.back();
        for (int k = input.size() + 1; k <= nr; ++k) {
            if (a[lastNumber].second != -1) {
                lastNumber = a[lastNumber].first - a[lastNumber].second;
                a[lastNumber].second = a[lastNumber].first;
                a[lastNumber].first = k;
            } else {
                lastNumber = 0;
                a[lastNumber].second = a[lastNumber].first;
                a[lastNumber].first = k;
            }
        }

        return lastNumber;
    }

    unsigned long long part_1(std::string_view path) {
        std::string str = file::readFileAsString(path);
        std::vector<int> input = utils::splitStringToInt(str, ",");

        return solve(input, 2020);
    }

    unsigned long long part_2(std::string_view path) {
        std::string str = file::readFileAsString(path);
        std::vector<int> input = utils::splitStringToInt(str, ",");

        return solve(input, 30000000);
    }
}

#ifndef TESTING
int main() {

    std::cout << "Part 1: " << aoc2020_day15::part_1("../2020/day15/input.in") << std::endl;
    std::cout << "Part 1: " << aoc2020_day15::part_2("../2020/day15/input.in") << std::endl;

    return 0;
}
#endif
