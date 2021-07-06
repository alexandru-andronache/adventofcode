#include "file.h"
#include "utilities.h"
#include "math_util.h"
#include <iostream>
#include <vector>
#include <cmath>

namespace aoc2019_day10 {
    struct point {
        int x;
        int y;
        double atan;
    };

    void calculate(int startX, int startY, const std::vector<std::vector<int>> board, std::vector<point>& asteroids) {
        std::vector<std::vector<int>> b = board;

        for (int i = startX; i < b.size(); ++i) {
            for (int j = startY; j < b[0].size(); ++j) {
                if (i != startX || j != startY) {
                    if (b[i][j] == 1) {
                        asteroids.push_back({i, j, 0.f});
                        for (int k = startX; k < b.size(); ++k) {
                            for (int l = startY; l < b[0].size(); ++l) {
                                if (math::coliniar(startX, startY, i, j, k, l)) {
                                    b[k][l] = 2;
                                }
                            }
                        }
                    }
                }
            }
        }

        for (int i = startX; i >= 0; --i) {
            for (int j = startY; j >= 0; --j) {
                if (i != startX || j != startY) {
                    if (b[i][j] == 1) {
                        asteroids.push_back({i, j, 0});
                        for (int k = startX; k >= 0; --k)  {
                            for (int l = startY; l >= 0; --l) {
                                if (math::coliniar(startX, startY, i, j, k, l)) {
                                    b[k][l] = 2;
                                }
                            }
                        }
                    }
                }
            }
        }

        for (int i = startX - 1; i >= 0; --i) {
            for (int j = startY + 1; j < b[0].size(); ++j) {
                if (i != startX || j != startY) {
                    if (b[i][j] == 1) {
                        asteroids.push_back({i, j, 0});
                        for (int k = startX - 1; k >= 0; --k)  {
                            for (int l = startY + 1; l < b[0].size(); ++l) {
                                if (math::coliniar(startX, startY, i, j, k, l)) {
                                    b[k][l] = 2;
                                }
                            }
                        }
                    }
                }
            }
        }

        for (int i = startX + 1; i < b.size(); ++i) {
            for (int j = startY - 1; j >= 0; --j) {
                if (i != startX || j != startY) {
                    if (b[i][j] == 1) {
                        asteroids.push_back({i, j, 0});
                        for (int k = startX + 1; k < b.size(); ++k)  {
                            for (int l = startY - 1; l >= 0; --l) {
                                if (math::coliniar(startX, startY, i, j, k, l)) {
                                    b[k][l] = 2;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::vector<int>> a(input.size(), std::vector<int>(input[0].size(), 0));

        for (int i = 0; i < input.size(); ++i) {
            for (int j = 0; j < input[0].size(); ++j) {
                a[i][j] = input[i][j] == '#';
            }
        }

        size_t min = 0;
        for (int i = 0; i < a.size(); ++i) {
            for (int j = 0; j < a[0].size(); ++j) {
                if (a[i][j] == 1) {
                    std::vector<point> v;
                    calculate(i, j, a, v);
                    min = std::max(min, v.size());
                }
            }
        }

        return min;
    }

    int part_2(std::string_view path, int index = 200) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::vector<int>> a(input.size(), std::vector<int>(input[0].size(), 0));

        for (int i = 0; i < input.size(); ++i) {
            for (int j = 0; j < input[0].size(); ++j) {
                a[i][j] = input[i][j] == '#';
            }
        }

        int X = 0, Y = 0;
        std::vector<point> asteroids;
        for (int i = 0; i < a.size(); ++i) {
            for (int j = 0; j < a[0].size(); ++j) {
                if (a[i][j] == 1) {
                    std::vector<point> v;
                    calculate(i, j, a, v);
                    if (v.size() > asteroids.size()) {
                        asteroids.clear();
                        asteroids = v;
                        X = i;
                        Y = j;
                    }
                }
            }
        }

        for (auto& i : asteroids) {
            i.atan = std::atan2( i.y - Y, i.x - X );
        }

        std::sort(asteroids.begin(), asteroids.end(), [](auto x, auto y) {
            return x.atan > y.atan;
        });

        return asteroids[index - 1].y * 100 + asteroids[index - 1].x;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2019_day10::part_1("../2019/day10/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2019_day10::part_2("../2019/day10/input.in") << std::endl;

    return 0;
}
#endif
