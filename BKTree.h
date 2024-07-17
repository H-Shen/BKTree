#ifndef BKTREE_H
#define BKTREE_H

#include "Node.h"

class BKTree {
public:
    BKTree();
    ~BKTree();
    BKTree(const BKTree& other) = delete;
    BKTree& operator=(const BKTree& other) = delete;
    BKTree(BKTree&& other) noexcept;
    BKTree& operator=(BKTree&& other) noexcept;
    [[nodiscard]] bool find_closest_word(const std::string& word, int max_distance, std::string& closest_word) const;
    void set_dictionary(const std::vector<std::string>& words);
    void reset();
    [[nodiscard]] int get_count() const;
private:
    Node* root;
    void delete_node(Node* node);
    void insert(const std::string& word);
    int count;
};

#endif
