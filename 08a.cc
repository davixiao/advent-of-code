#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>

std::unordered_map<std::string, 
    std::pair<std::string, std::string>> mp;

int main() {
    std::string moves;
    std::cin >> moves;

    std::string a, b, c, d;
    while (std::cin >> a >> b >> c >> d) {
        mp[a] = {c.substr(1, 3), d.substr(0, 3)};
    }

    std::string curr = "AAA";
    int pos = 0;
    int cnt = 0;
    while (curr != "ZZZ") {
        if (moves[pos] == 'L') {
            curr = mp[curr].first;
        }
        else {
            curr = mp[curr].second;
        }
        ++cnt;
        ++pos;
        if (pos >= moves.size()) pos = 0;
    }
    std::cout << cnt << "\n";
    return 0;
}
