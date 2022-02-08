#include "file.h"
#include "utilities.h"
#include <iostream>
#include <map>
#include <set>
#include <algorithm>

namespace aoc2020_day21 {
    unsigned long long part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::map<std::string, int> foods;
        std::vector<std::vector<int>> ingredients;
        std::vector<std::vector<int>> allergens;
        int index = 0;
        for (const auto &line : input) {
            std::vector<std::string> words = utils::splitString(line, " ,()");
            ingredients.emplace_back();
            allergens.emplace_back();
            int i = 0;
            while (words[i] != "contains") {
                if (foods.find(words[i]) == foods.end()) {
                    foods.insert({words[i], index});
                    index++;
                }
                ingredients.back().push_back(foods[words[i]]);
                i++;
            }
            i++;
            while (i < words.size()) {
                if (foods.find(words[i]) == foods.end()) {
                    foods.insert({words[i], index});
                    index++;
                }
                allergens.back().emplace_back(foods[words[i]]);
                i++;
            }
        }
        // how many different allergens do we have
        std::set<int> totalAllergens;
        for (const auto &line : allergens) {
            for (const auto &a : line) {
                totalAllergens.insert(a);
            }
        }

        std::vector<int> proccesedAllergens;
        while (proccesedAllergens.size() < totalAllergens.size()) {
            for (const auto &line : allergens) {
                for (const auto &a : line) {
                    if (std::find(proccesedAllergens.begin(), proccesedAllergens.end(), a) ==
                        proccesedAllergens.end()) {
                        std::vector<int> indexs;
                        for (int i = 0; i < allergens.size(); ++i) {
                            if (std::find(allergens[i].begin(), allergens[i].end(), a) != allergens[i].end()) {
                                indexs.push_back(i);
                            }
                        }
                        std::vector<int> possibleIngredients = ingredients[indexs[0]];
                        for (int i = 1; i < indexs.size(); ++i) {
                            std::vector<int> result;
                            std::vector<int> b = ingredients[indexs[i]];
                            std::sort(b.begin(), b.end());
                            std::sort(possibleIngredients.begin(), possibleIngredients.end());
                            std::set_intersection(b.begin(), b.end(), possibleIngredients.begin(),
                                                  possibleIngredients.end(),
                                                  std::back_inserter(result));
                            possibleIngredients = result;
                        }

                        if (possibleIngredients.size() == 1) {
                            proccesedAllergens.push_back(a);
                            for (int i = 0; i < ingredients.size(); ++i) {
                                ingredients[i].erase(
                                        std::remove(ingredients[i].begin(), ingredients[i].end(),
                                                    possibleIngredients[0]),
                                        ingredients[i].end());
                            }
                        }
                    }
                }
            }
        }

        int sum = 0;
        for (const auto &ingredient : ingredients) {
            sum += ingredient.size();
        }
        return sum;
    }

    std::string part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::map<std::string, int> foods;
        std::map<int, std::string> revertFoods;
        std::vector<std::vector<int>> ingredients;
        std::vector<std::vector<int>> allergens;
        int index = 0;
        for (const auto &line : input) {
            std::vector<std::string> words = utils::splitString(line, " ,()");
            ingredients.emplace_back();
            allergens.emplace_back();
            int i = 0;
            while (words[i] != "contains") {
                if (foods.find(words[i]) == foods.end()) {
                    foods.insert({words[i], index});
                    revertFoods.insert({index, words[i]});
                    index++;
                }
                ingredients.back().emplace_back(foods[words[i]]);
                i++;
            }
            i++;
            while (i < words.size()) {
                if (foods.find(words[i]) == foods.end()) {
                    foods.insert({words[i], index});
                    revertFoods.insert({index, words[i]});
                    index++;
                }
                allergens.back().emplace_back(foods[words[i]]);
                i++;
            }
        }

        // how many different allergens do we have
        std::set<int> totalAllergens;
        for (const auto &line : allergens) {
            for (const auto &a : line) {
                totalAllergens.insert(a);
            }
        }

        std::vector<int> proccesedAllergens;
        std::vector<std::pair<std::string, std::string>> inertIngredients;
        while (proccesedAllergens.size() < totalAllergens.size()) {
            for (const auto &line : allergens) {
                for (const auto &a : line) {
                    if (std::find(proccesedAllergens.begin(), proccesedAllergens.end(), a) ==
                        proccesedAllergens.end()) {
                        std::vector<int> indexs;
                        for (int i = 0; i < allergens.size(); ++i) {
                            if (std::find(allergens[i].begin(), allergens[i].end(), a) != allergens[i].end()) {
                                indexs.push_back(i);
                            }
                        }
                        std::vector<int> possibleIngredients = ingredients[indexs[0]];
                        for (int i = 1; i < indexs.size(); ++i) {
                            std::vector<int> result;
                            std::vector<int> b = ingredients[indexs[i]];
                            std::sort(b.begin(), b.end());
                            std::sort(possibleIngredients.begin(), possibleIngredients.end());
                            std::set_intersection(b.begin(), b.end(), possibleIngredients.begin(),
                                                  possibleIngredients.end(),
                                                  std::back_inserter(result));
                            possibleIngredients = result;
                        }

                        if (possibleIngredients.size() == 1) {
                            proccesedAllergens.push_back(a);
                            inertIngredients.emplace_back(revertFoods[possibleIngredients[0]], revertFoods[a]);
                            for (int i = 0; i < ingredients.size(); ++i) {
                                ingredients[i].erase(
                                        std::remove(ingredients[i].begin(), ingredients[i].end(),
                                                    possibleIngredients[0]),
                                        ingredients[i].end());
                            }
                        }
                    }
                }
            }
        }

        std::sort(inertIngredients.begin(), inertIngredients.end(), [](const auto &a, const auto &b) {
            return a.second < b.second;
        });
        std::string result;
        for (const auto &p : inertIngredients) {
            result.append(p.first + ",");
        }
        return result.substr(0, result.size() - 1);
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2020_day21::part_1("../2020/day21/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2020_day21::part_2("../2020/day21/input.in") << std::endl;

    return 0;
}
#endif
