#include <iostream>
#include <numeric>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <array>

constexpr int NUM_N = 1000;
constexpr int SZ = 110;
long dp[SZ][SZ][SZ];

std::string record_a, record_b;
std::vector<int> tokens;

// i = curr index of record
// j = next token count to match
// k = current token count
long solve(int i, int j, int k) {
    if (i >= record_a.size()) {
        return j == tokens.size();
    }
    if (dp[i][j][k] != -1)
        return dp[i][j][k];
    
    long ans = 0;
    if (record_a[i] == '#' || record_a[i] == '?') {
            ans += solve(i+1, j, k+1);
    }
    if (record_a[i] == '.' || record_a[i] == '?') {
        if (j < tokens.size() && k == tokens[j]) {
            ans += solve(i+1, j+1, 0);
        }
        else if (k == 0) {
            ans += solve(i+1, j, 0);
        }
    }
    
    return dp[i][j][k] = ans;
}

void reset_table() {
    for (auto i = 0; i < SZ; ++i) {
        for (auto j = 0; j < SZ; ++j) {
            for (auto k = 0; k < SZ; ++k) {
                dp[i][j][k] = -1;
            }
        }
    }
}

int main() {
    
    long ans = 0;
    for (auto i = 0; i < NUM_N; ++i) {
        reset_table();
        std::cin >> record_a >> record_b;

        // TIL C++ has no builtin split function
        tokens.clear();
        std::istringstream iss(record_b);
        std::string token;
        while(std::getline(iss, token, ','))  {
            tokens.push_back(std::stoi(token));
        }
        
        std::string cpy = record_a;
        std::vector<int> cpy_token = tokens;
        for (auto j = 0; j < 4; ++j) {
            record_a += "?" + cpy;
            tokens.insert(tokens.end(), cpy_token.begin(), cpy_token.end());
        }
        
        record_a += ".";
        ans += solve(0, 0, 0);
    }
    std::cout << ans << "\n";

    return 0;
}
