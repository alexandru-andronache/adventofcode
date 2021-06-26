#include "file.h"
#include "intcode.h"
#include <iostream>

namespace aoc2019_day21 {
    unsigned long long part_1(std::string_view path) {
        std::vector<unsigned long long> input = file::readFileAsArrayULL(path, ",");

        intcode::IntCode<unsigned long long>calc{input, {}};
        intcode::IntCode<unsigned long long>::exitState exit{0, 0, false, false};
        /*
         * NOT A T
         * NOT B J
         * OR T J
         * NOT C T
         * OR T J
         * AND D J
         */
        std::vector<std::string> lines = {"NOT A T\n",
                                          "NOT B J\n",
                                          "OR T J\n",
                                          "NOT C T\n",
                                          "OR T J\n",
                                          "AND D J\n",
                                          "WALK\n"};
        for (const auto& line : lines) {
            for (const auto& c : line) {
                calc.inputIDs.push_back(c);
            }
        }

        while (!exit.halt) {
            exit = calc.advance();
        }

        return exit.returnValue;
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<unsigned long long> input = file::readFileAsArrayULL(path, ",");

        intcode::IntCode<unsigned long long>calc{input, {}};
        intcode::IntCode<unsigned long long>::exitState exit{0, 0, false, false};
        /*
         * NOT A T
         * NOT B J
         * OR T J
         * NOT C T
         * OR T J
         * AND D J
         */
        std::vector<std::string> lines = {"NOT A T\n",
                                          "NOT B J\n",
                                          "OR T J\n",
                                          "NOT C T\n",
                                          "OR T J\n",
                                          "AND D J\n",
                                          "NOT J T\n",
                                          "OR H T\n",
                                          "OR E T\n",
                                          "AND T J\n",
                                          "RUN\n"};
        for (const auto& line : lines) {
            for (const auto& c : line) {
                calc.inputIDs.push_back(c);
            }
        }

        while (!exit.halt) {
            exit = calc.advance();
        }

        return exit.returnValue;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2019_day21::part_1("../2019/day21/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2019_day21::part_2("../2019/day21/input.in") << std::endl;

    return 0;
}
#endif
