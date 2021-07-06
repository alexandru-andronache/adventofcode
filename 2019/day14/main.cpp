#include "file.h"
#include "utilities.h"
#include <iostream>
#include <numeric>
#include <map>

namespace aoc2019_day14 {
    struct reaction {
        struct chemical {
            int quantity;
            int material;
        };
        std::vector<chemical> chemicals;
        chemical output{};
    };

    long long solve(const std::map<std::string, int>& chemicals, const std::vector<reaction>& reactions, long long fuel) {
        std::vector<long long> output(chemicals.size(), 0);
        std::vector<long long> extra(chemicals.size(), 0);
        output[chemicals.at("FUEL")] = fuel;

        while (true) {
            std::vector<long long> newOutput(chemicals.size(), 0);
            for (int i = 0; i < output.size(); ++i) {
                if (i != chemicals.at("ORE") && output[i] > 0) {
                    for (const auto & reaction : reactions) {
                        if (reaction.output.material == i) {
                            if (reaction.output.quantity <= output[i]) {
                                long long multiplier = output[i] / reaction.output.quantity;
                                for (const auto &chemical : reaction.chemicals) {
                                    newOutput[chemical.material] += chemical.quantity * multiplier;
                                }
                                output[i] = output[i] % reaction.output.quantity;
                            }
                            else {
                                for (const auto &chemical : reaction.chemicals) {
                                    newOutput[chemical.material] += chemical.quantity;
                                }
                                extra[i] = reaction.output.quantity - output[i];
                                output[i] = 0;
                            }
                            break;
                        }
                    }
                }
            }

            for (int i = 0; i < output.size(); ++i) {
                newOutput[i] += output[i];
            }

            output = newOutput;

            for (int i = 0; i < output.size(); ++i) {
                long long tmp = output[i];
                output[i] = std::max(0LL, output[i] - extra[i]);
                extra[i] = std::max(0LL, extra[i] - tmp);
            }

            bool found = true;
            for (int i = 0; i < output.size(); ++i) {
                if (output[i] > 0 && i != chemicals.at("ORE")) {
                    found = false;
                }
            }

            if (found) {
                return output[chemicals.at("ORE")];
            }
        }
    }

    unsigned long long part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);

        std::map<std::string, int> chemicals;
        int maxNr = 0;
        std::vector<reaction> reactions;
        for (const auto& line : input) {
            std::vector<std::string> tokens = utils::splitString(line, ", \n");
            int i = 0;
            reaction r;
            while (tokens[i] != "=>") {
                if (chemicals.find(tokens[i + 1]) == chemicals.end()) {
                    chemicals[tokens[i + 1]] = maxNr++;
                }
                r.chemicals.push_back({std::stoi(tokens[i]), chemicals[tokens[i + 1]]});
                i = i + 2;
            }
            i++;
            r.output.quantity = std::stoi(tokens[i]);
            if (chemicals.find(tokens[i + 1]) == chemicals.end()) {
                chemicals[tokens[i + 1]] = maxNr++;
            }
            r.output.material = chemicals[tokens[i + 1]];
            reactions.emplace_back(r);
        }

        return solve(chemicals, reactions, 1);
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);

        std::map<std::string, int> chemicals;
        const long long maxOre = 1000000000000;
        int maxNr = 0;
        std::vector<reaction> reactions;
        for (const auto& line : input) {
            std::vector<std::string> tokens = utils::splitString(line, ", \n");
            int i = 0;
            reaction r;
            while (tokens[i] != "=>") {
                if (chemicals.find(tokens[i + 1]) == chemicals.end()) {
                    chemicals[tokens[i + 1]] = maxNr++;
                }
                r.chemicals.push_back({std::stoi(tokens[i]), chemicals[tokens[i + 1]]});
                i = i + 2;
            }
            i++;
            r.output.quantity = std::stoi(tokens[i]);
            if (chemicals.find(tokens[i + 1]) == chemicals.end()) {
                chemicals[tokens[i + 1]] = maxNr++;
            }
            r.output.material = chemicals[tokens[i + 1]];
            reactions.emplace_back(r);
        }

        long long li = maxOre / solve(chemicals, reactions, 1);
        long long ls = li * 2;

        while (li <= ls) {
            long long m = (li + ls) / 2;
            if (solve(chemicals, reactions, m) <= maxOre) {
                li = m + 1;
            }
            else {
                ls = m - 1;
            }
        }

        return ls;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2019_day14::part_1("../2019/day14/input.in") << std::endl;
    std::cout << "Part 1: " << aoc2019_day14::part_2("../2019/day14/input.in") << std::endl;

    return 0;
}
#endif
