#include "file.h"
#include "utilities.h"
#include <iostream>
#include <map>

namespace aoc2021_day21 {

    void advanceDice(int& position, int& score, int& dice, int& rolls) {
        for (int i = 1; i <= 3; ++i) {
            dice++;
            if (dice > 100) {
                dice = 1;
            }
            position += dice;
        }
        rolls += 3;
        position = position % 10;
        if (position == 0) {
            position = 10;
        }
        score += position;
    }

    unsigned long long part_1(int startPos1, int startPos2) {
        int score1 = 0, score2 = 0, dice = 0, rolls = 0;
        while (score1 < 1000 && score2 < 1000) {
            advanceDice(startPos1, score1, dice, rolls);
            if (score1 < 1000) {
                advanceDice(startPos2, score2, dice, rolls);
            }
        }

        return std::min(score1, score2) * rolls;
    }

    struct State {
        int pos1;
        int pos2;
        int s1;
        int s2;
        int activePlayer;
    };
    auto comparator = [](const State& c1, const State& c2) -> bool
    {
        return std::tie(c1.pos1, c1.pos2, c1.s1, c1.s2, c1.activePlayer) <
               std::tie(c2.pos1, c2.pos2, c2.s1, c2.s2, c2.activePlayer);
    };

    std::map<State, std::pair<unsigned long long, unsigned long long>, decltype(comparator)> prevScores(comparator);

    std::vector<int> weight{0, 0, 0, 1, 3, 6, 7, 6, 3, 1};

    std::pair<unsigned long long, unsigned long long> solve_part_2(const int startPos1, const int startPos2, const int score1, const int score2, const int activePlayer) {
        unsigned long long winP1 = 0;
        unsigned long long winP2 = 0;

        for (int sumDice = 3; sumDice <= 9; ++sumDice) {
            if (activePlayer == 1) {
                int newStartPos1 = startPos1 + sumDice;
                while (newStartPos1 > 10) {
                    newStartPos1 -= 10;
                }
                int newScore1 = score1 + newStartPos1;
                if (newScore1 >= 21) {
                    winP1 += weight[sumDice];
                }
                else {
                    if (prevScores.find({newStartPos1, startPos2, newScore1, score2, 2}) == prevScores.end()) {
                        auto r = solve_part_2(newStartPos1, startPos2, newScore1, score2, 2);
                        prevScores.insert({{newStartPos1, startPos2, newScore1, score2, 2}, r});
                    }
                    auto result = prevScores[{newStartPos1, startPos2, newScore1, score2, 2}];
                    winP1 += result.first * weight[sumDice];
                    winP2 += result.second * weight[sumDice];
                }
            }
            else {
                int newStartPos2 = startPos2 + sumDice;
                while (newStartPos2 > 10) {
                    newStartPos2 -= 10;
                }
                int newScore2 = score2 + newStartPos2;
                if (newScore2 >= 21) {
                    winP2 += weight[sumDice];
                }
                else {
                    if (prevScores.find({startPos1, newStartPos2, score1, newScore2, 1}) == prevScores.end()) {
                        auto r = solve_part_2(startPos1, newStartPos2, score1, newScore2, 1);
                        prevScores.insert({{startPos1, newStartPos2, score1, newScore2, 1}, r});
                    }
                    auto result = prevScores[{startPos1, newStartPos2, score1, newScore2, 1}];
                    winP1 += result.first * weight[sumDice];
                    winP2 += result.second * weight[sumDice];
                }
            }
        }

        return {winP1, winP2};
    }

    unsigned long long part_2(int startPos1, int startPos2) {
        prevScores.clear();
        auto result = solve_part_2(startPos1, startPos2, 0, 0, 1);
        return std::max(result.first, result.second);
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2021_day21::part_1("../2021/day21/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2021_day21::part_2("../2021/day21/input.in") << std::endl;

    return 0;
}
#endif

#pragma clang diagnostic pop