#include "file.h"
#include "utilities.h"
#include <iostream>
#include <array>
#include <cmath>
#include <sstream>

namespace aoc2021_day23 {

    int steps = 0;

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
            // std::cout << "History\n";
            // for (const auto& l : moves) {
            //     std::cout << l << "\n";
            // }
            std::cout << "\n";
            std::cout << "\n";
        }

        void print_file() const {
            FILE *f = fopen("../2021/day23/test.out", "a");
            fprintf(f, "#############\n");
            // std::cout << "#############\n";
            // std::cout << "#";
            fprintf(f, "#");
            for (const auto& c : topLine) {
                if (c == 0)
                    fprintf(f, ".");
                else
                    fprintf(f, "%c", c);
                // if (c == 0) std::cout << ".";
                // else std::cout << c;
            }
            fprintf(f, "#\n");
            fprintf(f, "###");
            // std::cout << "#\n";
            // std::cout << "###";
            for (const auto& c: line1) {
                if (c == 0)
                    fprintf(f, ".");
                else
                    fprintf(f, "%c", c);
                fprintf(f, "#");
                // if (c == 0) std::cout << ".";
                // else std::cout << c;
                // std::cout << "#";
            }
            fprintf(f, "##\n");
            fprintf(f, "  #");
            // std::cout << "##\n";
            // std::cout << "  #";
            for (const auto &c : line2) {
                if (c == 0)
                    fprintf(f, ".");
                else
                    fprintf(f, "%c", c);
                fprintf(f, "#");
                // if (c == 0) std::cout << ".";
                // else std::cout << c;
                // std::cout << "#";
            }
            fprintf(f, "\n");
            fprintf(f, "  #########\n");
            fprintf(f, "Score: %d\n\n", score);
            fclose(f);
            // std::cout << "\n";
            // std::cout << "  #########\n";
            // std::cout << "Score: " << score << "\n";
            // std::cout << "\n";
        }
    };

    std::array<int, 4> letters{2, 4, 6, 8};
    std::array<int, 7> topPositions{0, 1, 3, 5, 7, 9, 10};

    int isPath(const state& currentState, int start, int target, int extra = 0, char letter = 'A') {
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

        return (std::abs(target - start) + extra) * std::pow(10, letter - 'A');
    }

    int part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        int minSteps = std::numeric_limits<int>::max();
        state initialState;
        std::vector<state> states;
        states.push_back({{}, {lines[2][3], lines[2][5], lines[2][7], lines[2][9]}, {lines[3][3], lines[3][5], lines[3][7], lines[3][9]}, 0});

        while (!states.empty()) {
            FILE *f = fopen("../2021/day23/test.out", "a");
            fprintf(f, "Steps : %d\n\n\n", steps);
            fclose(f);
            std::cout << "Steps : " << steps << "\n";
            steps++;
            std::vector<state> newStates;
            for (const auto& s : states) {
                if (s.score < minSteps) {
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
                                    pathSize = isPath(s, letters[target], i, 2, newState.topLine[i]);
                                    // std::ostringstream os;
                                    // os << "from top line position " << i << " into line 2 position " << target << " old score: " << s.score << " new score: " << s.score + pathSize;
                                    // newState.moves.push_back(os.str());
                                }
                                else {
                                    newState.line1[target] = newState.topLine[i];
                                    pathSize = isPath(s, letters[target], i, 1, newState.topLine[i]);
                                    // std::ostringstream os;
                                    // os << "from top line position " << i << " into line 1 position " << target << " old score: " << s.score << " new score: " << s.score + pathSize;
                                    // newState.moves.push_back(os.str());
                                }
                                newState.topLine[i] = 0;
                                newState.score = s.score + pathSize;
                                newStates.push_back(newState);
                            }
                        }
                    }

                    for (int i = 0; i < s.line1.size(); ++i) {
                        if (s.line1[i] != 'A' + i || (s.line1[i] == 'A' + i && s.line2[i] != 'A' + i)) {
                            for (int j = 0; j < topPositions.size(); ++j) {
                                int pathSize = isPath(s, letters[i], topPositions[j], 1, s.line1[i]);
                                if (s.topLine[topPositions[j]] == 0 && pathSize > 0) {
                                    state newState = s;
                                    newState.topLine[topPositions[j]] = s.line1[i];
                                    newState.score = s.score + pathSize;
                                    // std::ostringstream os;
                                    // os << "from line 1 position " << i << " into top line position " << topPositions[j] << " old score: " << s.score << " new score: " << newState.score;
                                    // newState.moves.push_back(os.str());
                                    newState.line1[i] = 0;
                                    newStates.push_back(newState);
                                }
                            }
                        }
                    }

                    for (int i = 0; i < s.line2.size(); ++i) {
                        if (s.line1[i] == 0 && s.line2[i] != 'A' + i) {
                            for (int j = 0; j < topPositions.size(); ++j) {
                                int pathSize = isPath(s, letters[i], topPositions[j], 2, s.line2[i]);
                                if (s.topLine[topPositions[j]] == 0 && pathSize > 0) {
                                    state newState = s;
                                    newState.topLine[topPositions[j]] = s.line2[i];
                                    newState.score = s.score + pathSize;
                                    newState.line2[i] = 0;
                                    // std::ostringstream os;
                                    // os << "from line 2 position " << i << " into top line position " << topPositions[j] << " old score: " << s.score << " new score: " << newState.score;
                                    // newState.moves.push_back(os.str());
                                    newStates.push_back(newState);
                                }
                            }
                        }
                    }
                }
            }
            states = newStates;

            for (const auto& s : states) {
                if (minSteps > s.score) {
                    bool sol = true;
                    for (int i = 0; i < s.line1.size(); ++i) {
                        if (s.line1[i] != 'A' + i) {
                            sol = false;
                        }
                    }

                    for (int i = 0; i < s.line2.size(); ++i) {
                        if (s.line2[i] != 'A' + i) {
                            sol = false;
                        }
                    }
                    if (sol) {
                        minSteps = std::min(minSteps, s.score);
                        s.print();
                    }
                }
            }

            int oldSize = states.size();
            states.erase(std::remove_if(states.begin(), states.end(), [](const state& s) {
                bool sol = true;
                for (const auto& l : s.topLine) {
                    if (l != 0) {
                        sol = false;
                    }
                }

                for (int i = 0; i < s.line1.size(); ++i) {
                    if (s.line1[i] != 'A' + i) {
                        sol = false;
                    }
                }

                for (int i = 0; i < s.line2.size(); ++i) {
                    if (s.line2[i] != 'A' + i) {
                        sol = false;
                    }
                }
                return sol;
            }), states.end());

            std::cout << "States removed: " << oldSize - states.size() << "\n";
            
            // for (const auto& s : states) {
            //     s.print_file();
            // }
        }

        return minSteps;
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
