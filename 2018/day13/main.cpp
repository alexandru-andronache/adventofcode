#include "file.h"
#include "direction.h"
#include <iostream>
#include <vector>
#include <map>

namespace aoc2018_day13 {
    enum class Direction {
        Down = 0,
        Left = 1,
        Up = 2,
        Right = 3
    };

    struct Cart {
        int x;
        int y;
        Direction d;
        int directionChanges;
    };

    void addRowToMap(std::string str, std::vector<std::vector<char>>& map, std::vector<Cart>& carts) {
        std::vector<char> c;
        for (int i = 0; i < str.size(); ++i) {
            switch (str[i]) {
                case ' ':
                case '-':
                case '|':
                case '+':
                case '/':
                case '\\':
                    c.push_back(str[i]);
                    break;
                case 'v':
                    c.push_back('|');
                    carts.push_back({(int)map.size(), i, Direction::Down, 0});
                    break;
                case '^':
                    c.push_back('|');
                    carts.push_back({(int)map.size(), i, Direction::Up, 0});
                    break;
                case '<':
                    c.push_back('-');
                    carts.push_back({(int)map.size(), i, Direction::Left, 0});
                    break;
                case '>':
                    c.push_back('-');
                    carts.push_back({(int)map.size(), i, Direction::Right, 0});
                    break;
            }
        }
        map.push_back(c);
    }

    bool shouldUpdateCart(const std::vector<Cart>& carts,
                          const Cart& cart) {
        int n = 0;
        for (const auto& c : carts) {
            if (c.x == cart.x && c.y == cart.y) {
                n++;
            }
        }
        return (n <= 1);
    }

    void moveCart(const std::vector<std::vector<char>>& map, Cart& cart) {
        std::map<std::pair<Direction, char>, Direction> dir;
        dir.insert({std::make_pair(Direction::Right, '/'), Direction::Up});
        dir.insert({std::make_pair(Direction::Right, '\\'), Direction::Down});
        dir.insert({std::make_pair(Direction::Left, '/'), Direction::Down});
        dir.insert({std::make_pair(Direction::Left, '\\'), Direction::Up});
        dir.insert({std::make_pair(Direction::Up, '/'), Direction::Right});
        dir.insert({std::make_pair(Direction::Up, '\\'), Direction::Left});
        dir.insert({std::make_pair(Direction::Down, '/'), Direction::Left});
        dir.insert({std::make_pair(Direction::Down, '\\'), Direction::Right});

        std::map<std::pair<Direction, int>, Direction> dirIntersection;
        dirIntersection.insert({std::make_pair(Direction::Right, 0), Direction::Up});
        dirIntersection.insert({std::make_pair(Direction::Right, 2), Direction::Down});
        dirIntersection.insert({std::make_pair(Direction::Left, 0), Direction::Down});
        dirIntersection.insert({std::make_pair(Direction::Left, 2), Direction::Up});
        dirIntersection.insert({std::make_pair(Direction::Up, 0), Direction::Left});
        dirIntersection.insert({std::make_pair(Direction::Up, 2), Direction::Right});
        dirIntersection.insert({std::make_pair(Direction::Down, 0), Direction::Right});
        dirIntersection.insert({std::make_pair(Direction::Down, 2), Direction::Left});

        int newX = cart.x, newY = cart.y;
        switch (cart.d) {
            case Direction::Right:
                newY = cart.y + 1;
                break;
            case Direction::Left:
                newY = cart.y - 1;
                break;
            case Direction::Up:
                newX = cart.x - 1;
                break;
            case Direction::Down:
                newX = cart.x + 1;
                break;
        }

        switch (map[newX][newY]) {
            case '/':
                case '\\':
                    cart.d = dir[std::make_pair(cart.d, map[newX][newY])];
                    break;
                    case '+':
                        if (cart.directionChanges != 1) {
                            cart.d = dirIntersection[std::make_pair(cart.d, cart.directionChanges)];
                        }
                        cart.directionChanges = (cart.directionChanges + 1) % 3;
                        break;
        }

        cart.x = newX;
        cart.y = newY;
    }

    std::pair<int, int> part_1(std::string_view path) {
        std::vector<std::vector<char>> map;
        std::vector<Cart> carts;
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        for (const auto& line : lines) {
            addRowToMap(line, map, carts);
        }

        while (true) {
            std::sort(carts.begin(), carts.end(), [](Cart c1, Cart c2) {
                if (c1.x != c2.x) {
                    return c1.x < c2.x;
                }
                return c1.y < c2.y;
            });

            auto crash = std::adjacent_find(carts.begin(), carts.end(), [](const auto& c1, const auto& c2) {
                return c1.x == c2.x && c1.y == c2.y;
            });
            if (crash != carts.end()) {
                return std::make_pair(crash->y, crash->x);
            }

            for (auto& cart : carts) {
                if (shouldUpdateCart(carts, cart)) {
                    moveCart(map, cart);
                }
            }
        }
    }

    std::pair<int, int> part_2(std::string_view path) {
        std::vector<std::vector<char>> map;
        std::vector<Cart> carts;
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        for (const auto& line : lines) {
            addRowToMap(line, map, carts);
        }

        while (true) {
            std::sort(carts.begin(), carts.end(), [](Cart c1, Cart c2) {
                if (c1.x != c2.x) {
                    return c1.x < c2.x;
                }
                return c1.y < c2.y;
            });

            std::vector<Cart> t;
            t.push_back({});
            t.insert(t.end(), carts.begin(), carts.end());
            t.push_back({});
            carts.clear();
            for (int i = 1; i < t.size() - 1; ++i) {
                if ((t[i].x != t[i - 1].x || t[i].y != t[i - 1].y) &&
                (t[i].x != t[i + 1].x || t[i].y != t[i + 1].y)) {
                    carts.push_back(t[i]);
                }
            }

            if (carts.size() == 1) {
                return std::make_pair(carts[0].y, carts[0].x);
            }

            for (auto& cart : carts) {
                if (shouldUpdateCart(carts, cart)) {
                    moveCart(map, cart);
                }
            }
        }
    }
}

#ifndef TESTING
int main() {
    auto sol1 = aoc2018_day13::part_1("../2018/day13/input.in");
    auto sol2 = aoc2018_day13::part_2("../2018/day13/input.in");
    std::cout << "Part 1: " << sol1.first << "," << sol1.second << std::endl;
    std::cout << "Part 2: " << sol2.first << "," << sol2.second << std::endl;

    return 0;
}
#endif
