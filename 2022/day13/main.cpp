#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <compare>

namespace aoc2022_day13 {
    struct Node {
        Node() {
            val = 0;
            parent = nullptr;
        }
        Node(int x, Node* p) {
            val = x;
            parent = p;
        }
        int val;
        std::vector<Node*> nodes;
        Node* parent;
    };

    void buildTree(std::string_view str, struct Node* root) {
        int i = 1;
        struct Node* current_node = root;
        while (i < str.size() - 1) {
            if (str[i] == '[') {
                Node *t = new Node(-1, current_node);
                current_node->nodes.push_back(t);
                current_node = t;
                i++;
            }
            else if (str[i] == ']') {
                current_node = current_node->parent;
                i++;
            }
            else if (str[i] == ',') {
                i++;
            }
            else {
                Node *t = new Node(utils::getNumber(str, i), current_node);
                current_node->nodes.push_back(t);
            }
        }
    }

    Node* buildTree(std::string_view str) {
        Node* root = new Node(-1, nullptr);
        buildTree(str, root);
        return root;
    }

    std::weak_ordering compare(Node* t1, Node* t2) {
        if (t1->val > -1 && t2->val > -1) {
            return t1->val <=> t2->val;
        }
        else if (t1->val == -1 && t2->val == -1) {
            int i = 0;
            while (i < t1->nodes.size() && i < t2->nodes.size()) {
                auto s = compare(t1->nodes[i], t2->nodes[i]);
                if (s != std::weak_ordering::equivalent) {
                    return s;
                }
                i++;
            }
            if (i == t1->nodes.size() && i < t2->nodes.size()) {
                return std::weak_ordering::less;
            }
            else if (i < t1->nodes.size() && i == t2->nodes.size()) {
                return std::weak_ordering::greater;
            }
            else {
                return std::weak_ordering::equivalent;
            }
        }
        else if (t1->val > -1 && t2->val == -1) {
            Node *t = new Node(-1, nullptr);
            t->nodes.push_back(t1);
            return compare(t, t2);
        }
        else {
            Node *t = new Node(-1, nullptr);
            t->nodes.push_back(t2);
            return compare(t1, t);
        }
    }

    int smaller(const std::vector<Node*>& nodes, std::string_view s) {
        int nr = 1;
        Node *t = buildTree(s);
        for (const auto& node : nodes) {
            if (compare(node, t) == std::weak_ordering::less) {
                nr++;
            }
        }
        return nr;
    }

    int part_1(std::string_view path) {
        int sol = 0;

        std::vector<std::string> input = file::readFileAsArrayString(path);
        for (const auto& l : input) {
            std::vector<std::string> t = utils::splitString(l, " ");
        }

        int index = 0;
        for (int i = 0; i < input.size(); i += 3) {
            index++;
            Node *t1 = buildTree(input[i]);
            Node *t2 = buildTree(input[i + 1]);

            if (compare(t1, t2) == std::strong_ordering::less) {
                sol += index;
            }
        }

        return sol;
    }

    int part_2(std::string_view path) {
        std::vector<Node*> nodes;
        std::vector<std::string> input = file::readFileAsArrayString(path);

        for (int i = 0; i < input.size(); i++) {
            if (input[i] != "") {
                Node *t = buildTree(input[i]);
                nodes.push_back(t);
            }
        }

        return smaller(nodes, "[[2]]") * (smaller(nodes, "[[6]]") + 1);
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2022_day13::part_1("../2022/day13/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2022_day13::part_2("../2022/day13/input.in") << std::endl;

    return 0;
}
#endif
