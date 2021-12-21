#include "file.h"
#include "utilities.h"
#include <iostream>
#include <list>

namespace aoc2021_day18 {
    const int OPEN = -1;
    const int CLOSE = -2;

    class Number {
    public:
        Number() = default;

        void add(std::string_view line) {
            bool needClose = false;
            if (!state.empty()) {
                state.push_front(OPEN);
                needClose = true;
            }
            for (const auto& c : line) {
                if (c == '[') {
                    state.push_back(OPEN);
                }
                else if (c == ']') {
                    state.push_back(CLOSE);
                }
                else if (c != ',') {
                    state.push_back(c - '0');
                }
            }
            if (needClose) {
                state.push_back(CLOSE);
            }
        }

        void split(std::list<int>::iterator it) {
            int value = *it;
            *it = OPEN;
            std::advance(it, 1);
            it = state.insert(it, value / 2);
            std::advance(it, 1);
            it = state.insert(it, value / 2 + value % 2);
            std::advance(it, 1);
            state.insert(it, CLOSE);
        }

        void explode(std::list<int>::iterator it) {
            int value1 = *(std::next(it, 1));
            int value2 = *(std::next(it, 2));

            auto before = it;
            while (before != state.begin() && *before < 0) {
                std::advance(before, -1);
            }
            if (before != state.begin()) {
                *before += value1;
            }

            *it = 0;
            std::advance(it, 1);
            auto end = it;
            std::advance(end, 3);

            auto after = end;
            while (after != state.end() && *after < 0) {
                std::advance(after, 1);
            }
            if (after != state.end()) {
                *after += value2;
            }

            state.erase(it, end);
        }

        bool shouldSpit() {
            auto it = state.begin();
            while (it != state.end()) {
                if (*it > 9) {
                    split(it);
                    return true;
                }
                std::advance(it, 1);
            }
            return false;
        }

        void parse2() {
            while (parse()) {

            }
        }

        // applies the next operation
        // return true if it's not finished
        bool parse() {
            auto it = state.begin();
            int braces = 0;
            while (it != state.end()) {
                braces += (*it == OPEN);
                braces -= (*it == CLOSE);
                if (braces > 4) {
                    int value1 = *(std::next(it, 1));
                    int value2 = *(std::next(it, 2));
                    if (value1 >= 0 && value2 >= 0) {
                        explode(it);
                        return true;
                    }
                }
                std::advance(it, 1);
            }
            if (shouldSpit()) {
                return true;
            }
            return false;
        }

        void minimize() {
            auto it = state.begin();
            while (*it != CLOSE) {
                std::advance(it, 1);
            }
            int value1 = *(std::next(it, -1));
            int value2 = *(std::next(it, -2));
            int value = value1 * 2 + value2 * 3;
            *it = value;
            auto begin = it;
            std::advance(begin, -3);
            state.erase(begin, it);
        }

        int magnitude() {
            while (state.size() > 1) {
                minimize();
            }
            return state.front();
        }

    private:
        std::list<int> state;
    };

    int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        Number nr;
        for (const auto& line : input) {
            nr.add(line);
            nr.parse2();
        }
        return nr.magnitude();
    }

    int part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        int maxSol = 0;
        for (int i = 0; i < input.size(); ++i) {
            for (int j = 0; j < input.size(); ++j) {
                if (i != j) {
                    Number nr;
                    nr.add(input[i]);
                    nr.add(input[j]);
                    while (nr.parse()) {
                    }
                    maxSol = std::max(maxSol, nr.magnitude());
                }
            }
        }
        return maxSol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2021_day18::part_1("../2021/day18/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2021_day18::part_2("../2021/day18/input.in") << std::endl;

    return 0;
}
#endif
