#include "file.h"
#include "utilities.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

namespace aoc2023_day09 {
    unsigned long long part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        unsigned long long sol = 0;

        for (const auto& line : input) {
            std::vector<int> t = utils::splitStringToInt(line, " ");
            bool isZero = false;
            while (!t.empty() && !isZero) {
                sol += t.back();
                std::vector<int> t1;
                for (int i = 0; i < t.size() - 1; ++i) {
                    t1.push_back(t[i + 1] - t[i]);
                }
                t = t1;
                isZero = std::all_of(t.begin(), t.end(), [](int i) {return i == 0;});
            }
        }
        return sol;
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        unsigned long long sol = 0;

        for (const auto& line : input) {
            std::vector<int> t = utils::splitStringToInt(line, " ");
            bool isZero = false;
            std::vector<int> prev;
            while (!t.empty() && !isZero) {
                std::vector<int> t1;
                prev.push_back(t.front());
                for (int i = 0; i < t.size() - 1; ++i) {
                    t1.push_back(t[i + 1] - t[i]);
                }
                t = t1;
                isZero = std::all_of(t.begin(), t.end(), [](int i) {return i == 0;});
            }
            int p = 0;
            for (int i = prev.size() - 1; i > 0; i--) {
                p = prev[i] - p;
            }
            sol += prev[0] - p;
        }
        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2023_day09::part_1("../2023/day09/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2023_day09::part_2("../2023/day09/input.in") << std::endl;

    return 0;
}
#endif
