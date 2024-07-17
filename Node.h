#ifndef NODE_H
#define NODE_H

#include <string>
#include <unordered_map>
#include "utility.hpp"

struct Node {
    std::string word;
    std::unordered_map<int, Node*, Utility::HashFunction> children{};
    explicit Node(std::string word) : word(std::move(word)) {}
};

#endif
