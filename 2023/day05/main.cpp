#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2023_day05 {
    unsigned long long part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::string> seed = utils::splitString(input[0], " ");
        std::vector<unsigned long long> seeds;
        for (int i = 1; i < seed.size(); ++i) {
            seeds.push_back(std::stoull(seed[i]));
        }
        int index = 3;
        while (index < input.size()) {
            std::vector<std::pair<unsigned long long, unsigned long long>> pairs1;
            std::vector<std::pair<unsigned long long, unsigned long long>> pairs2;
            while (index < input.size()  && !input[index].empty()) {
                std::vector<std::string> t = utils::splitString(input[index], " ");
                pairs2.emplace_back(std::stoull(t[0]), std::stoull(t[0]) + std::stoull(t[2]) - 1);
                pairs1.emplace_back(std::stoull(t[1]), std::stoull(t[1]) + std::stoull(t[2]) - 1);
                index++;
            }
            for (auto& s : seeds) {
                for (int j = 0; j < pairs1.size(); ++j) {
                    if (s >= pairs1[j].first && s <= pairs1[j].second) {
                        s += pairs2[j].first - pairs1[j].first;
                        break;
                    }
                }
            }
            index += 2;
        }

        return *std::min_element(seeds.begin(), seeds.end());
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::string> seed = utils::splitString(input[0], " ");
        std::vector<std::pair<unsigned long long, unsigned long long>> seeds;
        for (int i = 1; i < seed.size(); i += 2) {
            seeds.emplace_back(std::stoull(seed[i]), std::stoull(seed[i]) + std::stoull(seed[i + 1]));
        }
        int index = 3;
        while (index < input.size()) {
            std::vector<std::pair<unsigned long long, unsigned long long>> pairs1;
            std::vector<std::pair<unsigned long long, unsigned long long>> pairs2;
            while (index < input.size()  && !input[index].empty()) {
                std::vector<std::string> t = utils::splitString(input[index], " ");
                pairs2.emplace_back(std::stoull(t[0]), std::stoull(t[0]) + std::stoull(t[2]) - 1);
                pairs1.emplace_back(std::stoull(t[1]), std::stoull(t[1]) + std::stoull(t[2]) - 1);
                index++;
            }
            std::vector<std::pair<unsigned long long, unsigned long long>> newSeeds;
            int i = 0;
            while (i < seeds.size()) {
                bool found = false;
                for (int j = 0; j < pairs1.size() && !found; ++j) {
                    if (seeds[i].first >= pairs1[j].first && seeds[i].second <= pairs1[j].second) {
                        newSeeds.emplace_back(seeds[i].first + pairs2[j].first - pairs1[j].first,
                                              seeds[i].second + pairs2[j].first - pairs1[j].first);
                        found = true;
                    }
                    else if (seeds[i].first < pairs1[j].first && seeds[i].second >= pairs1[j].first) {
                        newSeeds.emplace_back(pairs1[j].first + pairs2[j].first - pairs1[j].first,
                                              seeds[i].second + pairs2[j].first - pairs1[j].first);
                        seeds.emplace_back(seeds[i].first, pairs1[j].first - 1);
                        found = true;
                    }
                    else if (seeds[i].first <= pairs1[j].second && seeds[i].second > pairs1[j].second) {
                        newSeeds.emplace_back(seeds[i].first + pairs2[j].first - pairs1[j].first,
                                              pairs1[j].second + pairs2[j].first - pairs1[j].first);
                        seeds.emplace_back(pairs1[j].second + 1, seeds[i].second);
                        found = true;
                    }
                    else if (seeds[i].first < pairs1[j].first && seeds[i].second > pairs1[j].second) {
                        newSeeds.emplace_back(pairs1[j].first + pairs2[j].first - pairs1[j].first,
                                              pairs1[j].second + pairs2[j].first - pairs1[j].first);
                        seeds.emplace_back(seeds[i].first, pairs1[j].first - 1);
                        seeds.emplace_back(pairs1[j].second + 1, seeds[i].second);
                        found = true;
                    }
                }
                if (!found) {
                    newSeeds.emplace_back(seeds[i]);
                }
                i++;
            }
            index += 2;
            seeds = newSeeds;
        }

        return std::min_element(seeds.begin(), seeds.end(), [](const auto& a, const auto&b) {
            return a.first < b.first;
        })->first;
    }
}

#ifdef TESTING
TEST(Tests2023Day05, part_1_test) {
    ASSERT_EQ(aoc2023_day05::part_1("../2023/day05/input_test.in"), 35);
}

TEST(Tests2023Day05, part_1_real_test) {
    ASSERT_EQ(aoc2023_day05::part_1("../2023/day05/input.in"), 157211394);
}

TEST(Tests2023Day05, part_2_test) {
    ASSERT_EQ(aoc2023_day05::part_2("../2023/day05/input_test.in"), 46);
}

TEST(Tests2023Day05, part_2_real_test) {
    ASSERT_EQ(aoc2023_day05::part_2("../2023/day05/input.in"), 50855035);
}
#endif

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2023_day05::part_1("../2023/day05/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2023_day05::part_2("../2023/day05/input.in") << std::endl;

    return 0;
}
#endif
