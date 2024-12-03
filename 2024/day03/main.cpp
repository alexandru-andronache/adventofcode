#include "file.h"
#include <iostream>

namespace aoc2024_day03 {
    bool isSubStringNext(const std::string_view& str, int position, const std::string_view& substr) {
        return str.substr(position, substr.size()) == substr;
    }

    unsigned long long part_1(std::string_view path) {
        unsigned long long sol = 0;
        std::vector<std::string> lines = file::readFileAsArrayString(path);

        for (const auto& line : lines) {
            int i = 0;
            int nr1 = 0, nr2 = 0;
            while (i < line.size()) {
                nr1 = 0, nr2 = 0;
                if (isSubStringNext(line, i, "mul")) {
                    i += 3;
                }
                else {
                    i++;
                    continue;
                }
                if (i < line.size() && line[i] == '(') {
                    i++;
                    while (i < line.size() && line[i] >= '0' && line[i] <= '9') {
                        nr1 = nr1 * 10 + (line[i] - '0');
                        i++;
                    }
                }
                else {
                    i++;
                    continue;
                }
                if (i < line.size() && line[i] == ',') {
                    i++;
                    while (i < line.size() && line[i] >= '0' && line[i] <= '9') {
                        nr2 = nr2 * 10 + (line[i] - '0');
                        i++;
                    }
                }
                else {
                    i++;
                    continue;
                }
                if (i < line.size() && line[i] == ')') {
                    i++;
                }
                else {
                    i++;
                    continue;
                }
                sol += nr1 * nr2;
            }
        }


        return sol;
    }

    unsigned long long part_2(std::string_view path) {
        unsigned long long sol = 0;
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        bool enable = true;

        for (const auto& line : lines) {
            int i = 0;
            int nr1 = 0, nr2 = 0;
            while (i < line.size())
            {
                nr1 = 0, nr2 = 0;
                if (isSubStringNext(line, i, "do()"))
                {
                    enable = true;
                    i += 4;
                    continue;
                }
                if (isSubStringNext(line, i, "don't()"))
                {
                    enable = false;
                    i += 7;
                    continue;
                }
                if (isSubStringNext(line, i, "mul"))
                {
                    i += 3;
                }
                else
                {
                    i++;
                    continue;
                }
                if (i < line.size() && line[i] == '(')
                {
                    i++;
                    while (i < line.size() && line[i] >= '0' && line[i] <= '9') {
                        nr1 = nr1 * 10 + (line[i] - '0');
                        i++;
                    }
                }
                else
                {
                    i++;
                    continue;
                }
                if (i < line.size() && line[i] == ',') {
                    i++;
                    while (i < line.size() && line[i] >= '0' && line[i] <= '9') {
                        nr2 = nr2 * 10 + (line[i] - '0');
                        i++;
                    }
                }
                else
                {
                    i++;
                    continue;
                }
                if (i < line.size() && line[i] == ')') {
                    i++;
                }
                else
                {
                    i++;
                    continue;
                }

                if (enable)
                {
                    sol += nr1 * nr2;
                }
            }
        }


        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2024_day03::part_1("../2024/day03/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2024_day03::part_2("../2024/day03/input.in") << std::endl;

    return 0;
}
#endif
