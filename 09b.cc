#include <iostream>
#include <numeric>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

constexpr int NUM_ROWS = 200; // 200

int solve(std::string &s) {
    std::vector<std::vector<int>> seqs;
    seqs.resize(1);
    std::stringstream ss(s);
    std::string token;
    while (ss >> token) {
        seqs[0].push_back(std::stoi(token));
    }
    // I used this loop condition since input seemed to be increasing
    while (std::accumulate(std::begin(seqs[seqs.size()-1]), 
        std::end(seqs[seqs.size()-1]), 0) != 0) {
        std::vector<int> tmp;
        for (auto i = 1; i < seqs[seqs.size()-1].size(); ++i) {
            tmp.push_back(seqs[seqs.size()-1][i] - seqs[seqs.size()-1][i-1]);
        }
        seqs.push_back(tmp);

    }

    // pattern: alternate adding or subtracting front values
    // idk why maybe since all sequences are increasing. Might be wrong :O
    int ret = 0;
    for (auto i = 0; i < seqs.size(); ++i) {
        if (i % 2 == 0)
            ret += seqs[i][0];
        else
            ret -= seqs[i][0];
    }
    return ret;
}

int main() {
    std::vector<int> values;
    std::string line;
    int ans = 0;
    for (int i = 0; i < NUM_ROWS; ++i) {
        std::getline(std::cin, line);
        ans += solve(line);
    }
    std::cout << ans << "\n";
    return 0;
}
