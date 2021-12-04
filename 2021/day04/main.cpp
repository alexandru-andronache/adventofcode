#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>

namespace aoc2021_day04 {

    int calculateScore(const std::vector<std::vector<std::vector<int>>>& cards,
                       const std::vector<std::vector<std::vector<bool>>>& mark,
                       int index,
                       int lastNumber) {
        int sum = 0;
        for (int i = 0; i < cards[0].size(); ++i) {
            for (int j = 0; j < cards[0][0].size(); ++j) {
                if (!mark[index][i][j]) {
                    sum += cards[index][i][j];
                }
            }
        }
        return sum * lastNumber;
    }

    int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<int> bingo = utils::splitStringToInt(input[0], ", ");
        std::vector<std::vector<std::vector<int>>> cards;

        for (int i = 2; i < input.size(); i += 6) {
            std::vector<std::vector<int>> card;
            for (int j = i; j < i + 5; ++j) {
                std::vector<int> line = utils::splitStringToInt(input[j], " ");
                card.push_back(line);
            }
            cards.push_back(card);
        }

        std::vector<std::vector<std::vector<bool>>> mark(cards.size(), std::vector<std::vector<bool>>(cards[0].size(), std::vector<bool>(cards[0][0].size(), false)));

        int index = 0;
        while (true) {
            for (int i = 0; i < cards.size(); ++i) {
                for (int j = 0; j < cards[0].size(); ++j) {
                    for (int k = 0; k < cards[0][0].size(); ++k) {
                        if (cards[i][j][k] == bingo[index]) {
                            mark[i][j][k] = true;
                        }
                    }
                }
            }

            for (int i = 0; i < cards.size(); ++i) {
                for (int j = 0; j < cards[0].size(); ++j) {
                    bool finished = true;
                    for (int k = 0; k < cards[0][0].size(); ++k) {
                        if (!mark[i][j][k]) {
                            finished = false;
                        }
                    }
                    if (finished) {
                        return calculateScore(cards, mark, i, bingo[index]);
                    }
                }
                for (int k = 0; k < cards[0][0].size(); ++k) {
                    bool finished = true;
                    for (int j = 0; j < cards[0].size(); ++j) {
                        if (!mark[i][j][k]) {
                            finished = false;
                        }
                    }
                    if (finished) {
                        return calculateScore(cards, mark, i, bingo[index]);
                    }
                }
            }
            index++;
        }

        return 0;
    }

    int part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<int> bingo = utils::splitStringToInt(input[0], ", ");
        std::vector<std::vector<std::vector<int>>> cards;

        for (int i = 2; i < input.size(); i += 6) {
            std::vector<std::vector<int>> card;
            for (int j = i; j < i + 5; ++j) {
                std::vector<int> line = utils::splitStringToInt(input[j], " ");
                card.push_back(line);
            }
            cards.push_back(card);
        }

        std::vector<std::vector<std::vector<bool>>> mark(cards.size(), std::vector<std::vector<bool>>(cards[0].size(), std::vector<bool>(cards[0][0].size(), false)));
        std::vector<bool> cardsCompleted(cards.size(), false);

        int index = 0;
        while (true) {
            for (int i = 0; i < cards.size(); ++i) {
                for (int j = 0; j < cards[0].size(); ++j) {
                    for (int k = 0; k < cards[0][0].size(); ++k) {
                        if (cards[i][j][k] == bingo[index]) {
                            mark[i][j][k] = true;
                        }
                    }
                }
            }

            for (int i = 0; i < cards.size(); ++i) {
                for (int j = 0; j < cards[0].size(); ++j) {
                    bool finished = true;
                    for (int k = 0; k < cards[0][0].size(); ++k) {
                        if (!mark[i][j][k]) {
                            finished = false;
                        }
                    }
                    if (finished) {
                        cardsCompleted[i] = true;
                        if (std::count(cardsCompleted.begin(), cardsCompleted.end(), false) == 0) {
                            return calculateScore(cards, mark, i, bingo[index]);
                        }
                    }
                }
                for (int k = 0; k < cards[0][0].size(); ++k) {
                    bool finished = true;
                    for (int j = 0; j < cards[0].size(); ++j) {
                        if (!mark[i][j][k]) {
                            finished = false;
                        }
                    }
                    if (finished) {
                        cardsCompleted[i] = true;
                        if (std::count(cardsCompleted.begin(), cardsCompleted.end(), false) == 0) {
                            return calculateScore(cards, mark, i, bingo[index]);
                        }
                    }
                }
            }
            index++;
        }

        return 0;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2021_day04::part_1("../2021/day04/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2021_day04::part_2("../2021/day04/input.in") << std::endl;

    return 0;
}
#endif
