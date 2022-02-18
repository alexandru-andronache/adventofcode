#include "file.h"
#include "utilities.h"
#include <iostream>
#include <array>
#include <cmath>
#include <map>
#include <algorithm>

namespace aoc2021_day23 {

    int steps = 0;

    template<std::size_t N> 
    struct stateWithoutScore {
        std::array<char, 11> topLine{};
        std::array<std::array<char, 4>, N> lines {};

        bool operator<(const stateWithoutScore &value) const {
            return std::tie(topLine, lines) < std::tie(value.topLine, value.lines);
        }
    };

    template<std::size_t N> 
    struct state {
        std::array<char, 11> topLine{};
        std::array<std::array<char, 4>, N> lines {};
        int score = 0;
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
    bool shouldAddPath(const state<N>& s, int minSteps, const std::map<stateWithoutScore<N>, int>& prevStates) {
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

        for (int i = 0; i < s.lines[0].size(); ++i) {
            for (int j = s.lines.size() - 1; j >= 0; --j) {
                if (s.lines[j][i] != 'A' + i) {
                    for (int l = j; l >= 0; --l) {
                        extra[s.lines[l][i] - 'A'] += l + 1;
                        pieces[s.lines[l][i] - 'A']++;
                    }
                    break;
                }
            }
        }

        int pow = 1;
        for (int i = 0; i < extra.size(); ++i) {
            sum = sum + (extra[i] + (pieces[i] * (pieces[i] + 1) / 2)) * pow;
            pow *= 10;
        }
        return sum;
    }

    template<std::size_t N> 
    int solve(const state<N>& startState) {
        std::map<stateWithoutScore<N>, int> prevStates;
        int minSteps = std::numeric_limits<int>::max();
        std::vector<state<N>> states;
        states.push_back(startState);

        while (!states.empty() && states.front().score < minSteps) {
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


            for (int k = 0; k < s.lines.size(); ++k) {
                for (int i = 0; i < s.lines[k].size(); ++i) {
                    bool shouldMove = true;
                    for (int l = 0; l < k; ++l) {
                        if (s.lines[l][i] != 0) shouldMove = false;
                    }
                    if (shouldMove) {
                        shouldMove = false;
                        for (int l = k; l < s.lines.size(); ++l) {
                            if (s.lines[l][i] != 'A' + i && s.lines[l][i] != 0) {
                                shouldMove = true;
                            }
                        }
                    }
                    // shouldMove if all s[l][i] == 0(l from 0 -> k - 1) and any s[l][i] are != 'A' + i and != 0 with l = k -> size 
                
                    if (s.lines[k][i] >= 'A' && s.lines[k][i] <= 'D' && shouldMove) {

                        // can i move it dirrectly into the final slot? 
                        bool moved = false;
                        int target = s.lines[k][i] - 'A';
                        int targetLine = -1;
                        for (int l = 0; l < s.lines.size() && targetLine == -1; ++l) {
                            if (s.lines[l][target] == 0) {
                                targetLine = l;
                                break;
                            }
                        }
                        bool valid = true;
                        for (int l = targetLine + 1; l < s.lines.size(); ++l) {
                            if (s.lines[l][target] != s.lines[k][i]) {
                                valid = false;
                            }
                        }
                        if (targetLine != -1 && valid) {
                            int path = isPath(s, letters[i], letters[target], s.lines[k][i]);
                            if (path > 0) {
                                moved = true;
                                state newState = s;
                                newState.score += path;
                                newState.lines[targetLine][target] = s.lines[k][i];
                                newState.lines[k][i] = 0;

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
                                int pathSize = isPath(s, letters[i], topPositions[j], s.lines[k][i]);
                                bool valid = true;
                                for (int l = 0; l < k; ++l) {
                                    if (s.lines[l][i] != 0) {
                                        valid = false;
                                    }
                                }
                                if (s.topLine[topPositions[j]] == 0 && pathSize > 0 && valid) {
                                    state newState = s;
                                    newState.topLine[topPositions[j]] = s.lines[k][i];
                                    newState.score = s.score + pathSize;
                                    newState.lines[k][i] = 0;
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
        }

        return minSteps;
    }

    int part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        state<2> initialState;
        initialState.lines[0] = {lines[2][3], lines[2][5], lines[2][7], lines[2][9]};
        initialState.lines[1] = {lines[3][3], lines[3][5], lines[3][7], lines[3][9]};
        initialState.score = 0;
        initialState.topLine = {};

        return solve(initialState) + calculateVerticalScore(initialState);
    }

    int part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        state<4> initialState;
        initialState.lines[0] = {lines[2][3], lines[2][5], lines[2][7], lines[2][9]};
        initialState.lines[1] = {'D', 'C', 'B', 'A'};
        initialState.lines[2] = {'D', 'B', 'A', 'C'};
        initialState.lines[3] = {lines[3][3], lines[3][5], lines[3][7], lines[3][9]};
        initialState.score = 0;
        initialState.topLine = {};

        return solve(initialState) + calculateVerticalScore(initialState);
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2021_day23::part_1("../2021/day23/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2021_day23::part_2("../2021/day23/input.in") << std::endl;

    return 0;
}
#endif
