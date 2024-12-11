#include "file.h"
#include "utilities.h"
#include <iostream>
#include <set>
#include <map>

namespace aoc2024_day11 {
    int sol = 0;
    int count_digit(unsigned long long number) {
        return int(log10(number) + 1);
    }

    unsigned long long solve(std::string_view path, int cycles = 25) {
        std::vector<int> stones = file::readFileAsArrayInt(path);
        std::map<unsigned long long, unsigned long long> cache;
        for (const auto & stone : stones) {
            cache[stone] += 1;
        }
        for (int cycle = 0; cycle < cycles; ++cycle) {
            std::map<unsigned long long, unsigned long long> newCache;
            for (const auto& c : cache) {
                int n = count_digit(c.first);
                if (c.first == 0) {
                    newCache[1] += c.second;
                }
                else if (n % 2 == 0) {
                    unsigned long long half = 0, other = c.first;
                    for (int i = 0; i < n / 2; ++i) {
                        half += other % 10 * pow(10, i);
                        other /= 10;
                    }
                    newCache[half] += c.second;
                    newCache[other] += c.second;
                }
                else {
                    newCache[c.first * 2024] += c.second;
                }
            }
            cache = newCache;
        }
        unsigned long long total = 0;
        for (const auto& c : cache) {
            total += c.second;
        }
        return total;
    }

    unsigned long long part_1(std::string_view path, int cycles = 25) {
        return solve(path, cycles);
    }

    unsigned long long part_2(std::string_view path, int cycles = 75) {
        return solve(path, cycles);
    }
}
#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2024_day11::part_1("../2024/day11/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2024_day11::part_2("../2024/day11/input.in") << std::endl;

    return 0;
}
#endif
