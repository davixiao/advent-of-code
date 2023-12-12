#include <iostream>
#include <numeric>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

constexpr int NUM_N = 1000;

int tot = 0;

bool matches(std::string &s, std::vector<int> &match) {
    std::vector<int> record;
    auto run = 0;
    s += '.';
    for (auto &status : s) {
        if (status == '#') {
            ++run;
        }
        else {
            if (run > 0)
                record.push_back(run);
            run = 0;
        }
    }

    if (record.size() != match.size())
        return false;
    for (auto i = 0; i < record.size(); ++i) {
        if (record[i] != match[i])
            return false;
    }
    return true;
}

void placements(std::string s, int n, std::vector<int> &match) {
    if (n >= s.size()) {
        if (matches(s, match))
            ++tot;
        return;
    }
    if (s[n] != '?') {
        placements(s, n + 1, match);
    }
    else {
        s[n] = '#';
        placements(s, n + 1, match);
        s[n] = '.';
        placements(s, n + 1, match);
    }
}

int main() {
    std::string record_a, record_b;
    for (auto i = 0; i < NUM_N; ++i) {
        std::cin >> record_a >> record_b;

        // TIL C++ has no builtin split function
        std::vector<int> tokens;
        std::istringstream iss(record_b);
        std::string token;
        while(std::getline(iss, token, ','))  {
            tokens.push_back(std::stoi(token));
        }
        placements(record_a, 0, tokens);
    }
    std::cout << tot << "\n";


    return 0;
}
