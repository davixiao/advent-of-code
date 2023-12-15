#include <iostream>
#include <numeric>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

const int NUM_ROWS = 100;

bool valid(int red, int green, int blue) {
    return red <= 12 && green <= 13 && blue <= 14;
}

bool validRound(std::string &s) {
    std::stringstream ss(s);
    std::string token;

    ss >> token; ss >> token;
    auto currNum = -1;

    while (ss >> token) {
        if (currNum == -1) {
            currNum = std::stoi(token);
        } else {
            auto color = token.substr(0, token.size()-1);
            if (color == "blue" && currNum > 14) {
                return false;
            } else if (color == "red" && currNum > 12) {
                return false;
            } else if (color == "green" && currNum > 13) {
                return false;
            }
            currNum = -1;
        }

    }
    return true;
}

// bool valid(std::string &s) {
//     std::s
// }

int main() {
    std::string line;
    std::fstream file{"./input/day2a.in"};
    auto ans = 0;
    for (int i = 1; i <= NUM_ROWS; ++i) {
        std::getline(file, line);
        line += ";";
        if (validRound(line)) {
            ans += i;
        } 
    }
    std::cout << ans << "\n";
    return 0;
}
