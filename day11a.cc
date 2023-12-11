#include <iostream>
#include <numeric>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

constexpr int NUM_N = 140;

std::vector<std::pair<int, int>> galaxies;

std::vector<std::vector<char>> image (
    NUM_N,
    std::vector<char> (NUM_N)
);

bool empty_col(int col) {
    for (auto i = 0; i < NUM_N; ++i) {
        if (image[i][col] == '#') return false;
    }
    return true;
}

void find_galaxies() {
    int num_rows = 0;
    for (auto i = 0; i < NUM_N; ++i) {
        int num_cols = 0;
        bool found = false;
        for (auto j = 0; j < NUM_N; ++j) {
            if (image[i][j] == '#') {
                found = true;
                galaxies.push_back({i+num_rows, j+num_cols});
            } 
            else {
                if (empty_col(j)) ++num_cols;
            }
        }
        if (!found) ++num_rows;
    }
}

int sum_paths() {
    int ans = 0;
    for (auto i = 0; i < galaxies.size(); ++i) {
        for (auto j = i + 1; j < galaxies.size(); ++j) {
            ans += (std::abs(galaxies[i].first - galaxies[j].first) +
                std::abs(galaxies[i].second - galaxies[j].second));
        }
    }
    return ans;
}

int main() {
    for (auto i = 0; i < NUM_N; ++i) {
        for (auto j = 0; j < NUM_N; ++j) {
            std::cin >> image[i][j];
        }
    }

    find_galaxies();

    std::cout << sum_paths() << "\n";
    return 0;
}
