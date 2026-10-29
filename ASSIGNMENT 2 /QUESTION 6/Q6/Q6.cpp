#include <iostream>
#include <cstdlib>
class Time {
    int h, m;
public:
    Time(int hh, int mm) : h(hh), m(mm) {}
    friend int minutesBetween(const Time& a, const Time& b);
    friend bool earlier(const Time& a, const Time& b);
};
inline int minutesBetween(const Time& a, const Time& b) {
    int x = a.h * 60 + a.m, y = b.h * 60 + b.m;
    return std::abs(x - y);
}
inline bool earlier(const Time& a, const Time& b) {
    return a.h * 60 + a.m < b.h * 60 + b.m;
}
int main() {
    Time departure(9, 45), arrival(13, 10);
    std::cout << minutesBetween(departure, arrival) << ' '
              << std::boolalpha << earlier(arrival, departure) << '\n';
    Time sameA(12, 0), sameB(12, 0), beforeNoon(11, 55), afterNoon(12, 5);
    std::cout << "same-time difference: " << minutesBetween(sameA, sameB) << '\n';
    std::cout << "11:55 earlier than 12:05: " << earlier(beforeNoon, afterNoon) << '\n';
}