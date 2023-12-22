#include "file.h"
#include "utilities.h"
#include <iostream>
#include <queue>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2023_day22 {
    using ll = long long;

    struct edge {
        int to, dist;
    };

    struct cube {
        int x1, y1, z1, x2, y2, z2;
    };
    struct item {
        int v, d;
        bool operator<(const item &other) const {
            return d > other.d;
        }
    };

    std::vector<int> resolve(int start, const std::vector<std::vector<edge>>& adj, const std::vector<cube>& cubes) {
        std::vector<int> dist(cubes.size(), 10000);
        dist[0] = 0;

        std::priority_queue<item> pq;
        pq.push({0, 0});
        while (!pq.empty()) {
            item t = pq.top();
            pq.pop();
            if (t.d == dist[t.v]) {
                for (const auto& x: adj[t.v]) {
                    if (x.to != start && t.d + x.dist < dist[x.to]) {
                        dist[x.to] = t.d + x.dist;
                        pq.push({x.to, dist[x.to]});
                    }
                }
            }
        }
        return dist;
    }

    int solve(std::string_view path, bool part1) {
        std::vector<std::vector<std::vector<int>>> p(400, std::vector<std::vector<int>>(400, std::vector<int>(400, 0)));
        std::vector<cube> cubes = {{0, 0, 0, 1000, 1000, 0}};

        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::vector<bool>> s(input.size(), std::vector<bool>(input.size(), false));

        for (int index = 0; const auto &line : input) {
            std::vector<std::string> tokens = utils::splitString(line, ",~");

            int x1 = std::stoi(tokens[0]), y1 = std::stoi(tokens[1]), z1 = std::stoi(tokens[2]);
            int x2 = std::stoi(tokens[3]), y2 = std::stoi(tokens[4]), z2 = std::stoi(tokens[5]);
            cubes.push_back({x1, y1, z1, x2, y2, z2});
            index++;
            for (int x = x1; x <= x2; ++x) {
                for (int y = y1; y <= y2; ++y) {
                    for (int z = z1; z <= z2; ++z) {
                        p[x][y][z] = index;
                    }
                }
            }
        }

        std::vector<std::vector<edge>> adj(cubes.size());
        for (int i = 1; i < cubes.size(); ++i) {
            for (int x = cubes[i].x1; x <= cubes[i].x2; ++x) {
                for (int y = cubes[i].y1; y <= cubes[i].y2; ++y) {
                    int zb = std::min(cubes[i].z1, cubes[i].z2);
                    for (int z = zb-1; z > 0; --z) {
                        if (p[x][y][z] > 0) {
                            adj[p[x][y][z]].push_back({i, zb - z - 1});
                            break;
                        }
                    }
                }
                adj[0].push_back({i, std::min(cubes[i].z1, cubes[i].z2)});
            }
        }

        int ans = 0;
        std::vector<int> base = resolve(-1, adj, cubes);
        if (part1) {
            for (int i = 1; i < cubes.size(); ++i) {
                std::vector<int> cur = resolve(i, adj, cubes);
                cur[i] = base[i];
                ans += (cur == base);
            }
        }
        else {
            for (int i = 1; i < cubes.size(); ++i) {
                std::vector<int> cur = resolve(i, adj, cubes);
                cur[i] = base[i];
                for (int j = 0; j < cubes.size(); ++j) {
                    if (cur[j] != base[j]) ans++;
                }
            }
        }
        return ans;
    }

    int part_1(std::string_view path){
        return solve(path, true);
    }

    unsigned long long part_2(std::string_view path) {
        return solve(path, false);
    }
}

#ifdef TESTING
TEST(Tests2023Day22, part_1_test) {
    ASSERT_EQ(aoc2023_day22::part_1("../2023/day22/input_test.in"), 5);
}

TEST(Tests2023Day22, part_1_real_test) {
    ASSERT_EQ(aoc2023_day22::part_1("../2023/day22/input.in"), 398);
}

TEST(Tests2023Day22, part_2_test) {
    ASSERT_EQ(aoc2023_day22::part_2("../2023/day22/input_test.in"), 7);
}

TEST(Tests2023Day22, part_2_real_test) {
    ASSERT_EQ(aoc2023_day22::part_2("../2023/day22/input.in"), 70727);
}
#endif

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2023_day22::part_1("../2023/day22/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2023_day22::part_2("../2023/day22/input.in") << std::endl;

    return 0;
}
#endif
