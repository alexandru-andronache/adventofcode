#include "file.h"
#include <iostream>

namespace aoc2017_day09 {
    int part_1(std::string_view path) {
        std::string input = file::readFileAsString(path);

        int sum = 0;
        int score = 0;
        bool isGarbage = false;
        bool ignoreNext = false;
        for (const auto& c : input) {
            if (ignoreNext) {
                ignoreNext = false;
            }
            else if (c == '!') {
                ignoreNext = true;
            }
            else if (isGarbage && c != '>') {

            }
            else if (c == '>') {
                isGarbage = false;
            }
            else if (c == '<' && !isGarbage) {
                isGarbage = true;
            }
            else if (c == '{') {
                score++;
            }
            else if (c == '}') {
                sum += score;
                score--;
            }
        }

        return sum;
    }

    int part_2(std::string_view path) {
        std::string input = file::readFileAsString(path);

        int nrGarbage = 0;
        bool isGarbage = false;
        bool ignoreNext = false;
        for (const auto& c : input) {
            if (ignoreNext) {
                ignoreNext = false;
            }
            else if (c == '!') {
                ignoreNext = true;
            }
            else if (isGarbage && c != '>') {
                nrGarbage++;
            }
            else if (c == '>') {
                isGarbage = false;
            }
            else if (c == '<' && !isGarbage) {
                isGarbage = true;
            }
        }
        return nrGarbage;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2017_day09::part_1("../2017/day09/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2017_day09::part_2("../2017/day09/input.in") << std::endl;

    return 0;
}
#endif
