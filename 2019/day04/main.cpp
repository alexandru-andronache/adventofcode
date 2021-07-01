#include "file.h"
#include <iostream>

namespace aoc2019_day04 {
    bool isAdjacent(int nr) {
        int prev = nr % 10;
        nr = nr / 10;
        while (nr > 0) {
            if (prev == nr % 10) return true;
            prev = nr % 10;
            nr = nr / 10;
        }
        return false;
    }

    bool neverDecrease(int nr) {
        int prev = nr % 10;
        nr = nr / 10;
        while (nr > 0) {
            if (prev < nr % 10) return false;
            prev = nr % 10;
            nr = nr / 10;
        }
        return true;
    }

    bool isAdjacentNoMoreThen2(int nr) {
        int prev = nr % 10;
        nr = nr / 10;
        int k = 1;
        while (nr > 0) {
            if (prev == nr % 10) {
                k++;
            }
            else {
                if (k == 2) {
                    return true;
                }
                else {
                    k = 1;
                }
            }

            prev = nr % 10;
            nr = nr / 10;
        }
        if (k == 2) return true;
        return false;
    }

    bool isValidPart1(int nr) {
        return isAdjacent(nr) & neverDecrease(nr);
    }

    bool isValidPart2(int nr) {
        return isAdjacentNoMoreThen2(nr) & neverDecrease(nr);
    }

    int part_1(int n = 109165, int m = 576723) {
        int sol = 0;
        for (int i = n; i <= m; ++i) {
            if (isValidPart1(i)) sol++;
        }
        return sol;
    }

    int part_2(int n = 109165, int m = 576723) {
        int sol = 0;
        for (int i = n; i <= m; ++i) {
            if (isValidPart2(i)) sol++;
        }
        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2019_day04::part_1() << std::endl;
    std::cout << "Part 2: " << aoc2019_day04::part_2() << std::endl;

    return 0;
}
#endif
