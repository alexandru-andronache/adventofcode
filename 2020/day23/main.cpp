#include "file.h"
#include "utilities.h"
#include <iostream>
#include <array>
#include <list>
#include <algorithm>

namespace aoc2020_day23 {
    int part_1(int N, int repetitions = 100, int maxNumber = 9) {
        std::list<int> numbers;
        std::vector<std::list<int>::iterator> indexes(maxNumber + 1);
        while (N) {
            numbers.push_front(N % 10);
            indexes[N % 10] = numbers.begin();
            N /= 10;
        }
        for (int i = 9 + 1; i <= maxNumber; ++i) {
            numbers.push_back(i);
            indexes[i] = std::prev(numbers.end());
        }
        auto currentIndex = numbers.begin();
        for (int step = 0; step < repetitions; ++step) {
            int currentNumber = *currentIndex;
            std::array<int, 3> removeItems{};
            auto nextItems = currentIndex;
            for (int i = 0; i < 3; ++i) {
                std::advance(nextItems, 1);
                if (nextItems == numbers.end()) {
                    nextItems = numbers.begin();
                }
                removeItems[i] = *nextItems;
            }
            for (int i = 0; i < 3; ++i) {
                auto deleteIndex = currentIndex;
                std::advance(deleteIndex, 1);
                if (deleteIndex == numbers.end()) {
                    deleteIndex = numbers.begin();
                }
                numbers.erase(deleteIndex);
            }
            int destinationNumber = currentNumber - 1;
            if (destinationNumber == 0) {
                destinationNumber = maxNumber;
            }
            while (std::find(removeItems.begin(), removeItems.end(), destinationNumber) != removeItems.end()) {
                destinationNumber--;
                if (destinationNumber == 0) destinationNumber = maxNumber;
            }
            auto destinationIndex = indexes[destinationNumber];
            for (int i = 0; i < 3; ++i) {
                indexes[removeItems[i]] = numbers.insert(std::next(destinationIndex), removeItems[i]);
                std::advance(destinationIndex, 1);
            }
            std::advance(currentIndex, 1);
            if (currentIndex == numbers.end()) {
                currentIndex = numbers.begin();
            }
        }

        auto it = indexes[1];
        std::advance(it, 1);
        int sol = 0;
        for (auto j = it; j != numbers.end(); ++j) {
            sol = sol * 10 + (*j);
        }
        for (auto j = numbers.begin(); j != indexes[1]; ++j) {
            sol = sol * 10 + (*j);
        }

        return sol;
    }

    unsigned long long part_2(int N, int repetitions = 10000000, int maxNumber = 1000000) {
        std::list<unsigned long long> numbers;
        std::vector<std::list<unsigned long long>::iterator> indexes(maxNumber + 1);
        while (N) {
            numbers.push_front(N % 10);
            indexes[N % 10] = numbers.begin();
            N /= 10;
        }
        for (int i = 9 + 1; i <= maxNumber; ++i) {
            numbers.push_back(i);
            indexes[i] = std::prev(numbers.end());
        }
        auto currentIndex = numbers.begin();
        for (int step = 0; step < repetitions; ++step) {
            int currentNumber = *currentIndex;
            std::array<int, 3> removeItems{};
            auto nextItems = currentIndex;
            for (int i = 0; i < 3; ++i) {
                std::advance(nextItems, 1);
                if (nextItems == numbers.end()) {
                    nextItems = numbers.begin();
                }
                removeItems[i] = *nextItems;
            }
            for (int i = 0; i < 3; ++i) {
                auto deleteIndex = currentIndex;
                std::advance(deleteIndex, 1);
                if (deleteIndex == numbers.end()) {
                    deleteIndex = numbers.begin();
                }
                numbers.erase(deleteIndex);
            }
            int destinationNumber = currentNumber - 1;
            if (destinationNumber == 0) {
                destinationNumber = maxNumber;
            }
            while (std::find(removeItems.begin(), removeItems.end(), destinationNumber) != removeItems.end()) {
                destinationNumber--;
                if (destinationNumber == 0) destinationNumber = maxNumber;
            }
            auto destinationIndex = indexes[destinationNumber];
            for (int i = 0; i < 3; ++i) {
                indexes[removeItems[i]] = numbers.insert(std::next(destinationIndex), removeItems[i]);
                std::advance(destinationIndex, 1);
            }
            std::advance(currentIndex, 1);
            if (currentIndex == numbers.end()) {
                currentIndex = numbers.begin();
            }
        }

        return (*(std::next(indexes[1]))) * (*(std::next(indexes[1], 2)));
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2020_day23::part_1(653427918) << std::endl;
    std::cout << "Part 2: " << aoc2020_day23::part_2(653427918) << std::endl;

    return 0;
}
#endif
