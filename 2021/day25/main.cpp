#include "file.h"
#include "utilities.h"
#include <iostream>
#include <map>

namespace aoc2021_day25 {
    int part_1(std::string_view path) {
        enum State{
            EMPTY = 0,
            LEFT = 1,
            DOWN = 2
        };
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        const int N = lines.size();
        const int M = lines[0].size();
        std::map<char, State> mapping {{'.', State::EMPTY}, {'>', State::LEFT}, {'v', State::DOWN}};

        std::vector<std::vector<State>> map(N, std::vector<State>(M, State::EMPTY));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                map[i][j] = mapping[lines[i][j]];
            }
        }

        int steps = 0;
        bool changed = true;

        while (changed) {
            changed = false;
            std::vector<std::vector<State>> newMap(N, std::vector<State>(M, State::EMPTY));
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    if (map[i][j] == State::LEFT && map[i][(j + 1) % M] == State::EMPTY && newMap[i][(j + 1) % M] == State::EMPTY) {
                        newMap[i][(j + 1) % M] = State::LEFT;
                        newMap[i][j] = State::EMPTY;
                        changed = true;
                    }
                    else if (newMap[i][j] == State::EMPTY) {
                        newMap[i][j] = map[i][j];
                    }
                }
            }
            map = newMap;
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    if (map[i][j] == State::DOWN && map[(i + 1) % N][j] == State::EMPTY && newMap[(i + 1) % N][j] == State::EMPTY)
                    {
                        newMap[(i + 1) % N][j] = State::DOWN;
                        newMap[i][j] = State::EMPTY;
                        changed = true;
                    }
                    else if (newMap[i][j] == State::EMPTY) {
                        newMap[i][j] = map[i][j];
                    }
                }
            }
            map = newMap;
            steps++;
        }

        return steps;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2021_day25::part_1("../2021/day25/input.in") << std::endl;
    return 0;
}
#endif
