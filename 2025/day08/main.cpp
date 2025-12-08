#include "file.h"
#include "utilities.h"
#include <vector>
#include <algorithm>
#include <set>
#include <iterator>

#include <fmt/printf.h>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2025_day08 {
    struct d{
        int index1, index2;
        unsigned long long dist;
    };
    unsigned long long part_1(std::string_view path, int connections = 1000) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::vector<utils::point3d> points;

        for (const auto& line : lines) {
            std::vector<int> tokens = utils::splitStringToInt(line, ",");
            points.emplace_back(tokens[0], tokens[1], tokens[2]);
        }

        std::vector<d> distances;

        for (int i = 0; i < points.size(); ++i) {
            for (int j = i + 1; j < points.size(); ++j) {
                unsigned long long dist = pow(points[i].x - points[j].x, 2) + pow(points[i].y - points[j].y, 2) + pow(points[i].z - points[j].z, 2);
                distances.emplace_back(i, j, dist);
            }
        }

        std::ranges::sort(distances, [](const auto& d1, const auto& d2) {
            return d1.dist < d2.dist;
        });

        std::vector<std::set<int>> groups;

        for (int i = 0; i < connections; ++i) {
            int index1 = distances[i].index1;
            int index2 = distances[i].index2;
            bool found = false;

            for (auto& group : groups) {
                if (group.contains(index1) || group.contains(index2)) {
                    group.insert(index1);
                    group.insert(index2);
                    found = true;
                    break;
                }
            }

            if (!found) {
                groups.push_back({index1, index2});
            }
        }

        bool notMerged = true;
        while (notMerged) {
            notMerged = false;
            std::vector<std::set<int>> newGroups;
            for (auto & group : groups) {
                bool merged = false;
                for (auto & newGroup : newGroups) {
                    std::set<int> intersection;
                    std::ranges::set_intersection(group, newGroup,
                                                  std::inserter(intersection, intersection.begin()));
                    if (!intersection.empty()) {
                        newGroup.insert(group.begin(), group.end());
                        merged = true;
                        notMerged = true;
                        break;
                    }
                }
                if (!merged) {
                    newGroups.push_back(group);
                }
            }
            groups = newGroups;
        }



        std::ranges::sort(groups, [](const auto& group1, const auto& group2) {
           return group1.size() > group2.size();
        });

        return groups[0].size() * groups[1].size() * groups[2].size();
    }

    int part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::vector<utils::point3d> points;

        for (const auto& line : lines) {
            std::vector<int> tokens = utils::splitStringToInt(line, ",");
            points.emplace_back(tokens[0], tokens[1], tokens[2]);
        }

        std::vector<d> distances;

        for (int i = 0; i < points.size(); ++i) {
            for (int j = i + 1; j < points.size(); ++j) {
                unsigned long long dist = pow(points[i].x - points[j].x, 2) + pow(points[i].y - points[j].y, 2) + pow(points[i].z - points[j].z, 2);
                distances.emplace_back(i, j, dist);
            }
        }

        std::ranges::sort(distances, [](const auto& d1, const auto& d2) {
            return d1.dist < d2.dist;
        });

        std::vector<std::set<int>> groups;
        std::vector<bool> visited(points.size(), false);
        int index = 0;

        while (true) {
            int index1 = distances[index].index1;
            int index2 = distances[index].index2;
            bool found = false;

            for (auto& group : groups) {
                if (group.contains(index1) || group.contains(index2)) {
                    group.insert(index1);
                    group.insert(index2);
                    found = true;
                    break;
                }
            }

            if (!found) {
                groups.push_back({index1, index2});
            }
            visited[index1] = true;
            visited[index2] = true;
            if (std::ranges::all_of(visited, [](const auto& v) {return v;})) {
                return points[index1].x * points[index2].x;
            }
            index++;
        }
        return 0;
    }
}

#ifdef TESTING
    TEST(Test2025Day08, part_1_test) {
        ASSERT_EQ(aoc2025_day08::part_1("../2025/day08/input_test.in", 10), 40);
    }

    TEST(Test2025Day08, part_1_real_test) {
        ASSERT_EQ(aoc2025_day08::part_1("../2025/day08/input.in", 1000), 63920);
    }

    TEST(Test2025Day08, part_2_test) {
        ASSERT_EQ(aoc2025_day08::part_2("../2025/day08/input_test.in"), 25272);
    }

    TEST(Test2025Day08, part_2_real_test) {
        ASSERT_EQ(aoc2025_day08::part_2("../2025/day08/input.in"), 1026594680);
    }
#endif

#ifndef TESTING
int main() {
    fmt::print("Part 1: {}\n", aoc2025_day08::part_1("../2025/day08/input.in"));
    fmt::print("Part 2: {}\n", aoc2025_day08::part_2("../2025/day08/input.in"));

    return 0;
}
#endif
