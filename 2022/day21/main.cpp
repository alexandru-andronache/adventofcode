#include "file.h"
#include "utilities.h"
#include <iostream>
#include <map>

namespace aoc2022_day21 {
    struct monkey {
        std::string op1;
        std::string op2;
        std::string operation;
        long long val;
        bool isCalculated;
        bool isHumanDependent;
    };

    std::map<std::string, monkey> monkeys;

    long long calculate(std::string m) {
        if (m == "humn") {
            monkeys[m].isHumanDependent = true;
        }
        if (monkeys[m].isCalculated) {
            return monkeys[m].val;
        }
        monkeys[monkeys[m].op1].val = calculate(monkeys[m].op1);
        if (monkeys[monkeys[m].op1].isHumanDependent) {
            monkeys[m].isHumanDependent = true;
        }
        monkeys[monkeys[m].op2].val = calculate(monkeys[m].op2);
        if (monkeys[monkeys[m].op2].isHumanDependent) {
            monkeys[m].isHumanDependent = true;
        }
        if (monkeys[m].operation == "+") {
            return monkeys[monkeys[m].op1].val + monkeys[monkeys[m].op2].val;
        }
        if (monkeys[m].operation == "-") {
            return monkeys[monkeys[m].op1].val - monkeys[monkeys[m].op2].val;
        }
        if (monkeys[m].operation == "*") {
            return monkeys[monkeys[m].op1].val * monkeys[monkeys[m].op2].val;
        }
        if (monkeys[m].operation == "/") {
            return monkeys[monkeys[m].op1].val / monkeys[monkeys[m].op2].val;
        }
        return 0;
    }

    long long calculateReverse(std::string m, long long totalValue) {
        if (m == "humn") {
            return totalValue;
        }
        if (monkeys[m].isCalculated) {
            return monkeys[m].val;
        }
        if (monkeys[monkeys[m].op1].isHumanDependent) {
            long long result = calculate(monkeys[m].op2);
            if (monkeys[m].operation == "+") {
                return calculateReverse(monkeys[m].op1, totalValue - result);
            }
            if (monkeys[m].operation == "-") {
                return calculateReverse(monkeys[m].op1, totalValue + result);
            }
            if (monkeys[m].operation == "*") {
                return calculateReverse(monkeys[m].op1, totalValue / result);
            }
            if (monkeys[m].operation == "/") {
                return calculateReverse(monkeys[m].op1, totalValue * result);
            }
        }

        if (monkeys[monkeys[m].op2].isHumanDependent) {
            long long result = calculate(monkeys[m].op1);
            if (monkeys[m].operation == "+") {
                return calculateReverse(monkeys[m].op2, totalValue - result);
            }
            if (monkeys[m].operation == "-") {
                return calculateReverse(monkeys[m].op2, result - totalValue);
            }
            if (monkeys[m].operation == "*") {
                return calculateReverse(monkeys[m].op2, totalValue / result);
            }
            if (monkeys[m].operation == "/") {
                return calculateReverse(monkeys[m].op2, result / totalValue);
            }
        }

        return 0;
    }



    long long part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        monkeys.clear();

        for (const auto& l : lines) {
            std::vector<std::string> t = utils::splitString(l, " :");
            if (t.size() > 2) {
                monkeys.insert({t[0], {t[1], t[3], t[2], 0, false, false}});
            }
            else {
                monkeys.insert({t[0], {"", "", "", std::stoll(t[1]), true, false}});
            }
        }

        return calculate("root");
    }

    long long part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        monkeys.clear();

        for (const auto& l : lines) {
            std::vector<std::string> t = utils::splitString(l, " :");
            if (t.size() > 2) {
                monkeys.insert({t[0], {t[1], t[3], t[2], 0, false, false}});
            }
            else {
                monkeys.insert({t[0], {"", "", "", std::stoll(t[1]), true, false}});
            }
        }

        calculate("root");

        if (monkeys[monkeys["root"].op1].isHumanDependent) {
            return calculateReverse(monkeys["root"].op1, monkeys[monkeys["root"].op2].val);
        }
        else {
            return calculateReverse(monkeys["root"].op2, monkeys[monkeys["root"].op1].val);
        }
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2022_day21::part_1("../2022/day21/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2022_day21::part_2("../2022/day21/input.in") << std::endl;

    return 0;
}
#endif
