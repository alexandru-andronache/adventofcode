#include "file.h"
#include "utilities.h"
#include <iostream>
#include <map>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2024_day24 {
    struct op {
        std::string op1;
        std::string op2;
        std::function<int(int, int)> calculate;
        std::string operation;
        std::string result;
    };

    unsigned long long part_1(std::string_view path) {
        const std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::map<std::string, int> instructions;
        std::vector<op> operations;

        int index = 0;
        while (!lines[index].empty()) {
            std::vector<std::string> tokens = utils::splitString(lines[index], ": ");
            instructions[tokens[0]] = std::stoi(tokens[1]);
            index++;
        }
        index++;
        while (index < lines.size()) {
            std::vector<std::string> tokens = utils::splitString(lines[index], "-> ");
            if (tokens[1] == "AND") {
                operations.emplace_back(tokens[0], tokens[2], [](int op1, int op2) {
                    return op1 & op2;
                }, "AND", tokens[3]);
            }
            else if (tokens[1] == "OR") {
                operations.emplace_back(tokens[0], tokens[2], [](int op1, int op2) {
                    return op1 | op2;
                }, "XOR", tokens[3]);
            }
            else if (tokens[1] == "XOR") {
                operations.emplace_back(tokens[0], tokens[2], [](int op1, int op2) {
                    return op1 ^ op2;
                }, "OR", tokens[3]);
            }
            index++;
        }

        bool finished = false;
        while (!finished) {
            finished = true;
            for (const auto& operation : operations) {
                if (instructions.contains(operation.op1) &&
                    instructions.contains(operation.op2) &&
                    !instructions.contains(operation.result)) {
                    instructions[operation.result] = operation.calculate(instructions[operation.op1], instructions[operation.op2]);
                    finished = false;
                }
            }
        }

        std::bitset<63> sol;
        for (const auto& [key, value] : instructions) {
            if (key.starts_with("z")) {
                sol.set(std::stoi(key.substr(1, 2)), value);
            }
        }

        return sol.to_ullong();
    }

    std::string find(const std::vector<op>& operations,
                     const std::string& key1,
                     const std::string& key2,
                     const std::string& result) {
        for (const auto& operation : operations) {
            if (operation.op1 == key1 && operation.op2 == key2 && operation.operation == result) {
                return operation.result;
            }
            if (operation.op1 == key2 && operation.op2 == key1 && operation.operation == result) {
                return operation.result;
            }
        }
        return "";
    }

    std::string part_2(std::string_view path) {
        const std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::vector<std::string> sol;
        std::map<std::string, int> instructions;
        std::vector<op> operations;
        int maxX = 0;

        int index = 0;
        while (!lines[index].empty()) {
            std::vector<std::string> tokens = utils::splitString(lines[index], ": ");
            instructions[tokens[0]] = std::stoi(tokens[1]);
            if (tokens[0].starts_with("x")) {
                maxX = std::max(maxX, std::stoi(tokens[0].substr(1, 2)));
            }
            index++;
        }
        index++;
        while (index < lines.size()) {
            std::vector<std::string> tokens = utils::splitString(lines[index], "-> ");
            if (tokens[1] == "AND") {
                operations.emplace_back(tokens[0], tokens[2], [](int op1, int op2) {
                    return op1 & op2;
                }, "AND", tokens[3]);
            }
            else if (tokens[1] == "OR") {
                operations.emplace_back(tokens[0], tokens[2], [](int op1, int op2) {
                    return op1 | op2;
                }, "OR", tokens[3]);
            }
            else if (tokens[1] == "XOR") {
                operations.emplace_back(tokens[0], tokens[2], [](int op1, int op2) {
                    return op1 ^ op2;
                }, "XOR", tokens[3]);
            }
            index++;
        }

        // Full Adder Logic:
        // A full adder adds three one-bit numbers (X1, Y1, and carry-in C0) and outputs a sum bit (Z1) and a carry-out bit (C1).
        // The logic for a full adder is as follows:
        // - X1 XOR Y1 -> M1 (intermediate sum)
        // - X1 AND Y1 -> N1 (intermediate carry)
        // - C0 AND M1 -> R1 (carry for intermediate sum)
        // - C0 XOR M1 -> Z1 (final sum)
        // - R1 OR N1 -> C1 (final carry)

        std::string c0, z1, c1;
        std::string finalZ = std::format("z{:0>{}}", maxX + 1, 2);

        for (int i = 0; i <= maxX; ++i) {
            std::string x = std::format("x{:0>{}}", i, 2);
            std::string y = std::format("y{:0>{}}", i, 2);

            std::string m1 = find(operations, x, y, "XOR");
            std::string n1 = find(operations, x, y, "AND");

            if (!c0.empty()) {
                std::string r1 = find(operations, c0, m1, "AND");
                if (r1.empty()) {
                    std::swap(m1, n1);
                    sol.insert(sol.end(), {m1, n1});
                    r1 = find(operations, c0, m1, "AND");
                }
                z1 = find(operations, c0, m1, "XOR");
                if (m1.starts_with("z")) {
                    std::swap(m1, z1);
                    sol.insert(sol.end(), {m1, z1});
                }
                if (n1.starts_with("z")) {
                    std::swap(n1, z1);
                    sol.insert(sol.end(), {n1, z1});
                }
                if (r1.starts_with("z")) {
                    std::swap(r1, z1);
                    sol.insert(sol.end(), {r1, z1});
                }
                c1 = find(operations, r1, n1, "OR");
            }
            else {
                z1 = m1;
                c1 = n1;
            }

            if (c1.starts_with("z") && c1 != finalZ) {
                std::swap(c1, z1);
                sol.insert(sol.end(), {c1, z1});
            }
            if (!c1.empty()) {
                c0 = c1;
            }
            else {
                c0 = find(operations, x, y, "AND");
            }
        }

        std::ranges::sort(sol);
        std::string final = sol[0];
        for (int i = 1; i < sol.size(); i++) {
            final += "," + sol[i];
        }

        return final;
    }
}


#ifdef TESTING
TEST(Tests2024Day24, part_1_test) {
    ASSERT_EQ(aoc2024_day24::part_1("../2024/day24/input_test.in"), 2024);
}

TEST(Tests2024Day24, part_1_real_test) {
    ASSERT_EQ(aoc2024_day24::part_1("../2024/day24/input.in"), 51745744348272);
}

TEST(Tests2024Day24, part_2_real_test) {
    ASSERT_EQ(aoc2024_day24::part_2("../2024/day24/input.in"), "bfq,bng,fjp,hkh,hmt,z18,z27,z31");
}
#endif

#ifndef TESTING
int main() {
    std::cout << std::format("Part 1: {}\n", aoc2024_day24::part_1("../2024/day24/input.in"));
    std::cout << std::format("Part 2: {}\n", aoc2024_day24::part_2("../2024/day24/input.in"));

    return 0;
}
#endif
