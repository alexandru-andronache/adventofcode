#include "file.h"
#include "utilities.h"
#include <iostream>
#include <algorithm>
#include <limits>

namespace aoc2015_day22 {
    struct spell {
        int manaCost;
        int turns;
        int damage;
        int heal;
        int gainArmor;
        int gainMana;
    };

    struct state {
        int bossHealth;
        int playerHealth;
        int playerArmour;
        int currentMana; // how much real mana i have right now
        int manaSpent; // how much mana i've spent(we need to minimize this value)
        std::vector<std::pair<int, int>> activeSpells; // pair.first id of the spell, pair.second number of turns still active
    };

    void processPassiveSpells(state& currentState, const std::vector<spell>& spells) {
        for (auto &active : currentState.activeSpells) {
            currentState.bossHealth -= spells[active.first].damage;
            currentState.currentMana += spells[active.first].gainMana;
            active.second--;
        }
        currentState.activeSpells.erase(std::remove_if(currentState.activeSpells.begin(),
                                                       currentState.activeSpells.end(),
                                                       [](const auto& spell) {
            return spell.second <= 0;
        }), currentState.activeSpells.end());
        currentState.playerArmour = 0;
        for (const auto& activeSpell : currentState.activeSpells) {
            currentState.playerArmour += spells[activeSpell.first].gainArmor;
        }
    }

    std::vector<spell> spells{{53, 0, 4, 0,0,0},
                              {73, 0, 2, 2, 0, 0},
                              {113, 6, 0, 0, 7, 0},
                              {173, 6, 3, 0, 0,0},
                              {229, 5, 0, 0, 0, 101}};

    int solve(int bossHealth, int bossDamage, int playerHealth, int playerMana, int playerHealthLoseEachTurn) {
        int maxPlayerHealth = playerHealth;
        std::vector<state> states{{bossHealth, playerHealth, 0, playerMana, 0, {}}};
        int minimumManaSpent = std::numeric_limits<int>::max();
        while (!states.empty()) {
            std::vector<state> newStates;
            for (const auto& s : states) {
                for (int i = 0; i < spells.size(); ++i) {
                    state currentState = s;
                    currentState.playerHealth -= playerHealthLoseEachTurn;
                    if (currentState.currentMana >= spells[i].manaCost && (currentState.manaSpent + spells[i].manaCost <= minimumManaSpent) && currentState.playerHealth > 0) {
                        processPassiveSpells(currentState, spells);
                        if (std::find_if(currentState.activeSpells.begin(), currentState.activeSpells.end(), [&](const auto& spell) {
                            return spell.first == i;
                        }) == currentState.activeSpells.end()) {
                            currentState.currentMana -= spells[i].manaCost;
                            currentState.manaSpent += spells[i].manaCost;
                            if (spells[i].turns > 0) {
                                currentState.activeSpells.emplace_back(i, spells[i].turns);
                            } else {
                                currentState.bossHealth -= spells[i].damage;
                                currentState.playerHealth = std::min(maxPlayerHealth, currentState.playerHealth + spells[i].heal);
                            }
                            if (currentState.bossHealth <= 0) {
                                minimumManaSpent = std::min(minimumManaSpent, currentState.manaSpent);
                            } else {
                                processPassiveSpells(currentState, spells);
                                if (currentState.bossHealth <= 0) {
                                    minimumManaSpent = std::min(minimumManaSpent, currentState.manaSpent);
                                }
                                else {
                                    currentState.playerHealth -= std::max(1, bossDamage - currentState.playerArmour);
                                    if (currentState.playerHealth > 0 && (currentState.manaSpent <= minimumManaSpent)) {
                                        newStates.emplace_back(currentState);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            states = newStates;
        }

        return minimumManaSpent;
    }

    int part_1(int bossHealth, int bossDamage, int playerHealth, int playerMana) {
        return solve(bossHealth, bossDamage, playerHealth, playerMana, 0);
    }

    int part_2(int bossHealth, int bossDamage, int playerHealth, int playerMana) {
        return solve(bossHealth, bossDamage, playerHealth, playerMana, 1);
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2015_day22::part_1(55, 8, 50, 500) << std::endl;
    std::cout << "Part 2: " << aoc2015_day22::part_2(55, 8, 50, 500) << std::endl;

    return 0;
}
#endif
