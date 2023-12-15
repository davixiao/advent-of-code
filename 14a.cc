#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <algorithm>

constexpr int N = 100;

std::vector<std::string> grid(N);

int solve() {
    auto ans = 0;
    std::vector<int> available(N, 0);
    for (auto row = 0; row < N; ++row) {
        for (auto col = 0; col < N; ++col) {
            if (grid[row][col] == '#') {
                available[col] = row + 1;
            }
            else if (grid[row][col] == 'O') {
                ans += N - available[col];
                ++available[col];
            }
        }
    }
    return ans;
}

int main() {
    for (auto i = 0; i < N; ++i) {
        std::cin >> grid[i];
    }
    
    std::cout << solve() << "\n";

    return 0;
}
