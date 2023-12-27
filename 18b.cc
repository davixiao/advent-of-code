#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <charconv>
#include <math.h>

constexpr int N = 674;

double shoelace(std::vector<std::pair<int, int>> points) {
    // shoelace
    long long left = 0, right = 0;
    for (auto i = 0; i < points.size(); ++i) {
        auto j = (i + 1) % points.size();
        left += (long long) points[i].first * (long long) points[j].second; 
        right += (long long) points[j].first * (long long) points[i].second;
    }
    return 0.5 * (double) abs(left - right);
}

long long picks(double area, int sz) {
    // A = i + b/2 - 1
    // + points on edge
    return (long long) (area - sz/2.0 + 1) + (long long) sz;
}

std::unordered_map<char, std::pair<int, int>> dirs = {
    {'R', {0, 1}},
    {'L', {0, -1}},
    {'U', {-1, 0}},
    {'D', {1, 0}}
};

int main() {
    std::vector<std::pair<int, int>> points {{0, 0}};

    char dir;
    int dist;
    std::string hex;
    for (auto i = 0; i < N; ++i) {
        std::cin >> dir >> dist >> hex;
        int d;
        std::from_chars(hex.c_str() + 2, hex.c_str()+7, d, 16);
        switch (hex[7]) {
        case '0':
            dir = 'R';
            break;
        case '1':
            dir = 'D';
            break;
        case '2':
            dir = 'L';
            break;
        case '3':
            dir = 'U';
            break;
        }
        for (auto j = 0; j < d; ++j) {
            points.push_back({
                points.back().first + dirs[dir].first,
                points.back().second + dirs[dir].second
            });
        }

    }
    std::cout << picks(shoelace(points), points.size()) << "\n";
    return 0;
}
