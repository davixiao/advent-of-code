#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>

std::vector<std::string> ttime;
std::vector<std::string> dist;

const int NUM_COLS = 4;

int main() {
    std::string tmp;
    std::cin >> tmp;
    ttime.resize(NUM_COLS);
    dist.resize(NUM_COLS);
    std::cin >> ttime[0] >> ttime[1] >> ttime[2] >> ttime[3];
    std::cin >> tmp;
    std::cin >> dist[0] >> dist[1] >> dist[2] >> dist[3];
    
    std::string stime = ttime[0] + ttime[1] + ttime[2] + ttime[3];
    std::string sdist = dist[0] + dist[1] + dist[2] + dist[3];

    auto total_time = std::stol(stime);
    auto total_dist = std::stol(sdist);
    auto speed = 0;
    auto cnt = 0;
    for (auto t = 0; t <= total_time; ++t) {
        if (speed * (total_time - t) > total_dist) {
            ++cnt;
        }
        ++speed;
    }
    
    std::cout << cnt << "\n";
    return 0;
}
