#include "file.h"
#include "utilities.h"
#include <iostream>
#include <forward_list>

namespace aoc2017_day17 {
    int part_1(int forward_value) {
        constexpr int LAST_VALUE = 2017;
        std::forward_list<int> l;
        l.push_front(0);
        auto it = l.begin();
        for (int k = 1; k <= LAST_VALUE; ++k) {
            for (int i = 0; i < forward_value; ++i) {
                it++;
                if (it == l.end()) {
                    it = l.begin();
                }
            }
            l.insert_after(it, k);
            it++;
        }
        it++;
        return *it;
    }

    int part_2(int forward_value) {
        constexpr int LAST_VALUE = 50000000;
        int valuesAfter0 = 1; // numbers of numbers after 0
        int valueAfter0 = 1; // the next number after 0
        int currentValue = 1; // current value in relationship with 0

        for (int i = 2; i <= LAST_VALUE; ++i) {
            currentValue = (currentValue + forward_value) % (valuesAfter0 + 1);
            if (currentValue == 0) {
                valueAfter0 = i;
            }
            currentValue++;
            valuesAfter0++;
        }

        return valueAfter0;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2017_day17::part_1(343) << std::endl;
    std::cout << "Part 2: " << aoc2017_day17::part_2(343) << std::endl;

    return 0;
}
#endif
