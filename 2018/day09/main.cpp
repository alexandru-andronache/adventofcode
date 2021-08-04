#include "file.h"
#include <iostream>
#include <vector>
#include <list>

namespace aoc2018_day09 {
    long long solve(int players, int marble) {
        std::vector<long long> score(players + 1, 0);
        int player = 1;
        std::list<int> l;
        l.push_back(0);
        auto it = l.begin();
        for (int i = 1; i <= marble; ++i) {
            if (i % 23) {
                it++;
                if (it == l.end()) {
                    it = l.begin();
                    it++;
                } else {
                    it++;
                }
                l.insert(it, i);
                it--;
            }
            else {
                score[player] += i;
                for (int k = 0; k < 7; ++k) {
                    it--;
                    if (it == l.begin()) {
                        it = l.end();
                    }
                }
                score[player] += (*it);
                l.erase(it);
                it++;
            }
            player = (player % players) + 1;
        }
        long long max = 0;
        for (const auto& p : score) {
            max = std::max(p, max);
        }
        return max;
    }

    long long part_1(int players, int marble) {
        return solve(players, marble);
    }

    long long part_2(int players, int marble) {
        return solve(players, marble * 100);
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2018_day09::part_1(438, 71626) << std::endl;
    std::cout << "Part 2: " << aoc2018_day09::part_2(438, 71626) << std::endl;

    return 0;
}
#endif
