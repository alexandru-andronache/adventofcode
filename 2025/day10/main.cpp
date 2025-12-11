#include <numeric>

#include "file.h"
#include "utilities.h"
#include <vector>
#include "z3++.h"

#include <fmt/printf.h>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2025_day10 {
    int part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        int result = 0;

        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, " ");
            std::vector<bool> state;
            for (int i = 1; i < tokens[0].size() - 1; ++i) {
                state.push_back(tokens[0][i] != '.');
            }
            std::vector<std::vector<int>> buttons;
            for (int i = 1; i < tokens.size() - 1; i++) {
                std::vector<int> button;
                for (int j = 1; j < tokens[i].size() - 1; j += 2) {
                    button.push_back(tokens[i][j] - '0');
                }
                buttons.push_back(button);
            }

            int min = INT_MAX;
            for (int i = 0; i <= std::pow(2, buttons.size()); ++i) {
                std::vector<bool> current_state(state.size(), false);
                int nr = 0;
                for (int j = 0; j < buttons.size() && nr < min; ++j) {
                    if ((i >> j) & 1) {
                        for (const auto& button : buttons[j]) {
                            current_state[button] = !current_state[button];
                        }
                        nr++;
                    }
                }
                bool valid = true;
                for (int j = 0; j < current_state.size(); ++j) {
                    if (current_state[j] != state[j]) {
                        valid = false;
                        break;
                    }
                }
                if (valid && nr < min) {
                    min = nr;
                }
            }
            result += min;
        }

        return result;
    }

    int part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        int result = 0;

        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, " ");
            std::vector<int> final_numbers = utils::splitStringToInt(tokens.back(), "{,}");
            std::vector<std::vector<int>> combinations(final_numbers.size(), std::vector<int>());
            for (int i = 1; i < tokens.size() - 1; i++) {
                for (int j = 1; j < tokens[i].size() - 1; j += 2) {
                    combinations[tokens[i][j] - '0'].push_back(i - 1);
                }
            }

            z3::config cfg;
            z3::context context(cfg);
            std::vector<z3::expr> exprs;
            for (int i = 0; i < tokens.size() - 2; ++i) {
                exprs.push_back(context.int_const(("x_" + std::to_string(i)).c_str()));
            }

            z3::optimize solver(context);
            for (int i = 0; i < combinations.size(); ++i) {
                z3::expr lhs = context.int_val(0);
                for (const auto& j : combinations[i]) {
                    lhs = lhs + exprs[j];
                }
                solver.add(lhs == context.int_val(final_numbers[i]));
            }

            for (auto& x : exprs) {
                solver.add(x >= 0);
            }

            z3::expr sum = context.int_val(0);
            for (auto& x : exprs) {
                sum = sum + x;
            }
            solver.minimize(sum);

            solver.check();
            result = std::accumulate(exprs.begin(), exprs.end(), result, [solver](const auto& total, const auto& x) {
                return total + solver.get_model().eval(x).get_numeral_int();
            });
        }

        return result;
    }
}

#ifdef TESTING
    TEST(Test2025Day10, part_1_test) {
        ASSERT_EQ(aoc2025_day10::part_1("../2025/day10/input_test.in"), 7);
    }

    TEST(Test2025Day10, part_1_real_test) {
        ASSERT_EQ(aoc2025_day10::part_1("../2025/day10/input.in"), 436);
    }

    TEST(Test2025Day10, part_2_test) {
        ASSERT_EQ(aoc2025_day10::part_2("../2025/day10/input_test.in"), 33);
    }

    TEST(Test2025Day10, part_2_real_test) {
        ASSERT_EQ(aoc2025_day10::part_2("../2025/day10/input.in"), 14999);
    }
#endif

#ifndef TESTING
int main() {
    fmt::print("Part 1: {}\n", aoc2025_day10::part_1("../2025/day10/input.in"));
    fmt::print("Part 2: {}\n", aoc2025_day10::part_2("../2025/day10/input.in"));

    return 0;
}
#endif
