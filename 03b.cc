#include <iostream>
#include <numeric>
#include <vector>
#include <fstream>
#include <string>

const int N = 140;

char access(const std::vector<std::string> &grid, int i, int j) {
    if (i < 0 || i > N) {
        return '.';
    }
    if (j < 0 || j > N) {
        return '.';
    }
    return grid[i][j];
}

int findNum(std::vector<std::string> &grid, int r, int c) {
    if (!isdigit(access(grid, r, c))) return 0;
    std::string ret;
    ret = grid[r][c];
    grid[r][c] = '.';
    for (int i = c+1; i < N; ++i) {
        if (!isdigit(grid[r][i])) break;
        ret += grid[r][i];
        grid[r][i] = '.';
    }
    for (int i = c-1; i > -1; --i) {
        if (!isdigit(grid[r][i])) break;
        ret.insert(0, 1, grid[r][i]);
        grid[r][i] = '.';
    }
    return std::stoi(ret);
}

int solve(std::vector<std::string> &grid) {
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (grid[i][j] == '*') {
                std::vector<int> tmp;
                
                tmp.push_back(findNum(grid, i+1, j));
                tmp.push_back(findNum(grid, i-1, j));
                tmp.push_back(findNum(grid, i, j+1));
                tmp.push_back(findNum(grid, i, j-1));
                tmp.push_back(findNum(grid, i+1, j+1));
                tmp.push_back(findNum(grid, i-1, j-1));
                tmp.push_back(findNum(grid, i+1, j-1));
                tmp.push_back(findNum(grid, i-1, j+1));

                int tot = 1;
                int cnt = 0;
                for (int k = 0; k < tmp.size(); ++k) {
                    if (tmp[k] != 0) {
                        tot *= tmp[k];
                        ++cnt;
                    }
                }
                if (cnt == 2) {
                    ans += tot;
                }
            }
        }
    }
    return ans;
}

int main() {
    std::string line;
    std::fstream file{"./input/day3.in"};

    std::vector<std::string> grid;

    for (int i = 1; i <= N; ++i) {
        std::getline(file, line);
        grid.push_back(line);
    }
    std::cout << solve(grid) << "\n";
    return 0;
}
