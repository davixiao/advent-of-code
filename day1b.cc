#include <iostream>
#include <numeric>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_map>
#include <algorithm>

const int NUM_ROWS = 1000;

std::unordered_map<std::string, int> numbers {
    {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4},
    {"five", 5}, {"six", 6}, {"seven", 7}, 
    {"eight", 8}, {"nine", 9},
    {"eno", 1}, {"owt", 2}, {"eerht", 3}, {"ruof", 4},
    {"evif", 5}, {"xis", 6}, {"neves", 7}, 
    {"thgie", 8}, {"enin", 9}
};

int findFirst(std::string const& line) {
    for (int j = 0; j < line.size(); ++j) {
        if (isdigit(line[j])) {
            return (line[j] - '0');
        }
        for (int k = 1; k <= line.size() - j; ++k) {
            const auto s = line.substr(j, k);
            if (numbers.find(s) != numbers.end()) {
                return numbers.at(s);
            }
        }
    }
    return -1;
}

int main() {
    std::string line;
    std::fstream file{"./input/day1a.in"};

    

    std::vector<int> values;
    for (int i = 0; i < NUM_ROWS; ++i) {
        std::getline(file, line);
        const auto first = findFirst(line);
        std::reverse(line.begin(), line.end());
        const auto second = findFirst(line);
        const auto value = first * 10 + second;
        values.push_back(value);    
    }
    const auto sum = std::accumulate(std::begin(values), std::end(values), 0);
    std::cout << sum << "\n";
    return 0;
}
