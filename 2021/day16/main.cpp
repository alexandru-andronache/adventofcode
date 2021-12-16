#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>
#include <numeric>
#include <map>

namespace aoc2021_day16 {
    std::map<char, std::string> mask {{'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
                                      {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
                                      {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
                                      {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}};
    unsigned long long binaryToInt(std::string_view bits, int start, int size) {
        if (start + size < bits.size()) {
            return utils::decimalToInt(bits.substr(start, size));
        }
        return 0;
    }

    unsigned long long calculateSumVersion(std::string_view bits, int& index) {
        unsigned long long versionSum = binaryToInt(bits, index, 3);
        index += 3;
        unsigned long long type = binaryToInt(bits, index, 3);
        index += 3;

        if (type == 4) {
            while (bits[index] == '1') {
                index += 5;
            }
            index += 5;
            return versionSum;
        }

        if (bits[index] == '0') {
            index++;
            unsigned long long length = binaryToInt(bits, index, 15);
            index += 15;
            int start = index;
            while (index < start + length) {
                versionSum += calculateSumVersion(bits, index);
            }
        }
        else {
            index++;
            unsigned long long nr = binaryToInt(bits, index, 11);
            index += 11;
            for (int i = 0; i < nr; ++i) {
                versionSum += calculateSumVersion(bits, index);
            }
        }
        return versionSum;
    }

    unsigned long long calculateSumValue(std::string_view bits, int& index) {
        std::string str;
        index += 3;
        unsigned long long typeValue = binaryToInt(bits, index, 3);
        index += 3;

        if (typeValue == 4) {
            while (index < bits.size() && bits[index] == '1') {
                str += bits.substr(index + 1, 4);
                index += 5;
            }
            if (index < bits.size()) {
                str += bits.substr(index + 1, 4);
                index += 5;
            }
            return utils::decimalToInt(str);
        }

        std::vector<unsigned long long> values;
        if (bits[index] == '0') {
            index++;
            unsigned long long length = binaryToInt(bits, index, 15);
            index += 15;
            int start = index;
            while (index < start + length) {
                values.push_back(calculateSumValue(bits, index));
            }
        }
        else {
            index++;
            unsigned long long nr = binaryToInt(bits, index, 11);
            index += 11;
            for (int i = 0; i < nr; ++i) {
                values.push_back(calculateSumValue(bits, index));
            }
        }

        if (typeValue == 0) {
            return std::accumulate(values.begin(), values.end(), 0ULL);
        }
        if (typeValue == 1) {
            return std::accumulate(values.begin(), values.end(), 1ULL, [](const auto& a, const auto&b) {
                return a * b;
            });
        }
        if (typeValue == 2) {
            return *std::min_element(values.begin(), values.end());
        }
        if (typeValue == 3) {
            return *std::max_element(values.begin(), values.end());
        }
        if (typeValue == 5) {
            return values[0] > values[1];
        }
        if (typeValue == 6) {
            return values[0] < values[1];
        }
        if (typeValue == 7) {
            return values[0] == values[1];
        }
    }

    unsigned long long part_1(std::string_view path) {
        std::string input = file::readFileAsString(path);
        std::string bits;
        for (const auto& letter : input) {
            bits += mask[letter];
        }
        int index = 0;

        return calculateSumVersion(bits, index);
    }

    unsigned long long part_2(std::string_view path) {
        std::string input = file::readFileAsString(path);
        std::string bits;
        for (const auto& letter : input) {
            bits += mask[letter];
        }
        int index = 0;

        return calculateSumValue(bits, index);
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2021_day16::part_1("../2021/day16/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2021_day16::part_2("../2021/day16/input.in") << std::endl;

    return 0;
}
#endif
