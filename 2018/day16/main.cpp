#include "file.h"
#include <iostream>
#include <array>
#include <vector>

namespace aoc2018_day16 {
    void addr(const std::array<int, 4>& registers, const std::array<int, 4>& instructions, std::array<int, 4>& output) {
        output = registers;
        output[instructions[3]] = output[instructions[1]] + output[instructions[2]];
    }

    void addi(const std::array<int, 4>& registers, const std::array<int, 4>& instructions, std::array<int, 4>& output) {
        output = registers;
        output[instructions[3]] = output[instructions[1]] + instructions[2];
    }

    void mulr(const std::array<int, 4>& registers, const std::array<int, 4>& instructions, std::array<int, 4>& output) {
        output = registers;
        output[instructions[3]] = output[instructions[1]] * output[instructions[2]];
    }

    void muli(const std::array<int, 4>& registers, const std::array<int, 4>& instructions, std::array<int, 4>& output) {
        output = registers;
        output[instructions[3]] = output[instructions[1]] * instructions[2];
    }

    void banr(const std::array<int, 4>& registers, const std::array<int, 4>& instructions, std::array<int, 4>& output) {
        output = registers;
        output[instructions[3]] = output[instructions[1]] & output[instructions[2]];
    }

    void bani(const std::array<int, 4>& registers, const std::array<int, 4>& instructions, std::array<int, 4>& output) {
        output = registers;
        output[instructions[3]] = output[instructions[1]] & instructions[2];
    }

    void borr(const std::array<int, 4>& registers, const std::array<int, 4>& instructions, std::array<int, 4>& output) {
        output = registers;
        output[instructions[3]] = output[instructions[1]] | output[instructions[2]];
    }

    void bori(const std::array<int, 4>& registers, const std::array<int, 4>& instructions, std::array<int, 4>& output) {
        output = registers;
        output[instructions[3]] = output[instructions[1]] | instructions[2];
    }

    void setr(const std::array<int, 4>& registers, const std::array<int, 4>& instructions, std::array<int, 4>& output) {
        output = registers;
        output[instructions[3]] = output[instructions[1]];
    }

    void seti(const std::array<int, 4>& registers, const std::array<int, 4>& instructions, std::array<int, 4>& output) {
        output = registers;
        output[instructions[3]] = instructions[1];
    }

    void gtir(const std::array<int, 4>& registers, const std::array<int, 4>& instructions, std::array<int, 4>& output) {
        output = registers;
        output[instructions[3]] = (instructions[1] > output[instructions[2]]) ? 1 : 0;
    }

    void gtri(const std::array<int, 4>& registers, const std::array<int, 4>& instructions, std::array<int, 4>& output) {
        output = registers;
        output[instructions[3]] = (output[instructions[1]] > instructions[2]) ? 1 : 0;
    }

    void gtrr(const std::array<int, 4>& registers, const std::array<int, 4>& instructions, std::array<int, 4>& output) {
        output = registers;
        output[instructions[3]] = (output[instructions[1]] > output[instructions[2]]) ? 1 : 0;
    }

    void eqir(const std::array<int, 4>& registers, const std::array<int, 4>& instructions, std::array<int, 4>& output) {
        output = registers;
        output[instructions[3]] = (instructions[1] == output[instructions[2]]) ? 1 : 0;
    }

    void eqri(const std::array<int, 4>& registers, const std::array<int, 4>& instructions, std::array<int, 4>& output) {
        output = registers;
        output[instructions[3]] = (output[instructions[1]] == instructions[2]) ? 1 : 0;
    }

    void eqrr(const std::array<int, 4>& registers, const std::array<int, 4>& instructions, std::array<int, 4>& output) {
        output = registers;
        output[instructions[3]] = (output[instructions[1]] == output[instructions[2]]) ? 1 : 0;
    }

    int part_1(std::string_view path) {
        std::vector<std::vector<std::array<int, 4>>> input;
        std::vector<std::array<int, 4>> instructions;
        std::vector<std::vector<std::string>> lines = file::readFileAndSplit(path, " :,[]");
        std::vector<std::array<int, 4>> tmp;
        for (const auto& line : lines) {
            if (tmp.empty() && !line.empty()) {
                if (line[0] == "Before") {
                    tmp.push_back({std::stoi(line[1]), std::stoi(line[2]), std::stoi(line[3]), std::stoi(line[4])});
                }
                else {
                    instructions.push_back({std::stoi(line[0]), std::stoi(line[1]), std::stoi(line[2]), std::stoi(line[3])});
                }
            }
            else if (tmp.size() == 1) {
                tmp.push_back({std::stoi(line[0]), std::stoi(line[1]), std::stoi(line[2]), std::stoi(line[3])});
            }
            else if (tmp.size() == 2) {
                tmp.push_back({std::stoi(line[1]), std::stoi(line[2]), std::stoi(line[3]), std::stoi(line[4])});
            }
            else if (tmp.size() == 3) {
                input.push_back(tmp);
                tmp.clear();
            }
        }

        int sol = 0;

        std::vector<void(*)(const std::array<int, 4>&, const std::array<int, 4>&, std::array<int, 4>&)> func;
        func.push_back(&addr);
        func.push_back(&addi);

        func.push_back(&mulr);
        func.push_back(&muli);

        func.push_back(&banr);
        func.push_back(&bani);

        func.push_back(&borr);
        func.push_back(&bori);

        func.push_back(&setr);
        func.push_back(&seti);

        func.push_back(&gtir);
        func.push_back(&gtri);
        func.push_back(&gtrr);

        func.push_back(&eqir);
        func.push_back(&eqri);
        func.push_back(&eqrr);

        for (const auto& s : input) {
            std::array<int, 4> output = {0, 0, 0, 0};
            int similar = 0;
            for (const auto& f : func) {
                f(s[0], s[1], output);
                if (output == s[2]) {
                    similar++;
                }
            }
            if (similar >= 3) {
                sol++;
            }
        }

        return sol;
    }

    int part_2(std::string_view path) {
        std::vector<std::vector<std::array<int, 4>>> input;
        std::vector<std::array<int, 4>> instructions;
        std::vector<std::vector<std::string>> lines = file::readFileAndSplit(path, " :,[]");
        std::vector<std::array<int, 4>> tmp;
        for (const auto& line : lines) {
            if (tmp.empty() && !line.empty()) {
                if (line[0] == "Before") {
                    tmp.push_back({std::stoi(line[1]), std::stoi(line[2]), std::stoi(line[3]), std::stoi(line[4])});
                }
                else {
                    instructions.push_back({std::stoi(line[0]), std::stoi(line[1]), std::stoi(line[2]), std::stoi(line[3])});
                }
            }
            else if (tmp.size() == 1) {
                tmp.push_back({std::stoi(line[0]), std::stoi(line[1]), std::stoi(line[2]), std::stoi(line[3])});
            }
            else if (tmp.size() == 2) {
                tmp.push_back({std::stoi(line[1]), std::stoi(line[2]), std::stoi(line[3]), std::stoi(line[4])});
            }
            else if (tmp.size() == 3) {
                input.push_back(tmp);
                tmp.clear();
            }
        }

        std::vector<void(*)(const std::array<int, 4>&, const std::array<int, 4>&, std::array<int, 4>&)> func;
        std::array<std::vector<void(*)(const std::array<int, 4>&, const std::array<int, 4>&, std::array<int, 4>&)>, 16> map;
        func.push_back(&addr);
        func.push_back(&addi);

        func.push_back(&mulr);
        func.push_back(&muli);

        func.push_back(&banr);
        func.push_back(&bani);

        func.push_back(&borr);
        func.push_back(&bori);

        func.push_back(&setr);
        func.push_back(&seti);

        func.push_back(&gtir);
        func.push_back(&gtri);
        func.push_back(&gtrr);

        func.push_back(&eqir);
        func.push_back(&eqri);
        func.push_back(&eqrr);

        for (const auto& s : input) {
            std::array<int, 4> output = {0, 0, 0, 0};
            std::vector<void(*)(const std::array<int, 4>&, const std::array<int, 4>&, std::array<int, 4>&)> possibleOp;
            for (const auto& f : func) {
                f(s[0], s[1], output);
                if (output == s[2]) {
                    possibleOp.push_back(f);
                }
            }
            if (map[s[1][0]].size() == 0) {
                map[s[1][0]].insert(map[s[1][0]].end(), possibleOp.begin(), possibleOp.end());
            }
            else {
                std::vector<void(*)(const std::array<int, 4>&, const std::array<int, 4>&, std::array<int, 4>&)> tmp(map[s[1][0]]);
                map[s[1][0]].clear();
                std::sort(possibleOp.begin(), possibleOp.end());
                std::sort(tmp.begin(), tmp.end());
                std::set_intersection(possibleOp.begin(), possibleOp.end(),
                                      tmp.begin(), tmp.end(),
                                      std::back_inserter(map[s[1][0]]));
            }
        }

        // Loop through opcodes and assign ones with one function not already assigned
        bool isSolved = true;
        while (isSolved) {
            for (const auto& f : map) {
                if (f.size() == 1) {
                    for (auto& m : map) {
                        if (f != m) {
                            m.erase(std::remove(m.begin(), m.end(), f[0]), m.end());
                        }
                    }
                }
            }
            isSolved = false;
            for (const auto& f: map) {
                if (f.size() > 1) {
                    isSolved = true;
                }
            }
        }

        std::array<int, 4> begin{0, 0, 0, 0};
        for (const auto& i : instructions) {
            std::array<int, 4> output;
            map[i[0]][0](begin, i, output);
            begin = output;
        }

        return begin[0];
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2018_day16::part_1("../2018/day16/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2018_day16::part_2("../2018/day16/input.in") << std::endl;

    return 0;
}
#endif
