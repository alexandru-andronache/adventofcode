#include "file.h"
#include "utilities.h"
#include <iostream>
#include <numeric>

namespace aoc2020_day13 {
    int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::string> buses = utils::splitString(input[1], ",");
        int time = std::stoi(input[0]);
        std::vector<int> numbers;
        for (const auto &bus : buses) {
            if (utils::isInteger(bus)) {
                numbers.push_back(std::stoi(bus));
            }
        }

        int minutes = std::numeric_limits<int>::max();
        int sol = 0;
        for (const auto &nr :numbers) {
            int p = nr - (time % nr);
            if (minutes > p) {
                minutes = p;
                sol = p * nr;
            }
        }
        return sol;
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::string> buses = utils::splitString(input[1], ",");
        std::vector<std::pair<int, int>> numbers;
        int j = 0;
        for (const auto &bus : buses) {
            if (utils::isInteger(bus)) {
                numbers.emplace_back(std::stoi(bus), j);
            }
            j++;
        }

        unsigned long long k = 0;
        unsigned long long step = numbers[0].first + numbers[0].second;
        bool found = false;
        while (!found) {
            found = true;
            k += step;
            for (const auto &nr : numbers) {
                if ((k + nr.second) % nr.first != 0) {
                    found = false;
                } else {
                    step = std::lcm(step, nr.first);
                }
            }
        }
        return k;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2020_day13::part_1("../2020/day13/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2020_day13::part_2("../2020/day13/input.in") << std::endl;

    return 0;
}
#endif
