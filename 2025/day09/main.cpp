#include "file.h"
#include "utilities.h"
#include "types.h"
#include <vector>

#include <fmt/printf.h>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2025_day09 {
    ull part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        ull result = 0;

        std::vector<utils::pointT<ull>> points;
        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, ",");
            points.emplace_back(std::stoull(tokens[0]), std::stoull(tokens[1]));
        }

        for (int i = 0; i < points.size(); ++i) {
            for (int j = i + 1; j < points.size(); ++j) {
                result = std::max(result, points[i].distanceX(points[j]) * points[i].distanceY(points[j]));
            }
        }

        return result;
    }

    ull part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        ull result = 0;

        std::vector<utils::pointT<ull>> points;
        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, ",");
            points.emplace_back(std::stoull(tokens[0]), std::stoull(tokens[1]));
        }

        std::vector<utils::edge<ull>> edges;
        for(int i = 0; i < points.size(); ++i) {
            edges.emplace_back(points[i], points[(i + 1) % points.size()]);
        }

        for(int i = 0; i < points.size(); ++i) {
            for(int j = i + 1; j < points.size(); ++j){
                ull x1 = std::min(points[i].x,points[j].x);
                ull x2 = std::max(points[i].x,points[j].x);
                ull y1 = std::min(points[i].y, points[j].y);
                ull y2 = std::max(points[i].y,points[j].y);

                ull area = points[i].distanceX(points[j]) * points[i].distanceY(points[j]);
                if (area <= result) {
                    continue;
                }

                bool valid = true;
                for (const auto &edge: edges) {
                    if (!valid) {
                        break;
                    }
                    if (edge.vertical()) {
                        if (edge.u.x > x1 && edge.u.x < x2) {
                            if (std::max(y1, std::min(edge.u.y, edge.v.y)) < std::min(y2, std::max(edge.u.y, edge.v.y))) {
                                valid = false;
                            }
                        }
                    }
                    else {
                        if (edge.u.y > y1 && edge.u.y < y2) {
                            if (std::max(x1, std::min(edge.u.x, edge.v.x)) < std::min(x2, std::max(edge.u.x, edge.v.x))) {
                                valid = false;
                            }
                        }
                    }
                }

                if (!valid) {
                    continue;
                }
                result = std::max(result,area);
            }
        }
        return result;
    }
}

#ifdef TESTING
    TEST(Test2025Day09, part_1_test) {
        ASSERT_EQ(aoc2025_day09::part_1("../2025/day09/input_test.in"), 50);
    }

    TEST(Test2025Day09, part_1_real_test) {
        ASSERT_EQ(aoc2025_day09::part_1("../2025/day09/input.in"), 4744899849);
    }

    TEST(Test2025Day09, part_2_test) {
        ASSERT_EQ(aoc2025_day09::part_2("../2025/day09/input_test.in"), 24);
    }

    TEST(Test2025Day09, part_2_real_test) {
        ASSERT_EQ(aoc2025_day09::part_2("../2025/day09/input.in"), 1540192500);
    }
#endif

#ifndef TESTING
int main() {
    fmt::print("Part 1: {}\n", aoc2025_day09::part_1("../2025/day09/input.in"));
    fmt::print("Part 2: {}\n", aoc2025_day09::part_2("../2025/day09/input.in"));

    return 0;
}
#endif
