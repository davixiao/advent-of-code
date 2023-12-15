#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <set>

std::unordered_map<std::string, 
    std::pair<std::string, std::string>> mp;

std::unordered_map<std::string, 
    std::vector<int>> dists;

std::set<std::pair<std::string, int>> seen;

int main() {
    std::string moves;
    std::cin >> moves;

    std::string a, b, c, d;
    while (std::cin >> a >> b >> c >> d) {
        mp[a] = {c.substr(1, 3), d.substr(0, 3)};
    }

    for (auto v : mp) {
        if (v.first[2] != 'A') continue;
        std::cout << v.first << "\n";
        std::string curr = v.first;
        auto pos = 0;
        auto cnt = 1; // I forgot, we need to count number of nodes, not distance
        seen.clear();
        while (seen.find({curr, pos}) == seen.end()) {
          
            seen.insert({curr, pos});
            if (moves[pos] == 'L') {
                curr = mp[curr].first;
            }
            else {
                curr = mp[curr].second;
            }
            if (curr[2] == 'Z') {
                dists[v.first].push_back(cnt);
            }
            ++cnt;
            ++pos;
            if (pos >= moves.size()) pos = 0;
        }
    }
    for (auto &v : dists) {
        std::cout << v.first << "\n";
        for (auto &j : v.second) {
            std::cout << j << "\n";
        }
    }

    long long x = (long long) dists["AAA"][0];
    // originally just inputted into LCM calculator online
    // came back to implement my own
    for (auto &v : dists) {
        // each node only touches one Z per cycle apparently
        // c++17 has lcm
        x = std::lcm(x, (long long)v.second[0]);
    }
    std::cout << x << "\n";
    return 0;
}
