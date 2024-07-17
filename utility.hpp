#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>
#include <vector>
#include <chrono>

namespace Utility {
    struct HashFunction {
        static uint64_t splitmix64(uint64_t x) {
            // http://xorshift.di.unimi.it/splitmix64.c
            x += 0x9e3779b97f4a7c15;
            x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
            x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
            return x ^ (x >> 31);
        }

        size_t operator()(uint64_t x) const {
            static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
            return splitmix64(x + FIXED_RANDOM);
        }

        // For a pair of integers
        size_t operator()(std::pair<uint64_t, uint64_t> x) const {
            static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
            return splitmix64(x.first + FIXED_RANDOM) ^
                   (splitmix64(x.second + FIXED_RANDOM) >> 1);
        }
    };
    // Get the edit distance between s1 and s2
    static int levenshtein_distance(const std::string& s1, const std::string& s2) {
        int m = static_cast<int>(s1.size());
        int n = static_cast<int>(s2.size());
        std::vector<std::vector<int>> d(m + 1, std::vector<int>(n + 1));
        for (int i = 0; i <= m; ++i) d[i][0] = i;
        for (int j = 0; j <= n; ++j) d[0][j] = j;
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                int cost = s1[i - 1] == s2[j - 1] ? 0 : 1;
                d[i][j] = std::min({ d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + cost });
            }
        }
        return d[m][n];
    }
}

#endif
