#include "file.h"
#include <iostream>

namespace aoc2017_day15 {
    int part_1(unsigned long long A, unsigned long long B) {
        constexpr unsigned long long GEN_A = 16807;
        constexpr unsigned long long GEN_B = 48271;
        constexpr unsigned long long MODULO = 2147483647;
        constexpr int ROUNDS = 40000000;
        int sol = 0;

        for (int i = 0; i < ROUNDS; ++i) {
            A = (A * GEN_A) % MODULO;
            B = (B * GEN_B) % MODULO;

            if (A % (1 << 16) == B % (1 << 16)) {
                sol++;
            }
        }
        return sol;
    }

    int part_2(unsigned long long A, unsigned long long B) {
        constexpr unsigned long long GEN_A = 16807;
        constexpr unsigned long long GEN_B = 48271;
        constexpr unsigned long long MODULO = 2147483647;
        constexpr int ROUNDS = 5000000;
        int sol = 0;

        for (int i = 0; i < ROUNDS; ++i) {
            A = (A * GEN_A) % MODULO;
            while (A % 4 != 0) {
                A = (A * GEN_A) % MODULO;
            }
            B = (B * GEN_B) % MODULO;
            while (B % 8 != 0) {
                B = (B * GEN_B) % MODULO;
            }

            if (A % (1 << 16) == B % (1 << 16)) {
                sol++;
            }
        }
        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2017_day15::part_1(722, 354) << std::endl;
    std::cout << "Part 1: " << aoc2017_day15::part_2(722, 354) << std::endl;

    return 0;
}
#endif
