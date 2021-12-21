#include "file.h"
#include "utilities.h"
#include <iostream>
#include <map>

namespace aoc2021_day21 {
    unsigned long long part_1(int startPos1, int startPos2) {
        int score1 = 0, score2 = 0, dice = 0, rolls = 0;
        while (score1 < 1000 && score2 < 1000) {
            for (int i = 1; i <= 3; ++i) {
                dice++;
                if (dice > 100) {
                    dice = 1;
                }
                startPos1 += dice;
            }
            rolls += 3;
            while (startPos1 > 10) {
                startPos1 -= 10;
            }
            score1 += startPos1;
            if (score1 < 1000) {
                for (int i = 1; i <= 3; ++i) {
                    dice++;
                    if (dice > 100) {
                        dice = 1;
                    }
                    startPos2 += dice;
                }
                rolls += 3;
                while (startPos2 > 10) {
                    startPos2 -= 10;
                }
                score2 += startPos2;
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

    FILE *f = fopen("output.txt", "w");

    std::pair<unsigned long long, unsigned long long> step2(const int startPos1, const int startPos2, const int score1, const int score2, const int activePlayer) {
        if (prevScores.find({startPos1, startPos2, score1, score2, activePlayer}) != prevScores.end()) {
            return prevScores[{startPos1, startPos2, score1, score2, activePlayer}];
        }

        unsigned long long winP1 = 0;
        unsigned long long winP2 = 0;
//        int pp1 = startPos1;
//        int pp2 = startPos2;
//        int ps1 = score1;
//        int ps2 = score2;
//        int activePlayerT = activePlayer;
        for (int dice1 = 1; dice1 <= 3; ++dice1) {
            for (int dice2 = 1; dice2 <= 3; ++dice2) {
                for (int dice3 = 1; dice3 <= 3; ++dice3) {
                    if (activePlayer == 1) {
                        int newStartPos1 = startPos1 + dice1 + dice2 + dice3;
                        while (newStartPos1 > 10) {
                            newStartPos1 -= 10;
                        }
                        int newScore1 = score1 + newStartPos1;
                        if (newScore1 >= 21) {
                            winP1++;
                        }
                        else {
                            if (prevScores.find({newStartPos1, startPos2, newScore1, score2, 2}) == prevScores.end()) {
                                auto r = step2(newStartPos1, startPos2, newScore1, score2, 2);
                                prevScores.insert({{newStartPos1, startPos2, newScore1, score2, 2}, r});
                            }
                            auto result = prevScores[{newStartPos1, startPos2, newScore1, score2, 2}];
                            winP1 += result.first;
                            winP2 += result.second;
                        }
                    }
                    else {
                        int newStartPos2 = startPos2 + dice1 + dice2 + dice3;
                        while (newStartPos2 > 10) {
                            newStartPos2 -= 10;
                        }
                        int newScore2 = score2 + newStartPos2;
                        if (newScore2 >= 21) {
                            winP2++;
                        }
                        else {
                            if (prevScores.find({startPos1, newStartPos2, score1, newScore2, 1}) == prevScores.end()) {
                                auto r = step2(startPos1, newStartPos2, score1, newScore2, 1);
                                prevScores.insert({{startPos1, newStartPos2, score1, newScore2, 1}, r});
                            }
                            auto result = prevScores[{startPos1, newStartPos2, score1, newScore2, 1}];
                            winP1 += result.first;
                            winP2 += result.second;
                        }
                    }
                }
            }
        }
        return {winP1, winP2};
    }

    unsigned long long part_2(int startPos1, int startPos2) {
        prevScores.clear();
        auto result = step2(startPos1, startPos2, 0, 0, 1);
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
