#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

constexpr int N = 674;

double shoelace(std::vector<std::pair<int, int>> points) {
    // shoelace
    double left = 0, right = 0;
    for (auto i = 0; i < points.size(); ++i) {
        auto j = (i + 1) % points.size();
        left += points[i].first * points[j].second; 
        right += points[j].first * points[i].second;
    }
    return 0.5 * abs(left - right);
}

int picks(double area, int sz) {
    // A = i + b/2 - 1
    // + points on edge
    return (int) (area - sz/2.0 + 1) + sz;
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
        for (auto j = 0; j < dist; ++j) {
            points.push_back({
                points.back().first + dirs[dir].first,
                points.back().second + dirs[dir].second
            });
        }
    }
    std::cout << picks(shoelace(points), points.size()) << "\n";
    return 0;
}
