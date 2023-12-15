#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <algorithm>

constexpr int N = 100;

std::vector<std::string> grid(N);

void rotate_clockwise() { 
    for (auto i = 0; i < N/2; ++i) {
        for (auto j = i; j < N-i-1; ++j) {

            auto tmp = grid[i][j];
            grid[i][j] = grid[N-1-j][i];
            grid[N-1-j][i] = grid[N-1-i][N-1-j];
            grid[N-1-i][N-1-j] = grid[j][N-1-i];
            grid[j][N-1-i] = tmp;
        }
    }
}

int solve() {
    auto ans = 0;
    std::vector<int> available(N, 0);
    for (auto row = 0; row < N; ++row) {
        for (auto col = 0; col < N; ++col) {
            if (grid[row][col] == '#') {
                available[col] = row + 1;
            }
            else if (grid[row][col] == 'O') {

                std::swap(
                    grid[available[col]][col],
                    grid[row][col]
                );
                ans += N - available[col];
                ++available[col];
            }
        }
    }
    return ans;
}

void print() {
    auto ans = 0;
    for (auto row = 0; row < N; ++row) {
        for (auto col = 0; col < N; ++col) {
            std::cout << grid[row][col] << " ";
        }
        std::cout << "\n";
    }
}

int value() {
    auto ans = 0;
    for (auto row = 0; row < N; ++row) {
        for (auto col = 0; col < N; ++col) {
            if (grid[row][col] == 'O') {
                ans += N - row;
            }
        }
    }
    return ans;
}

int main() {
    for (auto i = 0; i < N; ++i) {
        std::cin >> grid[i];
    }
    
    // std::cout << solve() << "\n";
    std::vector<int> cycles;
    for (auto j = 0; j < 1100; ++j) {
        cycles.push_back(value());
        for (auto i = 0; i < 4; ++i) {
            auto t = solve(); // tilts everything
            rotate_clockwise();
        }
    }

    // I just found the cycle by hand
    // the numbers started repeating at 83rd index
    // I could have also written
    // for (auto i = 0; i < cycles.size(); ++i) {
    //     std::cout << cycles[i] << "\n";
    // }


    constexpr int start = 83;
    constexpr int end = 154;
    constexpr int length = end - start + 1;
    std::cout << cycles[(1000000000-start) % length + start] << "\n";

    return 0;
}
