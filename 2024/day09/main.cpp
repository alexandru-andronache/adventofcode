#include "file.h"
#include <iostream>
#include <utilities.h>

namespace aoc2024_day09 {
    unsigned long long part_1(std::string_view path) {
        unsigned long long sol = 0;
        std::string input = file::readFileAsString(path);
        std::vector<int> numbers;

        int index = 0;
        for (int i = 0; i < input.size(); i += 2) {
            for (int j = 0; j < input[i] - '0'; ++j) {
                numbers.push_back(index);
            }
            index++;
            for (int j = 0; j < input[i + 1] - '0'; ++j) {
                numbers.push_back(-1);
            }
        }

        int start = 0;
        for (int i = numbers.size() - 1; i >= 0; --i) {
            if (numbers[i] != -1 && start <= i) {
                while (start < numbers.size() && numbers[start] != -1) {
                    start++;
                }
                if (start <= i) {
                    std::swap(numbers[i], numbers[start]);
                }
            }
        }

        for (int i = 0; i < numbers.size(); ++i) {
            if (numbers[i] != -1) {
                sol += numbers[i] * i;
            }
        }

        return sol;
    }

    unsigned long long part_2(std::string_view path) {
        unsigned long long sol = 0;
        std::string input = file::readFileAsString(path);
        std::vector<int> numbers;

        int index = 0;
        for (int i = 0; i < input.size(); i += 2) {
            for (int j = 0; j < input[i] - '0'; ++j) {
                numbers.push_back(index);
            }
            index++;
            for (int j = 0; j < input[i + 1] - '0'; ++j) {
                numbers.push_back(-1);
            }
        }

        int i = numbers.size() - 1;
        int id = numbers.back();
        int start = 0;
        while (i >= 0) {
            start = 0;
            while (i >= 0 && numbers[i] == -1) {
                i--;
            }
            if (id < numbers[i]) {
                i--;
                continue;
            }
            id = numbers[i];
            int startI = i;
            int size = 1;
            i--;
            while (i >= 0 && numbers[i] != -1 && numbers[i + 1] == numbers[i]) {
                size++;
                i--;
            }
            int endI = i + 1;
            bool found = false;
            while (!found && start < numbers.size()) {
                int begin = 0;
                while (start < numbers.size() && numbers[start] != -1) {
                    start++;
                }
                begin = start;
                while (start < numbers.size() && numbers[start] == -1) {
                    start++;
                }
                int end = start - 1;
                if (end - begin + 1 >= size) {
                    for (int k = startI; k >= endI; --k) {
                        if (k >= begin + startI - k) {
                            std::swap(numbers[k], numbers[begin + startI - k]);
                        }
                    }
                    found = true;
                }
            }
        }

        for (int i = 0; i < numbers.size(); ++i) {
            if (numbers[i] != -1) {
                sol += numbers[i] * i;
            }
        }

        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2024_day09::part_1("../2024/day09/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2024_day09::part_2("../2024/day09/input.in") << std::endl;

    return 0;
}
#endif
