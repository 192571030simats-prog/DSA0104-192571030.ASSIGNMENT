#include <array>
#include <cstddef>
#include <iostream>
#include <set>
enum class Zone { Inner = 0, Middle = 1, Outer = 2, Airport = 3 };
constexpr std::array<long long, 4> BASE_PAISE = {1000, 2000, 3000, 6000};
constexpr int PEAK_PERCENT = 20;
constexpr int WEEKEND_DISCOUNT_PERCENT = 10;
constexpr long long MIN_BALANCE_PAISE = 5000;

long long calculateFare(Zone zone, bool peak, bool weekend) {
    const auto index = static_cast<std::size_t>(zone);
    if (index >= BASE_PAISE.size()) return -1;
    long long base = BASE_PAISE[index];
    if (weekend) return base - base * WEEKEND_DISCOUNT_PERCENT / 100;
    if (peak) return base + base * PEAK_PERCENT / 100;
    return base;
}
class MonthlyPass {
    std::set<Zone> zones_;
public:
    MonthlyPass(Zone first, Zone second) : zones_{first, second} {}
    bool covers(Zone z) const { return zones_.count(z) != 0; }
};
class SmartCard {
    long long balance_;
public:
    explicit SmartCard(long long balance) : balance_(balance) {}
    long long balance() const { return balance_; }
    bool canTravel(long long f) const { return f >= 0 && balance_ - f >= MIN_BALANCE_PAISE; }
    bool deduct(long long f) {
        if (!canTravel(f)) return false;
        balance_ -= f;
        return true;
    }
};
int main() {
    std::cout << "Airport weekday off-peak paise: "
              << calculateFare(Zone::Airport, false, false) << '\n';
    std::cout << "Airport weekday peak paise: "
              << calculateFare(Zone::Airport, true, false) << '\n';
    std::cout << "Airport weekend paise: "
              << calculateFare(Zone::Airport, true, true) << '\n';
    MonthlyPass pass(Zone::Inner, Zone::Middle);
    std::cout << "Pass covers Inner: " << pass.covers(Zone::Inner) << '\n';
}
