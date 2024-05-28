#include <iostream>
int main () {
    int num{};
    std::cin >> num;
    std::cout << num;
    int sndNum{};
    std::cin >> sndNum;
    std::cout << sndNum;
    return 0;
}

std::string increasingMsg = "Increasing (" + std::to_string(lengthIncreasing) + "). ";
    std::string decreasingMsg = "Decreasing (" + std::to_string(lengthDecreasing) + "). ";
    if (lengthDecreasing > lengthIncreasing) {
        return decreasingMsg + increasingMsg;
    } else {
        return increasingMsg + decreasingMsg;
    }
