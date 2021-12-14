#include "file.h"
#include "utilities.h"
#include <iostream>
#include <map>
#include <vector>


namespace aoc2021_day14 {
    unsigned long long solve(std::string_view path, int steps) {
        std::vector<std::string> input = file::readFileAsArrayString(path);

        std::map<std::string, std::vector<std::string>> rules;
        for (int i = 2; i < input.size(); ++i) {
            std::vector<std::string> tokens = utils::splitString(input[i], " ->");
            rules[tokens[0]] = {std::string() + tokens[0][0] + tokens[1][0], std::string() + tokens[1][0] + tokens[0][1]};
        }

        std::map<std::string, unsigned long long> state;
        for (int i = 1; i < input[0].size(); ++i) {
            if (state.find(std::string() + input[0][i - 1] + input[0][i]) == state.end()) {
                state[std::string() + input[0][i - 1] + input[0][i]] = 1;
            }
            else {
                state[std::string() + input[0][i - 1] + input[0][i]]++;
            }
        }

        for (int step = 0; step < steps; ++step) {
            std::map<std::string, unsigned long long> newState;
            for (const auto& c : state) {
                auto r = rules[c.first];
                for (int i = 0; i < 2; ++i) {
                    if (newState.find(r[i]) == newState.end()) {
                        newState[r[i]] = c.second;
                    } else {
                        newState[r[i]] += c.second;
                    }
                }
            }
            state = newState;
        }

        std::vector<unsigned long long> letters(26, 0);
        for (const auto& s : state) {
            letters[s.first[0] - 'A'] += s.second;
        }
        letters[input[0].back() - 'A']++;
        std::sort(letters.begin(), letters.end());
        unsigned long long min = 0;
        for (const auto& l : letters) {
            if (l > 0 && min == 0) {
                min = l;
            }
        }

        return letters.back() - min;
    }

    unsigned long long part_1(std::string_view path) {
        return solve(path, 10);
    }

    unsigned long long part_2(std::string_view path) {
        return solve(path, 40);
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2021_day14::part_1("../2021/day14/input.in") << std::endl;
    std::cout << "Part 1: " << aoc2021_day14::part_2("../2021/day14/input.in") << std::endl;

    return 0;
}
#endif
