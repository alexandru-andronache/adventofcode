#include "file.h"
#include "utilities.h"
#include <iostream>
#include <map>
#include <stack>
#include <set>

namespace aoc2018_day07 {
    int getNextLetter(const std::vector<std::vector<char>>& input,
                      const std::vector<bool>& possibleSolutions,
                      const std::vector<bool>& startedTasks) {
        for (int i = 0; i < input.size(); ++i) {
            bool isSol = true;
            for (const auto& l : input[i]) {
                if (possibleSolutions[l - 'A'])
                    isSol = false;
            }
            if (isSol && possibleSolutions[i] && !startedTasks[i]) {
                return i;
            }
        }
        return -1;
    }

    bool shouldContinue(int seconds, const std::vector<std::pair<int, int>>& workers) {
        if (seconds == -1) {
            return true;
        }
        for (const auto& w : workers) {
            if (w.first != -1) {
                return true;
            }
        }
        return false;
    }

    std::string part_1(std::string_view path) {
        std::vector<std::vector<char>> input(26, std::vector<char>());
        std::vector<std::vector<std::string>> lines = file::readFileAndSplit(path, " ");
        for (const auto& line : lines) {
            input[line[7][0] - 'A'].push_back(line[1][0]);
        }

        std::string sol = "";
        std::vector<bool> possibleSolutions(26, false);
        std::vector<bool> startedTasks(26, false);
        for (int i = 0; i < input.size(); ++i) {
            for (const auto& l : input[i]) {
                possibleSolutions[l - 'A'] = true;
            }
            if (!input[i].empty()) {
                possibleSolutions[i] = true;
            }
        }
        int letter = getNextLetter(input, possibleSolutions, startedTasks);
        while (letter != -1) {
            if (letter != -1) {
                possibleSolutions[letter] = false;
                sol += letter + 'A';
            }
            letter = getNextLetter(input, possibleSolutions, startedTasks);
        }
        return sol;
    }

    int part_2(std::string_view path, int nrWorkers = 2, int extraSeconds = 0) {
        std::vector<std::vector<char>> input(26, std::vector<char>());
        std::vector<std::vector<std::string>> lines = file::readFileAndSplit(path, " ");
        for (const auto& line : lines) {
            input[line[7][0] - 'A'].push_back(line[1][0]);
        }

        std::string sol = "";
        std::vector<bool> possibleSolutions(26, false);
        std::vector<bool> startedTasks(26, false);
        for (int i = 0; i < input.size(); ++i) {
            for (const auto& l : input[i]) {
                possibleSolutions[l - 'A'] = true;
            }
            if (!input[i].empty()) {
                possibleSolutions[i] = true;
            }
        }
        std::vector<std::pair<int, int>> workers(nrWorkers, {-1, 0});
        int seconds = -1;
        while (shouldContinue(seconds, workers)) {
            for (int i = 0; i < nrWorkers; ++i) {
                if (workers[i].first != -1 && workers[i].first + workers[i].second + extraSeconds == seconds) {
                    possibleSolutions[workers[i].first] = false;
                    startedTasks[workers[i].first] = false;
                    workers[i].first = -1;
                    workers[i].second = 0;
                }
            }
            seconds++;
            for (int i = 0; i < nrWorkers; ++i) {
                int l = getNextLetter(input, possibleSolutions, startedTasks);
                if (workers[i].first == -1 && l != -1) {
                    startedTasks[l] = true;
                    workers[i].first = l;
                    workers[i].second = seconds;
                }
            }
        }
        return seconds;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2018_day07::part_1("../2018/day07/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2018_day07::part_2("../2018/day07/input.in", 5, 60) << std::endl;

    return 0;
}
#endif
