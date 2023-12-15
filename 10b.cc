/**
 * Not very clean. 
 * expand each pixel to 3x3.
 *     .|.
 * | = .|.
 *     .|.
 * I reused dist array alot. -2 for outside, -3 for inside loop
 * then, just count the number of original "." that have dist = -3
 * 
 * spent a lot of time debugging --> writing messy code. Need to
 * revisit.
 */
#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <algorithm>

constexpr int N = 141; // 141
constexpr int TN = 3*N; // 141


std::vector<std::string> grid_old;

std::vector<std::vector<int>> dists (
    TN,
    std::vector<int> (TN, -1)
);

std::vector<std::vector<char>> grid (
    TN,
    std::vector<char> (TN, '.')
);

void expand() {
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < N; ++j) {
            auto ti = 3*i + 1;
            auto tj = 3*j + 1;
            // x . .
            // . . .
            // . . .
            if (grid_old[i][j] == '-') {
                grid[ti][tj] = '-';
                grid[ti][tj+1] = '-';
                grid[ti][tj-1] = '-';
            }
            else if (grid_old[i][j] == '|') { 
    
                grid[ti][tj] = '|';
                grid[ti-1][tj] = '|';
                grid[ti+1][tj] = '|';

            }
            else if (grid_old[i][j] == 'F') {
                grid[ti][tj] = 'F';
                grid[ti][tj+1] = '-';
                grid[ti+1][tj] = '|';
            }
            else if (grid_old[i][j] == '7') {
                grid[ti][tj] = '7';
                grid[ti][tj-1] = '-';
                grid[ti+1][tj] = '|';
            }
            else if (grid_old[i][j] == 'L') {
                grid[ti][tj] = 'L';
                grid[ti][tj+1] = '-';
                grid[ti-1][tj] = '|';
            }
            else if (grid_old[i][j] == 'J') {
                grid[ti][tj] = 'J';
                grid[ti][tj-1] = '-';
                grid[ti-1][tj] = '|';
            }
            else if (grid_old[i][j] == 'S') {
                // S can take any pipe form, I just looked at my dataset to tell which one
                // it is.
                grid[ti][tj] = 'S';
                grid[ti-1][tj] = '|';
                grid[ti+1][tj] = '|';
            }
        }
    }
}

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
    return (0 <= r && r < TN) && (0 <= c && c < TN);
}


int solve(int si, int sj) {
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
                    dists[nxt_r][nxt_c] = dists[r][c];
                    if (nxt_r % 3 == 0 && nxt_c % 3 == 0) dists[nxt_r][nxt_c]++;
                    q.push({nxt_r, nxt_c});
                }
            }
        }
    }

    int ans = 0;
    for (auto i = 0; i < TN; ++i) {
        for (auto j = 0; j < TN; ++j) {
            ans = std::max(ans, dists[i][j]);
        }
    }

    return ans;
}

int cnt_points() {
    int cnt = 0;
    for (auto r = 0; r < N; ++r) {
        for (auto c = 0; c < N; ++c) {
            auto tr = 3*r + 1;
            auto tc = 3*c + 1;
            if (dists[tr][tc] == -3) {
                ++cnt;
            }
        }
    }
    
    return cnt;
}

int bfs(int si, int sj, int cnt) {
    // int tot = 0;
    std::queue<std::pair<int, int>> q;
    dists[si][sj] = cnt;
    q.push({si, sj});

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        for (auto &dir : dirs) {
            auto [dr, dc] = dir.second;
            auto nr = r + dr;
            auto nc = c + dc;
            if (bounds(nr, nc)  && dists[nr][nc] == -1) {
                dists[nr][nc] = cnt;
                q.push({nr, nc});
            }
        }
    }
    return 0;
}

// if we touch a border, we should be able to directly connect

void fill() {
    int cnt = -2;
    int ans = 0;
    for (auto i = 0; i < TN; ++i) {
        for (auto j = 0; j < TN; ++j) {
            if (dists[i][j] == -1) {
                // this should only run twice
                // 50/50 chance on which one is our answer lol

                int a =  bfs(i, j, cnt);
                if (a > 0) {
                    std::cout << cnt << " " << a << "\n";
                }
                cnt -= 1;
            }
        }
    }
    std::cout << ans << "\n";
}

int main() {
    // pad grid with 0s on top and left to avoid out of bounds
    grid_old.push_back(std::string(N, '*'));

    std::string line;    
    for (auto i = 0; i < N; ++i) {
        std::getline(std::cin, line);
        grid_old.push_back('*' + line);
    }

    expand();
   


    for (auto i = 0; i < TN; ++i) {
        for (auto j = 0; j < TN; ++j) {
            if (grid[i][j] == 'S') {
                std::cout << solve(i, j) << "\n";
            }
        }
    }
 
    fill();
    std::cout << cnt_points() << "\n";
    
    return 0;
}
