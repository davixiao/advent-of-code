#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>

std::vector<int> ttime;
std::vector<int> dist;

const int NUM_COLS = 4;

int main() {
    std::string tmp;
    std::cin >> tmp;
    ttime.resize(NUM_COLS);
    dist.resize(NUM_COLS);
    std::cin >> ttime[0] >> ttime[1] >> ttime[2] >> ttime[3];
    std::cin >> tmp;
    std::cin >> dist[0] >> dist[1] >> dist[2] >> dist[3];
    auto ans = 1;
    for (auto i = 0; i < NUM_COLS; ++i) {
        auto speed = 0;
        auto cnt = 0;
        for (auto t = 0; t <= ttime[i]; ++t) {
            if (speed * (ttime[i] - t) > dist[i]) {
                ++cnt;
            }
            ++speed;
        }
        ans *= cnt;
    }
    std::cout << ans << "\n";
    return 0;
}
