#include <iostream>
#include <numeric>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>

const int NUM_ROWS = 190;

std::vector<std::pair<long, long>> seeds;
std::vector<std::vector<long>> tuples;

void process_seeds(std::string &s) {
    std::stringstream ss(s);
    std::string a, b;
    ss >> a;
    while (ss >> a >> b) {
        std::pair<long, long> tmp = {std::stol(a),std::stol(a) + std::stol(b) - 1};
        seeds.push_back(tmp);
    }
}

void process_tuple(std::string &s) {
    std::stringstream ss(s);
    std::string token;
    std::vector<long> tuple(3);
    std::string a, b, c;
    ss >> a >> b >> c;
    tuple[0] = std::stol(a);
    tuple[1] = std::stol(b);
    tuple[2] = std::stol(c);
    tuples.push_back(tuple);
}

int main() {
    std::string line;
    std::fstream file{"./input/day5.in"};
    std::getline(file, line); // seed
    process_seeds(line);
    std::getline(file, line); // empty

    for (auto i = 0; i < 7; ++i) {
        tuples.clear();
        std::getline(file, line); // header
        std::getline(file, line);
        while (line != "") {
            process_tuple(line);
            std::getline(file, line);
        }
        std::sort(tuples.begin(), tuples.end());

        std::vector<std::pair<long ,long>> new_seeds;
        for (auto j = 0; j < seeds.size(); ++j) {
            std::vector<std::pair<long, long>> overlapped;
            for (auto k = 0; k < tuples.size(); ++k) {
                auto sstart = tuples[k][1];
                auto eend = tuples[k][1] + tuples[k][2] - 1;
                if (sstart <= seeds[j].second && seeds[j].first <= eend) {
                    auto diff = tuples[k][1] - tuples[k][0];
                    std::pair<long, long> overlap = {std::max(seeds[j].first, sstart) - diff, 
                        std::min(seeds[j].second, eend) - diff};
                    new_seeds.push_back(overlap);
                    overlapped.push_back({
                        std::max(seeds[j].first, sstart), std::min(seeds[j].second, eend)
                    });
                }
            }
            overlapped.push_back({seeds[j].first-1, seeds[j].first-1});
            overlapped.push_back({seeds[j].second+1, seeds[j].second+1});
            std::sort(overlapped.begin(), overlapped.end());
            for (auto j = 1; j < overlapped.size(); ++j) {
                if (overlapped[j-1].second + 1 < overlapped[j].first) {
                    new_seeds.push_back({overlapped[j-1].second + 1, overlapped[j].first-1});
                }
            }
        }
        seeds.clear();
        seeds.insert(std::end(seeds), std::begin(new_seeds), std::end(new_seeds));
    }
    long ans = 2e16;
    for (auto i = 0; i < seeds.size(); ++i) {
        ans = std::min(ans, seeds[i].first);
    }
    std::cout << ans << "\n";

    return 0;
}
