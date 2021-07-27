#include "file.h"
#include <iostream>
#include <vector>
#include <set>

namespace aoc2017_day06 {
    int part_1(std::string_view path) {
        std::vector<int> input = file::readFileAsArrayInt(path);

        std::set<std::vector<int>> states;
        while (states.insert(input).second) {
            auto it = std::max_element(input.begin(), input.end());
            int max = *it;
            *it = 0;
            for (int i = 0; i < max; ++i) {
                it++;
                if (it == input.end()) {
                    it = input.begin();
                }
                (*it)++;
            }
        }
        return states.size();
    }

    int part_2(std::string_view path) {
        std::vector<int> input = file::readFileAsArrayInt(path);

        std::set<std::vector<int>> states;
        while (states.insert(input).second) {
            auto it = std::max_element(input.begin(), input.end());
            int max = *it;
            *it = 0;
            for (int i = 0; i < max; ++i) {
                it++;
                if (it == input.end()) {
                    it = input.begin();
                }
                (*it)++;
            }
        }
        std::set<std::vector<int>> loop;
        while (loop.insert(input).second) {
            auto it = std::max_element(input.begin(), input.end());
            int max = *it;
            *it = 0;
            for (int i = 0; i < max; ++i) {
                it++;
                if (it == input.end()) {
                    it = input.begin();
                }
                (*it)++;
            }
        }
        return loop.size();
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2017_day06::part_1("../2017/day06/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2017_day06::part_2("../2017/day06/input.in") << std::endl;

    return 0;
}
#endif
