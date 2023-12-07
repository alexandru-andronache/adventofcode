#include "file.h"
#include "utilities.h"
#include <iostream>
#include <map>
#include <stack>
#include <set>
#include <algorithm>

namespace aoc2023_day07 {
    struct hand {
        hand(std::string c, int b) {
            cards = std::move(c);
            bid = b;
        }
        std::string cards;
        int bid;
    };

    int type(std::string hand, bool withJokers) {
        std::map<char, int> t{{'2', 0}, {'3', 0}, {'4', 0}, {'5', 0}, {'6', 0}, {'7', 0},
                              {'8', 0}, {'9', 0}, {'T', 0}, {'Q', 0}, {'K', 0}, {'A', 0}};
        if (!withJokers){
            t.insert({'J', 0});
        }
        int jokers = 0;
        for (const auto& c : hand) {
            if (!withJokers || c != 'J') {
                t[c]++;
            }
            if (c == 'J') jokers++;
        }
        std::vector<int> occurance;
        for (const auto& c : t) {
            if (c.second != 0) {
                occurance.push_back(c.second);
            }
        }
        std::sort(occurance.begin(), occurance.end(), [](const auto& a, const auto& b) {
            return a > b;
        });
        if (withJokers) {
            if (occurance.size() > 0) {
                occurance[0] += jokers;
            }
            else {
                occurance.push_back(jokers);
            }
        }

        if (occurance[0] == 5) return 7;
        if (occurance[0] == 4) return 6;
        if (occurance.size() >= 2 && occurance[0] == 3 && occurance[1] == 2) return 5;
        if (occurance[0] == 3) return 4;
        if (occurance.size() >= 2 && occurance[0] == 2 && occurance[1] == 2) return 3;
        if (occurance[0] == 2) return 2;
        return 1;
    }

    int compare(std::string card1, std::string card2, bool withJokers) {
        int t1 = type(card1, withJokers);
        int t2 = type(card2, withJokers);
        if (t1 != t2) {
            return t1 < t2;
        }
        std::map<char, int> p{{'2', 1}, {'3', 2}, {'4', 3},
                              {'5', 4}, {'6', 5}, {'7', 6},
                              {'8', 7}, {'9', 8}, {'T', 9},
                              {'Q',  11}, {'K', 12},
                              {'A', 13}};;
        if (!withJokers) {
            p.insert({'J', 10});
        }
        else {
            p.insert({'J', 0});
        }

        for (int i = 0; i < card1.size(); ++i) {
            if (card1[i] != card2[i]) {
                return p[card1[i]] < p[card2[i]];
            }
        }

        return false;
    }
    unsigned long long solve (std::string_view path, bool withJokers) {
        std::vector<std::string> input = file::readFileAsArrayString(path);

        unsigned long long sol = 0;
        std::vector<hand> hands;
        for (const auto& line : input) {
            std::vector<std::string> t = utils::splitString(line, " ");
            hands.emplace_back(t[0], std::stoi(t[1]));
        }

        std::sort(hands.begin(), hands.end(), [withJokers](const auto& a, const auto& b) {
            return compare(a.cards, b.cards, withJokers);
        });

        for (int i = 0; i < hands.size(); ++i) {
            sol += (i + 1) * hands[i].bid;
        }

        return sol;
    }


    unsigned long long part_1(std::string_view path) {
        return solve(path, false);
    }

    unsigned long long part_2(std::string_view path) {
        return solve(path, true);
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2023_day07::part_1("../2023/day07/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2023_day07::part_2("../2023/day07/input.in") << std::endl;

    return 0;
}
#endif
