#include "file.h"
#include "utilities.h"
#include <vector>
#include <iostream>
#include <numeric>
#include <limits>

namespace aoc2015_day15 {
    struct ingredient {
        ingredient(int a, int b, int c, int d, int e) {
            capacity = a;
            durability = b;
            flavor = c;
            texture = d;
            calories = e;
        }
        int capacity;
        int durability;
        int flavor;
        int texture;
        int calories;
    };

    int part_1(std::string_view path, int teaspoons) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<ingredient> ingredients;
        for (const auto& line : input) {
            std::vector<std::string> tokens = utils::splitString(line, " ,");
            ingredients.emplace_back(std::stoi(tokens[2]),
                                     std::stoi(tokens[4]),
                                     std::stoi(tokens[6]),
                                     std::stoi(tokens[8]),
                                     std::stoi(tokens[10]));
        }

        int maxSum = std::numeric_limits<int>::min();

        std::vector<int> teaspoon(input.size() - 1, 0);
        while (teaspoon[0] <= teaspoons) {
            int sumCapacity = 0, sumDurability = 0, sumFlavor = 0, sumTexture = 0;
            for (int i = 0; i < input.size() - 1; ++i) {
                sumCapacity += ingredients[i].capacity * teaspoon[i];
                sumDurability += ingredients[i].durability * teaspoon[i];
                sumFlavor += ingredients[i].flavor * teaspoon[i];
                sumTexture += ingredients[i].texture * teaspoon[i];
            }
            int sum = std::accumulate(teaspoon.begin(), teaspoon.end(), 0);
            sumCapacity = std::max(0, sumCapacity + (teaspoons - sum) * ingredients.back().capacity);
            sumDurability = std::max(0, sumDurability + (teaspoons - sum) * ingredients.back().durability);
            sumFlavor = std::max(0, sumFlavor + (teaspoons - sum) * ingredients.back().flavor);
            sumTexture = std::max(0, sumTexture + (teaspoons - sum) * ingredients.back().texture);

            maxSum = std::max(maxSum, sumCapacity * sumDurability * sumFlavor * sumTexture);
            teaspoon.back()++;
            auto it = teaspoon.end() - 1;
            while (it != teaspoon.begin() && *it > teaspoons) {
                *it = 0;
                it = std::prev(it);
                (*it)++;
            }
        }

        return maxSum;
    }

    int part_2(std::string_view path, int teaspoons, int calories) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<ingredient> ingredients;
        for (const auto& line : input) {
            std::vector<std::string> tokens = utils::splitString(line, " ,");
            ingredients.emplace_back(std::stoi(tokens[2]),
                                     std::stoi(tokens[4]),
                                     std::stoi(tokens[6]),
                                     std::stoi(tokens[8]),
                                     std::stoi(tokens[10]));
        }

        int maxSum = std::numeric_limits<int>::min();

        std::vector<int> teaspoon(input.size() - 1, 0);
        while (teaspoon[0] <= teaspoons) {
            int sumCapacity = 0, sumDurability = 0, sumFlavor = 0, sumTexture = 0, sumCalories = 0;
            for (int i = 0; i < teaspoon.size(); ++i) {
                sumCapacity += ingredients[i].capacity * teaspoon[i];
                sumDurability += ingredients[i].durability * teaspoon[i];
                sumFlavor += ingredients[i].flavor * teaspoon[i];
                sumTexture += ingredients[i].texture * teaspoon[i];
                sumCalories += ingredients[i].calories * teaspoon[i];
            }
            int sum = std::accumulate(teaspoon.begin(), teaspoon.end(), 0);
            sumCapacity = std::max(0, sumCapacity + (teaspoons - sum) * ingredients.back().capacity);
            sumDurability = std::max(0, sumDurability + (teaspoons - sum) * ingredients.back().durability);
            sumFlavor = std::max(0, sumFlavor + (teaspoons - sum) * ingredients.back().flavor);
            sumTexture = std::max(0, sumTexture + (teaspoons - sum) * ingredients.back().texture);
            sumCalories = std::max(0, sumCalories + (teaspoons - sum) * ingredients.back().calories);

            if (sumCalories == calories) {
                maxSum = std::max(maxSum, sumCapacity * sumDurability * sumFlavor * sumTexture);
            }
            teaspoon.back()++;
            auto it = teaspoon.end() - 1;
            while (it != teaspoon.begin() && *it > teaspoons) {
                *it = 0;
                it = std::prev(it);
                (*it)++;
            }
        }

        return maxSum;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2015_day15::part_1("../2015/day15/input.in", 100) << std::endl;
    std::cout << "Part 1: " << aoc2015_day15::part_2("../2015/day15/input.in", 100, 500) << std::endl;

    return 0;
}
#endif
