#include "file.h"
#include "utilities.h"
#include <iostream>
#include <map>
#include <stack>
#include <set>
#include <algorithm>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2023_day07 {
    struct hand {
        hand(std::string c, int b, int t) {
            cards = std::move(c);
            bid = b;
            type = t;
        }
        std::string cards;
        int bid;
        int type;
    };

    int type(std::string_view hand, bool withJokers) {
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
            if (!occurance.empty()) {
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

    int compare(const hand& hand1, const hand& hand2, bool withJokers) {
        if (hand1.type != hand2.type) {
            return hand1.type < hand2.type;
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

        for (int i = 0; i < hand1.cards.size(); ++i) {
            if (hand1.cards[i] != hand2.cards[i]) {
                return p[hand1.cards[i]] < p[hand2.cards[i]];
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
            hands.emplace_back(t[0], std::stoi(t[1]), type(t[0], withJokers));
        }

        std::sort(hands.begin(), hands.end(), [withJokers](const auto& a, const auto& b) {
            return compare(a, b , withJokers);
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

#ifdef TESTING
TEST(Tests2023Day07, part_1_test) {
    ASSERT_EQ(aoc2023_day07::part_1("../2023/day07/input_test.in"), 6440);
}

TEST(Tests2023Day07, part_1_real_test) {
    ASSERT_EQ(aoc2023_day07::part_1("../2023/day07/input.in"), 246163188);
}

TEST(Tests2023Day07, part_2_test) {
    ASSERT_EQ(aoc2023_day07::part_2("../2023/day07/input_test.in"), 5905);
}

TEST(Tests2023Day07, part_2_real_test) {
    ASSERT_EQ(aoc2023_day07::part_2("../2023/day07/input.in"), 245794069);
}
#endif

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2023_day07::part_1("../2023/day07/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2023_day07::part_2("../2023/day07/input.in") << std::endl;

    return 0;
}
#endif
