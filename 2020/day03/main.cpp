#include "file.h"
#include "utilities.h"
#include <iostream>

namespace aoc2020_day03 {
    int solve(const std::vector<std::string> &input, int down, int right) {
        int sol = 0;
        int j = 0;
        for (int i = 0; i < input.size(); i += down) {
            if (input[i][j] == '#') {
                sol++;
            }
            j = (j + right) % input[0].size();
        }
        return sol;
    }

    int part_1(std::string_view path, int down = 1, int right = 3) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        return solve(input, down, right);
    }

    int part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        return solve(input, 1, 1) *
               solve(input, 1, 3) *
               solve(input, 1, 5) *
               solve(input, 1, 7) *
               solve(input, 2, 1);
    }
}

#ifndef TESTING
int main() {


    std::cout << "Part 1: " << aoc2020_day03::part_1("../2020/day03/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2020_day03::part_2("../2020/day03/input.in") << std::endl;

    return 0;
}
#endif
