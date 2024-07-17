#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <stdexcept>
#include <thread>
#include <bit>
#include <queue>
#include "BKTree.h"

constexpr int MAX_EDIT_DISTANCE = 4;

BKTree::BKTree() : root(nullptr), count(0) {}

BKTree::~BKTree() {
    reset();
}

BKTree::BKTree(BKTree&& other) noexcept : root(other.root), count(other.count) {
    other.root = nullptr;
    other.count = 0;
}

BKTree& BKTree::operator=(BKTree&& other) noexcept {
    if (this != &other) {
        reset();
        root = other.root;
        count = other.count;
        other.root = nullptr;
        other.count = 0;
    }
    return *this;
}

// Return the closest word from the dictionary such that their edit distance is not larger than max distance given.
// A wrapper pair will be return such that its boolean member indicates if at least one of the best matches is found.
[[nodiscard]] bool BKTree::find_closest_word(const std::string& word, int max_distance, std::string& closest_word) const {
    if (!root) {
        throw std::runtime_error("BKTree not initialized");
    }
    if (max_distance > MAX_EDIT_DISTANCE) {
        throw std::runtime_error("The max edit distance cannot be larger than " + std::to_string(MAX_EDIT_DISTANCE));
    }
    // Breadth-First Search
    std::queue<Node*> candidates;
    candidates.push(root);
    std::string().swap(closest_word);
    int min_distance = max_distance + 1;
    Node* node;
    int distance;
    bool match_found = false;

    while (!candidates.empty()) {
        node = candidates.front();
        candidates.pop();
        distance = Utility::levenshtein_distance(word, node->word);
        if (distance < min_distance) {
            min_distance = distance;
            closest_word = node->word;
            match_found = true;
        }
        if (min_distance == 0) {
            break;
        }
        for (int i = std::max(0, distance - max_distance); i <= distance + max_distance; ++i) {
            auto it = node->children.find(i);
            if (it != node->children.end()) {
                candidates.push(it->second);
            }
        }
    }
    return match_found;
}

void BKTree::set_dictionary(const std::vector<std::string>& words) {
    if (words.empty()) {
        throw std::runtime_error("Dictionary cannot be empty!");
    }
    reset();
    int reserve_slots = static_cast<int>(std::bit_ceil(words.size()));
    std::unordered_set<std::string> unique_words;
    unique_words.reserve(reserve_slots);
    for (const auto& word : words) {
        unique_words.insert(word);
    }
    std::vector<std::string> unique_wordlist(unique_words.begin(), unique_words.end());
    std::sort(unique_wordlist.begin(), unique_wordlist.end());
    for (const auto& word : unique_wordlist) {
        insert(word);
    }
}

void BKTree::reset() {
    delete_node(root);
    root = nullptr;
}

[[nodiscard]] int BKTree::get_count() const {
    return count;
}

void BKTree::delete_node(Node* node) {
    if (node) {
        for (auto& child : node->children) {
            delete_node(child.second);
        }
        delete node;
        --count;
    }
}

void BKTree::insert(const std::string& word) {
    if (!root) {
        root = new Node(word);
        ++count;
        return;
    }
    auto node = root;
    int distance;
    while (true) {
        distance = Utility::levenshtein_distance(word, node->word);
        auto it = node->children.find(distance);
        if (it == node->children.end()) {
            node->children[distance] = new Node(word);
            ++count;
            break;
        } else {
            node = it->second;
        }
    }
}
