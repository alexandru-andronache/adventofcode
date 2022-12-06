#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>
#include <string>

namespace aoc2022_day06 {
    int solve(std::string_view path, int size) {
        std::string input = file::readFileAsString(path);

        int i = 0;
        std::vector<char> t;
        while (i < input.size()) {
            auto it = std::find(t.begin(), t.end(), input[i]);
            if (it != t.end()) {
                std::vector<char> tmp;
                std::copy(std::next(it), t.end(), std::back_inserter(tmp));
                t.clear();
                std::copy(tmp.begin(), tmp.end(), std::back_inserter(t));
            }
            t.push_back(input[i]);
            if (t.size() == size) {
                return i + 1;
            }
            i++;
        }

        return 0;
    }
    int part_1(std::string_view path) {
        return solve(path, 4);
    }

    int part_2(std::string_view path) {
        return solve(path, 14);
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2022_day06::part_1("../2022/day06/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2022_day06::part_2("../2022/day06/input.in") << std::endl;

    return 0;
}
#endif
