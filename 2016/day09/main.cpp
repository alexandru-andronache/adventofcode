#include "file.h"
#include "utilities.h"
#include <iostream>

namespace aoc2016_day09 {
    int part_1(std::string_view path) {
        std::string input = file::readFileAsString(path);

        int i = 0;
        int size = 0;
        while (i < input.size()) {
            if (input[i] == '(') {
                i++;
                int nrCharacters = utils::getNumber(input, i);
                i++;
                int repetitions = utils::getNumber(input, i);
                i++;
                size += nrCharacters * repetitions;
                i += nrCharacters;
            }
            else {
                size++;
                i++;
            }
        }
        return size;
    }

    long long processString(std::string_view str, int start, int end) {
        int i = start;
        long long size = 0;
        while (i < end) {
            if (str[i] == '(') {
                i++;
                int nrCharacters = utils::getNumber(str, i);
                i++;
                int repetitions = utils::getNumber(str, i);
                i++;
                size += processString(str, i, i + nrCharacters) * repetitions;
                i += nrCharacters;
            }
            else {
                i++;
                size++;
            }
        }
        return size;
    }

    long long part_2(std::string_view path) {
        std::string input = file::readFileAsString(path);

        return processString(input, 0, input.size());
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2016_day09::part_1("../2016/day09/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2016_day09::part_2("../2016/day09/input.in") << std::endl;

    return 0;
}
#endif
