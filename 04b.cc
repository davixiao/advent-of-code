#include <iostream>
#include <numeric>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

const int NUM_ROWS = 190;

int solve(std::string &s) {
    std::stringstream ss(s);
    std::string token;

    ss >> token; ss >> token; ss >> token;
    std::vector<int> winners;
    while (token != "|") {
        winners.push_back(std::stoi(token));
        ss >> token;
    }
    int tot = 0;
    while (ss >> token) {
        int num = std::stoi(token);
        if (std::find(winners.begin(), winners.end(), num) != winners.end()) {
            ++tot;
        }
    }
    return tot;
}

int main() {
    std::string line;
    std::fstream file{"./input/day4.in"};
    auto ans = 0;
    std::vector<int> cnt(NUM_ROWS);
    for (int i = 0; i < NUM_ROWS; ++i) {
        std::getline(file, line);
        ++cnt[i];
        ans += cnt[i];
        auto num = solve(line);
        for (int j = i + 1; j <= i+num; ++j) {
            cnt[j] += cnt[i];
        }
    }
    std::cout << ans << "\n";
    return 0;
}
