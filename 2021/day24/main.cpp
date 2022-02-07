#include "file.h"
#include "utilities.h"
#include <iostream>
#include <array>
#include <stack>

namespace aoc2021_day24 {
    unsigned long long part_1(std::string_view path) {
        /*
            the input for this is very custom
            it consist of 14 parts of 18 lines each
            in each part you either multiply the final number by 26 or divide it by 26
            the solution will be to match the parts were you multiply with the parts where you divide it
            and then get the maximum value between 1 and 9 that maches this equation:
            max + value from line 15 in part1 + value from line 5 in part2 = a number between 1 and 9
        */
        std::stack<std::pair<int, int>> st;
        std::array<int, 14> sol;
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        for (int i = 0; i < lines.size(); i = i + 18) {
            std::vector<std::string> instructions1 = utils::splitString(lines[i + 15], " ");
            std::vector<std::string> instructions2 = utils::splitString(lines[i + 5], " ");
            if (lines[i + 4] == "div z 1") {
                st.push({i / 18, std::stoi(instructions1[2])});
            }
            else {
                int sum = st.top().second + std::stoi(instructions2[2]);
                int max = 9;
                while (max + sum > 9) {
                    max--;
                }
                sol[st.top().first] = max;
                sol[i / 18] = max + sum;
                st.pop();
            }
        }

        unsigned long long rez = 0;
        for (const auto &nr : sol) {
            rez = rez * 10 + nr;
        }
        return rez;
    }

    unsigned long long part_2(std::string_view path) {
        std::stack<std::pair<int, int>> st;
        std::array<int, 14> sol {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        for (int i = 0; i < lines.size(); i = i + 18) {
            std::vector<std::string> instructions1 = utils::splitString(lines[i + 15], " ");
            std::vector<std::string> instructions2 = utils::splitString(lines[i + 5], " ");
            if (lines[i + 4] == "div z 1") {
                st.push({i / 18, std::stoi(instructions1[2])});
            }
            else {
                int sum = st.top().second + std::stoi(instructions2[2]);
                int min = 1;
                while (min + sum < 1) {
                    min++;
                }
                sol[st.top().first] = min;
                sol[i / 18] = min + sum;
                st.pop();
            }
        }

        unsigned long long rez = 0;
        for (const auto &nr : sol) {
            rez = rez * 10 + nr;
        }
        return rez;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2021_day24::part_1("../2021/day24/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2021_day24::part_2("../2021/day24/input.in") << std::endl;

    return 0;
}
#endif
