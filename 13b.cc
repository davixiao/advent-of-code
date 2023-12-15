#include <iostream>
#include <numeric>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

int horizontal(std::vector<std::string> &grid) {
    for (auto split = 0; split < grid.size() - 1; ++split) {
        auto top = split;
        auto bot = split+1;
        bool good = true;
        int lives = 1;
        while (0 <= top && bot < grid.size()) {
            for (auto i = 0; i < grid[top].size(); ++i) {
                if (grid[top][i] != grid[bot][i]) {
                    if (lives) {
                        --lives;
                    }
                    else {
                        good = false;
                        break;
                    }
                }
            }
            --top;
            ++bot;
        }
        if (good && lives == 0) return 100 * split + 100;
    }
    return 0;
}

int vertical(std::vector<std::string> &grid) {
    for (auto split = 0; split < grid[0].size() - 1; ++split) {
        auto left = split;
        auto right = split+1;
        bool good = true;
        int lives = 1;
        while (0 <= left && right < grid[0].size()) {
            for (auto i = 0; i < grid.size(); ++i) {
                if (grid[i][left] != grid[i][right]) {
                    if (lives) {
                        --lives;
                    }
                    else {
                        good = false;
                        break;
                    }
                }
            }
            --left;
            ++right;
        }
        if (good && lives == 0) return split + 1;
    }
    return 0;
}

int main() {
    std::string line;
    std::vector<std::string> grid;
    auto ans = 0;
    while (std::getline(std::cin, line)) {
        if (line == "") {
            ans += horizontal(grid) + vertical(grid);
            grid.clear();
        }
        else {
            grid.push_back(line);
        }
    }
    
    ans += horizontal(grid) + vertical(grid);
    std::cout << ans << "\n";

    return 0;
}
