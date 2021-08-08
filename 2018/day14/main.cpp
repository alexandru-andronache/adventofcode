#include "file.h"
#include "utilities.h"
#include <iostream>
#include <numeric>
#include <map>
#include <deque>

namespace aoc2018_day14 {
    std::string part_1(int n) {
        std::deque<int> recipes{3, 7};
        int elf1 = 0, elf2 = 1;
        while (n + 10 > recipes.size()) {
            int p = recipes[elf1] + recipes[elf2];
            if (p < 10) {
                recipes.push_back(p);
            }
            else {
                recipes.push_back(p / 10);
                recipes.push_back(p % 10);
            }
            elf1 = (elf1 + 1 + recipes[elf1]) % recipes.size();
            elf2 = (elf2 + 1 + recipes[elf2]) % recipes.size();
        }
        std::string sol;
        for (int i = n; i < n + 10; ++i) {
            sol.append(std::to_string(recipes[i]));
        }
        return sol;
    }

    int part_2(int n) {
        std::string N = std::to_string(n);
        std::deque<int> recipes{3, 7};
        int elf1 = 0, elf2 = 1;
        while (true) {
            int p = recipes[elf1] + recipes[elf2];
            std::vector<int> v;
            if (p < 10) {
                v.push_back(p);
            }
            else {
                v.push_back(p / 10);
                v.push_back(p % 10);
            }

            for (const auto& x : v) {
                recipes.push_back(x);
                std::string sol;
                for (int j = recipes.size() - N.size(); j < recipes.size(); ++j) {
                    sol.append(std::to_string(recipes[j]));
                }
                if (sol.compare(N) == 0) {
                    return recipes.size() - N.size();
                }

            }
            elf1 = (elf1 + 1 + recipes[elf1]) % recipes.size();
            elf2 = (elf2 + 1 + recipes[elf2]) % recipes.size();
        }
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2018_day14::part_1(637061) << std::endl;
    std::cout << "Part 1: " << aoc2018_day14::part_2(637061) << std::endl;

    return 0;
}
#endif
