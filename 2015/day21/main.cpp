#include "file.h"
#include "utilities.h"
#include <iostream>
#include <algorithm>

namespace aoc2015_day21 {
    struct item {
        item(int c, int d, int a) {
            cost = c;
            damage = d;
            armor = a;
        }
        int cost;
        int damage;
        int armor;
    };

    std::vector<item> weapons{{8, 4, 0}, {10, 5, 0}, {25, 6, 0}, {40, 7, 0}, {74, 8, 0}};
    std::vector<item> armors{{0, 0, 0}, {13, 0, 1}, {31, 0, 2}, {53, 0, 3}, {75, 0, 4}, {102, 0, 5}};
    std::vector<item> rings{{25, 1, 0}, {50, 2, 0}, {100, 3, 0}, {20, 0, 1}, {40, 0, 2}, {80, 0, 3}};

    bool canPlayerWin(int bossHealth, int bossDamage, int bossArmour,
                      int playerHealth, int playerDamage, int playerArmour) {
        while (bossHealth > 0 && playerHealth > 0) {
            bossHealth -= std::max(playerDamage - bossArmour, 1);
            if (bossHealth > 0) {
                playerHealth -= std::max(bossDamage - playerArmour, 1);
            }
        }
        return (playerHealth > 0);
    }

    int getMaxCost() {
        std::sort(weapons.begin(), weapons.end(), [](const auto& a, const auto& b) {
            return a.cost > b.cost;
        });
        std::sort(armors.begin(), armors.end(), [](const auto& a, const auto& b) {
            return a.cost > b.cost;
        });
        std::sort(rings.begin(), rings.end(), [](const auto& a, const auto& b) {
            return a.cost > b.cost;
        });
        return weapons[0].cost + armors[0].cost + rings[0].cost + rings[1].cost + rings[2].cost;
    }

    int part_1(int bossHealth, int bossDamage, int bossArmour, int playerHealth) {
        int maxCost = getMaxCost();
        int li = 0, ls = maxCost;
        while (li <= ls) {
            int m = (li + ls) / 2;
            bool canWin = false;
            for (const auto &w : weapons) {
                for (const auto &a : armors) {
                    // no rings
                    if (w.cost + a.cost <= m) {
                        if (canPlayerWin(bossHealth, bossDamage, bossArmour, playerHealth, w.damage, a.armor)) {
                            canWin = true;
                        }
                    }
                    // one ring
                    if (!canWin) {
                        for (const auto &r : rings) {
                            if (w.cost + a.cost + r.cost <= m) {
                                if (canPlayerWin(bossHealth, bossDamage, bossArmour, playerHealth, w.damage + r.damage,
                                                 a.armor + r.armor)) {
                                    canWin = true;
                                }
                            }
                        }
                    }
                    //twp rings
                    if (!canWin) {
                        for (int i = 0; i < rings.size(); ++i) {
                            for (int j = i + 1; j < rings.size(); ++j) {
                                if (w.cost + a.cost + rings[i].cost + rings[j].cost <= m) {
                                    if (canPlayerWin(bossHealth, bossDamage, bossArmour, playerHealth,
                                                     w.damage + rings[i].damage + rings[j].damage,
                                                     a.armor + rings[i].armor + rings[j].armor)) {
                                        canWin = true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (canWin) {
                ls = m - 1;
            } else {
                li = m + 1;
            }
        }

        return li;
    }

    int part_2(int bossHealth, int bossDamage, int bossArmour, int playerHealth) {
        int maxCost = getMaxCost();
        for (int k = maxCost; k >= 0; --k) {
            bool canLose = false;
            for (const auto &w : weapons) {
                for (const auto &a : armors) {
                    // no rings
                    if (w.cost + a.cost == k) {
                        if (!canPlayerWin(bossHealth, bossDamage, bossArmour, playerHealth, w.damage, a.armor)) {
                            canLose = true;
                        }
                    }
                    // one ring
                    if (!canLose) {
                        for (const auto &r : rings) {
                            if (w.cost + a.cost + r.cost == k) {
                                if (!canPlayerWin(bossHealth, bossDamage, bossArmour, playerHealth, w.damage + r.damage,
                                                  a.armor + r.armor)) {
                                    canLose = true;
                                }
                            }
                        }
                    }
                    //twp rings
                    if (!canLose) {
                        for (int i = 0; i < rings.size(); ++i) {
                            for (int j = i + 1; j < rings.size(); ++j) {
                                if (w.cost + a.cost + rings[i].cost + rings[j].cost == k) {
                                    if (!canPlayerWin(bossHealth, bossDamage, bossArmour, playerHealth,
                                                      w.damage + rings[i].damage + rings[j].damage,
                                                      a.armor + rings[i].armor + rings[j].armor)) {
                                        canLose = true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (canLose) {
                return k;
            }
        }
        return 0;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2015_day21::part_1(100, 8, 2, 100) << std::endl;
    std::cout << "Part 2: " << aoc2015_day21::part_2(100, 8, 2, 100) << std::endl;

    return 0;
}
#endif
