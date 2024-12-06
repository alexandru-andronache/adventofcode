#include "file.h"
#include "utilities.h"
#include <iostream>

namespace aoc2024_day06 {
    int part_1(std::string_view path) {
        int sol = 0;

        std::vector<std::vector<char>> map = file::readFileAsMapChar(path);
        std::vector<std::vector<int>> v;

        int x = 0, y = 0;
        for (int i = 0; i < map.size(); ++i)
        {
            std::vector<int> p;
            for (int j = 0; j < map[0].size(); ++j)
            {
                p.push_back(0);
                if (map[i][j] == '^')
                {
                    x = i, y = j;
                }
            }
            v.push_back(p);
        }

        std::vector<utils::point> visited;
        visited.emplace_back(x, y);

        std::vector<utils::point> points;
        points.emplace_back(x, y);
        utils::point dir = { -1, 0 };
        bool found = false;
        map[x][y] = '.';

        while (!found) {
            if (x + dir.x >= 0 && x + dir.x < map.size() && y + dir.y >= 0 && y + dir.y < map[0].size() && map[x + dir.x][y + dir.y] == '.')
            {
                x += dir.x;
                y += dir.y;
                v[x][y] = 1;
            }
            else if (x + dir.x >= 0 && x + dir.x < map.size() && y + dir.y >= 0 && y + dir.y < map[0].size() && map[x + dir.x][y + dir.y] == '#')
            {
                if (dir.x == -1 && dir.y == 0)
                {
                    dir.x = 0, dir.y = 1;
                }
                else if (dir.x == 0 && dir.y == 1)
                {
                    dir.x = 1, dir.y = 0;
                }
                else if (dir.x == 1 && dir.y == 0)
                {
                    dir.x = 0, dir.y = -1;
                }
                else if (dir.x == 0 && dir.y == -1)
                {
                    dir.x = -1, dir.y = 0;
                }
            }
            else
            {
                found = true;
            }
        }


        for (int i = 0; i < v.size(); ++i)
        {
            for (int j = 0; j < v[0].size(); ++j)
            {
                if (v[i][j] == 1)
                {
                    sol++;
                }
            }
        }

        return sol;
    }

    int part_2(std::string_view path) {
        int sol = 0;

        std::vector<std::vector<char>> map = file::readFileAsMapChar(path);
        std::vector<std::vector<char>> originalMap = map;
        std::vector<std::vector<utils::point>> v;
        std::vector<std::vector<utils::point>> origialV;

        int x = 0, y = 0;
        for (int i = 0; i < map.size(); ++i)
        {
            std::vector<utils::point> p;
            for (int j = 0; j < map[0].size(); ++j)
            {
                p.emplace_back(0, 0);
                if (map[i][j] == '^')
                {
                    x = i, y = j;
                }
            }
            v.push_back(p);
        }
        origialV = v;
        int startX = x, startY = y;
        for (int k = 0; k < map.size(); ++k)
        {
            for (int j = 0; j < map[0].size(); ++j)
            {
                map = originalMap;
                v = origialV;
                if (map[k][j] == '.')
                {
                    map[k][j] = '#';
                    map[startX][startY] = '.';
                    utils::point dir = { -1, 0 };
                    int xx = startX, yy = startY;
                    while (v[xx][yy].x != dir.x || v[xx][yy].y != dir.y)
                    {
                        if (xx + dir.x >= 0 && xx + dir.x < map.size() && yy + dir.y >= 0 && yy + dir.y < map[0].size() && map[xx + dir.x][yy + dir.y] == '.')
                        {
                            v[xx][yy] = dir;
                            xx += dir.x;
                            yy += dir.y;
                        }
                        else if (xx + dir.x >= 0 && xx + dir.x < map.size() && yy + dir.y >= 0 && yy + dir.y < map[0].size() && map[xx + dir.x][yy + dir.y] == '#')
                        {
                            if (dir.x == -1 && dir.y == 0)
                            {
                                dir.x = 0, dir.y = 1;
                            }
                            else if (dir.x == 0 && dir.y == 1)
                            {
                                dir.x = 1, dir.y = 0;
                            }
                            else if (dir.x == 1 && dir.y == 0)
                            {
                                dir.x = 0, dir.y = -1;
                            }
                            else if (dir.x == 0 && dir.y == -1)
                            {
                                dir.x = -1, dir.y = 0;
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                    if (v[xx][yy].x == dir.x && v[xx][yy].y == dir.y)
                    {
                        sol++;
                    }
                }
            }
        }


        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2024_day06::part_1("../2024/day06/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2024_day06::part_2("../2024/day06/input.in") << std::endl;

    return 0;
}
#endif
