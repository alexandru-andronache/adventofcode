#include "file.h"
#include "utilities.h"
#include <iostream>
#include <array>
#include <algorithm>

namespace aoc2022_day10 {
    int cycle(int& c, int X) {
        c++;
        if (c == 20 || c == 60 || c == 100 || c == 140 || c == 180 || c == 220) {
            return X * c;
        }
        return 0;
    }

    void cycle_part_2(int& c, int X) {
        c++;
        if (std::abs(((c - 1) % 40) - X) < 2) {
            std::cout << "#";
        }
        else {
            std::cout << ".";
        }
        if (c % 40 == 0) {
            std::cout << "\n";
        }
    }
    int part_1(std::string_view path) {

        std::vector<std::string> input = file::readFileAsArrayString(path);
        int X = 1;
        int sum = 0;
        int c = 0;
        std::vector<std::pair<int, int>> prev;
        for (const auto& l : input) {
            std::vector<std::string> t = utils::splitString(l, " ");
            if (t[0] == "noop") {
                sum += cycle(c, X);
            }
            else {
                sum += cycle(c, X);
                sum += cycle(c, X);
                X += std::stoi(t[1]);
            }
        }

        return sum;
    }

    int part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        int X = 1;
        int c = 0;
        std::vector<std::pair<int, int>> prev;
        for (const auto& l : input) {
            std::vector<std::string> t = utils::splitString(l, " ");

            if (t[0] == "noop") {
                cycle_part_2(c, X);
            }
            else {
                cycle_part_2(c, X);
                cycle_part_2(c, X);
                X += std::stoi(t[1]);
            }
        }

        return 0;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2022_day10::part_1("../2022/day10/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2022_day10::part_2("../2022/day10/input.in") << std::endl;

    return 0;
}
#endif
