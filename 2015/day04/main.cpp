#include "file.h"
#include "md5.h"
#include <iostream>

namespace aoc2015_day04 {
    int part_1(std::string_view path) {
        int i = 0;
        while (md5::calculateMD5(input + std::to_string(i)).substr(0, 5) != "00000") {
            i++;
        }
        return i;
    }

    int part_2(std::string_view path) {
        int i = 0;
        while (md5::calculateMD5(input + std::to_string(i)).substr(0, 6) != "000000") {
            i++;
        }
        return i;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2015_day04::part_1("ckczppom") << std::endl;
    std::cout << "Part 2: " << aoc2015_day04::part_2("ckczppom") << std::endl;

    return 0;
}
#endif
