#include "file.h"
#include "utilities.h"
#include <iostream>

namespace aoc2020_day18 {
    unsigned long long calculateSum(std::string_view expression, int &size) {
        int i = 0;
        std::vector<unsigned long long> nr;
        bool isAddition = false;
        while (i < expression.size()) {
            if (expression[i] == ' ') {
                i++;
            } else if (expression[i] >= '0' && expression[i] <= '9') {
                if (nr.empty()) {
                    nr.push_back(expression[i] - '0');
                } else {
                    nr.back() = isAddition ? nr.back() + (expression[i] - '0') : nr.back() * (expression[i] - '0');
                    isAddition = false;
                }
                i++;
            } else if (expression[i] == '+') {
                isAddition = true;
                i++;
            } else if (expression[i] == '*') {
                i++;
            } else if (expression[i] == '(') {
                if (nr.empty()) {
                    nr.push_back(calculateSum(expression.substr(i + 1), size));
                } else {
                    unsigned long long x = calculateSum(expression.substr(i + 1), size);
                    nr.back() = isAddition ? nr.back() + x : nr.back() * x;
                    isAddition = false;
                }
                i = i + size + 1;
            } else if (expression[i] == ')') {
                i++;
                size = i;
                return nr.back();
            }
        }
        return nr.back();
    }

    unsigned long long calculateSumPart2(std::string_view expression, int &size) {
        int i = 0;
        std::vector<unsigned long long> factors;
        bool isAddition = false;
        while (i < expression.size()) {
            if (expression[i] == ' ') {
                i++;
            } else if (expression[i] >= '0' && expression[i] <= '9') {
                if (isAddition) {
                    factors.back() = factors.back() + (expression[i] - '0');
                    isAddition = false;
                } else {
                    factors.push_back(expression[i] - '0');
                }
                i++;
            } else if (expression[i] == '+') {
                isAddition = true;
                i++;
            } else if (expression[i] == '*') {
                i++;
            } else if (expression[i] == '(') {
                unsigned long long x = calculateSumPart2(expression.substr(i + 1), size);
                if (isAddition) {
                    factors.back() = factors.back() + x;
                    isAddition = false;
                } else {
                    factors.push_back(x);
                }
                i = i + size + 1;
            } else if (expression[i] == ')') {
                i++;
                size = i;
                unsigned long long prod = 1;
                for (const auto &x : factors) {
                    prod = prod * x;
                }
                return prod;
            }
        }
        unsigned long long prod = 1;
        for (const auto &x : factors) {
            prod = prod * x;
        }
        return prod;
    }

    unsigned long long part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        unsigned long long sum = 0;
        for (const auto &line : input) {
            int size = 0;
            sum += calculateSum(line, size);
        }
        return sum;
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        unsigned long long sum = 0;
        for (const auto &line : input) {
            int size = 0;
            sum += calculateSumPart2(line, size);
        }
        return sum;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2020_day18::part_1("../2020/day18/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2020_day18::part_2("../2020/day18/input.in") << std::endl;

    return 0;
}
#endif
