#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>
#include <list>

namespace aoc2016_day19 {
    int part_1(int elfs) {
        std::vector<int> gifts(elfs, 1);
        while (true) {
            for (int i = 0; i < elfs; ++i) {
                if (gifts[i] != 0) {
                    int j = (i + 1) % gifts.size();
                    while (gifts[j] == 0 || j == i) {
                        j = (j + 1) % gifts.size();
                    }
                    gifts[i] += gifts[j];
                    gifts[j] = 0;
                }
            }
            int sol = -1;
            bool isSol = true;
            for (int i = 0; i < elfs; ++i) {
                if (gifts[i] != 0) {
                    if (sol == -1) {
                        sol = i + 1;
                    }
                    else {
                        isSol = false;
                    }
                }
            }
            if (isSol) {
                return sol;
            }
        }
    }

    int part_2(int elfs) {
        std::list<int> gifts;
        for (int i = 0; i < elfs; ++i) {
            gifts.push_back(i);
        }
        auto it = gifts.begin();
        std::advance(it, gifts.size() / 2);
        while (gifts.size() > 1) {
            it = gifts.erase(it);
            if (it == gifts.end()) {
                it = gifts.begin();
            }
            if (gifts.size() % 2 == 0) {
                std::advance(it, 1);
                if (it == gifts.end()) {
                    it = gifts.begin();
                }
            }

        }
        return gifts.front() + 1;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2016_day19::part_1(3001330) << std::endl;
    std::cout << "Part 2: " << aoc2016_day19::part_2(3001330) << std::endl;

    return 0;
}
#endif
