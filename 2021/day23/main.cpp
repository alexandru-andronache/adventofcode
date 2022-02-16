#include "file.h"
#include "utilities.h"
#include <iostream>
#include <array>
#include <cmath>
#include <sstream>
#include <map>

namespace aoc2021_day23 {

    int steps = 0;

    struct stateWithoutScore {
        std::array<char, 11> topLine{};
        std::array<char, 4> line1{};
        std::array<char, 4> line2{};

        bool operator<(const stateWithoutScore &value) const {
            return std::tie(topLine, line1, line2) < std::tie(value.topLine, value.line1, value.line2);
        }
    };

    struct state {
        std::array<char, 11> topLine{};
        std::array<char, 4> line1{};
        std::array<char, 4> line2{};
        int score = 0;

        // std::vector<std::string> moves;

        void print() const
        {
            std::cout << "#############\n";
            std::cout << "#";
            for (const auto &c : topLine)
            {
                if (c == 0) std::cout << ".";
                else std::cout << c;
            }
            std::cout << "#\n";
            std::cout << "###";
            for (const auto &c : line1)
            {
                if (c == 0) std::cout << ".";
                else std::cout << c;
                std::cout << "#";
            }
            std::cout << "##\n";
            std::cout << "  #";
            for (const auto &c : line2)
            {
                if (c == 0) std::cout << ".";
                else std::cout << c;
                std::cout << "#";
            }
            std::cout << "\n";
            std::cout << "  #########\n";
            std::cout << "Score: " << score << "\n";
            std::cout << "\n";
            std::cout << "\n";
            std::cout << "\n";
        }

        void print_file() const {
            FILE *f = fopen("../2021/day23/test.out", "a");
            fprintf(f, "#############\n");
            fprintf(f, "#");
            for (const auto& c : topLine) {
                if (c == 0)
                    fprintf(f, ".");
                else
                    fprintf(f, "%c", c);
            }
            fprintf(f, "#\n");
            fprintf(f, "###");
            for (const auto& c: line1) {
                if (c == 0)
                    fprintf(f, ".");
                else
                    fprintf(f, "%c", c);
                fprintf(f, "#");
            }
            fprintf(f, "##\n");
            fprintf(f, "  #");
            for (const auto &c : line2) {
                if (c == 0)
                    fprintf(f, ".");
                else
                    fprintf(f, "%c", c);
                fprintf(f, "#");
            }
            fprintf(f, "\n");
            fprintf(f, "  #########\n");
            fprintf(f, "Score: %d\n\n", score);
            fclose(f);
        }
    };

    std::array<int, 4> letters{2, 4, 6, 8};
    std::array<int, 7> topPositions{0, 1, 3, 5, 7, 9, 10};

    int isPath(const state& currentState, int start, int target, char letter = 'A') {
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

    bool isSol(const state& s) {
        for (const auto& l : s.topLine) {
            if (l != 0) {
                return false;
            }
        }
        for (int i = 0; i < s.line1.size(); ++i) {
            if (s.line1[i] != 'A' + i) {
                return false;
            }
        }

        for (int i = 0; i < s.line2.size(); ++i) {
            if (s.line2[i] != 'A' + i) {
                return false;
            }
        }

        return true;
    }

    bool shouldAddPath(const state& s, int minSteps, const std::map<stateWithoutScore, int>& prevStates) {
        if (s.score > minSteps) {
            return false;
        }
        auto it = prevStates.find({s.topLine, s.line1, s.line2});
         if (it != prevStates.end()) {
             if (it->second <= s.score) {
                 return false;
             }
        }

        return true;
    }

    int calculateVerticalScore(const state& s) {
        int sum = 0;
        std::array<int, 4> extra{0, 0, 0, 0};
        std::array<int, 4> pieces{0, 0, 0, 0};
        for (int i = 0; i < s.line2.size(); ++i) {
            if (s.line2[i] != i + 'A') {
                extra[s.line2[i] - 'A'] += 2;
                extra[s.line1[i] - 'A'] += 1;
                pieces[s.line2[i] - 'A']++;
                pieces[s.line1[i] - 'A']++;
            }
            else if (s.line1[i] != i + 'A') {
                extra[s.line1[i] - 'A'] += 1;
                pieces[s.line1[i] - 'A']++;
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
        state initialState;
        std::vector<state> states;
        states.push_back({{}, {lines[2][3], lines[2][5], lines[2][7], lines[2][9]}, {lines[3][3], lines[3][5], lines[3][7], lines[3][9]}, 0});

        int initialScore = calculateVerticalScore(states.front());

        while (states.front().score < minSteps) {
            std::pop_heap(states.begin(), states.end(), [](const auto &s1, const auto &s2)
                          { return s1.score > s2.score; });
            const auto s = states.front();
            states.pop_back();

            for (int i = 0; i < s.topLine.size(); ++i) {
                if (s.topLine[i] >= 'A' && s.topLine[i] <= 'D') {
                    int target = s.topLine[i] - 'A';
                    int pathSize = isPath(s, letters[target], i);
                    if (s.line1[target] == 0 &&
                        (s.line2[target] == 0 || s.line2[target] == s.topLine[i]) &&
                        pathSize > 0) {
                        state newState = s;
                        if (s.line2[target] == 0) {
                            newState.line2[target] = newState.topLine[i];
                            pathSize = isPath(s, letters[target], i, newState.topLine[i]);
                        }
                        else {
                            newState.line1[target] = newState.topLine[i];
                            pathSize = isPath(s, letters[target], i, newState.topLine[i]);
                        }
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
                            prevStates.insert({{newState.topLine, newState.line1, newState.line2}, newState.score});
                        }
                    }
                }
            }

            for (int i = 0; i < s.line1.size(); ++i) {
                if (s.line1[i] >= 'A' && s.line1[i] <= 'D')
                if (s.line1[i] != 'A' + i || (s.line1[i] == 'A' + i && s.line2[i] != 'A' + i)) {

                    // can i move it dirrectly into the final slot? 
                    bool moved = false;
                    int target = s.line1[i] - 'A';
                    if (s.line1[target] == 0 || s.line2[target] == 0) {
                        int path = isPath(s, letters[i], letters[target]);
                        if (path > 0) {
                            moved = true;
                            state newState = s;
                            if (s.line2[target] == 0) {
                                newState.score += isPath(s, letters[i], letters[target], s.line1[i]);
                                newState.line2[target] = s.line1[i];
                                newState.line1[i] = 0;
                            }
                            else {
                                newState.score += isPath(s, letters[i], letters[target], s.line1[i]);
                                newState.line1[target] = s.line1[i];
                                newState.line1[i] = 0;
                            }

                            if (isSol(newState)) {
                                minSteps = std::min(minSteps, newState.score);
                            }
                            else if (shouldAddPath(newState, minSteps, prevStates)) {
                                states.push_back(newState);
                                std::push_heap(states.begin(), states.end(), [](const auto& s1, const auto& s2) {
                                    return s1.score > s2.score;
                                });
                                prevStates.insert({{newState.topLine, newState.line1, newState.line2}, newState.score});
                            }
                        }
                    }

                    if (!moved) {
                        for (int j = 0; j < topPositions.size(); ++j) {
                            int pathSize = isPath(s, letters[i], topPositions[j], s.line1[i]);
                            if (s.topLine[topPositions[j]] == 0 && pathSize > 0) {
                                state newState = s;
                                newState.topLine[topPositions[j]] = s.line1[i];
                                newState.score = s.score + pathSize;
                                newState.line1[i] = 0;
                                if (isSol(newState)) {
                                    minSteps = std::min(minSteps, newState.score);
                                }
                                else if (shouldAddPath(newState, minSteps, prevStates)) {
                                    states.push_back(newState);
                                    std::push_heap(states.begin(), states.end(), [](const auto &s1, const auto &s2)
                                                   { return s1.score > s2.score; });
                                    prevStates.insert({{newState.topLine, newState.line1, newState.line2}, newState.score});
                                }
                            }
                        }
                    }
                }
            }

            for (int i = 0; i < s.line2.size(); ++i) {
                if (s.line2[i] >= 'A' && s.line2[i] <= 'D')
                if (s.line1[i] == 0 && s.line2[i] != 'A' + i) {

                    // can i move it dirrectly into the final slot? 
                    bool moved = false;
                    int target = s.line2[i] - 'A';
                    if (s.line1[target] == 0 || s.line2[target] == 0) {
                        int path = isPath(s, letters[i], letters[target]);
                        if (path > 0) {
                            moved = true;
                            state newState = s;
                            if (s.line2[target] == 0) {
                                newState.score += isPath(s, letters[i], letters[target], s.line2[i]);
                                newState.line2[target] = s.line2[i];
                                newState.line2[i] = 0;
                            }
                            else {
                                newState.score += isPath(s, letters[i], letters[target], s.line2[i]);
                                newState.line1[target] = s.line2[i];
                                newState.line2[i] = 0;
                            }
                            if (isSol(newState)) {
                                minSteps = std::min(minSteps, newState.score);
                            }
                            else if (shouldAddPath(newState, minSteps, prevStates)) {
                                states.push_back(newState);
                                std::push_heap(states.begin(), states.end(), [](const auto &s1, const auto &s2)
                                               { return s1.score > s2.score; });
                                prevStates.insert({{newState.topLine, newState.line1, newState.line2}, newState.score});
                            }
                        }
                    }

                    if (!moved) {
                        for (int j = 0; j < topPositions.size(); ++j) {
                            int pathSize = isPath(s, letters[i], topPositions[j], s.line2[i]);
                            if (s.topLine[topPositions[j]] == 0 && pathSize > 0) {
                                state newState = s;
                                newState.topLine[topPositions[j]] = s.line2[i];
                                newState.score = s.score + pathSize;
                                newState.line2[i] = 0;
                                if (isSol(newState)) {
                                    minSteps = std::min(minSteps, newState.score);
                                }
                                else if (shouldAddPath(newState, minSteps, prevStates)) {
                                    states.push_back(newState);
                                    std::push_heap(states.begin(), states.end(), [](const auto &s1, const auto &s2)
                                                   { return s1.score > s2.score; });
                                    prevStates.insert({{newState.topLine, newState.line1, newState.line2}, newState.score});
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
