#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>

namespace aoc2017_day13 {
    struct State {
        int max;
        int current;
        int direction;
    };

    int solve(std::vector<State> state) {
        int sol = 0;
        for (int i = 0; i < state.size(); ++i) {
            if (state[i].current == 0) {
                sol += i * state[i].max;
            }
            for (auto& s : state) {
                s.current += s.direction;
                if (s.current < 0) {
                    s.current = 1;
                    s.direction = 1;
                }
                else if (s.current >= s.max) {
                    s.current = s.max - 2;
                    s.direction = -1;
                }
            }
        }
        return sol;
    }

    int part_1(std::string_view path) {
        std::vector<std::pair<int, int>> input;
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        for (const auto& line : lines) {
            std::vector<int> tokens = utils::splitStringToInt(line, " :");
            input.emplace_back(tokens[0], tokens[1]);
        }

        std::vector<State> state;
        int lastState = 0;
        for (const auto& line : input) {
            for (int i = lastState; i < line.first; ++i) {
                state.push_back({0, 0, 1});
            }
            state.push_back({line.second, 0, 1});
            lastState = line.first + 1;
        }

        return solve(state);
    }

    int part_2(std::string_view path) {
        std::vector<std::pair<int, int>> input;
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        for (const auto& line : lines) {
            std::vector<int> tokens = utils::splitStringToInt(line, " :");
            input.emplace_back(tokens[0], tokens[1]);
        }

        std::vector<State> state;
        int lastState = 0;
        for (const auto& line : input) {
            for (int i = lastState; i < line.first; ++i) {
                state.push_back({0, 0, 1});
            }
            state.push_back({line.second, 0, 1});
            lastState = line.first + 1;
        }

        int m = 1;
        while (true) {
            bool found = true;
            for (int i = 0; i < state.size(); ++i) {
                if ((state[i].max > 0) && ((m + i + state[i].current) % (2 * (state[i].max - 1)) == 0)) {
                    found = false;
                    i = state.size();
                }
            }

            if (found) {
                return m;
            }
            m++;
        }
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2017_day13::part_1("../2017/day13/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2017_day13::part_2("../2017/day13/input.in") << std::endl;

    return 0;
}
#endif
