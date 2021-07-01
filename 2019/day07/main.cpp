#include "file.h"
#include "utilities.h"
#include "intcode.h"
#include <iostream>
#include <map>
#include <stack>
#include <set>

namespace aoc2019_day07 {
    long long part_1(std::string_view path) {
        std::vector<long long> input = file::readFileAsArrayLongLong(path, ",");

        std::vector<int> v {0, 1, 2, 3, 4};
        long long max = 0;

        do {
            long long inputId = 0;
            for (const auto &i : v) {
                std::deque in {i, inputId};
                intcode::IntCode<long long> calculator(input, in);
                intcode::IntCode<long long>::exitState exit = calculator.advance();
                inputId = exit.returnValue;
            }
            max = std::max(max, inputId);
        } while(std::next_permutation(v.begin(), v.end()));

        return max;
    }

    int part_2(std::string_view path) {
        std::vector<long long> input = file::readFileAsArrayLongLong(path, ",");
        
        std::vector<int> v {5, 6, 7, 8, 9};
        long long max = 0;

        do {
            std::vector<intcode::IntCode<long long>> states{{input, {v[0], 0}, 0},
                                                            {input, {v[1]}, 0},
                                                            {input, {v[2]}, 0},
                                                            {input, {v[3]}, 0},
                                                            {input, {v[4]}, 0}};
            bool shouldStop = false;
            long long returnValue = 0;

            while (!shouldStop) {
                auto it = states.begin();
                for (const auto &i : v) {
                    intcode::IntCode<long long>::exitState exit = it->advance();
                    if (exit.returnValue != 0)
                        returnValue = exit.returnValue;
                    it++;
                    shouldStop = exit.halt;
                    if (it != states.end()) {
                        it->inputIDs.push_back(exit.returnValue);
                    }
                    else {
                        states.front().inputIDs.push_back(exit.returnValue);
                    }
                }
            }
            max = std::max(max, returnValue);
        } while(std::next_permutation(v.begin(), v.end()));

        return max;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2019_day07::part_1("../2019/day07/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2019_day07::part_2("../2019/day07/input.in") << std::endl;

    return 0;
}
#endif
