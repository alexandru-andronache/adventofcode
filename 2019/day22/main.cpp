#include "file.h"
#include "utilities.h"
#include "math_util.h"
#include <iostream>
#include <numeric>

namespace aoc2019_day22 {
    unsigned int part_1(std::string_view path, int size = 10007, int card = 2019) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        __int128_t A = 1;
        __int128_t B = 0;
        for (const auto& line : lines) {
            std::vector<std::string> words = utils::splitString(line, " ");
            if (line == "deal into new stack") {
                A = math::mod(-A, size);
                B = math::mod(size - 1 - B, size);
            }
            else if (words[0] == "cut") {
                B = math::mod(B - std::stoi(words[1]), size);
            }
            else {
                A = math::mod(A * std::stoi(words[3]), size);
                B = math::mod(B * std::stoi(words[3]), size);
            }
        }

        return math::mod(A * card + B, size);
    }

    long long part_2(std::string_view path, long long position = 2020, long long size = 119315717514047, long long rounds = 101741582076661) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);

        __int128 A = 1;
        __int128 B = 0;

        std::reverse(lines.begin(), lines.end());

        for (const auto& line : lines) {
            std::vector<std::string> words = utils::splitString(line, " ");

            if (line == "deal into new stack") {
                B = math::mod(size - 1 - B, size);
                A = math::mod(-A, size);
            }
            else if (words[0] == "cut") {
                B = math::mod(B + std::stoi(words[1]), size);
            }
            else {
                B = math::mod(B * math::modularInverse(std::stoll(words[3]), size), size);
                A = math::mod(A * math::modularInverse(std::stoll(words[3]), size), size);
            }
        }

        __int128_t finalA = math::modular_power(A, rounds, size);
        __int128_t finalB = math::mod(B * math::modular_divide(finalA - 1, A - 1, size), size);

        return math::mod(finalA * position + finalB, size);
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2019_day22::part_1("../2019/day22/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2019_day22::part_2("../2019/day22/input.in") << std::endl;
//    std::cout << "Part 2: " << aoc2019_day22::part_2("../2019/day22/input.in", 6289, 10007, 1) << std::endl;
//    std::cout << "Part 2: " << aoc2019_day22::part_2("../2019/day22/input_test2.in", 8, 10, 1) << std::endl;
    return 0;
}
#endif
