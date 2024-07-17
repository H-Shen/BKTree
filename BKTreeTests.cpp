#include <cassert>
#include <iostream>
#include "BKTree.h"

int main() {

    // Create a BKTree instance
    BKTree tree;
    // Test adding words
    std::vector<std::string> dictionary = {"hello", "world", "help"};
    tree.set_dictionary(dictionary);

    // Test searching for similar words
    std::string answer;
    bool result = tree.find_closest_word("hell", 1, answer);
    assert(result);
    std::cout << answer << '\n';

    result = tree.find_closest_word("help", 0, answer);
    assert(result);
    std::cout << answer << '\n';

    result = tree.find_closest_word("hero", 2, answer);
    assert(result);
    std::cout << answer << '\n';

    return 0;
}