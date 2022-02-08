#include "file.h"
#include "utilities.h"
#include <iostream>
#include <algorithm>

namespace aoc2020_day06 {
    void fillArrayWithLetters(std::vector<int> &letters, std::string_view str) {
        for (const auto &c : str) {
            letters[c - 'a']++;
        }
    }

    int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<int> answers(26, 0);
        int sol = 0;
        for (const auto &line: input) {
            if (line.empty()) {
                sol += std::count_if(answers.begin(), answers.end(), [](const auto &c) {
                    return c > 0;
                });
                std::fill(answers.begin(), answers.end(), false);
            } else {
                fillArrayWithLetters(answers, line);
            }
        }
        return sol;
    }

    int part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<int> answers(26, 0);
        int sol = 0;
        int lines = 0;
        for (const auto &line: input) {
            if (line.empty()) {
                sol += std::count(answers.begin(), answers.end(), lines);
                std::fill(answers.begin(), answers.end(), 0);
                lines = 0;
            } else {
                lines++;
                fillArrayWithLetters(answers, line);
            }
        }
        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2020_day06::part_1("../2020/day06/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2020_day06::part_2("../2020/day06/input.in") << std::endl;

    return 0;
}
#endif
