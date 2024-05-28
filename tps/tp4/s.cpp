
#include <iostream>
#include <string>

bool isEqual(const std::string& a, const std::string& b) {
    if (a == b) return true;
    size_t len = a.length();
    if (len % 2 != 0 || len != b.length()) return false;
    size_t mid = len / 2;
    std::string a1 = a.substr(0, mid);
    std::string a2 = a.substr(mid);
    std::string b1 = b.substr(0, mid);
    std::string b2 = b.substr(mid);

    return  (isEqual(a1, b2) && isEqual(a2, b1)) || (isEqual(a1, b1) && isEqual(a2, b2));
}

int main() {
    std::string a, b;
    std::getline(std::cin, a);
    std::getline(std::cin, b);

    if (isEqual(a, b)) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
    return 0;
}
