#include "file.h"
#include "utilities.h"
#include "dir.h"
#include "point.h"
#include <iostream>
#include <numeric>
#include <set>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2024_day15 {
    int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::vector<char>> map;
        int index = 0;
        while (!input[index].empty()) {
            std::vector<char> row;
            for (char c : input[index]) {
                row.push_back(c);
            }
            map.push_back(row);
            index++;
        }
        index++;
        utils::point r = utils::findValue(map, '@');
        point::point robot{r.x, r.y};
        for (int i = index; i < input.size(); ++i) {
            for (const auto& c : input[i]) {
                point::point newPosition = robot + direction::getDirection(c);
                if (map[newPosition.getX()][newPosition.getY()] == '.') {
                    std::swap(map[robot.getX()][robot.getY()], map[newPosition.getX()][newPosition.getY()]);
                    robot = newPosition;
                }
                else if (map[newPosition.getX()][newPosition.getY()] == 'O') {
                    point::point p = newPosition;
                    while (map[p.getX()][p.getY()] == 'O') {
                        p += direction::getDirection(c);
                    }
                    if (map[p.getX()][p.getY()] == '.') {
                        std::swap(map[p.getX()][p.getY()], map[newPosition.getX()][newPosition.getY()]);
                        map[robot.getX()][robot.getY()] = '.';
                        robot += direction::getDirection(c);
                    }
                }
            }
        }

        int score = 0;
        for (int i = 0; i < map.size(); ++i) {
            for (int j = 0; j < map[0].size(); ++j) {
                score += (i * 100 + j) * (map[i][j] == 'O');
            }
        }

        return score;
    }

    int part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::vector<char>> map;
        int index = 0;
        while (!input[index].empty()) {
            std::vector<char> row;
            for (char c : input[index]) {
                if (c == '#') {
                    row.insert(row.end(), {'#', '#'});
                }
                else if (c == 'O') {
                    row.insert(row.end(), {'[', ']'});
                }
                else if (c == '.') {
                    row.insert(row.end(), {'.', '.'});
                }
                else if (c == '@') {
                    row.insert(row.end(), {'@', '.'});
                }
            }
            map.push_back(row);
            index++;
        }
        index++;
        utils::point r = utils::findValue(map, '@');
        point::point robot = {r.x, r.y};
        for (int i = index; i < input.size(); ++i) {
            for (const auto& c : input[i]) {
                point::point newPosition = robot + direction::getDirection(c);
                if (map[newPosition.getX()][newPosition.getY()] == '.') {
                    std::swap(map[robot.getX()][robot.getY()], map[newPosition.getX()][newPosition.getY()]);
                    robot = newPosition;
                }
                else if (map[newPosition.getX()][newPosition.getY()] == '[' || map[newPosition.getX()][newPosition.getY()] == ']') {
                    std::vector<std::vector<char>> tempMap = map;
                    point::point oldPosition = robot;
                    if (direction::getDirection(c).isHorizontal()) {
                        bool valid = true;
                        while (map[oldPosition.getX()][oldPosition.getY()] != '.' && map[oldPosition.getX()][oldPosition.getY()] != '#') {
                            if (tempMap[newPosition.getX()][newPosition.getY()] == '#') {
                                valid = false;
                            }
                            tempMap[newPosition.getX()][newPosition.getY()] = map[oldPosition.getX()][oldPosition.getY()];
                            newPosition += direction::getDirection(c);
                            oldPosition += direction::getDirection(c);
                        }
                        if (valid) {
                            tempMap[robot.getX()][robot.getY()] = '.';
                            robot = robot + direction::getDirection(c);
                            map = tempMap;
                        }
                    }
                    else {
                        std::vector<point::point> points{newPosition};
                        std::set<point::point> visited;
                        visited.insert(newPosition);
                        if (map[newPosition.getX()][newPosition.getY()] == '[') {
                            points.emplace_back(newPosition.getX(), newPosition.getY() + 1);
                            visited.insert({newPosition.getX(), newPosition.getY() + 1});
                        }
                        else {
                            points.emplace_back(newPosition.getX(), newPosition.getY() - 1);
                            visited.insert({newPosition.getX(), newPosition.getY() - 1});
                        }
                        while (!points.empty()) {
                            std::vector<point::point> newPoints;
                            for (const auto& p : points) {
                                point::point newP = p + direction::getDirection(c);
                                if (map[newP.getX()][newP.getY()] == '[' || map[newP.getX()][newP.getY()] == ']') {
                                    newPoints.emplace_back(newP.getX(), newP.getY());
                                    if (map[newP.getX()][newP.getY()] == '[') {
                                        newPoints.emplace_back(newP.getX(), newP.getY() + 1);
                                    }
                                    else {
                                        newPoints.emplace_back(newP.getX(), newP.getY() - 1);
                                    }
                                }
                            }
                            points = newPoints;
                            for (const auto& p : points) {
                                visited.insert(p);
                            }
                        }
                        visited.insert(robot);
                        bool valid = true;
                        std::set<point::point> updated;
                        for (const auto& v : visited) {
                            if (map[v.getX() + direction::getDirection(c).getX()][v.getY() + direction::getDirection(c).getY()] != '#') {
                                tempMap[v.getX() + direction::getDirection(c).getX()][v.getY() + direction::getDirection(c).getY()] = map[v.getX()][v.getY()];
                                updated.insert({v.getX() + direction::getDirection(c).getX(), v.getY() + direction::getDirection(c).getY()});
                            }
                            else {
                                valid = false;
                            }
                        }
                        for (const auto& v : visited) {
                            if (!updated.contains(v)) {
                                tempMap[v.getX()][v.getY()] = '.';
                            }
                        }
                        if (valid) {
                            map = tempMap;
                            robot = robot + direction::getDirection(c);
                        }
                    }
                }
            }
        }

        int score = 0;
        for (int i = 0; i < map.size(); ++i) {
            for (int j = 0; j < map[0].size(); ++j) {
                score += (i * 100 + j) * (map[i][j] == '[');
            }
        }

        return score;
    }
}

#ifdef TESTING
namespace aoc2024_day15 {
    TEST(Tests2024Day15, part_1_small_test) {
        ASSERT_EQ(part_1("../2024/day15/input_test_small.in"), 2028);
    }

    TEST(Tests2024Day15, part_1_test) {
        ASSERT_EQ(part_1("../2024/day15/input_test.in"), 10092);
    }

    TEST(Tests2024Day15, part_1_real_test) {
        ASSERT_EQ(part_1("../2024/day15/input.in"), 1497888);
    }

    TEST(Tests2024Day15, part_2_small_test) {
        ASSERT_EQ(part_2("../2024/day15/input_test_small_part_2.in"), 618);
    }

    TEST(Tests2024Day15, part_2_test) {
        ASSERT_EQ(part_2("../2024/day15/input_test.in"), 9021);
    }

    TEST(Tests2024Day15, part_2_real_test) {
        ASSERT_EQ(part_2("../2024/day15/input.in"), 1522420);
    }
}
#endif

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2024_day15::part_1("../2024/day15/input.in") << std::endl;
    std::cout << "Part 1: " << aoc2024_day15::part_2("../2024/day15/input.in") << std::endl;

    return 0;
}
#endif
