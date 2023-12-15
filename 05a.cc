#include <iostream>
#include <numeric>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>

const int NUM_ROWS = 190;

std::vector<long> seeds;
std::vector<std::vector<long>> tuples;

void process_seeds(std::string &s) {
    std::stringstream ss(s);
    std::string token;
    ss >> token;
    while (ss >> token) {
        seeds.push_back(std::stol(token));
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
        for (auto j = 0; j < seeds.size(); ++j) {
            for (auto k = 0; k < tuples.size(); ++k) {
                auto rrange = tuples[k][2];
                if (seeds[j] <= tuples[k][1] + rrange && seeds[j] >= tuples[k][1]) {
                    seeds[j] = tuples[k][0] + (seeds[j] - tuples[k][1]);
                    break;
                }
            }
        }
    }
    // for (auto i = 0; i < seeds.size(); ++i) {
    //     std::cout << seeds[i] << " ";
    // }
    // std::cout << "\n";

    std::cout << *std::min_element(seeds.begin(), seeds.end()) << "\n";

    return 0;
}
