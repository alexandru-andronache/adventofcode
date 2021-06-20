#include "file.h"
#include <iostream>

namespace aoc2016_day16 {
    std::string solve(std::string input, int size) {
        while (input.size() < size) {
            std::string reverse = "0";
            for (int i = input.size() - 1; i >= 0; --i) {
                reverse += '0' + (input[i] - '0' + 1) % 2;
            }
            input += reverse;
        }
        input = input.substr(0, size);

        while (input.size() % 2 == 0) {
            std::string checksum;
            for (int i = 0; i < input.size(); i += 2) {
                if (input[i] == input[i + 1]) {
                    checksum += "1";
                }
                else {
                    checksum += "0";
                }
            }
            input = checksum;
        }

        return input;
    }

    std::string part_1(const std::string& input) {
        return solve(input, 272);
    }

    std::string part_2(const std::string& input) {
        return solve(input, 35651584);
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2016_day16::part_1("00101000101111010") << std::endl;
    std::cout << "Part 2: " << aoc2016_day16::part_2("00101000101111010") << std::endl;

    return 0;
}
#endif
