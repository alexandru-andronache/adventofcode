#include "file.h"
#include "utilities.h"
#include <iostream>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2024_day17 {
    long long getValue(int n, const std::vector<long long>& numbers) {
        if (n < 4) {
            return n;
        }
        return numbers[n - 4];
    }

    std::vector<int> solve(long long a, long long b, long long c, const std::vector<int>& instructions) {
        std::vector<int> output;
        std::vector<long long> numbers{a, b, c};
        int index = 0;
        while (index < instructions.size()) {
            bool update = true;
            if (instructions[index] == 0) {
                numbers[0] >>= getValue(instructions[index + 1], numbers);
            }
            else if (instructions[index] == 1) {
                numbers[1] ^= instructions[index + 1];
            }
            else if (instructions[index] == 2) {
                numbers[1] = getValue(instructions[index + 1], numbers) % 8;
            }
            else if (instructions[index] == 3) {
                if (numbers[0] != 0) {
                    index = instructions[index + 1];
                    update = false;
                }
            }
            else if (instructions[index] == 4) {
                numbers[1] ^= numbers[2];
            }
            else if (instructions[index] == 5) {
                output.emplace_back(getValue(instructions[index + 1], numbers) % 8);
            }
            else if (instructions[index] == 6) {
                numbers[1] = numbers[0] >> getValue(instructions[index + 1], numbers);
            }
            else if (instructions[index] == 7) {
                numbers[2] = numbers[0] >> getValue(instructions[index + 1], numbers);
            }
            if (update) {
                index += 2;
            }
        }
        return output;
    }

    std::string part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::vector<long long> numbers{0, 0, 0};
        for (int i = 0; i < 3; ++i) {
            std::vector<std::string> tokens = utils::splitString(lines[i], " ");
            numbers[i] = std::stoll(tokens[2]);
        }
        const std::vector<std::string> tokens = utils::splitString(lines[4], " ,");
        std::vector<int> instructions;
        for (int i = 1; i < tokens.size(); ++i) {
            instructions.emplace_back(std::stoi(tokens[i]));
        }

        return utils::vectorToString(solve(numbers[0], numbers[1], numbers[2], instructions), ',');
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::vector<int> output;
        std::vector<long long> numbers{0, 0, 0};
        for (int i = 0; i < 3; ++i) {
            std::vector<std::string> tokens = utils::splitString(lines[i], " ");
            numbers[i] = std::stoll(tokens[2]);
        }
        const std::vector<std::string> tokens = utils::splitString(lines[4], " ,");
        std::vector<int> instructions;
        for (int i = 1; i < tokens.size(); ++i) {
            instructions.emplace_back(std::stoi(tokens[i]));
        }

        long long a = 0;
        for (int i = 0; i < instructions.size(); ++i) {
            a <<= 3;
            std::vector<int> temp(instructions.end() - i - 1, instructions.end());
            while (solve(a,numbers[1], numbers[2], instructions) != temp) {
                a++;
            }
        }
        return a;
    }
}

#ifdef TESTING
namespace aoc2024_day17{
    TEST(Tests2024Day17, part_1_test) {
        ASSERT_EQ(part_1("../2024/day17/input_test.in"), "4,6,3,5,6,3,5,2,1,0");
    }

    TEST(Tests2024Day17, part_1_real_test) {
        ASSERT_EQ(part_1("../2024/day17/input.in"), "2,3,6,2,1,6,1,2,1");
    }

    TEST(Tests2024Day17, part_2_test) {
        ASSERT_EQ(part_2("../2024/day17/input_test_part_2.in"), 117440);
    }

    TEST(Tests2024Day17, part_2_real_test) {
        ASSERT_EQ(part_2("../2024/day17/input.in"), 90938893795561);
    }
}
#endif

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2024_day17::part_1("../2024/day17/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2024_day17::part_2("../2024/day17/input.in") << std::endl;

    return 0;
}
#endif
