#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <algorithm>

constexpr int N = 140; // 140

std::vector<std::string> grid;
std::unordered_map<char, std::pair<int, int>> dirs {
    {'N', {-1, 0}},
    {'S', {1, 0}},
    {'W', {0, -1}},
    {'E', {0, 1}}
};

std::unordered_map<char, std::vector<char>> pipe_dirs {
    {'|', {'N', 'S'}},
    {'-', {'E', 'W'}},
    {'L', {'N', 'E'}},
    {'J', {'N', 'W'}},
    {'7', {'S', 'W'}},
    {'F', {'S', 'E'}},
    {'.', {}},
    {'S', {'N', 'S', 'E', 'W'}}
};

std::pair<int, int> next(int r, int c, char dir) {
    return {
        r + dirs[dir].first,
        c + dirs[dir].second
    };
}

bool go_next(int nxt_r, int nxt_c, char curr_dir) {
    auto pipe = pipe_dirs[grid[nxt_r][nxt_c]];

    if (curr_dir == 'N')
        return std::find(pipe.begin(), pipe.end(), 'S') != pipe.end();
    else if (curr_dir == 'S')
        return std::find(pipe.begin(), pipe.end(), 'N') != pipe.end();
    else if (curr_dir == 'E')
        return std::find(pipe.begin(), pipe.end(), 'W') != pipe.end();
    else if (curr_dir == 'W')
        return std::find(pipe.begin(), pipe.end(), 'E') != pipe.end();
    return false;
}

bool bounds(int r, int c) {
    return (0 <= r && r < N) && (0 <= c && c < N);
}


int solve(int si, int sj) {
    std::vector<std::vector<int>> dists (
        N,
        std::vector<int> (N, -1)
    );

    std::queue<std::pair<int, int>> q;
    dists[si][sj] = 0;
    q.push({si, sj});

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        auto pipe = pipe_dirs[grid[r][c]];
        for (auto dir : pipe) {
            auto [nxt_r, nxt_c] = next(r, c, dir);
            if (bounds(nxt_r, nxt_c) && go_next(nxt_r, nxt_c, dir)) {
                if (dists[nxt_r][nxt_c] == -1) {
                    dists[nxt_r][nxt_c] = dists[r][c] + 1;
                    q.push({nxt_r, nxt_c});
                }
            }
        }
    }

    int ans = 0;
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < N; ++j) {
            ans = std::max(ans, dists[i][j]);
        }
    }

    return ans;
}

int main() {
    std::string line;
    for (auto i = 0; i < N; ++i) {
        std::getline(std::cin, line);
        grid.push_back(line);
    }

    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < N; ++j) {
            if (grid[i][j] == 'S') {
                std::cout << solve(i, j) << "\n";
                return 0;
            }
        }
    }

    return 0;
}
