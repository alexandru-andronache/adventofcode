#include "file.h"
#include "utilities.h"
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <cmath>

namespace aoc2022_day11 {
    typedef unsigned long long ULL;
    struct monkey {
        std::vector<ULL> items;
        std::function<ULL(ULL, ULL)> f;
        int mod;
        int divisible;
        int monkeyTrue;
        int monkeyFalse;
        ULL itemsInspected;
    };

    ULL mul(ULL x, ULL y) {
        return x * y;
    }

    ULL add(ULL x, ULL y) {
        return x + y;
    }

    ULL solve(std::vector<monkey> monkeys, int rounds, std::function<ULL(ULL)> modifier) {
        for (int r = 0; r < rounds; ++r) {
            for (auto& m : monkeys) {
                for (auto& item : m.items) {
                    m.itemsInspected++;
                    if (m.mod != -1) {
                        item = m.f(item, m.mod);
                    }
                    else {
                        item = m.f(item, item);
                    }
                    item = modifier(item);
                    if (item % m.divisible == 0) {
                        monkeys[m.monkeyTrue].items.push_back(item);
                    }
                    else {
                        monkeys[m.monkeyFalse].items.push_back(item);
                    }
                }
                m.items.clear();
            }
        }

        std::sort(monkeys.begin(), monkeys.end(), [](const auto& m1, const auto& m2) {
            return m1.itemsInspected > m2.itemsInspected;
        });

        return monkeys[0].itemsInspected * monkeys[1].itemsInspected;
    }

    ULL readData(std::string_view path, std::vector<monkey>& monkeys) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        ULL lcm = 1;

        for (int i = 0; i < input.size(); i = i + 7) {
            monkey m;
            {
                std::vector<std::string> t = utils::splitString(input[i + 1], " ,");
                for (int j = 2; j < t.size(); ++j) {
                    m.items.push_back(std::stoi(t[j]));
                }
            }
            {
                std::vector<std::string> t = utils::splitString(input[i + 2], " ,");
                if (t[4] == "*") {
                    m.f = mul;
                }
                else if (t[4] == "+") {
                    m.f = add;
                }
                if (t[5] == "old") {
                    m.mod = -1;
                }
                else {
                    m.mod = std::stoi(t[5]);
                }
            }
            {
                std::vector<std::string> t = utils::splitString(input[i + 3], " ,");
                m.divisible = std::stoi(t[3]);
            }
            {
                std::vector<std::string> t = utils::splitString(input[i + 4], " ,");
                m.monkeyTrue = std::stoi(t[5]);
            }
            {
                std::vector<std::string> t = utils::splitString(input[i + 5], " ,");
                m.monkeyFalse = std::stoi(t[5]);
            }
            m.itemsInspected = 0;
            monkeys.push_back(m);
            lcm *= m.divisible;
        }
        return lcm;
    }

    ULL part_1(std::string_view path) {
        std::vector<monkey> monkeys;
        readData(path, monkeys);

        return solve(monkeys, 20, [](ULL x) {
            return floor(x / 3);
        });
    }

    ULL part_2(std::string_view path) {
        std::vector<monkey> monkeys;
        ULL lcm = readData(path, monkeys);

        return solve(monkeys, 10000, [lcm](ULL x) {
            return x % lcm;
        });
    }
}
#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2022_day11::part_1("../2022/day11/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2022_day11::part_2("../2022/day11/input.in") << std::endl;

    return 0;
}
#endif
