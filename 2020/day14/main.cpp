#include "file.h"
#include "utilities.h"
#include <iostream>
#include <numeric>
#include <map>

namespace aoc2020_day14 {
    unsigned long long part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::map<unsigned long long, unsigned long long> values;
        std::string mask;
        for (const auto &line : input) {
            if (line.substr(0, 4) == "mask") {
                mask = line.substr(7);
                std::reverse(mask.begin(), mask.end());
            } else {
                std::vector<std::string> numbers = utils::splitString(line, "[] =");
                unsigned long long nr = std::stoll(numbers[2]);
                for (unsigned long long i = 0; i < mask.size(); ++i) {
                    if (mask[i] == '1') {
                        nr |= (1ull << i);
                    } else if (mask[i] == '0') {
                        nr &= ~(1ull << i);
                    }
                }
                values[std::stoll(numbers[1])] = nr;
            }
        }

        unsigned long long sum = 0;
        for (const auto &el : values) {
            sum += el.second;
        }
        return sum;
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::map<unsigned long long, unsigned long long> values;
        std::string mask;
        for (const auto &line : input) {
            if (line.substr(0, 4) == "mask") {
                mask = line.substr(7);
                std::reverse(mask.begin(), mask.end());
            } else {
                std::vector<std::string> numbers = utils::splitString(line, "[] =");
                unsigned long long nr = std::stoll(numbers[1]);
                std::string floating = "";
                for (int i = 0; i < mask.size(); ++i) {
                    if (mask[i] == '1' || mask[i] == 'X') {
                        floating += mask[i];
                    } else {
                        std::bitset<40> bits(nr);
                        if (bits.test(i)) {
                            floating += '1';
                        } else {
                            floating += '0';
                        }
                    }
                }
                int x = 0;
                for (const auto &c : floating) {
                    if (c == 'X') {
                        x++;
                    }
                }

                for (int i = 0; i < std::pow(2, x); ++i) {
                    std::bitset<40> b(i);
                    int k = 0;
                    std::string p = floating;
                    for (int j = 0; j < p.size(); ++j) {
                        if (p[j] == 'X') {
                            if (b.test(k)) {
                                p[j] = '1';
                            } else {
                                p[j] = '0';
                            }
                            k++;
                        }
                    }
                    std::reverse(p.begin(), p.end());
                    std::bitset<40> c(p);
                    values[c.to_ullong()] = std::stoll(numbers[2]);
                }
            }
        }

        unsigned long long sum = 0;
        for (const auto &el : values) {
            sum += el.second;
        }
        return sum;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2020_day14::part_1("../2020/day14/input.in") << std::endl;
    std::cout << "Part 1: " << aoc2020_day14::part_2("../2020/day14/input.in") << std::endl;

    return 0;
}
#endif
