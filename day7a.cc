#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>

std::vector<std::pair<std::string, int>> hands;
std::vector<std::pair<std::string, int>> sorted_hands;

std::unordered_map<char, int> card_map = {
    {'T', 10},
    {'J', 11},
    {'Q', 12},
    {'K', 13},
    {'A', 14},
};

int value(char x)
{
    return isdigit(x) ? x - '0' : card_map[x];
}

int rank(std::string &s) 
{
    std::unordered_map<char, int> mp;
    for (auto i = 0; i < s.size(); ++i)
    {
        ++mp[s[i]];
    }
    
    int cnt = 0;
    for (auto it : mp)
    {
        cnt = std::max(cnt, it.second);
    }

    if (cnt == 5) return 7;
    if (cnt == 4) return 6;
    if (cnt == 3 && mp.size() == 2) return 5;
    if (cnt == 3) return 4;
    if (cnt == 2 && mp.size() == 3) return 3;
    if (cnt == 2) return 2;
    return 1;
}

bool cmpLarger(std::pair<std::string, int> hand1, 
    std::pair<std::string, int> hand2)
{
    auto rank1 = rank(hand1.first);
    auto rank2 = rank(hand2.first);
    if (rank1 != rank2)
        return rank1 > rank2;
    for (auto i = 0; i < 5; ++i)
    {
        if (value(hand1.first[i]) < value(hand2.first[i]))
            return false;
        if (value(hand1.first[i]) > value(hand2.first[i]))
            return true;
    }
    return true;
}

// idk why I made my own sort
void place_hand(std::pair<std::string, int> hand)
{
    auto i = 0;
    while (i < sorted_hands.size()
        && cmpLarger(hand, sorted_hands[i]))
    {
        ++i;
    }
    sorted_hands.insert(sorted_hands.begin() + i, hand);
} 

constexpr int NUM_ROWS = 1000;

int main() 
{
    for (auto i = 0; i < NUM_ROWS; ++i) 
    {
        std::string hand;
        int bid;
        std::cin >> hand >> bid;
        hands.push_back({hand, bid});
    }
    
    for (auto i = 0; i < NUM_ROWS; ++i)
    {
        place_hand(hands[i]);
    }
    long long ans = 0;
    for (auto i = 0; i < NUM_ROWS; ++i)
    {
        ans += sorted_hands[i].second * (i + 1);
    }
    std::cout << ans << "\n";
    return 0;
}
