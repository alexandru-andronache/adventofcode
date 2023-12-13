#include "file.h"
#include "utilities.h"
#include <iostream>

namespace aoc2023_day13 {
    int compareString(std::string_view str1, std::string_view str2) {
        int diff = 0;
        for (int i = 0; i < str1.size(); ++i) {
            if (str1[i] != str2[i]) {
                diff++;
            }
        }
        return diff;
    }

    int isReflexion(const std::vector<std::string>& lines, int nrDiff) {
        for (int i = 0; i < lines.size() - 1; ++i) {
            //reflexion between i and i + 1
            int sumDiff = 0;
            for (int j = 0; j <= i; ++j) {
                if (i - j >= 0 && i + 1 + j < lines.size()) {
                    sumDiff += compareString(lines[i - j], lines[i + 1 + j]);
                }
            }
            if (sumDiff == nrDiff) {
                return i + 1;
            }
        }
        return 0;
    }

    unsigned long long solve(std::string_view path, int diff) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        unsigned long long sol = 0;
        int index = 0;
        while (index < input.size()) {
            int start = index;
            std::vector<std::string> horizontal;
            while (index < input.size() && input[index] != "") {
                horizontal.emplace_back(input[index]);
                index++;
            }
            int end = index - 1;
            index++;

            sol += 100 * isReflexion(horizontal, diff);

            std::vector<std::string> vertical;
            for (int i = 0; i < input[start].size(); ++i) {
                std::string p;
                for (int j = start; j <= end; ++j) {
                    p += input[j][i];
                }
                vertical.push_back(p);
            }

            sol += isReflexion(vertical, diff);
        }
        return sol;
    }

    unsigned long long part_1(std::string_view path) {
        return solve(path, 0);
    }

    unsigned long long part_2(std::string_view path) {
        return solve(path, 1);
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2023_day13::part_1("../2023/day13/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2023_day13::part_2("../2023/day13/input.in") << std::endl;

    return 0;
}
#endif
