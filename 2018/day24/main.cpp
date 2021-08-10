#include "file.h"
#include "utilities.h"
#include <iostream>

namespace aoc2018_day24 {
    struct Group {
        int units;
        int hitPoints;
        std::vector<std::string> immune;
        std::vector<std::string> weak;
        int attack;
        std::string attackType;
        int initiative;
        int team; // 0 for Immune System and 1 for Infection
        int id;
        int target = -1; // used during phase 1
    };

    std::pair<int, int> combat(std::vector<Group> armies) {
        int sumTeam0 = armies.size() / 2, sumTeam1 = armies.size() / 2;
        bool damages = true;

        while (sumTeam0 > 0 && sumTeam1 > 0 && damages) {
            sumTeam0 = sumTeam1 = 0;
            damages = false;

            // phase 1 -
            std::sort(armies.begin(), armies.end(), [](const Group &army1, const Group &army2) {
                if (army1.units * army1.attack != army2.units * army2.attack) {
                    return army1.units * army1.attack > army2.units * army2.attack;
                }
                return army1.initiative > army2.initiative;
            });

            std::vector<bool> targetsSelected(armies.size(), false);

            for (auto& army : armies) {
                army.target = -1;
            }
            for (auto &army : armies) {
                int maxDamage = std::numeric_limits<int>::min();
                int effectivePowerDefender = 0;
                int initiativeDefender = 0;
                int idTarget = -1;
                for (int i = 0; i < armies.size(); ++i) {
                    if (armies[i].team != army.team && !targetsSelected[armies[i].id] && armies[i].units > 0) {
                        auto itImmune = std::find(armies[i].immune.begin(), armies[i].immune.end(), army.attackType);
                        auto itWeak = std::find(armies[i].weak.begin(), armies[i].weak.end(), army.attackType);
                        int attackPower = army.attack * army.units;
                        if (itWeak != std::end(armies[i].weak)) {
                            attackPower *= 2;
                        }
                        if (itImmune != std::end(armies[i].immune)) {
                            attackPower = 0;
                        }
                        if (attackPower == maxDamage) {
                            if (effectivePowerDefender == armies[i].attack * armies[i].units) {
                                if (initiativeDefender < armies[i].initiative) {
                                    idTarget = armies[i].id;
                                    initiativeDefender = armies[i].initiative;
                                }
                            }
                            if (effectivePowerDefender < armies[i].attack * armies[i].units) {
                                idTarget = armies[i].id;
                                effectivePowerDefender = armies[i].attack * armies[i].units;
                                initiativeDefender = armies[i].initiative;
                            }
                        }
                        if (attackPower > maxDamage) {
                            idTarget = armies[i].id;
                            maxDamage = attackPower;
                            effectivePowerDefender = armies[i].attack * armies[i].units;
                            initiativeDefender = armies[i].initiative;
                        }
                    }
                }
                if (idTarget >= 0) {
                    army.target = idTarget;
                    targetsSelected[idTarget] = true;
                }
            }

            // phase 2
            std::sort(armies.begin(), armies.end(), [](const Group &army1, const Group &army2) {
                return army1.initiative > army2.initiative;
            });

            for (auto &army : armies) {
                int targetId = -1;
                for (int i = 0; i < armies.size(); ++i) {
                    if (armies[i].id == army.target) {
                        targetId = i;
                    }
                }

                if (targetId != -1) {
                    auto itImmune = std::find(armies[targetId].immune.begin(), armies[targetId].immune.end(),
                                              army.attackType);
                    auto itWeak = std::find(armies[targetId].weak.begin(), armies[targetId].weak.end(), army.attackType);
                    int attackPower = army.attack * army.units;
                    if (itWeak != std::end(armies[targetId].weak)) {
                        attackPower *= 2;
                    }
                    if (itImmune != std::end(armies[targetId].immune)) {
                        attackPower = 0;
                    }
                    if (attackPower >= armies[targetId].hitPoints) {
                        damages = true;
                    }
                    armies[targetId].units = std::max(armies[targetId].units - attackPower / armies[targetId].hitPoints, 0);
                }
            }

            for (const auto &army : armies) {
                if (army.team == 0) {
                    sumTeam0 += army.units;
                }
                else {
                    sumTeam1 += army.units;
                }
            }
        }

        if (!damages) {
            return {sumTeam0 + sumTeam1, 2};
        }

        return {sumTeam0 + sumTeam1, sumTeam0 > 0 ? 0 : 1};
    }

    int part_1(std::string_view path) {
        std::vector<Group> armies;
        int currentTeam = 0;
        int id = 0;
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, " (,;:)");

            if (!tokens.empty() && tokens[0] == "Infection") {
                currentTeam++;
            }

            if (tokens.size() > 3) {
                Group g;
                g.units = std::stoi(tokens[0]);
                g.hitPoints = std::stoi(tokens[4].c_str());
                int currentId = 7;

                while (tokens[currentId] == "immune" || tokens[currentId] == "weak") {
                    if (tokens[currentId] == "immune") {
                        currentId += 2;
                        while (tokens[currentId] != "weak" && tokens[currentId] != "with") {
                            g.immune.push_back(tokens[currentId]);
                            currentId++;
                        }
                    }
                    if (tokens[currentId] == "weak") {
                        currentId += 2;
                        while (tokens[currentId] != "immune" && tokens[currentId] != "with") {
                            g.weak.push_back(tokens[currentId]);
                            currentId++;
                        }
                    }
                }
                currentId += 5;
                g.attack = std::stoi(tokens[currentId]);
                currentId++;
                g.attackType = tokens[currentId];
                g.initiative = std::stoi(tokens[currentId + 4]);
                g.team = currentTeam;
                g.id = id++;
                armies.push_back(g);
            }
        }
        return combat(armies).first;
    }

    int part_2(std::string_view path) {
        std::vector<Group> armies;
        int currentTeam = 0;
        int id = 0;
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, " (,;:)");

            if (!tokens.empty() && tokens[0] == "Infection") {
                currentTeam++;
            }

            if (tokens.size() > 3) {
                Group g;
                g.units = std::stoi(tokens[0]);
                g.hitPoints = std::stoi(tokens[4].c_str());
                int currentId = 7;

                while (tokens[currentId] == "immune" || tokens[currentId] == "weak") {
                    if (tokens[currentId] == "immune") {
                        currentId += 2;
                        while (tokens[currentId] != "weak" && tokens[currentId] != "with") {
                            g.immune.push_back(tokens[currentId]);
                            currentId++;
                        }
                    }
                    if (tokens[currentId] == "weak") {
                        currentId += 2;
                        while (tokens[currentId] != "immune" && tokens[currentId] != "with") {
                            g.weak.push_back(tokens[currentId]);
                            currentId++;
                        }
                    }
                }
                currentId += 5;
                g.attack = std::stoi(tokens[currentId]);
                currentId++;
                g.attackType = tokens[currentId];
                g.initiative = std::stoi(tokens[currentId + 4]);
                g.team = currentTeam;
                g.id = id++;
                armies.push_back(g);
            }
        }

        int li = 0, ls = 3000;
        int sol = 0;
        while (li <= ls) {
            int m = (li + ls) / 2;
            std::vector<Group> newArmies(armies);
            for (auto& army : newArmies) {
                if (army.team == 0) {
                    army.attack += m;
                }
            }
            auto result = combat(newArmies);
            if (result.second == 0) {
                sol = result.first;
                ls = m - 1;
            }
            else {
                li = m + 1;
            }
        }
        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2018_day24::part_1("../2018/day24/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2018_day24::part_2("../2018/day24/input.in") << std::endl;

    return 0;
}
#endif
