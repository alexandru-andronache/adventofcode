#include "file.h"
#include "utilities.h"
#include <iostream>
#include <deque>
#include <map>
#include <algorithm>

namespace aoc2020_day22 {
    int calculateScore(const std::deque<int> &player) {
        int sol = 0;
        for (int i = 0; i < player.size(); ++i) {
            sol += (player.size() - i) * player[i];
        }
        return sol;
    }

    std::pair<int, int> playRound(std::deque<int> player1, std::deque<int> player2) {
        std::map<std::deque<int>, std::vector<std::deque<int>>> prevState;

        bool isSol = false;
        while (!isSol) {
            if (player1.empty() || player2.empty()) {
                isSol = true;
            }
            std::vector<std::deque<int>> states = prevState[player1];
            if (std::find(states.begin(), states.end(), player2) != states.end()) {
                isSol = true;
            }
            if (!isSol) {
                prevState[player1].push_back(player2);
                int x = player1.front();
                player1.pop_front();
                int y = player2.front();
                player2.pop_front();
                auto result = 1;
                if (player1.size() >= x && player2.size() >= y) {
                    int max1 = *std::max_element(player1.begin(), player1.begin() + x);
                    int max2 = *std::max_element(player2.begin(), player2.begin() + y);
                    if (max1 > max2) {
                        result = 1;
                    } else {
                        result = playRound({player1.begin(), player1.begin() + x},
                                           {player2.begin(), player2.begin() + y}).first;
                    }
                } else {
                    if (x < y) {
                        result = 2;
                    }
                }
                if (result == 1) {
                    player1.emplace_back(x);
                    player1.emplace_back(y);
                } else {
                    player2.emplace_back(y);
                    player2.emplace_back(x);
                }

            }
        }
        if (player1.empty() && !player2.empty()) {
            return {2, calculateScore(player2)};
        }
        return {1, calculateScore(player1)};
    }

    int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<int> player1;
        std::vector<int> player2;
        int index = 1;
        while (!input[index].empty()) {
            player1.push_back(std::stoi(input[index]));
            index++;
        }
        index += 2;
        while (index < input.size()) {
            player2.push_back(std::stoi(input[index]));
            index++;
        }
        std::deque<int> p1(player1.size());
        std::deque<int> p2(player2.size());
        std::copy(player1.begin(), player1.end(), p1.begin());
        std::copy(player2.begin(), player2.end(), p2.begin());

        while (!p1.empty() && !p2.empty()) {
            int x = p1.front();
            p1.pop_front();
            int y = p2.front();
            p2.pop_front();

            if (x < y) {
                p2.emplace_back(y);
                p2.emplace_back(x);
            } else {
                p1.emplace_back(x);
                p1.emplace_back(y);
            }
        }

        return calculateScore(p1) + calculateScore(p2);
    }

    int part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<int> player1;
        std::vector<int> player2;
        int index = 1;
        while (!input[index].empty()) {
            player1.push_back(std::stoi(input[index]));
            index++;
        }
        index += 2;
        while (index < input.size()) {
            player2.push_back(std::stoi(input[index]));
            index++;
        }
        std::deque<int> p1(player1.size());
        std::deque<int> p2(player2.size());
        std::copy(player1.begin(), player1.end(), p1.begin());
        std::copy(player2.begin(), player2.end(), p2.begin());

        return playRound(p1, p2).second;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2020_day22::part_1("../2020/day22/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2020_day22::part_2("../2020/day22/input.in") << std::endl;

    return 0;
}
#endif
