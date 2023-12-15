#include <iostream>
#include <numeric>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

const int NUM_ROWS = 100;

bool valid(int red, int green, int blue) {
    return red <= 12 && green <= 13 && blue <= 14;
}

int validRound(std::string &s) {
    std::stringstream ss(s);
    std::string token;

    ss >> token; ss >> token;
    auto currNum = -1;

    auto blue = 0;
    auto red = 0;
    auto green = 0;

    while (ss >> token) {
        if (currNum == -1) {
            currNum = std::stoi(token);
        } else {
            auto color = token.substr(0, token.size()-1);
            if (color == "blue") {
                blue = std::max(blue, currNum);
            } else if (color == "red") {
                red = std::max(red, currNum);
            } else if (color == "green") {
                green = std::max(green, currNum);
            }
            currNum = -1;
        }

    }
    return blue*red*green;
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
        ans += validRound(line);
    }
    std::cout << ans << "\n";
    return 0;
}
