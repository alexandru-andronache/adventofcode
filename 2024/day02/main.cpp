#include "file.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

namespace aoc2024_day02 {
    bool validate(const std::vector<int>& input) {
        bool isSol = std::ranges::is_sorted(input) || std::ranges::is_sorted(input, std::greater<>());
        for (int j = 0; j < input.size() - 1; ++j)
        {
            if (std::abs(input[j] - input[j + 1]) >= 4 || std::abs(input[j] - input[j + 1]) == 0)
            {
                isSol = false;
            }
        }
        return isSol;
    }

    unsigned long long part_1(std::string_view path) {
        unsigned long long sol = 0;

        const std::vector<std::vector<int>>& input = file::readFileAsVectorOfVectors(path);

        for (const auto & line : input)
        {
            if (validate(line))
            {
                sol++;
            }
        }

        return sol;
    }

    unsigned long long part_2(std::string_view path) {
        unsigned long long sol = 0;

        const std::vector<std::vector<int>>& input = file::readFileAsVectorOfVectors(path);

        for (const auto & line : input)
        {
            for (int j = 0; j < line.size(); ++j)
            {
                std::vector<int> temp = line;
                temp.erase(temp.begin() + j);
                if (validate(temp))
                {
                    sol++;
                    break;
                }
            }
        }

        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2024_day02::part_1("../2024/day02/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2024_day02::part_2("../2024/day02/input.in") << std::endl;

    return 0;
}
#endif
