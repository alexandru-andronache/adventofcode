#include "file.h"
#include "utilities.h"
#include <iostream>
#include <array>
#include <cmath>
#include <sstream>
#include <map>
#include <algorithm>

namespace aoc2021_day23 {

    int steps = 0;

    struct stateWithoutScore {
        std::array<char, 11> topLine{};
        std::array<std::array<char, 4>, 2> lines {};

        bool operator<(const stateWithoutScore &value) const {
            return std::tie(topLine, lines) < std::tie(value.topLine, value.lines);
        }
    };

    template<std::size_t N> 
    struct state {
        std::array<char, 11> topLine{};
        std::array<std::array<char, 4>, N> lines {};
        int score = 0;

        // void print() const
        // {
        //     std::cout << "#############\n";
        //     std::cout << "#";
        //     for (const auto &c : topLine)
        //     {
        //         if (c == 0) std::cout << ".";
        //         else std::cout << c;
        //     }
        //     std::cout << "#\n";
        //     std::cout << "###";
        //     for (const auto &c : lines[0])
        //     {
        //         if (c == 0) std::cout << ".";
        //         else std::cout << c;
        //         std::cout << "#";
        //     }
        //     std::cout << "##\n";
        //     std::cout << "  #";
        //     for (const auto &c : lines[1])
        //     {
        //         if (c == 0) std::cout << ".";
        //         else std::cout << c;
        //         std::cout << "#";
        //     }
        //     std::cout << "\n";
        //     std::cout << "  #########\n";
        //     std::cout << "Score: " << score << "\n";
        //     std::cout << "\n";
        //     std::cout << "\n";
        //     std::cout << "\n";
        // }

        // void print_file() const {
        //     FILE *f = fopen("../2021/day23/test.out", "a");
        //     fprintf(f, "#############\n");
        //     fprintf(f, "#");
        //     for (const auto& c : topLine) {
        //         if (c == 0)
        //             fprintf(f, ".");
        //         else
        //             fprintf(f, "%c", c);
        //     }
        //     fprintf(f, "#\n");
        //     fprintf(f, "###");
        //     for (const auto& c: lines[0]) {
        //         if (c == 0)
        //             fprintf(f, ".");
        //         else
        //             fprintf(f, "%c", c);
        //         fprintf(f, "#");
        //     }
        //     fprintf(f, "##\n");
        //     fprintf(f, "  #");
        //     for (const auto &c : lines[1]) {
        //         if (c == 0)
        //             fprintf(f, ".");
        //         else
        //             fprintf(f, "%c", c);
        //         fprintf(f, "#");
        //     }
        //     fprintf(f, "\n");
        //     fprintf(f, "  #########\n");
        //     fprintf(f, "Score: %d\n\n", score);
        //     fclose(f);
        // }
    };

    std::array<int, 4> letters{2, 4, 6, 8};
    std::array<int, 7> topPositions{0, 1, 3, 5, 7, 9, 10};

    template<std::size_t N> 
    int isPath(const state<N>& currentState, int start, int target, char letter = 'A') {
        if (start < target) {
            for (int i = start + 1; i < target; ++i) {
                if (currentState.topLine[i] != 0) {
                    return 0;
                }
            }
        }
        else {
            for (int i = target + 1; i < start; ++i) {
                if (currentState.topLine[i] != 0) {
                    return 0;
                }
            }
        }

        return std::abs(target - start) * std::pow(10, letter - 'A');
    }

    template<std::size_t N> 
    bool isSol(const state<N>& s) {
        for (const auto& l : s.topLine) {
            if (l != 0) {
                return false;
            }
        }

        for (const auto& line : s.lines) {
            for (int i = 0; i < line.size(); ++i) {
                if (line[i] != 'A' + i) {
                    return false;
                }
            }
        }

        return true;
    }

    template<std::size_t N> 
    bool shouldAddPath(const state<N>& s, int minSteps, const std::map<stateWithoutScore, int>& prevStates) {
        if (s.score > minSteps) {
            return false;
        }
        auto it = prevStates.find({s.topLine, s.lines});
         if (it != prevStates.end()) {
             if (it->second <= s.score) {
                 return false;
             }
        }

        return true;
    }

    template<std::size_t N> 
    int calculateVerticalScore(const state<N>& s) {
        int sum = 0;
        std::array<int, 4> extra{0, 0, 0, 0};
        std::array<int, 4> pieces{0, 0, 0, 0};
        for (int i = 0; i < s.lines[1].size(); ++i) {
            if (s.lines[1][i] != i + 'A') {
                extra[s.lines[1][i] - 'A'] += 2;
                extra[s.lines[0][i] - 'A'] += 1;
                pieces[s.lines[1][i] - 'A']++;
                pieces[s.lines[0][i] - 'A']++;
            }
            else if (s.lines[0][i] != i + 'A') {
                extra[s.lines[0][i] - 'A'] += 1;
                pieces[s.lines[0][i] - 'A']++;
            }
        }
        int pow = 1;
        for (int i = 0; i < extra.size(); ++i) {
            sum = sum + (extra[i] + (pieces[i] * (pieces[i] + 1) / 2)) * pow;
            pow *= 10;
        }
        return sum;
    }

    int part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::map<stateWithoutScore, int> prevStates;
        int minSteps = std::numeric_limits<int>::max();
        state<2> initialState;
        std::vector<state<2>> states;
        initialState.lines[0] = {lines[2][3], lines[2][5], lines[2][7], lines[2][9]};
        initialState.lines[1] = {lines[3][3], lines[3][5], lines[3][7], lines[3][9]};
        initialState.score = 0;
        initialState.topLine = {};
        states.push_back(initialState);

        int initialScore = calculateVerticalScore(states.front());

        while (states.front().score < minSteps) {
            std::pop_heap(states.begin(), states.end(), [](const auto &s1, const auto &s2)
                          { return s1.score > s2.score; });
            const auto s = states.front();
            states.pop_back();

            for (int i = 0; i < s.topLine.size(); ++i) {
                if (s.topLine[i] >= 'A' && s.topLine[i] <= 'D') {
                    int target = s.topLine[i] - 'A';
                    int pathSize = isPath(s, letters[target], i, s.topLine[i]);
                    bool valid = true;
                    int line = -1;
                    for (int j = 0; j < s.lines.size(); ++j) {
                        if (s.lines[j][target] != 0 && s.lines[j][target] != s.topLine[i]) {
                            valid = false;
                        }
                        else if (s.lines[j][target] == 0) {
                            line = j;
                        }
                    }
                    if (valid && pathSize > 0) {
                        state newState = s;
                        newState.lines[line][target] = newState.topLine[i];
                        newState.topLine[i] = 0;
                        newState.score = s.score + pathSize;
                        if (isSol(newState)) {
                            minSteps = std::min(minSteps, newState.score);
                        }
                        else if (shouldAddPath(newState, minSteps, prevStates)) {
                            states.push_back(newState);
                            std::push_heap(states.begin(), states.end(), [](const auto& s1, const auto& s2) {
                                return s1.score > s2.score;
                            });
                            prevStates.insert({{newState.topLine, newState.lines}, newState.score});
                        }
                    }
                }
            }

            for (int i = 0; i < s.lines[0].size(); ++i) {
                if (s.lines[0][i] >= 'A' && s.lines[0][i] <= 'D')
                if (s.lines[0][i] != 'A' + i || (s.lines[0][i] == 'A' + i && s.lines[1][i] != 'A' + i)) {

                    // can i move it dirrectly into the final slot? 
                    bool moved = false;
                    int target = s.lines[0][i] - 'A';
                    if (s.lines[0][target] == 0 || s.lines[1][target] == 0) {
                        int path = isPath(s, letters[i], letters[target]);
                        if (path > 0) {
                            moved = true;
                            state newState = s;
                            if (s.lines[1][target] == 0) {
                                newState.score += isPath(s, letters[i], letters[target], s.lines[0][i]);
                                newState.lines[1][target] = s.lines[0][i];
                                newState.lines[0][i] = 0;
                            }
                            else {
                                newState.score += isPath(s, letters[i], letters[target], s.lines[0][i]);
                                newState.lines[0][target] = s.lines[0][i];
                                newState.lines[0][i] = 0;
                            }

                            if (isSol(newState)) {
                                minSteps = std::min(minSteps, newState.score);
                            }
                            else if (shouldAddPath(newState, minSteps, prevStates)) {
                                states.push_back(newState);
                                std::push_heap(states.begin(), states.end(), [](const auto& s1, const auto& s2) {
                                    return s1.score > s2.score;
                                });
                                prevStates.insert({{newState.topLine, newState.lines}, newState.score});
                            }
                        }
                    }

                    if (!moved) {
                        for (int j = 0; j < topPositions.size(); ++j) {
                            int pathSize = isPath(s, letters[i], topPositions[j], s.lines[0][i]);
                            if (s.topLine[topPositions[j]] == 0 && pathSize > 0) {
                                state newState = s;
                                newState.topLine[topPositions[j]] = s.lines[0][i];
                                newState.score = s.score + pathSize;
                                newState.lines[0][i] = 0;
                                if (isSol(newState)) {
                                    minSteps = std::min(minSteps, newState.score);
                                }
                                else if (shouldAddPath(newState, minSteps, prevStates)) {
                                    states.push_back(newState);
                                    std::push_heap(states.begin(), states.end(), [](const auto &s1, const auto &s2)
                                                   { return s1.score > s2.score; });
                                    prevStates.insert({{newState.topLine, newState.lines}, newState.score});
                                }
                            }
                        }
                    }
                }
            }

            for (int i = 0; i < s.lines[1].size(); ++i) {
                if (s.lines[1][i] >= 'A' && s.lines[1][i] <= 'D')
                if (s.lines[0][i] == 0 && s.lines[1][i] != 'A' + i) {

                    // can i move it dirrectly into the final slot? 
                    bool moved = false;
                    int target = s.lines[1][i] - 'A';
                    if (s.lines[0][target] == 0 || s.lines[1][target] == 0) {
                        int path = isPath(s, letters[i], letters[target]);
                        if (path > 0) {
                            moved = true;
                            state newState = s;
                            if (s.lines[1][target] == 0) {
                                newState.score += isPath(s, letters[i], letters[target], s.lines[1][i]);
                                newState.lines[1][target] = s.lines[1][i];
                                newState.lines[1][i] = 0;
                            }
                            else {
                                newState.score += isPath(s, letters[i], letters[target], s.lines[1][i]);
                                newState.lines[0][target] = s.lines[1][i];
                                newState.lines[1][i] = 0;
                            }
                            if (isSol(newState)) {
                                minSteps = std::min(minSteps, newState.score);
                            }
                            else if (shouldAddPath(newState, minSteps, prevStates)) {
                                states.push_back(newState);
                                std::push_heap(states.begin(), states.end(), [](const auto &s1, const auto &s2)
                                               { return s1.score > s2.score; });
                                prevStates.insert({{newState.topLine, newState.lines}, newState.score});
                            }
                        }
                    }

                    if (!moved) {
                        for (int j = 0; j < topPositions.size(); ++j) {
                            int pathSize = isPath(s, letters[i], topPositions[j], s.lines[1][i]);
                            if (s.topLine[topPositions[j]] == 0 && pathSize > 0) {
                                state newState = s;
                                newState.topLine[topPositions[j]] = s.lines[1][i];
                                newState.score = s.score + pathSize;
                                newState.lines[1][i] = 0;
                                if (isSol(newState)) {
                                    minSteps = std::min(minSteps, newState.score);
                                }
                                else if (shouldAddPath(newState, minSteps, prevStates)) {
                                    states.push_back(newState);
                                    std::push_heap(states.begin(), states.end(), [](const auto &s1, const auto &s2)
                                                   { return s1.score > s2.score; });
                                    prevStates.insert({{newState.topLine, newState.lines}, newState.score});
                                }
                            }
                        }
                    }
                }
            }
        }

        return minSteps + initialScore;
    }

    int part_2(std::string_view path) {
        return 0;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2021_day23::part_1("../2021/day23/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2021_day23::part_2("../2021/day23/input.in") << std::endl;

    return 0;
}
#endif
