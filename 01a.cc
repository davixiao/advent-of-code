#include <iostream>
#include <numeric>
#include <vector>
#include <fstream>
#include <string>

const int NUM_ROWS = 1000;

int main() {
    std::string line;
    std::fstream file{"./input/day1a.in"};

    std::vector<int> values;
    for (int i = 0; i < NUM_ROWS; ++i) {
        std::getline(file, line);
        int value = 0;
        for (int j = 0; j < line.size(); ++j) {
            if (isdigit(line[j])) {
                value += (line[j] - '0') * 10;
                break;
            }
        }
        for (int j = line.size() - 1; j > -1; --j) {
            if (isdigit(line[j])) {
                value += line[j] - '0';
                break;
            }
        }
        values.push_back(value);    
    }
    const auto sum = std::accumulate(std::begin(values), std::end(values), 0);
    std::cout << sum << "\n";
    return 0;
}
