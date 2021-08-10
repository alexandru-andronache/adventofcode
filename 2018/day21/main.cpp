#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>
#include <array>
#include <map>

namespace aoc2018_day21 {
    void addr(std::array<long long, 6>& registers, const std::array<int, 3>& instructions) {
        registers[instructions[2]] = registers[instructions[0]] + registers[instructions[1]];
    }

    void addi(std::array<long long, 6>& registers, const std::array<int, 3>& instructions) {
        if (instructions[2] == 1 && registers[1] == 0) {
            registers[1] = registers[2] / 256 - 1;
            if (registers[1] <= 0) {
                registers[1] = registers[instructions[0]] + instructions[1];
            }
        }
        else {
            registers[instructions[2]] = registers[instructions[0]] + instructions[1];
        }
    }

    void mulr(std::array<long long, 6>& registers, const std::array<int, 3>& instructions) {
        registers[instructions[2]] = registers[instructions[0]] * registers[instructions[1]];
    }

    void muli(std::array<long long, 6>& registers, const std::array<int, 3>& instructions) {
        registers[instructions[2]] = registers[instructions[0]] * instructions[1];
    }

    void banr(std::array<long long, 6>& registers, const std::array<int, 3>& instructions) {
        registers[instructions[2]] = registers[instructions[0]] & registers[instructions[1]];
    }

    void bani(std::array<long long, 6>& registers, const std::array<int, 3>& instructions) {
        registers[instructions[2]] = registers[instructions[0]] & instructions[1];
    }

    void borr(std::array<long long, 6>& registers, const std::array<int, 3>& instructions) {
        registers[instructions[2]] = registers[instructions[0]] | registers[instructions[1]];
    }

    void bori(std::array<long long, 6>& registers, const std::array<int, 3>& instructions) {
        registers[instructions[2]] = registers[instructions[0]] | instructions[1];
    }

    void setr(std::array<long long, 6>& registers, const std::array<int, 3>& instructions) {
        registers[instructions[2]] = registers[instructions[0]];
    }

    void seti(std::array<long long, 6>& registers, const std::array<int, 3>& instructions) {
        registers[instructions[2]] = instructions[0];
    }

    void gtir(std::array<long long, 6>& registers, const std::array<int, 3>& instructions) {
        registers[instructions[2]] = (instructions[0] > registers[instructions[1]]) ? 1 : 0;
    }

    void gtri(std::array<long long, 6>& registers, const std::array<int, 3>& instructions) {
        registers[instructions[2]] = (registers[instructions[0]] > instructions[1]) ? 1 : 0;
    }

    void gtrr(std::array<long long, 6>& registers, const std::array<int, 3>& instructions) {
        registers[instructions[2]] = (registers[instructions[0]] > registers[instructions[1]]) ? 1 : 0;
    }

    void eqir(std::array<long long, 6>& registers, const std::array<int, 3>& instructions) {
        registers[instructions[2]] = (instructions[0] == registers[instructions[1]]) ? 1 : 0;
    }

    void eqri(std::array<long long, 6>& registers, const std::array<int, 3>& instructions) {
        registers[instructions[2]] = (registers[instructions[0]] == instructions[1]) ? 1 : 0;
    }

    void eqrr(std::array<long long, 6>& registers, const std::array<int, 3>& instructions) {
        registers[instructions[2]] = (registers[instructions[0]] == registers[instructions[1]]) ? 1 : 0;
    }

    int solve(const std::vector<std::pair<std::string, std::array<int, 3>>>& instructions,
              int ip_register,
              std::function<bool(long long a, long long b)> comp) {
        /*
         * when we arrive at the instruction 28 (eqrr 3 0 1) we are going to compare the register[3] with
         * register[0] and register[0] has no input in what we are doing until then
         * so to solve it we don't care about register[0] we just have to check all the values in register[3]
         * They will be keeped in a map until they repeat and then we find the smallest one and the biggest one
         */

        // when we arrive at the instruction 28 (eqrr 3 0 1) we are going to compare the register[3] with
        std::array<long long, 6> registers = {1, 0, 0, 0, 0, 0};
        std::map<std::string, void(*)(std::array<long long, 6>&, const std::array<int, 3>&)> func;
        func.insert({"addr", &addr});
        func.insert({"addi", &addi});

        func.insert({"mulr", &mulr});
        func.insert({"muli", &muli});

        func.insert({"banr", &banr});
        func.insert({"bani", &bani});

        func.insert({"borr", &borr});
        func.insert({"bori", &bori});

        func.insert({"setr", &setr});
        func.insert({"seti", &seti});

        func.insert({"gtir", &gtir});
        func.insert({"gtri", &gtri});
        func.insert({"gtrr", &gtrr});

        func.insert({"eqir", &eqir});
        func.insert({"eqri", &eqri});
        func.insert({"eqrr", &eqrr});

        std::map<long long, int> previousValues;

        int ip_value = 0;
        int steps = 0;
        int sol = 0;

        while (ip_value < instructions.size()) {
            if (ip_value == 30) {
                auto it = previousValues.find(registers[3]);
                if (it != previousValues.end()) {
                    long long step = it->second;

                    for (const auto& p : previousValues) {
                        if (comp(step, p.second)) {
                            step = p.second;
                            sol = p.first;
                        }
                    }
                    break;
                }
                else {
                    previousValues.insert({registers[3], steps});
                }
            }
            registers[ip_register] = ip_value;
            func[instructions[ip_value].first](registers, instructions[ip_value].second);
            ip_value = registers[ip_register];
            ip_value++;
            steps++;
        }

        return sol;
    }

    int part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        int ip = 0;
        std::vector<std::pair<std::string, std::array<int, 3>>> input;
        for (char i : lines[0]) {
            if (i >= '0' && i <= '9') {
                ip = ip * 10 +  i - '0';
            }
        }
        for (int i = 1; i < lines.size(); ++i) {
            std::vector<std::string> tokens = utils::splitString(lines[i], " ");
            input.push_back({tokens[0], {std::stoi(tokens[1]), std::stoi(tokens[2]), std::stoi(tokens[3])}});
        }

        return solve(input, ip, [](long long a, long b) { return a > b; });
    }

    int part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        int ip = 0;
        std::vector<std::pair<std::string, std::array<int, 3>>> input;
        for (char i : lines[0]) {
            if (i >= '0' && i <= '9') {
                ip = ip * 10 +  i - '0';
            }
        }
        for (int i = 1; i < lines.size(); ++i) {
            std::vector<std::string> tokens = utils::splitString(lines[i], " ");
            input.push_back({tokens[0], {std::stoi(tokens[1]), std::stoi(tokens[2]), std::stoi(tokens[3])}});
        }

        return solve(input, ip, [](long long a, long b) { return a < b; });
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2018_day21::part_1("../2018/day21/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2018_day21::part_2("../2018/day21/input.in") << std::endl;

    return 0;
}
#endif
