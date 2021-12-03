#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>

namespace aoc2021_day03 {
    int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<int> instances(input[0].size(), 0);

        for (const auto& line : input) {
            for (int i = 0; i < line.size(); ++i) {
                if (line[i] == '1') {
                    instances[i]++;
                }
            }
        }

        std::string bits(input[0].size(), '0');
        for (int i = 0; i < input[0].size(); ++i) {
            if (instances[i] > input.size() / 2) {
                bits[i] = '1';
            }
        }

        return utils::decimalToInt(bits) * utils::decimalToInt(bits, '0');
    }

    int part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);

        std::vector<bool> oxygenIndex(input.size(), true);
        for (int i = 0; i < input[0].size(); ++i) {
            int size = std::count(oxygenIndex.begin(), oxygenIndex.end(), true);
            if (size > 1) {
                int instances = 0;
                for (int j = 0; j < input.size(); ++j) {
                    if (input[j][i] == '1' && oxygenIndex[j]) {
                        instances++;
                    }
                }
                for (int j = 0; j < oxygenIndex.size(); ++j) {
                    if (input[j][i] == '1' && instances >= size - instances && oxygenIndex[j]) {
                        oxygenIndex[j] = true;
                    } else if (input[j][i] == '0' && instances < size - instances && oxygenIndex[j]) {
                        oxygenIndex[j] = true;
                    } else {
                        oxygenIndex[j] = false;
                    }
                }
            }
        }

        int oxygen = utils::decimalToInt(input[std::find(oxygenIndex.begin(), oxygenIndex.end(), true) - oxygenIndex.begin()]);

        std::vector<bool> co2Index(input.size(), true);

        for (int i = 0; i < input[0].size(); ++i) {
            int size = std::count(co2Index.begin(), co2Index.end(), true);
            if (size > 1) {
                int instances = 0;
                for (int j = 0; j < input.size(); ++j) {
                    if (input[j][i] == '1' && co2Index[j]) {
                        instances++;
                    }
                }
                for (int j = 0; j < co2Index.size(); ++j) {
                    if (input[j][i] == '1' && instances < size - instances && co2Index[j]) {
                        co2Index[j] = true;
                    } else if (input[j][i] == '0' && instances >= size - instances && co2Index[j]) {
                        co2Index[j] = true;
                    } else {
                        co2Index[j] = false;
                    }
                }
            }
        }

        int co2 = utils::decimalToInt(input[std::find(co2Index.begin(), co2Index.end(), true) - co2Index.begin()]);

        return co2 * oxygen;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2021_day03::part_1("../2021/day03/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2021_day03::part_2("../2021/day03/input.in") << std::endl;

    return 0;
}
#endif
