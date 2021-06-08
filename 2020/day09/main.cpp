#include "file.h"
#include "utilities.h"
#include <iostream>
#include <deque>

namespace aoc2020_day09 {
    int part_1(std::string_view path, int size = 25) {
        std::vector<int> input = file::readFileAsArrayInt(path);
        std::deque<int> sums;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (i != j) {
                    sums.push_back(input[i] + input[j]);
                }
            }
        }

        for (int i = size; i < input.size(); ++i) {
            if (std::find(sums.begin(), sums.end(), input[i]) == sums.end()) {
                return input[i];
            }
            sums.erase(sums.begin(), sums.begin() + size - 1);
            for (int j = 0; j < size - 1; ++j) {
                sums.push_back(input[i] + input[i - j - 1]);
            }
        }
        return 0;
    }

    int part_2(std::string_view path, int nr = 27911108) {
        std::vector<int> input = file::readFileAsArrayInt(path);
        for (int i = 0; i < input.size(); ++i) {
            int sum = input[i];
            int j = i;
            while (j + 1 < input.size() && sum < nr) {
                j++;
                sum += input[j];
            }
            if (sum == nr) {
                return *std::min_element(input.begin() + i, input.begin() + j + 1) +
                       *std::max_element(input.begin() + i, input.begin() + j + 1);
            }
        }
        return 0;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2020_day09::part_1("../2020/day09/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2020_day09::part_2("../2020/day09/input.in") << std::endl;

    return 0;
}
#endif
