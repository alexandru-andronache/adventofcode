#include "file.h"
#include "utilities.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <limits>

namespace aoc2022_day07 {

    const long long MAX_PART_1 = 100000;

    const long long TOTAL_SPACE_PART_2 = 70000000;
    const long long SPACE_NEEDED_PART_2 = 30000000;

    struct Node {
        long long size;
        std::string name;
        std::vector<Node*> nodes;
        Node* parent;
    };

    long long dfs_part1(Node* root) {
       long long s = 0;
       for (const auto& n : root->nodes) {
           s += dfs_part1(n);
       }
       if (root->size <= MAX_PART_1) {
           s += root->size;
       }
       return s;
    }

    long long dfs_part2(Node* root, int space) {
        long long min = std::numeric_limits<long long>::max();
        for (const auto& n : root->nodes) {
            min = std::min(min, dfs_part2(n, space));
        }
        if (root->size >= space) {
            return std::min(root->size, min);
        }
    }

    void buildTree(std::string_view path, struct Node* root) {
        struct Node* current_node = root;

        std::vector<std::string> input = file::readFileAsArrayString(path);
        int k = 0;
        while (k < input.size()) {
            std::vector<std::string> t = utils::splitString(input[k], " ");
            if (t[0] == "$") {
                if (t[1] == "cd") {
                    if (t[2] == "..") {
                        if (current_node->parent != nullptr) {
                            current_node = current_node->parent;
                        }
                    }
                    else if (t[2] == "/") {
                        current_node = root;
                    }
                    else {
                        // go to folder t[2]
                        for (const auto& f : current_node->nodes) {
                            if (f->name == t[2]) {
                                current_node = f;
                                break;
                            }
                        }
                    }
                    k++;
                }
                else if (t[1] == "ls") {
                    k++;
                    while (k < input.size() && input[k][0] != '$') {
                        std::vector<std::string> t1 = utils::splitString(input[k], " ");
                        if (t1[0] == "dir") {
                            Node* tmp = new Node();
                            tmp->size = 0;
                            tmp->parent = current_node;
                            tmp->name = t1[1];
                            current_node->nodes.push_back(tmp);
                        }
                        else {
                            Node* t = current_node;
                            while (t != nullptr) {
                                t->size += std::stoi(t1[0]);
                                t = t->parent;
                            }
                        }
                        k++;
                    }
                }
            }
        }
    }

    long long part_1(std::string_view path) {
        struct Node* root = new Node();
        root->parent = nullptr;
        root->size = 0;
        root->name = "";

        buildTree(path, root);

        return dfs_part1(root);
    }

    long long part_2(std::string_view path) {
        struct Node* root = new Node();
        root->parent = nullptr;
        root->size = 0;
        root->name = "";
        buildTree(path, root);

        long long freeSpace = TOTAL_SPACE_PART_2 - root->size;
        long long spaceToDelete = SPACE_NEEDED_PART_2 - freeSpace;

        return dfs_part2(root, spaceToDelete);
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2022_day07::part_1("../2022/day07/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2022_day07::part_2("../2022/day07/input.in") << std::endl;

    return 0;
}
#endif
