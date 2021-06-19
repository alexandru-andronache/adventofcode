#include "file.h"
#include "utilities.h"
#include <iostream>
#include <map>
#include <stack>
#include <set>

namespace aoc2016_day07 {
    int part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);

        int sol = 0;
        for (const auto& line : lines) {
            bool hasAbba = false;
            bool insideBrackets = false;
            bool hasAbbaInsideBrackets = false;
            for (int i = 0; i < line.size() - 3; ++i) {
                if (line[i] == '[') {
                    insideBrackets = true;
                }
                else if (line[i] == ']') {
                    insideBrackets = false;
                }
                else {
                    if (line[i] == line[i + 3] && line[i + 1] == line[i + 2] && line[i] != line[i + 1]) {
                        if (insideBrackets) {
                            hasAbbaInsideBrackets = true;
                        }
                        else {
                            hasAbba = true;
                        }
                    }
                }
            }

            if (hasAbba && !hasAbbaInsideBrackets) {
                sol++;
            }
        }

        return sol;
    }

    int part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);

        int sol = 0;
        for (const auto& line : lines) {
            std::vector<std::string> aba;
            std::vector<std::string> bab;
            bool insideBrackets = false;
            for (int i = 0; i < line.size() - 2; ++i) {
                if (line[i] == '[') {
                    insideBrackets = true;
                }
                else if (line[i] == ']') {
                    insideBrackets = false;
                }
                else {
                    if (line[i] == line[i + 2] && line[i] != line[i + 1]) {
                        if (insideBrackets) {
                            bab.push_back(line.substr(i, 3));
                        }
                        else {
                            aba.push_back(line.substr(i, 3));
                        }
                    }
                }
            }
            bool isSol = false;
            for (const auto& l : aba) {
                for (const auto& p : bab) {
                    if (l[1] == p[0] && l[0] == p[1]) {
                        isSol = true;
                    }
                }
            }
            if (isSol) {
                sol++;
            }
        }

        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2016_day07::part_1("../2016/day07/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2016_day07::part_2("../2016/day07/input.in") << std::endl;

    return 0;
}
#endif
